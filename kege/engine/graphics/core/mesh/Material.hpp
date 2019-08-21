/*! @author     Kenneth Anthony Esdaile
 *  @date       created on 10/24/15
 *  @copyright  Copyright (c) 2016 kae. All rights reserved.
 *  @file       Material.h
 *  @project    kege engine. */
#ifndef __KEGE_GRAPHICS_MATERIAL__
#define __KEGE_GRAPHICS_MATERIAL__
#include "shared.hpp"
#include "string.hpp"
#include "Light.hpp"
#include "../../../graphics/core/framework/Shader.hpp"
namespace kege{namespace gfx{
    
    class Material
    {
    public:
        
        void ApplyLights(const gfx::ArrayLights& lights)const;
        
        virtual const shared::Shader& GetShader()const = 0;
        virtual shared::Shader& GetShader() = 0;
        
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
}}
namespace kege{namespace shared{
    typedef mem::shared< gfx::Material > Material;
}}
#endif /* defined(__model_object__Material__) */
