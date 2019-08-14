/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/29/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Tilemap.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef Tilemap_hpp
#define Tilemap_hpp
#include "cgm.hpp"
#include "array2.hpp"
#include "Message.hpp"
#include "TerrainTile.hpp"
namespace kege{namespace gfx{
    class TerrainSystem;
    
    class Tilemap
    {
    public:
        cg::vec3 GetPosition(int x, int z)const;
        cg::vec2 GetTexcoord(int x, int z)const;
        cg::vec3 GetTangent(int x, int z)const;
        cg::vec3 GetNormal(int x, int z)const;
        double GetHeight(int x, int z)const;
        void Upload(int x, int z);
        void Unload(int x, int z);
        bool Empty() const;
        
    private:
        Tilemap(int x, int z, TerrainSystem* sys);
        ~ Tilemap();
        
    protected:
        ds::array2< gfx::Gameobject* > tiles;
        TerrainSystem* terrain_system;
        cg::int2 tcoord;
        FILE* file;
        int bitsperpixel;
        int count;
        int height;
        int width;
        
    private:
        Tilemap* next;
        Tilemap* prev;
        friend TerrainSystem;
    };
}}
#endif /* Tilemap_hpp */
