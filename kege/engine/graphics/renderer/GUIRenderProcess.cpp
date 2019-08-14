/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIRenderProcess.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "GUI.hpp"
#include "Graphics.hpp"
#include "RenderingSystem.hpp"
#include "GUIRenderProcess.hpp"
namespace kege{namespace gfx{

    void GUIRenderProcess::Render( kege::SceneFrame& frame )
    {
        cg::GUI* gui = (cg::GUI*) renderer->GetScene()->GetSystem("GUI");
        if (gui == nullptr) return;
        
        gfx::Graphics::EnableCullingCW();
        gfx::Graphics::EnableDepthTest();
        gfx::Graphics::EnableBlending();
        gfx::Graphics::AlphaBlending();
        gui->Render();
        gfx::Graphics::DisableBlending();
    }
    void GUIRenderProcess::UnInit()
    {
    }
    bool GUIRenderProcess::Init()
    {
        return true;
    }
}}
