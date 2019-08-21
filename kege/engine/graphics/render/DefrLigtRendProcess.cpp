/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       DefrLigtRendProcess.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "RenderingSystem.hpp"
#include "DefrLigtRendProcess.hpp"
namespace kege{namespace gfx{
    
    DefrLigtRendProcess::DefrLigtRendProcess( int x, int y, int w, int h )
    :   height( h )
    ,   width( w )
    ,   x( x )
    ,   y( y )
    {}
    
    void DefrLigtRendProcess::Render( gfx::RenderingSystem* renderer )
    {
        if ( fbo == nullptr ) return;
        
        fbo->Bind();
        fbo->ViewPort( x, y, width, height );
        fbo->ClearColor(0.8, 0.8, 0.8, 1.0);
        fbo->Clear();
        {
            Draw( renderer );
        }
        fbo->Unbind();
    }
    
    void DefrLigtRendProcess::Draw( gfx::RenderingSystem* renderer )
    {
        shared::Shader shader = renderer->GetShader("DefrLigtShader");
        shader->Enable();
        //shader->SetUBO("LIGHTS", cg::uint size, const void *data)
        renderer->DrawQuad();
        shader->Disable();
    }
    
    void DefrLigtRendProcess::UnInit( gfx::RenderingSystem* renderer )
    {
        fbo = nullptr;
    }
    bool DefrLigtRendProcess::Init( gfx::RenderingSystem* renderer )
    {
        if ( renderer != nullptr)
        {
            if (renderer->GetFramebuffer( "ColorFrameBuffer" ) == nullptr)
            {
                core::FBOLayout layout(1);
                fbo = gfx::Graphics::CreateFramebuffer();
                layout.AddRenderTexture2D(0, core::COLOR_COMPONENT, core::RGB16, 3, NULL, true);//position
                fbo->Create( width, height, layout );
                
                renderer->AddFramebuffer( "ColorFrameBuffer", fbo );
            };
            return true;
        }
        return false;
    }
}}
