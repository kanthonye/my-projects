/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/10/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       RenderEffect.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "Graphics.hpp"
#include "RenderEffect.hpp"
#include "RenderingSystem.hpp"
namespace kege{namespace gfx{
    
    RenderEffect::RenderEffect( int x, int y, int w, int h, const ds::string& read, const ds::string& write, const ds::string& shader )
    :   fbo_write( write )
    ,   fbo_read( read )
    ,   shader_name( shader )
    ,   height( h )
    ,   width( w )
    ,   x( x )
    ,   y( y )
    {}
    void RenderEffect::Render( kege::SceneFrame& frame )
    {
        SharedFramebuffer write = renderer->GetFramebuffer( fbo_write );
        SharedFramebuffer read = renderer->GetFramebuffer( fbo_read );
        gfx::SharedShader shader = renderer->GetShader( shader_name );
        if (read == nullptr || write == nullptr || shader == nullptr)
        {
            return;
        }
        write->Bind();
        read->BindTextureColorComponents();
        {
            shader->Enable();
            Draw( frame );
            shader->Disable();
        }
        read->UnbindTextureColorComponents();
        write->Unbind();
    }
    void RenderEffect::Draw( kege::SceneFrame& frame )
    {
        renderer->DrawQuad();
    }
    void RenderEffect::UnInit()
    {}
    bool RenderEffect::Init()
    {
        return true;
    }
}}
