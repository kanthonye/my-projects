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
#include "../../graphics/core/Graphics.hpp"
namespace kege{namespace gfx{
    
    /**
     *  This type of renderer is for rendering TerrainTile
     */
    class TerrainMaterial : public gfx::Material
    {
    public:
        
        void SetTangentmapTexture( const shared::Texture& texture );
        void SetNormalmapTexture( const shared::Texture& texture );
        
        const shared::Shader& GetShader()const;
        shared::Shader& GetShader();
        
//        
//        void SetUpperSkyColor( const cg::vec4& value );
//        void SetLowerSkyColor( const cg::vec4& value );
//        const cg::vec4& GetUpperSkyColors() const;
//        const cg::vec4& GetLowerSkyColors() const;
//        
//        const shared::Shader& GetShader()const;
//        shared::Shader& GetShader();
//        
//        void Unbind()const;
//        void Bind()const;
//        bool Init();
        
        virtual void Unbind()const;
        virtual void Bind()const;
        virtual bool Init();
        
        TerrainMaterial( shared::ADSEffect _mtl_property );
        
        TerrainMaterial(void);
        
    protected:
        
        static shared::Shader _shader;
        shared::ADSEffect _property;
        
        shared::Texture _mapDiff;
        shared::Texture _mapADS;
        shared::Texture _mapNorm;
        shared::Texture _mapTang;
        
        bool transparency;
        bool has_texture;
        int  blendmode;
    };
}}
#endif /* TerrainRenderer_hpp */
