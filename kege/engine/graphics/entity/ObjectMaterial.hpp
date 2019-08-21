/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/23/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ObjectMaterial.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef ObjectMaterial_hpp
#define ObjectMaterial_hpp
#include "../../graphics/core/mesh/ADSEffect.hpp"
#include "../../graphics/core/mesh/Material.hpp"
namespace kege{namespace gfx{
    
    class ObjectMaterial : public gfx::Material
    {
    public:
        
        void SetProperty(const shared::ADSEffect& property);
        shared::ADSEffect GetProperty();
        
        const shared::Shader& GetShader()const;
        shared::Shader& GetShader();
        
        virtual void SetLightCount(int count) const;
        virtual void ApplyModelMatrix(const cg::mat44& transform) const;
        virtual bool Init();
        virtual void Unbind()const;
        virtual void Bind()const;
        
        ObjectMaterial( shared::ADSEffect _mtl_property );
        ObjectMaterial(const gfx::ObjectMaterial& material);
        ObjectMaterial(void);
        
    protected:
        
        static shared::Shader _shader;
        shared::ADSEffect _property;
    };
}}
#endif /* EntityMaterial_hpp */
