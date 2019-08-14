//
//  TerrainLoader.cpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/20/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//
#include "image.hpp"
#include "Terrain.hpp"
#include "TerrainTile.hpp"
#include "Graphics.hpp"
#include "MeshComponent.hpp"
#include "TerrainSystem.hpp"
#include "TerrainLoader.hpp"
namespace kege{namespace gfx{
  
    kege::shared_image TerrainLoader::GenerateTangentmap()
    {
        TerrainSystem* sys = _map->GetSystem();
        const cg::uint tilesize = sys->GetTileSize();
        const cg::uint length = 1 + tilesize;
        double tx,tz,r;
        cg::vec3 tangent;
        cg::vec3 vert_egde[2];
        cg::vec2 uv_egde[2];
        cg::vec3 vp[4];
        cg::vec2 vt[4];
        int x1,z1, index[4];
        
        const unsigned int buffer_size = length * length;
        const double u = 1.0 / (float) length;
        
        cg::vec3* tangents = new cg::vec3[buffer_size];
        memset(tangents, 0x0, sizeof(cg::vec3)*buffer_size);
        
        for (int x, z=0; z<tilesize; z++)
        {
            z1 = (z+1);
            tz = (double) z / (double) tilesize;
            for (x=0; x<tilesize; x++)
            {
                x1 = (x+1);
                tx = (double) x / (double) tilesize;
                /* v0------->v1
                 *  ^  1   / |
                 *  |    /   |
                 *  |  /  2  v
                 * v2<-------v3
                 *
                 <---- vertices of the quad ---->
                 */
                vp[0] = _map->CalculatePosition(x , z);
                vp[1] = _map->CalculatePosition(x1, z);
                vp[2] = _map->CalculatePosition(x ,z1);
                vp[3] = _map->CalculatePosition(x1,z1);
                /*
                 <---- texture coord of the quad ---->
                 */
                vt[0] = cg::vec2(tx  ,   tz);
                vt[1] = cg::vec2(tx+u,   tz);
                vt[2] = cg::vec2(tx  , tz+u);
                vt[3] = cg::vec2(tx+u, tz+u);
                /*
                 <---- indices of each quad ---->
                 */
                index[0] = x + z * tilesize;
                index[1] = index[0] + 1;
                index[2] = index[0] + tilesize;
                index[3] = index[2] + 1;
                /*
                 <---- compute the tangent of first triangle in the quad ---->
                 */
                vert_egde[0] = vp[1] - vp[0];
                vert_egde[1] = vp[2] - vp[0];
                uv_egde[0]   = vt[1] - vt[0];
                uv_egde[1]   = vt[2] - vt[0];
                
                r = (uv_egde[0].x * uv_egde[1].y - uv_egde[0].y * uv_egde[1].x);
                r = (r == 0.00)? 1.00: 1.0F / r;
                
                tangent = (vert_egde[0] * uv_egde[1].y - vert_egde[1] * uv_egde[0].y) * r;
                /*
                 <---- store tangent of first triangle at each index of first triangle---->
                 */
                tangents[ index[0] ] += tangent;
                tangents[ index[1] ] += tangent;
                tangents[ index[2] ] += tangent;
            }
        }
        
        unsigned int color_channel = 3;
        unsigned int image_size = tilesize * tilesize * color_channel;
        cg::ubyte* data = new cg::ubyte[image_size];
        cg::ubyte* color = data;
        
        for (int i = 0; i <buffer_size; i++)
        {
            tangent = cg::normalize3( tangents[i] );
            /*
             <---- store tangent as image color data ---->
             @ since tangent = (tangent + 1.0) * 0.5 to get rid of negative sign
             so we can store in rgb color channel of image, when using tangent
             texture in shader you must convert it back by doing
             tangent = texture(tangent_texture, uv).rgb * 2 -1.
             */
            tangent = (tangent + 1.0) * 0.5;
            tangent = tangent * 255;
            
            color[0] = tangent.x;
            color[1] = tangent.y;
            color[2] = tangent.z;
            color += color_channel;
        }
        
        return kege::shared_image( new kege::image<cg::ubyte>(3, 24, tilesize, tilesize, gfx::GFX::UNSIGNED_BYTE, data) );
    }
    
