/*!
 *  @author     Kenneth Anthony Esdaile
 *  @date       created on 4/23/19
 *  @copyright  Copyright (c) 2014 kae. All rights reserved.
 *  @file       RenderingSystem.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef RenderingSystem_hpp
#define RenderingSystem_hpp
#include "Scene.hpp"
#include "System.hpp"
#include "Mesh.hpp"
#include "Framebuffer.hpp"
#include "DebugRenderer.hpp"
#include "RenderProcess.hpp"
#include "RenderEffect.hpp"
namespace kege{namespace gfx{
   
    /**
     The @b RenderingSystem is a SubSystem that is responsible for rendering the
     current scene. @b RenderingSystem is of the group @b GRAPHICS_UPDATE, thus it
     is the @b SystemGraphics responsibility to update it.
     */
    class RenderingSystem : public kege::SubSystem
    {
    public:
        
        const gfx::ArrayLights& GetLights(const cg::vec3& min, const cg::vec3& max);
        
        void SetCamera(const gfx::Camera& camera)const;
        
        void SetBackGroundColor(const cg::vec4& value); // ?!!!: TODO
        void SetGamma(float value); // ?!!!: TODO
        float GetGamma() const; // ?!!!: TODO
        
        void Update(double time_delta);
        void Render();
        void UnInit();
        bool Init();
        
        gfx::Window* GetWindow();
        
        
        void AddRenderEffect( RenderEffect* effect );
        
        gfx::SharedFramebuffer AddFramebuffer( const ds::string& name, gfx::SharedFramebuffer& fbo );
        gfx::SharedFramebuffer GetFramebuffer( const ds::string& name );
        void BindFramebufferTexture( const ds::string& name, int index );
        void DisableFramebuffer( const ds::string& name );
        void EnableFramebuffer( const ds::string& name );
        
        void AddRenderProcess( gfx::RenderProcess* process );
        gfx::SharedShader GetShader( const ds::string& name );
        void DrawQuad();
        
        ~ RenderingSystem();
        RenderingSystem();
        
    private:
        
        std::unordered_map< unsigned long, gfx::SharedFramebuffer > framebuffers;
        std::unordered_map< unsigned long, gfx::SharedShader > shaders;
        ds::array< gfx::RenderProcess* > processes;
        
        gfx::LightPartition partition;
        gfx::SharedShader shader;
        kege::SceneFrame frame;
        
        kege::shared<gfx::Window> _window;
        gfx::SharedVAO vao;
        float gamma;
    };
}}
#endif /* RendereringSystem_hpp */
