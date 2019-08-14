/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/26/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       TerrainTextures.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef TerrainTextures_hpp
#define TerrainTextures_hpp
#include "MaterialTexture.hpp"
namespace kege{namespace gfx{
    
    class TerrainTextures : public gfx::MaterialTexture
    {
    public:
        
        void Unbind() const override;
        void Bind() const override;
        void UnInit() override;
        void Init() override;
        
        TerrainTextures(const gfx::SharedTexture& normmap, const gfx::SharedTexture& tangmap);
        ~ TerrainTextures();
        TerrainTextures();
        
        gfx::SharedTexture normmap;
        gfx::SharedTexture tangmap;
    };
}}
#endif /* TerrainTextures_hpp */
