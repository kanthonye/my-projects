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

    void ForwardRenderProcess::Render( gfx::RenderingSystem* renderer )
    {
        gfx::Graphics::EnableCullingCW();
        gfx::Graphics::EnableDepthTest();
        
        RenderSubmissionMap renderables = renderer->GetRenderables();
        RenderSubmissions::iterator obj;
        RenderSubmissionMap::iterator i;
        RenderEntry* instance;
        for (i=renderables.begin(); i!=renderables.end(); i++)
        {
            obj = i->second.begin();
            while ( obj != nullptr )
            {
                instance = &obj.element();
                instance->mesh->Bind();
                instance->mesh->GetDrawMaterial()->BindMaterial();
                instance->mesh->Draw( instance->matrix );
                instance->mesh->Unbind();
                obj++;
            }
        }
    }
    void ForwardRenderProcess::UnInit( gfx::RenderingSystem* renderer )
    {
    }
    bool ForwardRenderProcess::Init( gfx::RenderingSystem* renderer )
    {
        return true;
    }

}}
