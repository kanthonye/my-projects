//
//  TerrainMaterial.hpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/21/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef TerrainMaterial_hpp
#define TerrainMaterial_hpp
#include "Light.hpp"
#include "Material.hpp"
#include "TerrainTextures.hpp"
namespace kege{namespace gfx{
    
    /**
     *  This type of renderer is for rendering TerrainTile
     */
    class TerrainMaterial : public gfx::Material
    {
    public:
        
        virtual void SetProperty(const SharedMaterialProperty& property){_property = property;}
        virtual void SetTexture(const SharedMaterialTexture& texture){_texture = texture;}
        virtual SharedMaterialProperty GetProperty(){return _property;}
        virtual SharedMaterialTexture GetTexture(){return _texture;}
        
        const gfx::SharedShader& GetShader()const;
        gfx::SharedShader& GetShader();
        
        virtual void SetLightCount(int count) const;
        virtual void ApplyModelMatrix(const cg::mat44& transform) const;
        virtual bool Init();
        virtual void Unbind()const;
        virtual void Bind()const;
        
        TerrainMaterial
        (   SharedMaterialProperty _mtl_property
         ,  SharedMaterialTexture _mtl_texture  );
        
        TerrainMaterial(void);
        
    protected:
        
        static SharedShader _shader;
        static SharedUniform _unif_light_count;
        static SharedUniform _unif_matrix;
        static SharedUniform _unif_ambi;
        static SharedUniform _unif_diff;
        static SharedUniform _unif_spec;
        static SharedUniform _unif_emis;
        static SharedUniform _unif_dens;
        static SharedUniform _unif_alfa;
        static SharedUniform _unif_shin;
        static SharedUniform _unif_norm;
        static SharedUniform _unif_tang;
        
        
        SharedMaterialProperty _property;
        SharedMaterialTexture _texture;
    };
}}
#endif /* TerrainRenderer_hpp */
