//
//  Mesh.cpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 5/24/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "../../../graphics/core/mesh/Mesh.hpp"
#include "../../../graphics/core/Graphics.hpp"
namespace kege{namespace gfx{
    
    void gfx::Mesh::SetMesh( const shared::Geometry& geomtry, const shared::DrawElement& draw_element )
    {
        _geomtry = geomtry;
        _draw_element = draw_element;
    }

    void Mesh::DrawInstanced( cg::uint instances )const
    {
        if ( _geomtry == nullptr ) return;
        _geomtry->DrawInstanced( _draw_element, instances );
    }
    
    void Mesh::Draw( const cg::mat44& transform )const
    {
        if ( _geomtry == nullptr ) return;
        _geomtry->Draw( _draw_element, transform );
    }
    
    const shared::DrawElement& Mesh::GetDrawMaterial()const
    {
        return _draw_element;
    }
    const shared::Geometry& Mesh::GetGeomtry()const
    {
        return _geomtry;
    }

    shared::DrawElement& Mesh::GetDrawMaterial()
    {
        return _draw_element;
    }
    shared::Geometry& Mesh::GetGeomtry()
    {
        return _geomtry;
    }

    bool Mesh::IsBinded()const
    {
        return _isbind;
    }
    
    void Mesh::Unbind() const
    {
        if ( _geomtry == nullptr ) return;
        _geomtry->Unbind();
    }
    void Mesh::Bind() const
    {
        if ( _geomtry == nullptr ) return;
        _geomtry->Bind();
    }
    
    void Mesh::UnInit()
    {
        _draw_element = nullptr;
        _geomtry = nullptr;
        _init = false;
    }
    
    bool Mesh::Init()
    {
        if ( _init ) return true;
        if ( !_geomtry->Init() )
        {
            return false;
        };
        if ( !_draw_element->Init() )
        {
            return false;
        };
        _init = true;
        return _init;
    }
    
    void Mesh::Destory()
    {
        UnInit();
        _draw_element = nullptr;
    }

    Mesh::Mesh( const shared::Geometry& geomtry, const shared::DrawElement& draw_element )
    :   _draw_element( draw_element )
    ,   _geomtry( geomtry )
    ,   _isbind( false )
    ,   _init( false )
    {
    }
 
    Mesh:: ~Mesh()
    {
        Destory();
    }
    
    Mesh::Mesh()
    :   _isbind( false )
    ,   _init( false )
    {}
}}
