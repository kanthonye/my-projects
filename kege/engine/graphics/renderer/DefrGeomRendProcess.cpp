/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/10/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       DeferredRenderProcess.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#include "RenderingSystem.hpp"
#include "DefrGeomRendProcess.hpp"
namespace kege{namespace gfx{
    
    DefrGeomRendProcess::DefrGeomRendProcess( int x, int y, int w, int h )
    :   height( h )
    ,   width( w )
    ,   x( x )
    ,   y( y )
    {}
    
    void DefrGeomRendProcess::Render( kege::SceneFrame& frame )
    {
        if ( fbo == nullptr ) return;
        
        fbo->Bind();
        fbo->ViewPort( x, y, width, height );
        fbo->ClearColor(0,0,0,0);
        fbo->Clear();
        {
            Draw( frame );
        }
        fbo->Unbind();
    }
    
    void DefrGeomRendProcess::Draw( kege::SceneFrame& frame )
    {
        gfx::RenderComponents& renderables = frame.renderables[ 0 ];
        for (gfx::RenderComponents::iterator obj=renderables.begin(); obj!=nullptr; obj++)
        {
            obj->Draw( renderer );
        }
    }
    
    void DefrGeomRendProcess::UnInit()
    {
        fbo = nullptr;
    }
    bool DefrGeomRendProcess::Init()
    {
        if ( renderer != nullptr)
        {
            if (renderer->GetFramebuffer( "DefrGeomFrameBuffer" ) == nullptr)
            {
                gfx::FBOLayout layout(5);
                fbo = gfx::Graphics::CreateFramebuffer();
                renderer->AddFramebuffer( "DefrGeomFrameBuffer", fbo );
                
                layout.AddRenderTexture2D(0, gfx::COLOR_COMPONENT, gfx::RGB32, 3, NULL, true);//position
                layout.AddRenderTexture2D(1, gfx::COLOR_COMPONENT, gfx::RGB16, 3, NULL, true);//normal
                layout.AddRenderTexture2D(2, gfx::COLOR_COMPONENT, gfx::RGB16, 3, NULL, true);//diffmap
                layout.AddRenderTexture2D(3, gfx::COLOR_COMPONENT, gfx::RGB16, 3, NULL, true);//matrmap
                layout.AddRenderTexture2D(4, gfx::DEPTH_COMPONENT, gfx::INT24, 1, NULL, false);//depth
                
                fbo->Create( width, height, layout );
            };
            return true;
        }
        return false;
    }
}}
