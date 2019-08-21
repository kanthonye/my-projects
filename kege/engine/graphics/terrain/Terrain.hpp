//
//  Terrain.hpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/20/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef Terrain_hpp
#define Terrain_hpp
#include "Mesh.hpp"
#include "NodeEntity.hpp"
#include "array2.hpp"
#include "Heightmap.hpp"
namespace kege{namespace gfx{
    class TerrainSystem;
    class Region;
    
    class Terrain : public gfx::NodeEntity
    {
    public:
        
        void GetQuadHeigh(double quad[6], double px, double pz)const;
        cg::vec4 GetHeightmapNormal(cg::point3 const& position)const;
        cg::vec4 GetHeightmapNormal(double px, double pz)const;
        double GetHeightmapHeight(cg::point3 const& position)const;
        double GetHeightmapHeight(double px, double pz)const;
        
        virtual void Submit( gfx::RenderingSystem* renderer );
        
        /*
         initialize this object components
         */
        virtual bool Init(kege::Scene* scene);
        
        /*
         update this objects components
         */
        virtual void Update(double delta_ms);
        
        /*
         clear entities
         */
        virtual void UnInit();
        
        /*
         release scene object data */
        virtual void Destroy();
        
        
        const Heightmap& GetHeightmap()const;
        Heightmap& GetHeightmap();
        
//        cg::vec3 CalculateTangent(int x0, int z0, int x1, int z1, int x2, int z2)const;
//        cg::vec3 CalculatePosition(int x, int z)const;
//        cg::vec2 CalculateTexcoord(int x, int z)const;
//        cg::vec3 CalculateNormal(int x, int z)const;
//        double   GetHeight(int x, int z)const;
//        double   GetPixel(int x, int z)const;
        
        cg::int2 GetTerrainCoord()const;
        TerrainSystem* GetSystem();
        Region* GetRoot();
        
        
        int GetSize()const;
        /**
         * @param terrain_size is the size of the visible terrain to render
         * @param quadtree_size is the maximum size of a quadtree node
         * @param leaf_size is the minimum size of a quadtree node
         * @param scale is the size to scale the terrain by
         */
        Terrain( int x, int z, TerrainSystem* system );
        ~ Terrain();
        
    private:
        
        Heightmap _hmap;
        
        friend Region;
        
        TerrainSystem* _system;
        Region* _root;
        cg::int2 _coord;
    };
}}
#endif /* Terrain_hpp */
