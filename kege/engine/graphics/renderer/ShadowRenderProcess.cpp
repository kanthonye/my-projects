/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/10/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ShadowRenderProcess.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "Graphics.hpp"
#include "RenderingSystem.hpp"
#include "ShadowRenderProcess.hpp"
namespace kege{namespace gfx{
    
    ShadowRenderProcess::ShadowRenderProcess( int x, int y, int w, int h, const ds::string& read, const ds::string& write, const ds::string& shader )
    :   RenderEffect( x, y, w, h, read, write, shader )
    {}
    
    void ShadowRenderProcess::Render( kege::SceneFrame& frame )
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
            Draw( frame );
        }
        read->UnbindTextureColorComponents();
        write->Unbind();
    }
    void ShadowRenderProcess::Draw( kege::SceneFrame& frame )
    {
        
    }
    void ShadowRenderProcess::UnInit()
    {}
    bool ShadowRenderProcess::Init()
    {
        return true;
    }
}}
