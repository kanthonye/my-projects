
//
//  Renderer.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/13/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#include "VFS.hpp"
#include "Light.hpp"
#include "Renderer.hpp"
#include "Graphics.hpp"
#include "RenderingSystem.hpp"
namespace kege{namespace gfx{
    
    
//    const gfx::ArrayLights& Renderer::GetLights(const cg::vec3& min, const cg::vec3& max)
//    {
//        return system->GetLights(min, max);
//    }
//    
//    void Renderer::Render(gfx::SceneObjects& objects, gfx::LightPartition& partition)
//    {
//        Graphics::EnableCullingCW();
//        Graphics::EnableDepthTest();
//        for (gfx::SceneObjects::iterator obj=objects.begin(); obj!=nullptr; obj++)
//        {
//            //obj->Draw( this );
//        }
//    }
    
//    void Renderer::Render(gfx::Gameobject* obj, const gfx::ArrayLights* lights)
//    {
//    }
    
    const shared<gfx::Shader>& Renderer::GetShader()const
    {
        return shader;
    }
    
    shared<gfx::Shader>& Renderer::GetShader()
    {
        return shader;
    }

    void Renderer::Unbind()const
    {
        shader->Disable();
    }
    
    void Renderer::Bind()const
    {
        shader->Enable();
    }
    
    bool Renderer::LoadShader(const ds::string& filename)
    {
        shader = Graphics::CreateShader(filename);
        if ( shader != nullptr)
        {
//            shader->Enable();
//            if ( enable_light )
//            {
//                light_count = shader->GetUniform("LightCount");
//                light_count.SetInt(4);
//            }
//            matrix = shader->GetUniform("ModelMatrix");
//            shader->Disable();
            return true;
        }
        return false;
    }
    
    void Renderer::EnablePointFrame()
    {
        gfx::Graphics::EnableBlending();
    }
    void Renderer::EnableWireFrame()
    {
        gfx::Graphics::EnableWireFrame();
    }
    void Renderer::EnableFillFrame()
    {
        gfx::Graphics::EnableFillFrame();
    }
    void Renderer::DisableCulling()
    {
        gfx::Graphics::DisableCulling();
    }
    void Renderer::EnableCullingCCW()
    {
        gfx::Graphics::EnableCullingCCW();
    }
    void Renderer::EnableCullingCW()
    {
        gfx::Graphics::EnableCullingCW();
    }
    void Renderer::DisableDepthTest()
    {
        gfx::Graphics::DisableDepthTest();
    }
    void Renderer::EnableDepthTest()
    {
        gfx::Graphics::EnableDepthTest();
    }
    void Renderer::DisableBlending()
    {
        gfx::Graphics::DisableBlending();
    }
    void Renderer::EnableBlending()
    {
        gfx::Graphics::EnableBlending();
    }
    void Renderer::AlphaBlending()
    {
        gfx::Graphics::AlphaBlending();
    }
    void Renderer::ClearScreen()
    {
        gfx::Graphics::ClearScreen();
    }
    
    void Renderer::UnInit()
    {
    }
    
    bool Renderer::Init()
    {
        return true;
    }
    
    Renderer::~ Renderer()
    {}
    
    Renderer::Renderer()
    :   enable_light(false)
    {}
}}
