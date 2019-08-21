/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/14/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       DrawElement.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#include "../../../graphics/core/Graphics.hpp"
#include "../../../graphics/core/mesh/DrawElement.hpp"
namespace kege{namespace gfx{
    
    void DrawElement::DrawInstanceIndices( const core::VAO* vao, cg::uint instances )const
    {
        vao->DrawIndicesInstanced( _draw_mode, _draw_count, nullptr, instances );
    }
    void DrawElement::DrawInstanceArray( const core::VAO* vao, cg::uint instances )const
    {
        vao->DrawArraysInstanced( _draw_mode, _starting_index, _draw_count, instances );
    }
    void DrawElement::DrawIndices( const core::VAO* vao, const cg::mat44& transform )const
    {
        _material->GetShader()->SetMat44f( "ModelMatrix", transform.data );
        vao->DrawIndices( _draw_mode, _draw_count, nullptr );
    }
    void DrawElement::DrawArray( const core::VAO* vao, const cg::mat44& transform )const
    {
        _material->GetShader()->SetMat44f( "ModelMatrix", transform.data );
        vao->DrawArrays( _draw_mode, _starting_index, _draw_count );
    }

    void DrawElement::UnbindMaterial()const
    {
        _material->Unbind();
    }
    void DrawElement::BindMaterial()const
    {
        _material->Bind();
    }
    
    void DrawElement::ApplyLights( const gfx::ArrayLights& lights )const
    {
        _material->ApplyLights( lights );
    }
    
    void DrawElement::SetMaterial(const shared::Material& material)
    {
        _material = material;
    }
    
    const shared::Material& DrawElement::GetMaterial()const
    {
        return _material;
    }
    shared::Material& DrawElement::GetMaterial()
    {
        return _material;
    }
    
    void DrawElement::SetStartingIndex( cg::uint value )
    {
        _starting_index = value;
    }
    void DrawElement::SetDrawCount( cg::uint value )
    {
        _draw_count = value;
    }
    void DrawElement::SetDrawMode( cg::uint value )
    {
        _draw_mode = gfx::Graphics::GetConstant( value );
    }
    
    cg::uint DrawElement::GetStartingIndex()const
    {
        return _starting_index;
    }
    cg::uint DrawElement::GetDrawCount()const
    {
        return _draw_count;
    }
    cg::uint DrawElement::GetDrawMode()const
    {
        return _draw_mode;
    }
    
    void DrawElement::UnInit()
    {
        _material = nullptr;
    }
    bool DrawElement::Init()
    {
        if ( !_material.hasRef() )
        {
            return false;
        }
        return _material->Init();
    }
    
    DrawElement::DrawElement( cg::uint draw_mode, cg::uint starting_index, cg::uint draw_count, const shared::Material& material )
    :   _material( material )
    ,   _starting_index( starting_index )
    ,   _draw_count( draw_count )
    ,   _draw_mode( gfx::Graphics::GetConstant( draw_mode ) )
    {}
    DrawElement::DrawElement( )
    :   _starting_index( 0 )
    ,   _draw_count( 0 )
    ,   _draw_mode( 4 )
    {}
}}


