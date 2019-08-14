//
//  Renderer.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/13/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp
#include "UBO.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "Transform.hpp"
#include "NodeEntity.hpp"
#include "Skeleton.hpp"
#include "SceneLight.hpp"
#include "GLUniform.hpp"
#include "Shader.hpp"

namespace kege{namespace gfx{
    class RenderingSystem;
    
    class Renderer
    {
    public:
        
        virtual void SetMaterialSpecular(cg::vec4 const& spec) const{}
        virtual void SetMaterialEmission(cg::vec4 const& emis) const{}
        virtual void SetMaterialAmbient(cg::vec4 const& ambi) const{}
        virtual void SetMaterialDiffuse(cg::vec4 const& diff) const{}
        virtual void SetMaterialTransparency(bool val) const{}
        virtual void SetMaterialTxtrScale(float val) const{}
        virtual void SetMaterialShininess(float val) const{}
        virtual void SetMaterialDensity(float val) const{}
        virtual void SetMaterialAlpha(float val) const{}
        
        virtual void UnInit();
        virtual bool Init();
        
        void EnablePointFrame();
        void EnableWireFrame();
        void EnableFillFrame();
        void DisableCulling();
        void EnableCullingCCW();
        void EnableCullingCW();
        void DisableDepthTest();
        void EnableDepthTest();
        void DisableBlending();
        void EnableBlending();
        void AlphaBlending();
        void ClearScreen();
        
        bool LoadShader(const ds::string& filename);
        const shared<gfx::Shader>& GetShader()const;
        shared<gfx::Shader>& GetShader();
        
        void BlendFunc(int blendmode)const;
        
        void Unbind()const;
        void Bind()const;
        
        ~ Renderer();
        
    protected:
        
        Renderer();
        
    protected:
        
        friend gfx::RenderingSystem;
        gfx::RenderingSystem* system;
        shared<gfx::Shader> shader;
        gfx::GLUniform light_count;
        gfx::GLUniform matrix;
        bool enable_light;
    };
}}
#endif /* Renderer_hpp */
