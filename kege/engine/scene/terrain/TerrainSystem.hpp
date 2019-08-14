/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/26/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       TerrainSystem.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef TerrainSystem_hpp
#define TerrainSystem_hpp
#include "cgm.hpp"
#include "Message.hpp"
#include "Terrain.hpp"
#include "SubSystem.hpp"
#include "TerrainLoader.hpp"
namespace kege{namespace gfx{
    class Region;
    class Tilemap;
    
    class TerrainSystem : public kege::SubSystem
    {
        friend TerrainTile;
        friend Tilemap;
        friend Region;
        friend gfx::Terrain;
        
        cg::int2 WorldToLocalTilecoord(int x, int z);
        
    public:
        
        void HandleMessage( const kege::Message& message ) override;
        void Update(double delta) override;
        void UnInit() override;
        bool Init() override;
        
        float GetNormmapStrength() const {return normmap_strength;}
        int GetTerrainSize() const {return terrain_size;}
        float GetResolution() const {return resolution;}
        int GetRegionSize() const {return region_size;}
        int GetMaxHeight() const {return max_height;}
        int GetMinHeight() const {return min_height;}
        int GetTileSize() const {return tile_size;}
        int GetColumns() const {return columns;}
        int GetScale() const {return scale;}
    
        TerrainSystem(int region_size, int terrain_size, int tile_size, int scale, int min_height, int max_height);
        ~TerrainSystem();
        
    private:
        
        gfx::Terrain* terrain;
        
        float normmap_strength;
        float resolution;
        int max_height;
        int min_height;
        int region_size;
        int terrain_size;
        int tile_size;
        int columns;
        int scale;
    };
}}
#endif /* TerrainSystem_hpp */
