/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/26/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       TerrainTextures.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "Graphics.hpp"
#include "TerrainTextures.hpp"
namespace kege{namespace gfx{
    
    void TerrainTextures::Unbind() const
    {
        if (normmap != nullptr)
        {
            normmap->SetBindingPoint(0);
            normmap->Unbind();
        }
        if (tangmap != nullptr)
        {
            tangmap->SetBindingPoint(1);
            tangmap->Unbind();
        }
    }
    
    void TerrainTextures::Bind() const
    {
        if (normmap != nullptr)
        {
            normmap->SetBindingPoint(0);
            normmap->Bind();
        }
        if (tangmap != nullptr)
        {
            tangmap->SetBindingPoint(1);
            tangmap->Bind();
        }
    }
    
    void TerrainTextures::UnInit()
    {
        if (normmap != nullptr)
        {
            normmap->UnCreate();
        }
        if (tangmap != nullptr)
        {
            tangmap->UnCreate();
        }
    }
    
    void TerrainTextures::Init()
    {
        if (normmap != nullptr)
        {
            normmap->Create();
        }
        if (tangmap != nullptr)
        {
            tangmap->Create();
        }
    }
    
    TerrainTextures::TerrainTextures(const gfx::SharedTexture& normmap, const gfx::SharedTexture& tangmap)
    :   normmap(normmap)
    ,   tangmap(tangmap)
    {
    }
    
    TerrainTextures::~ TerrainTextures()
    {
        if (normmap != nullptr)
        {
            normmap->UnCreate();
            normmap = nullptr;
        }
        if (tangmap != nullptr)
        {
            tangmap->UnCreate();
            tangmap = nullptr;
        }
    }
    
    TerrainTextures::TerrainTextures()
    {
        kege::image8i image = kege::open_image("soil_colr.tga");
        if( !image.empty() )
        {
            gfx::Texture2D* txtr2D = gfx::Graphics::CreateTexture2D();
            txtr2D->Create(image, true, gfx::REPEAT, gfx::LINEAR_FILTER);
            normmap = txtr2D;
        }
    }
}}
