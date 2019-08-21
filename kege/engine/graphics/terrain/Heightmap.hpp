/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/18/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Heightmap.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef Heightmap_hpp
#define Heightmap_hpp
#include "Mesh.hpp"
#include "array2.hpp"
#include "NodeEntity.hpp"
namespace kege{namespace gfx{
    class TerrainSystem;
    class Terrain;
    
    class Heightmap
    {
    public:
        
        cg::vec3 GetVertexTangent( int x0, int z0,  int x1, int z1,  int x2, int z2 )const;
        cg::vec3 GetVertexPosition( int x, int z )const;
        cg::vec2 GetVertexTexcoord( int x, int z )const;
        cg::vec3 GetVertexNormal( int x, int z )const;
        double   GetPixel( cg::uint x, cg::uint z )const;
        
        TerrainSystem* GetSystem();
        
        int GetSize()const;
        
        Heightmap( int x, int z, TerrainSystem* system );
        ~ Heightmap();
        
    public:
        
        ds::array2< float > _data;
        TerrainSystem* _system;
        int _x;
        int _z;
        
        friend Terrain;
    };
}}
#endif /* Heightmap_hpp */
