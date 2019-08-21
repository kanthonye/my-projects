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
#include "SceneLight.hpp"
namespace kege{namespace gfx{

    struct RenderEntry
    {
        RenderEntry( const shared::Mesh& mesh, const cg::mat44& matrix )
        :   mesh( mesh )
        ,   matrix( matrix )
        {}
        
        shared::Mesh mesh;
        cg::mat44 matrix;
    };
    typedef ds::dlist< gfx::RenderEntry > RenderSubmissions;
    typedef std::unordered_map< int, gfx::RenderSubmissions > RenderSubmissionMap;
    
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
        
        core::Window* GetWindow();
        
        
        void AddRenderEffect( RenderEffect* effect );
        
        shared::Framebuffer AddFramebuffer( const ds::string& name, shared::Framebuffer& fbo );
        shared::Framebuffer GetFramebuffer( const ds::string& name );
        void BindFramebufferTexture( const ds::string& name, int index );
        void DisableFramebuffer( const ds::string& name );
        void EnableFramebuffer( const ds::string& name );
        
        void AddRenderProcess( gfx::RenderProcess* process );
        shared::Shader GetShader( const ds::string& name );
        
        gfx::RenderSubmissionMap& GetRenderables();
        gfx::LightPartition& GetLights();
        
        void Submit( const shared::Mesh& mesh, const cg::mat44& matrix );
        void DrawQuad();
        
        ~ RenderingSystem();
        RenderingSystem();
        
    private:
        
        std::unordered_map< unsigned long, shared::Framebuffer > framebuffers;
        std::unordered_map< unsigned long, shared::Shader > shaders;
        ds::array< gfx::RenderProcess* > processes;
        
        
        gfx::RenderSubmissionMap renderables;
        gfx::LightPartition lights;
        
        shared::Shader shader;
        shared::Window _window;
        shared::VAO vao;
        float gamma;
    };
}}
#endif /* RendereringSystem_hpp */
