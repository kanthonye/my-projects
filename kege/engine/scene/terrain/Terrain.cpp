//
//  Terrain.cpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/20/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//
#include "GenMeshGrid.hpp"
#include "Region.hpp"
#include "Terrain.hpp"
#include "TerrainSystem.hpp"
namespace kege{namespace gfx{
    
    void Terrain::GetRenderables( kege::SceneFrame& frame )
    {
        gfx::Gameobject::GetRenderables( frame );
        if (_root != nullptr)
        {
            _root->GetRenderables( frame );
        }
    }
    
    bool Terrain::Init(kege::Scene* scene)
    {
        if (_init == true) return _init;
        
        ds::string name = ds::string::strprint("~/terrain/map(%i,%i).tga", _coord.x,_coord.y);
        ds::string filename = kege::VFS::GetInstance().GetFilename(name);
        if ((_file = fopen(filename.c_str(), "r")) == nullptr)
        {
            return false;
        }
        
        fseek(_file, 12, SEEK_SET);
        fread(&_size, 2, 1, _file);
        fseek(_file, 16, SEEK_SET);
        fread(&_bpp, 1, 1, _file);
        _header = 18; // header size
        
        int width = _size -1;
        width = width / _system->tile_size;
        _root = new Region(_coord.x, _coord.y, width);
        
        SetRadius( sqrt( cg::sq(width * _system->scale * 0.5) * 2 ) );
        return gfx::Gameobject::Init(scene);
    }
    
    void Terrain::Update(double delta_ms)
    {
        gfx::Gameobject::Update(delta_ms);
        if (_root != nullptr)
        {
            _root->Update( this );
        }
    }
    
    void Terrain::UnInit()
    {
        if (_root != nullptr)
        {
            delete _root;
            _root = nullptr;
        }
        if (_file != nullptr)
        {
            fclose(_file);
            _file = nullptr;
        }
        NodeEntity::UnInit();
        RemoveChildren();
    }
    
    void Terrain::Destroy()
    {
        NodeEntity::Destroy();
        _system = nullptr;
    }

    cg::vec3 Terrain::CalculatePosition(int x, int z)const
    {
        return cg::vec3(x * _system->GetScale(), GetHeight(x,z), z * _system->GetScale());
    }
    
    cg::vec2 Terrain::CalculateTexcoord(int x, int z)const
    {
        return cg::vec2(float(x / _size), float(z / _size));
    }
    
    cg::vec3 Terrain::CalculateTangent(int x0,int z0,  int x1,int z1,  int x2,int z2)const
    {
        cg::vec3 v[2],p[3];
        cg::vec2 e[2],t[3];
        float r;
        
        // <---- positions for the triangle ---->
        p[0] = CalculatePosition(x0, z0);
        p[1] = CalculatePosition(x1, z1);
        p[2] = CalculatePosition(x2, z2);
        
        // <---- uvcoord for the triangle ---->
        t[0] = CalculateTexcoord(x0, z0);
        t[1] = CalculateTexcoord(x1, z1);
        t[2] = CalculateTexcoord(x2, z2);
        
        // <---- compute the tangent for triangle ---->
        v[0] = p[1] - p[0];
        v[1] = p[2] - p[0];
        e[0] = t[1] - t[0];
        e[1] = t[2] - t[0];
        
        r = (e[0].x * e[1].y - e[0].y * e[1].x);
        r = (r == 0.00)? 1.00: 1.0F / r;
        
        return (v[0] * e[1].y - v[1] * e[0].y) * r;
    }
    
    cg::vec3 Terrain::CalculateNormal(int x, int z)const
    {
        // surrounding pixels
        double tl = GetPixel(x-1, z-1); // top left
        double  l = GetPixel(x-1, z  ); // left
        double bl = GetPixel(x-1, z+1); // bottom left
        double  t = GetPixel(x  , z-1); // top
        double  b = GetPixel(x  , z+1); // bottom
        double tr = GetPixel(x+1, z-1); // top right
        double  r = GetPixel(x+1, z  ); // right
        double br = GetPixel(x+1, z+1); // bottom right
        
        
        /* applying sobel filter
         *
         *      |-1  0  1|
         * Gx = |-2  0  2| * A
         *      |-1  0  1|
         *
         *      |-1 -2 -1|
         * Gy = | 0  0  2| * A
         *      | 1  2  1|
         */
        const double dx = (tr + 2.0 * r + br) - (tl + 2.0 * l + bl);
        const double dy = (bl + 2.0 * b + br) - (tl + 2.0 * t + tr);
        const double dz = 1.0 / _system->GetNormmapStrength();
        
        // to get rid of the negatives mult normalize normal by a half and add a half
        return cg::normalize3( cg::vec3(dx, dy, dz) ) * 0.5 + 0.5;
    }
    
    double Terrain::GetPixel(int x, int z)const
    {
        if ( _file == nullptr) return 0.0;
        
        if (x >= _size) x %= _size;
        while (x < 0)   x += _size;
        if (z >= _size) z %= _size;
        while (z < 0)   z += _size;
        
        cg::ubyte value = 0;
        long i = _size * z + x;
        fseek(_file, i+_header, SEEK_SET);
        fread(&value, 1, 1, _file);
        
        return cg::clamp(double(value) / 255.0, 0.0, 1.0);
    }
    
    double Terrain::GetHeight(int x, int z)const
    {
        return cg::lerp( _system->GetMinHeight(), _system->GetMaxHeight(), GetPixel(x, z) );
    }
    
    cg::int2 Terrain::GetTerrainCoord()const
    {
        return _coord;
    }
    TerrainSystem* Terrain::GetSystem()
    {
        return _system;
    }
    Region* Terrain::GetRoot()
    {
        return _root;
    }
    
    int Terrain::GetSize()const
    {
        return _size;
    }
    Terrain::~ Terrain()
    {
        UnInit();
    }
    Terrain::Terrain(int x, int z, TerrainSystem* system)
    :   gfx::NodeEntity(gfx::Gameobject::TERRAIN, "Terrain")
    ,   _system(system)
    ,   _root(nullptr)
    ,   _file(nullptr)
    ,   _coord(x,z)
    ,   _header(18)
    ,   _size(0)
    ,   _bpp(1)
    {
    }
}}