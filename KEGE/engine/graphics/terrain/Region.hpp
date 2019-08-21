/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/22/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       TerrainMap.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef TerrainMap_hpp
#define TerrainMap_hpp
#include "TerrainTile.hpp"
namespace kege{namespace gfx{
    class TerrainSystem;
    class TaskLoad;
    class Terrain;
    class Region;
    
    enum RegionType
    {
        NODE = 1,
        OBJECT = 2
    };
    
    struct RegionChild
    {
        RegionType type;
        
        union
        {
            Region *node;
            TerrainTile *tile;
        };
        RegionChild()
        :   type(RegionType::NODE)
        ,   node(nullptr)
        {
        }
    };
    
    
    class Region
    {
    public:
        
        void operator()(float x, float z, int size);
        void Submit( gfx::RenderingSystem* renderer );
        void Update(Terrain* terrain);
        Region(int x, int z, int size);
        ~ Region();
        
    private:
        
        void CreateTerrainTile(Terrain* terrain);
        bool SubDivide(Terrain* terrain);
        void UnDivide(Terrain* terrain);
        void RemoveChild(Terrain* terrain);
        void AddChild();
        Region();
        
    private:
        
        RegionChild _region;
        float _x,_z;
        int _size;
    };
}}

#endif /* TerrainMap_hpp */
