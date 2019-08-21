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
#include "../../graphics/terrain/TerrainMaterial.hpp"
namespace kege{namespace gfx{
    
    void TerrainMaterial::SetTangentmapTexture( const shared::Texture& texture )
    {
        _mapTang = texture;
    }
    void TerrainMaterial::SetNormalmapTexture( const shared::Texture& texture )
    {
        _mapNorm = texture;
    }
    
    const shared::Shader& TerrainMaterial::GetShader()const
    {
        return _shader;
    }
    
    shared::Shader& TerrainMaterial::GetShader()
    {
        return _shader;
    }
    
    bool TerrainMaterial::Init()
    {
        if ( _shader == nullptr)
        {
            _shader = gfx::Graphics::CreateShader("~/shaders/terrain/terrain-shader.shdr");
            if ( _shader != nullptr)
            {
                _shader->Enable();
                
                _shader->SetFloat("MAX_HEIGHT",  50);
                _shader->SetFloat("MIN_HEIGHT", -50);
                _shader->SetFloat("TILE_SIZE", 32);
                _shader->SetFloat("MAP_SIZE", 1024);
                _shader->SetFloat("SCALE", 16);
                
                _shader->SetInt( "mapVertNorm", 0 );
                _shader->SetInt( "mapVertTang", 1 );
                _shader->SetInt( "mapColrDiff", 2 );
                _shader->SetInt( "mapColrADS" , 3 );
                
                _shader->Disable();
            }
            
        }
        if ( _mapNorm != nullptr)
        {
            if ( !_mapNorm->Valid() )
            {
                _mapNorm->Create();
            }
        }
        
        if ( _mapTang != nullptr)
        {
            if ( !_mapTang->Valid() )
            {
                _mapTang->Create();
            }
        }
        
        if ( _mapDiff == nullptr)
        {
            kege::image8i image = kege::open_image("soil_colr.tga");
            if( !image.empty() )
            {
                core::Texture2D* txtr2D = gfx::Graphics::CreateTexture2D();
                txtr2D->Create(image, true, core::REPEAT, core::LINEAR_FILTER);
                _mapDiff = txtr2D;
            }
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
    
        if ( _mapNorm != nullptr )
        {
            _mapNorm->SetBindingPoint( 0 );
            _mapNorm->Bind();
        }
        
        if ( _mapTang != nullptr )
        {
            _mapTang->SetBindingPoint( 1 );
            _mapTang->Bind();
        }
        
        if ( _mapDiff != nullptr )
        {
            _mapDiff->SetBindingPoint( 2 );
            _mapDiff->Bind();
        }
        
        if ( _mapDiff != nullptr )
        {
            _mapDiff->SetBindingPoint( 3 );
            _mapDiff->Bind();
        }
    }
    
    TerrainMaterial::TerrainMaterial( shared::ADSEffect property )
    :   gfx::Material( kege::ENUM::_TERRAIN_TILE )
    ,   _property(property)
    {}
    
    TerrainMaterial::TerrainMaterial(void)
    :   gfx::Material( kege::ENUM::_TERRAIN_TILE )
    {
    }
    
    shared::Shader TerrainMaterial::_shader;
}}