    kege::shared_image TerrainLoader::GenerateNormalmap()
    {
        TerrainSystem* sys = _map->GetSystem();
        const cg::uint channels = 3;
        const cg::uint tilesize = sys->GetTileSize();
        const cg::uint pixel_row = tilesize * channels;
        const cg::uint image_size = tilesize * pixel_row;
        cg::ubyte * data = new cg::ubyte[image_size];
        
        cg::uint x,z,i;
        cg::vec3 normal;
        
        for (z=0; z<tilesize; z++)
        {
            for (x=0; x<tilesize; x++)
            {
                i = (x * channels) + z * pixel_row;
                
                normal = _map->CalculateNormal(_x+x, _z+z);
                data[i++] = normal.x * 255;
                data[i++] = normal.y * 255;
                data[i++] = normal.z * 255;
            }
        }
        return kege::shared_image( new kege::image<cg::ubyte>(3, 24, tilesize, tilesize, gfx::GFX::UNSIGNED_BYTE, data) );
    }
    
    gfx::SharedMesh TerrainLoader::GenerateMesh()
    {
        TerrainSystem* sys = _map->GetSystem();
        
        cg::uint tilesize = 1 + sys->GetTileSize();
        cg::uint size = tilesize * tilesize;
        cg::uint i,mx,mz;
        
        gfx::Mesh* mesh = new gfx::Mesh;
        mesh->GetVertexBuffer().setbuffer(size * 3, 3, size);
        mesh->GetVertexBuffer().GetVertexLayout().AddElem(gfx::VERTEX_POSITION, 3, 0);
        cg::point3* vp = mesh->GetVertexBuffer().GetBuffer<cg::point3>();
        
        int row;
        int isize = sys->GetTileSize() * sys->GetTileSize() * 6;
        gfx::IndexBuffer * indices = &mesh->GetIndexBuffer();
        indices->setsize(isize);
        indices->setcount(0);
        
        for (mz=0; mz<tilesize; mz++)
        {
            for (mx=0; mx<tilesize; mx++)
            {
                i = tilesize * mz + mx;
                vp[i].x = mx;
                vp[i].y = _map->GetHeight(_x+mx, _z+mz);
                vp[i].z = mz;
            }
        }
        
        for (int z = 0; z < sys->GetTileSize(); z++)
        {
            row = (tilesize) * z;
            for (int x = 0; x < sys->GetTileSize(); x++)
            {
                int a = x + row;
                int b = a + 1;
                int c = a + tilesize;
                int d = c + 1;
                indices->add3(a,c,d);
                indices->add3(d,b,a);
            }
        }
        return gfx::SharedMesh( mesh );
    }
    
    gfx::SharedTexture TerrainLoader::GetTangentTexture()
    {
        gfx::Texture2D* tang = gfx::Graphics::CreateTexture2D();
        tang->SetTextureInfo
        (
         TextureInfo2D
         (   GenerateTangentmap()
          ,  gfx::LINEAR_FILTER
          ,  gfx::LINEAR_FILTER
          ,  gfx::REPEAT
          ,  gfx::REPEAT
          ,  true  )
         );
        return gfx::SharedTexture( tang );
    }
    
    gfx::SharedTexture TerrainLoader::GetNormalTexture()
    {
        gfx::Texture2D* norm = gfx::Graphics::CreateTexture2D();
        norm->SetTextureInfo
        (
         TextureInfo2D
         (   GenerateNormalmap()
          ,  gfx::LINEAR_FILTER
          ,  gfx::LINEAR_FILTER
          ,  gfx::CLAMP_TO_EDGE
          ,  gfx::CLAMP_TO_EDGE
          ,  true  )
         );
        return gfx::SharedTexture( norm );
    }
    
    gfx::SharedMaterial TerrainLoader::GetMaterial()
    {
        SharedMaterialTexture textr = new TerrainTextures( GetNormalTexture(), nullptr);// GetTangentTexture() );
        return gfx::SharedMaterial( new gfx::TerrainMaterial(nullptr, textr) );
    }
    
    gfx::MeshComponent* TerrainLoader::GetMeshComponent()
    {
        return new gfx::MeshComponent(GenerateMesh(), GetMaterial());
    }
    
    void TerrainLoader::Execute()
    {
        _tile->Attach( GetMeshComponent() );
        _tile->SetLoaded(true);
    }
}}
