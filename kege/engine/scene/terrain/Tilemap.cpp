/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/29/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Tilemap.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#include "VFS.hpp"
#include "Terrain.hpp"
#include "Tilemap.hpp"
#include "TerrainSystem.hpp"
#include "TerrainMaterial.hpp"
#include "MeshComponent.hpp"
namespace kege{namespace gfx{
    
    cg::vec3 Tilemap::GetPosition(int x, int z)const
    {
        return cg::vec3(x, GetHeight(x,z), z);
    }
    
    cg::vec2 Tilemap::GetTexcoord(int x, int z)const
    {
        return cg::vec2(float(x/terrain_system->tile_size), float(z/terrain_system->tile_size));
    }

    cg::vec3 Tilemap::GetTangent(int x, int z)const
    {
        cg::vec3 tangent(0.0);
        cg::vec3 pc,norm[4];
        cg::vec2 tc,egde[4];
        float r;
        //       t
        //       |
        //  l----c----r
        //       |
        //       b
        pc = GetPosition(  x, z );
        norm[0] = GetPosition(x-1, z );
        norm[1] = GetPosition(x+1, z );
        norm[2] = GetPosition(  x,z+1);
        norm[3] = GetPosition(  x,z-1);
        
        tc = GetTexcoord(  x, z );
        egde[0] = GetTexcoord(x-1, z );
        egde[1] = GetTexcoord(x+1, z );
        egde[2] = GetTexcoord(  x,z+1);
        egde[3] = GetTexcoord(  x,z-1);
        
        norm[0] = norm[0] - pc;
        norm[1] = norm[1] - pc;
        norm[2] = norm[2] - pc;
        norm[3] = norm[3] - pc;
        
        egde[0] = egde[0] - tc;
        egde[1] = egde[1] - tc;
        egde[2] = egde[2] - tc;
        egde[3] = egde[3] - tc;
        
        
        r = (egde[0].x * egde[1].y - egde[0].y * egde[1].x);
        r = (r == 0.00)? 1.00: 1.0F / r;
        tangent = (norm[0] * egde[1].y - norm[1] * egde[0].y) * r;
        
        r = (egde[1].x * egde[2].y - egde[1].y * egde[2].x);
        r = (r == 0.00)? 1.00: 1.0F / r;
        tangent += (norm[1] * egde[2].y - norm[2] * egde[1].y) * r;
        
        r = (egde[2].x * egde[3].y - egde[2].y * egde[3].x);
        r = (r == 0.00)? 1.00: 1.0F / r;
        tangent += (norm[2] * egde[3].y - norm[3] * egde[2].y) * r;
        
        r = (egde[3].x * egde[0].y - egde[3].y * egde[0].x);
        r = (r == 0.00)? 1.00: 1.0F / r;
        tangent += (norm[3] * egde[0].y - norm[0] * egde[3].y) * r;
        
        return cg::normalize3( tangent );
    }
    
    cg::vec3 Tilemap::GetNormal(int x, int z)const
    {
        cg::vec3 normal;
        double h[8];
        //  0----1----2
        //  |    |    |
        //  3----h----4
        //  |    |    |
        //  5----6----7
        h[0] = GetHeight(x-1, z-1);
        h[1] = GetHeight(  x, z-1);
        h[2] = GetHeight(x+1, z-1);
        
        h[3] = GetHeight(x-1, z);
        h[5] = GetHeight(  x, z);
        h[4] = GetHeight(x+1, z);
        
        h[5] = GetHeight(x-1, z+1);
        h[6] = GetHeight(  x, z+1);
        h[7] = GetHeight(x+1, z+1);
        
        // Compute dx using Sobel:
        //  -1[0] 0 1[2]
        //  -2[3] 0 2[4]
        //  -1[5] 0 1[7]
        normal.x = (h[2] + 2.0*h[4] + h[7]) - (h[0] + 2.0*h[3] + h[5]);
        
        // Compute dy using Sobel:
        //  -1[0] -2[1] -1[2]
        //    0     0     0
        //   1[5]  2[6]  1[7]
        // @note I invert y so that i dont have to do it in shader
        normal.y = (h[5] + 2.0*h[6] + h[7]) - (h[0] + 2.0*h[1] + h[2]);
        
        normal.z = 1.0 / terrain_system->normmap_strength;
        normal = cg::normalize3(normal) * 0.5 + 0.5;
        return normal;
    }

