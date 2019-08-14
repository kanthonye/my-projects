//
//  TerrainMaterial.cpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/21/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "Light.hpp"
#include "Graphics.hpp"
#include "Enumerator.hpp"
#include "TerrainTile.hpp"
#include "TerrainMaterial.hpp"
#include "TerrainTextures.hpp"
namespace kege{namespace gfx{
    
    const gfx::SharedShader& TerrainMaterial::GetShader()const
    {
        return _shader;
    }
    
    gfx::SharedShader& TerrainMaterial::GetShader()
    {
        return _shader;
    }
    
    void TerrainMaterial::ApplyModelMatrix(const cg::mat44& transform) const
    {
        if (_unif_matrix == nullptr) return;
        _unif_matrix->SetMat44f( transform.data );
    }
    
    void TerrainMaterial::SetLightCount(int count) const
    {
        if (_unif_light_count == nullptr) return;
        _unif_light_count->SetInt( count );
    }
    
    bool TerrainMaterial::Init()
    {
        if ( _shader == nullptr)
        {
            _shader = gfx::Graphics::CreateShader("~/shaders/terrain/terrain-shader.shdr");
            if ( _shader != nullptr)
            {
                _shader->Enable();
                
                _unif_light_count = _shader->GetUniform("LightCount");
                
                SharedUniform temp;
                temp = _shader->GetUniform("MAX_HEIGHT");
                if (temp != nullptr) temp->SetFloat(50);
                
                temp = _shader->GetUniform("MIN_HEIGHT");
                if (temp != nullptr) temp->SetFloat(-50);
                
                temp = _shader->GetUniform("TILE_SIZE");
                if (temp != nullptr) temp->SetFloat(32);
                
                temp = _shader->GetUniform("MAP_SIZE");
                if (temp != nullptr) temp->SetFloat(1024);
                
                temp = _shader->GetUniform("SCALE");
                if (temp != nullptr) temp->SetFloat(16);
                
                _unif_matrix = _shader->GetUniform("ModelMatrix");
                _unif_diff = _shader->GetUniform("Material.diffuse");
                _unif_spec = _shader->GetUniform("Material.specular");
                _unif_ambi = _shader->GetUniform("Material.ambient");
                _unif_emis = _shader->GetUniform("Material.emission");
                _unif_dens = _shader->GetUniform("Material.density");
                _unif_alfa = _shader->GetUniform("Material.alpha");
                _unif_shin = _shader->GetUniform("Material.shininess");
                
                _unif_norm = _shader->GetUniform("TerrainNormalmap");
                if (_unif_norm != nullptr)
                {
                    _unif_norm->SetInt( 0 );
                }
                _unif_tang = _shader->GetUniform("TerrainTangentmap");
                if (_unif_tang != nullptr)
                {
                    _unif_tang->SetInt( 1 );
                }
                
                _shader->Disable();
            }
        }
        if (_texture != nullptr)
        {
            _texture->Init();
        }
        return true;
    }
    
    void TerrainMaterial::Unbind()const
    {
        _shader->Disable();
    }
    
    void TerrainMaterial::Bind()const
    {
        _shader->Enable();
        
        if (_property != nullptr)
        {
            _unif_ambi->SetVec4f( _property->GetAmbient().rgba );
            _unif_diff->SetVec4f( _property->GetAmbient().rgba );
            _unif_spec->SetVec4f( _property->GetAmbient().rgba );
            _unif_emis->SetVec4f( _property->GetAmbient().rgba );
            _unif_shin->SetFloat( _property->GetShininess() );
            _unif_dens->SetFloat( _property->GetDensity() );
            _unif_alfa->SetFloat( _property->GetAlpha() );
            if ( _property->GetAlpha() < 1.0 )
            {
                Graphics::EnableBlending();
                Graphics::AlphaBlending();
            }
        }
        
        if ( _texture != nullptr )
        {
            _texture->Bind();
        }
    }
    
    TerrainMaterial::TerrainMaterial
    (   SharedMaterialProperty property
     ,  SharedMaterialTexture texture  )
    :   gfx::Material( kege::ENUM::_TERRAIN_TILE )
    ,   _property(property)
    ,   _texture(texture)
    {}
    
    TerrainMaterial::TerrainMaterial(void)
    :   gfx::Material( kege::ENUM::_TERRAIN_TILE )
    {
    }
    
    SharedShader TerrainMaterial::_shader;
    SharedUniform TerrainMaterial::_unif_light_count;
    SharedUniform TerrainMaterial::_unif_matrix;
    SharedUniform TerrainMaterial::_unif_ambi;
    SharedUniform TerrainMaterial::_unif_diff;
    SharedUniform TerrainMaterial::_unif_spec;
    SharedUniform TerrainMaterial::_unif_emis;
    SharedUniform TerrainMaterial::_unif_dens;
    SharedUniform TerrainMaterial::_unif_alfa;
    SharedUniform TerrainMaterial::_unif_shin;
    SharedUniform TerrainMaterial::_unif_norm;
    SharedUniform TerrainMaterial::_unif_tang;
}}
