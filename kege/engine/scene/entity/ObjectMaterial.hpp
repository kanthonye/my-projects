/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/23/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ObjectMaterial.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef ObjectMaterial_hpp
#define ObjectMaterial_hpp
#include "Material.hpp"
namespace kege{namespace gfx{
    
    class ObjectMaterial : public gfx::Material
    {
    public:
        
        void SetProperty(const SharedMaterialProperty& property);
        void SetTexture(const SharedMaterialTexture& texture);
        SharedMaterialProperty GetProperty();
        SharedMaterialTexture GetTexture();
        
        const SharedShader& GetShader()const;
        SharedShader& GetShader();
        
        virtual void SetLightCount(int count) const;
        virtual void ApplyModelMatrix(const cg::mat44& transform) const;
        virtual bool Init();
        virtual void Unbind()const;
        virtual void Bind()const;
        
        ObjectMaterial
        (   SharedMaterialProperty _mtl_property
         ,  SharedMaterialTexture _mtl_texture  );
        
        ObjectMaterial(const gfx::ObjectMaterial& material);
        ObjectMaterial(void);
        
    protected:
        
        static SharedShader _shader;
        SharedMaterialProperty _property;
        SharedMaterialTexture _texture;
    };
}}
#endif /* EntityMaterial_hpp */
