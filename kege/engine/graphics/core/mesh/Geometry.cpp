/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/14/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Geometry.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../../graphics/core/mesh/Geometry.hpp"
#include "../../../graphics/core/Graphics.hpp"
namespace kege{namespace gfx{

    void Geometry::DrawInstanced( const shared::DrawElement& draw, cg::uint instances )const
    {
        if ( !IsBinded() ) return;
        
        if ( _vao->GetIBO().hasRef() )
        {
            draw->DrawInstanceIndices( _vao.rawptr(), instances );
        }
        else
        {
            draw->DrawInstanceArray( _vao.rawptr(), instances );
        }
    }
    
    void Geometry::Draw( const shared::DrawElement& draw, const cg::mat44& transform )const
    {
        if ( !IsBinded() ) return;
        
        if ( _vao->GetIBO().hasRef() )
        {
            draw->DrawIndices( _vao.rawptr(), transform );
        }
        else
        {
            draw->DrawArray( _vao.rawptr(), transform );
        }
    }
    
    const shared::VertexBuffer& Geometry::GetVertexBuffer()const
    {
        return _vertex_buffer;
    }

    const shared::IndexBuffer&  Geometry::GetIndexBuffer()const
    {
        return _index_buffer;
    }
    
    shared::VertexBuffer& Geometry::GetVertexBuffer()
    {
        return _vertex_buffer;
    }

    shared::IndexBuffer&  Geometry::GetIndexBuffer()
    {
        return _index_buffer;
    }
    
    void Geometry::SetCenterPoint(const cg::point3& val)
    {
        _center = val;
    }
    
    const cg::point3& Geometry::GetCenterPoint()const
    {
        return _center;
    }
    
    void Geometry::SetMinPoint(const cg::point3& m)
    {
        _min = m;
    }
    
    const cg::point3& Geometry::GetMinPoint()const
    {
        return _min;
    }
    
    void Geometry::SetMaxPoint(const cg::point3& m)
    {
        _max = m;
    }
    
    const cg::point3& Geometry::GetMaxPoint()const
    {
        return _max;
    }
    
    void Geometry::operator = ( const Geometry& geom )
    {
        _vertex_buffer = geom._vertex_buffer;
        _index_buffer  = geom._index_buffer;
    }
    
    bool Geometry::IsBinded()const
    {
        return _isbind;
    }
    
    void Geometry::Unbind() const
    {
        if ( !_vao.hasRef() ) return;
        const_cast<bool&>( _isbind ) = true;
        _vao->Unbind();
    }
    void Geometry::Bind() const
    {
        if ( !_vao.hasRef() ) return;
        const_cast<bool&>( _isbind ) = true;
        _vao->Bind();
    }
    
    
    void Geometry::UnInit()
    {
        _vertex_buffer = nullptr;
        _index_buffer = nullptr;
        _vao = nullptr;
        
        _isbind = false;
        _init = false;
    }
    
    bool Geometry::Init()
    {
        if ( _init ) return true;
        _vao = Graphics::CreateVAO( _vertex_buffer.rawptr(), _index_buffer.rawptr() );
        _vertex_buffer = nullptr;
        _index_buffer = nullptr;
        _init = true;
        return _init;
    }
    
    Geometry::Geometry( core::VertexBuffer* vb, core::IndexBuffer* ib )
    :   _vertex_buffer( vb )
    ,   _index_buffer( ib )
    ,   _isbind( false )
    ,   _init( false )
    {}
    
    Geometry::Geometry( const Geometry& geom )
    :   _vertex_buffer( geom._vertex_buffer )
    ,   _index_buffer( geom._index_buffer )
    ,   _isbind( false )
    ,   _init( false )
    {}
    Geometry::~ Geometry()
    {
        UnInit();
    }
    Geometry::Geometry()
    :   _isbind( false )
    ,   _init( false )
    {}
}}
