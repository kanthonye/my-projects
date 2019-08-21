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
    
    void ShadowRenderProcess::Render( gfx::RenderingSystem* renderer )
    {
        shared::Framebuffer write = renderer->GetFramebuffer( fbo_write );
        shared::Framebuffer read = renderer->GetFramebuffer( fbo_read );
        shared::Shader shader = renderer->GetShader( shader_name );
        if (read == nullptr || write == nullptr || shader == nullptr)
        {
            return;
        }
        write->Bind();
        read->BindTextureColorComponents();
        {
            Draw( renderer );
        }
        read->UnbindTextureColorComponents();
        write->Unbind();
    }
    void ShadowRenderProcess::Draw( gfx::RenderingSystem* renderer )
    {
        
    }
    void ShadowRenderProcess::UnInit( gfx::RenderingSystem* renderer )
    {}
    bool ShadowRenderProcess::Init( gfx::RenderingSystem* renderer )
    {
        return true;
    }
}}
