/*!
 *  @author     Kenneth Anthony Esdaile
 *  @date       created on 4/23/19
 *  @copyright  Copyright (c) 2014 kae. All rights reserved.
 *  @file       RenderingSystem.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "Graphics.hpp"
#include "Skeleton.hpp"
#include "Camera.hpp"
#include "GameEngine.hpp"
#include "RenderingSystem.hpp"
#include "GUIRenderProcess.hpp"
#include "ForwardRenderProcess.hpp"
namespace kege{namespace gfx{
    
    const gfx::ArrayLights& RenderingSystem::GetLights(const cg::vec3& min, const cg::vec3& max)
    {
        return partition.GetLights(min, max);
    }
    
    void RenderingSystem::SetCamera(const gfx::Camera& camera)const
    {
        cg::mat44 matrices[2];
        matrices[0] = camera.GetProjection();
        matrices[1] = camera.GetViewMatrix();
        shader->SetUBO("CAMERA", sizeof(matrices), matrices);
    }
    
    void RenderingSystem::SetBackGroundColor(const cg::vec4& value)
    {
        gfx::Graphics::SetBackgroundColor( value );
    }
    
    void RenderingSystem::SetGamma(float value)
    {
        gamma = value;
    }
    float RenderingSystem::GetGamma() const
    {
        return gamma;
    }
    
    void RenderingSystem::Update(double time_delta)
    {}
    
    void RenderingSystem::Render()
    {
        kege::Scene* scene = GetScene();
        if (scene == nullptr) return;
        
        SetCamera( *scene->GetCamera() );
        scene->GetRootNode().GetRenderables( frame );
        
        for (int i=0; i<processes.size(); i++)
        {
            processes[ i ]->Render( frame );
        }

        frame.gameobjects.clear();
        frame.renderables.clear();
        frame.lights.Clear();
        partition.Clear();
    }
    
    void RenderingSystem::UnInit()
    {
        for (int i=0; i<processes.size(); i++)
            delete processes[i];
        processes.clear();
        
        if (vao != nullptr)
        {
            vao->UnCreate();
            vao = nullptr;
        }
        _init = false;
    }
    
    bool RenderingSystem::Init()
    {
        if ( _init ) return _init;
        shader = gfx::Graphics::CreateShader();
        
        vao = gfx::Graphics::CreateVAO();
        vao->Create();
        
        cg::mat44 matrices[2] = {cg::mat44(1.0), cg::mat44(1.0)};
        shader->SetUBO( "CAMERA", sizeof(matrices), matrices );
        
        for (int i=0; i<processes.size(); i++)
        {
            processes[i]->Init();
        }
        _init = true;
        return _init;
    }
    
    gfx::SharedFramebuffer RenderingSystem::AddFramebuffer( const ds::string& name, gfx::SharedFramebuffer& fbo )
    {
        framebuffers[ name.hash() ] = fbo;
        return fbo;
    }
    
    gfx::SharedFramebuffer RenderingSystem::GetFramebuffer( const ds::string& name )
    {
        std::unordered_map< unsigned long, gfx::SharedFramebuffer >::iterator m = framebuffers.find( name.hash() );
        if ( m == framebuffers.end() )
        {
            return gfx::SharedFramebuffer();
        }
        return m->second;
    }
    void RenderingSystem::BindFramebufferTexture( const ds::string& name, int index )
    {
        gfx::SharedFramebuffer fbo = GetFramebuffer( name );
        if (fbo != nullptr)
        {
            fbo->BindTextureColorComponents();
        }
    }
    void RenderingSystem::DisableFramebuffer( const ds::string& name )
    {
        gfx::SharedFramebuffer fbo = GetFramebuffer( name );
        if (fbo != nullptr)
        {
            fbo->Unbind();
        }
    }
    void RenderingSystem::EnableFramebuffer( const ds::string& name )
    {
        gfx::SharedFramebuffer fbo = GetFramebuffer( name );
        if (fbo != nullptr)
        {
            fbo->Bind();
        }
    }
    
    void RenderingSystem::AddRenderProcess( gfx::RenderProcess* process )
    {
        processes.resize( processes.size() + 1 );
        processes[ processes.size() - 1 ] = process;
        process->renderer = this;
    }
    
    gfx::SharedShader RenderingSystem::GetShader( const ds::string& name )
    {
        return nullptr;
    }
    void RenderingSystem::DrawQuad()
    {
        if (vao != nullptr)
        {
            vao->Bind();
            vao->Draw(gfx::Graphics::GetConstant(gfx::DRAW_TRIANGLES), 0, 4);
            vao->Unbind();
        }
    }
    
    RenderingSystem::~ RenderingSystem()
    {
        UnInit();
    }
    
    RenderingSystem::RenderingSystem()
    :   kege::SubSystem("RenderingSystem")
    ,   _window()
    ,   gamma(2.2)
    {
        partition.Set(0, 0, 0, 512, 32);
        AddRenderProcess( new ForwardRenderProcess );
        AddRenderProcess( new GUIRenderProcess );
    }
}}
