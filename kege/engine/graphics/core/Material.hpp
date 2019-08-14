/*! @author     Kenneth Anthony Esdaile
 *  @date       created on 10/24/15
 *  @copyright  Copyright (c) 2016 kae. All rights reserved.
 *  @file       Material.h
 *  @project    kege engine. */
#ifndef __KEGE_GRAPHICS_MATERIAL__
#define __KEGE_GRAPHICS_MATERIAL__
#include "shared.hpp"
#include "string.hpp"
#include "Shader.hpp"
#include "SceneLight.hpp"
#include "MaterialTexture.hpp"
#include "MaterialProperty.hpp"
namespace kege{namespace gfx{
    
    class Material
    {
    public:
        
        void ApplyLights(const gfx::ArrayLights& lights)const;
        
        virtual const SharedShader& GetShader()const = 0;
        virtual SharedShader& GetShader() = 0;
        
        virtual void SetProperty(const SharedMaterialProperty& property) = 0;
        virtual void SetTexture(const SharedMaterialTexture& texture) = 0;
        virtual void ApplyModelMatrix(const cg::mat44& transform) const {}
        virtual void SetLightCount(int count) const {}
        
        inline cg::uint GetType() const {return _type;}
        
        virtual void SetReflectLight(bool value);
        virtual bool ReflectLight()const;
        
        virtual void Unbind()const = 0;
        virtual void Bind()const = 0;
        virtual bool Init() = 0;
        
        virtual ~ Material(void);
        Material(cg::uint _type);
        
    protected:
        
        cg::uint _type;
        bool _reflect_light;
    };
    
    
    typedef kege::shared<gfx::Material> SharedMaterial;
}}
#endif /* defined(__model_object__Material__) */
