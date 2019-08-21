/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/18/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       TerrainLoadTask.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "image.hpp"
#include "Terrain.hpp"
#include "TerrainTile.hpp"
#include "Graphics.hpp"
#include "Model.hpp"
#include "TerrainSystem.hpp"
#include "TerrainLoader.hpp"
#include "TerrainLoadTask.hpp"
namespace kege{namespace gfx{
    
    shared::image TerrainLoadTask::GenerateTangentmap()
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
                vp[0] = _map->GetVertexPosition(x , z);
                vp[1] = _map->GetVertexPosition(x1, z);
                vp[2] = _map->GetVertexPosition(x ,z1);
                vp[3] = _map->GetVertexPosition(x1,z1);
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
        
        return shared::image( new kege::image<cg::ubyte>(3, 24, tilesize, tilesize, core::UNSIGNED_BYTE, data) );
    }
    
    shared::image TerrainLoadTask::GenerateNormalmap()
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
                
                normal = _map->GetVertexNormal(_x+x, _z+z);
                data[i++] = normal.x * 255;
                data[i++] = normal.y * 255;
                data[i++] = normal.z * 255;
            }
        }
        return shared::image( new kege::image<cg::ubyte>(3, 24, tilesize, tilesize, core::UNSIGNED_BYTE, data) );
    }
    
    shared::Geometry TerrainLoadTask::GenerateGeometry()
    {
        TerrainSystem* sys = _map->GetSystem();
        int isize = sys->GetTileSize() * sys->GetTileSize() * 6;
        cg::uint tilesize = 1 + sys->GetTileSize();
        cg::uint size = tilesize * tilesize;
        cg::uint i,mx,mz;
        
        core::VertexBuffer* vb = new core::VertexBuffer;
        core::VertexLayout* vl = &vb->GetVertexLayout();
        core::IndexBuffer*  ib = new core::IndexBuffer;
        
        vb->setbuffer( size * 3, 3, size );
        vl->AddElem( core::VERTEX_POSITION, 3, 0 );
        ib->setsize( isize );
        ib->setcount( 0 );
        
        cg::point3* vp = vb->GetBuffer<cg::point3>();
        
        int row;
        
        for (mz=0; mz<tilesize; mz++)
        {
            for (mx=0; mx<tilesize; mx++)
            {
                i = tilesize * mz + mx;
                vp[i].x = mx;
                vp[i].y = _map->GetPixel( _x+mx, _z+mz );
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
                ib->add3(a,c,d);
                ib->add3(d,b,a);
            }
        }
        return new gfx::Geometry( vb, ib );
    }
    
    shared::Texture TerrainLoadTask::GetTangentTexture()
    {
        core::Texture2D* texture = gfx::Graphics::CreateTexture2D();
        texture->SetTextureInfo( core::TextureInfo2D( GenerateTangentmap(),  core::LINEAR_FILTER,  core::LINEAR_FILTER,  core::REPEAT,  core::REPEAT,  true ) );
        return shared::Texture( texture );
    }
    
    shared::Texture TerrainLoadTask::GetNormalTexture()
    {
        core::Texture2D* texture = gfx::Graphics::CreateTexture2D();
        texture->SetTextureInfo( core::TextureInfo2D( GenerateNormalmap(),  core::LINEAR_FILTER,  core::LINEAR_FILTER,  core::REPEAT,  core::REPEAT,  true ) );
        return shared::Texture( texture );
    }
    
    shared::Material TerrainLoadTask::GetMaterial()
    {
        TerrainMaterial* material = new TerrainMaterial;
        material->SetNormalmapTexture( GetNormalTexture() );
//        material->SetTangentmapTexture( GetTangentTexture() );
        return material;
    }
    
    gfx::Model* TerrainLoadTask::GetModel()
    {
        shared::Geometry geometry = GenerateGeometry();
        shared::Mesh mesh = new gfx::Mesh( geometry, new DrawElement( core::DRAW_TRIANGLES, 0, (int) geometry->GetIndexBuffer()->size(), GetMaterial() ) );
        return new gfx::Model( mesh );
    }
    
    void TerrainLoadTask::Execute()
    {
        _tile->Attach( GetModel() );
        _tile->SetLoaded(true);
    }
}}
