/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/25/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       SkydomeMaterial.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef SkydomeMaterial_hpp
#define SkydomeMaterial_hpp
#include "enumtypes.hpp"
#include "Material.hpp"
namespace kege{namespace gfx{
    
    class SkydomeMaterial : public gfx::Material
    {
    public:
        
        void SetProperty(const SharedMaterialProperty& property){}
        void SetTexture(const SharedMaterialTexture& texture){}
        void ApplyModelMatrix(const cg::mat44& transform) const;
        
        const gfx::SharedShader& GetShader()const;
        gfx::SharedShader& GetShader();
        
        bool Init();
        void Unbind()const;
        void Bind()const;
        
        SkydomeMaterial(void);
        
        static SharedShader _shader;
        
        SharedUniform _unif_matrix;
        SharedTexture _texture;
    };
}}
#endif /* SkydomeMaterial_hpp */