    double Tilemap::GetHeight(int x, int z)const
    {
        if ( file == nullptr) return 0.0;
        int value = 0;
        
        cg::uint i = (width * z) + (x);
        fseek(file, i+18, SEEK_SET);
        fread(&value, 1, 1, file);
        
        return double(value) / 255.0;
    }
    
    void Tilemap::Upload(int x, int z)
    {
        int tx = x * terrain_system->tile_size;
        int tz = z * terrain_system->tile_size;
        cg::uint mx,mz,tilesize = 1 + terrain_system->tile_size;
        cg::uint i, size = tilesize * tilesize;
        double h;
        gfx::Mesh* mesh = new gfx::Mesh;
        mesh->GetVertexBuffer().setbuffer(size * 3, 3, size);
        mesh->GetVertexBuffer().GetVertexLayout().AddElem(gfx::VERTEX_POSITION, 3, 0);
        cg::point3* vp = mesh->GetVertexBuffer().GetBuffer<cg::point3>();
        for (mz=0; mz<tilesize; mz++)
        {
            for (mx=0; mx<tilesize; mx++)
            {
                h = GetHeight(tx+mx, tz+mz);
                i = tilesize * mz + mx;
                
                vp[i].x = mx;
                vp[i].y = cg::lerp(-50.0, 50.0, h);
                vp[i].z = mz;
            }
        }
        
        int isize = terrain_system->tile_size * terrain_system->tile_size * 6;
        gfx::IndexBuffer * indices = &mesh->GetIndexBuffer();
        indices->setsize(isize);
        indices->setcount(0);
        for (int z = 0; z < terrain_system->tile_size; z++)
        {
            float row = (tilesize) * z;
            for (int x = 0; x < terrain_system->tile_size; x++)
            {
                int a = x + row;
                int b = a + 1;
                int c = a + tilesize;
                int d = c + 1;
                indices->add3(a,c,d);
                indices->add3(d,b,a);
            }
        }
        
        Entity* tile = new Entity();
        gfx::SharedMesh shared_mesh( mesh );
        gfx::SharedMaterial shared_material( new gfx::TerrainMaterial );
        tile->Attach( new gfx::MeshComponent(shared_mesh, shared_material ) );
        tile->GetLocal().translation.x = (tcoord.x * terrain_system->columns + x) * terrain_system->tile_size;
        tile->GetLocal().translation.z = (tcoord.y * terrain_system->columns + z) * terrain_system->tile_size;
        tile->SetLoaded( true );
        
        terrain_system->terrain->AddChild( tile );
        tiles.set(x, z, tile);
        count++;
    }
    
    void Tilemap::Unload(int x, int z)
    {
        gfx::Gameobject* terrain = tiles.at(x, z);
        if (terrain == nullptr) return;
        terrain->SetActive( false );
        tiles.set(x, z, nullptr);
        count--;
    }
    
    bool Tilemap::Empty() const
    {
        return count <= 0;
    }
    
    Tilemap::Tilemap(int x, int z, TerrainSystem* sys)
    :   terrain_system(sys)
    ,   next(nullptr)
    ,   prev(nullptr)
    ,   file(nullptr)
    ,   bitsperpixel(8)
    ,   count(0)
    ,   tcoord(x,z)
    ,   width(0)
    ,   height(0)
    {
        ds::string name = ds::string::strprint("~/terrain/map(%i,%i).tga",x,z);
        ds::string filename = kege::VFS::GetInstance().GetFilename(name);
        file = fopen(filename.c_str(), "r");
        tiles.resize(terrain_system->columns, terrain_system->columns);
        int capacity = terrain_system->columns * terrain_system->columns;
        for (int i=0; i<capacity; i++)
        {
            tiles[i] = nullptr;
        }
        
        int skipover = 0;
        
        if (file != nullptr)
        {
            /* Display the header fields */
            fgetc(file);
            fgetc(file);
            fgetc(file);
            fread(&skipover,2,1,file);
            fread(&skipover,2,1,file);
            fgetc(file);
            fread(&skipover,2,1,file);
            fread(&skipover,2,1,file);
            fread(&width,2,1,file);
            fread(&height,2,1,file);
            bitsperpixel = fgetc(file);
            fgetc(file);
        }
    }
    
    Tilemap::~ Tilemap()
    {
        if (file != nullptr)
        {
            fclose( file );
            file = nullptr;
        }
    }
}}

