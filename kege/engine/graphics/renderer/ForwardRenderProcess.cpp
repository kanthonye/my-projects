/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ForwardRenderProcess.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "Graphics.hpp"
#include "RenderingSystem.hpp"
#include "ForwardRenderProcess.hpp"
namespace kege{namespace gfx{

    void ForwardRenderProcess::Render( kege::SceneFrame& frame )
    {
        gfx::Graphics::EnableCullingCW();
        gfx::Graphics::EnableDepthTest();
        
        std::unordered_map<int, gfx::RenderComponents>::iterator i;
        for (i=frame.renderables.begin(); i!=frame.renderables.end(); i++)
        {
            for (gfx::RenderComponents::iterator obj=i->second.begin(); obj!=nullptr; obj++)
            {
                obj->Draw( renderer );
            }
        }
    }
    void ForwardRenderProcess::UnInit()
    {
    }
    bool ForwardRenderProcess::Init()
    {
        return true;
    }

}}
