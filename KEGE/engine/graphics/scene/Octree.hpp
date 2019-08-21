/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/18/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Octree.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef World_hpp
#define World_hpp
#include "cgm.hpp"
namespace kege{namespace gfx{
    class OctreeObject;
    class Octant;
    
    class Octree
    {
    private:
        
        int  GetCoverage( OctreeObject* object );
        void UpdateOctants();
        void UpdateObjects();
        
    public:
        
        bool PartlyInside( const cg::vec3& min, const cg::vec3& max );
        bool FullyInside( const cg::vec3& min, const cg::vec3& max );
        bool Insert( OctreeObject* object );
        void Add( OctreeObject* object );
        void UpdateWorld();
        void Clear();
        
        Octree( int x, int y, int z, int w, float minsize );
        ~ Octree();
        Octree();
        
    private:
        
        std::vector< OctreeObject* >* _objects;
        Octant* _octant;
        Octree* _parent;
        int  _x, _y, _z, _w;
        float _minsize;
        bool _isleaf;
    };
    
    
    class Octant
    {
    public:
        
        Octant()
        :   upper_front_right( nullptr )
        ,   upper_front_left( nullptr )
        ,   upper_back_right( nullptr )
        ,   upper_back_left( nullptr )
        ,   lower_front_right( nullptr )
        ,   lower_front_left( nullptr )
        ,   lower_back_right( nullptr )
        ,   lower_back_left( nullptr )
        {}
        
        union
        {
            struct
            {
                Octree* upper_front_right;
                Octree* upper_front_left;
                Octree* upper_back_right;
                Octree* upper_back_left;
                Octree* lower_front_right;
                Octree* lower_front_left;
                Octree* lower_back_right;
                Octree* lower_back_left;
            };
            Octree* nodes[8];
        };
    };
    
    
    class OctreeObject
    {
    public:
        OctreeObject( const cg::vec3& min, const cg::vec3& max )
        :   min( min )
        ,   max( max )
        {}
        
        cg::vec3 min;
        cg::vec3 max;
    };
}}
#endif /* World_hpp */
