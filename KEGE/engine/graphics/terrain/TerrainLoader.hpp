/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/18/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       TerrainLoader.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef TerrainLoader_hpp
#define TerrainLoader_hpp
#include "Mesh.hpp"
#include "array2.hpp"
#include "NodeEntity.hpp"
namespace kege{namespace gfx{
    class TerrainSystem;
    
    class TerrainLoader
    {
    public:
        
        cg::vec3 CalculateTangent(int x0, int z0, int x1, int z1, int x2, int z2)const;
        cg::vec3 CalculatePosition(int x, int z)const;
        cg::vec2 CalculateTexcoord(int x, int z)const;
        cg::vec3 CalculateNormal(int x, int z)const;
        double   GetHeight(int x, int z)const;
        double   GetPixel(int x, int z)const;
        cg::int2 GetTerrainCoord()const;
        TerrainSystem* GetSystem();
        
        
        int GetSize()const;
        ~ TerrainLoader();
        TerrainLoader( int x, int z, TerrainSystem* system );
        
    public:
        
        TerrainSystem* _system;
        FILE* _file;
        int _header;
        int _size;
        int _bpp;
    };
}}
#endif /* TerrainLoader_hpp */
