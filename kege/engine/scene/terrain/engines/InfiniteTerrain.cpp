//
//  InfiniteTerrain.cpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/20/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "TerrainSystem.hpp"
#include "TerrainTextures.hpp"
#include "InfiniteTerrain.hpp"
namespace kege{namespace gfx{
    
//    class TerrainFile : public Terramap
//    {
//    public:
//
//        cg::vec2 GetVertexTexcoord(int x, int z) override;
//        cg::vec3 GetVertexPosition(int x, int z) override;
//        cg::vec3 GetVertexTangent(int x, int z) override;
//        cg::vec3 GetVertexNormal(int x, int z) override;
//        cg::vec3 GetVertexColor(int x, int z) override;
//        float GetVertexHeight(int x, int z) override;
//        gfx::SharedMesh GetTile(int x, int z) override;
//
//        virtual ~ TerrainFile(){}
//
//        TerrainFile();
//
//        int _tile_size;
//    };

//    cg::vec2 InfiniteTerrainMap::GetVertexTexcoord(int x, int z)
//    {
//        return cg::vec2(float(x/_tile_size), float(z/_tile_size));
//    }
//    
//    cg::vec3 InfiniteTerrainMap::GetVertexPosition(int x, int z)
//    {
//        return cg::vec3(x, GetVertexHeight( x,z ), z);
//    }
//    
//    cg::vec3 InfiniteTerrainMap::GetVertexTangent(int x, int z)
//    {
//        cg::vec3 tangent(0.0);
//        cg::vec3 pc,norm[4];
//        cg::vec2 tc,egde[4];
//        float r;
//        //       t
//        //       |
//        //  l----c----r
//        //       |
//        //       b
//        pc = GetVertexPosition(  x, z );
//        norm[0] = GetVertexPosition(x-1, z );
//        norm[1] = GetVertexPosition(x+1, z );
//        norm[2] = GetVertexPosition(  x,z+1);
//        norm[3] = GetVertexPosition(  x,z-1);
//        
//        tc = GetVertexTexcoord(  x, z );
//        egde[0] = GetVertexTexcoord(x-1, z );
//        egde[1] = GetVertexTexcoord(x+1, z );
//        egde[2] = GetVertexTexcoord(  x,z+1);
//        egde[3] = GetVertexTexcoord(  x,z-1);
//        
//        norm[0] = norm[0] - pc;
//        norm[1] = norm[1] - pc;
//        norm[2] = norm[2] - pc;
//        norm[3] = norm[3] - pc;
//        
//        egde[0] = egde[0] - tc;
//        egde[1] = egde[1] - tc;
//        egde[2] = egde[2] - tc;
//        egde[3] = egde[3] - tc;
//        
//        
//        r = (egde[0].x * egde[1].y - egde[0].y * egde[1].x);
//        r = (r == 0.00)? 1.00: 1.0F / r;
//        tangent = (norm[0] * egde[1].y - norm[1] * egde[0].y) * r;
//        
//        r = (egde[1].x * egde[2].y - egde[1].y * egde[2].x);
//        r = (r == 0.00)? 1.00: 1.0F / r;
//        tangent += (norm[1] * egde[2].y - norm[2] * egde[1].y) * r;
//        
//        r = (egde[2].x * egde[3].y - egde[2].y * egde[3].x);
//        r = (r == 0.00)? 1.00: 1.0F / r;
//        tangent += (norm[2] * egde[3].y - norm[3] * egde[2].y) * r;
//        
//        r = (egde[3].x * egde[0].y - egde[3].y * egde[0].x);
//        r = (r == 0.00)? 1.00: 1.0F / r;
//        tangent += (norm[3] * egde[0].y - norm[0] * egde[3].y) * r;
//        
//        return cg::normalize3( tangent );
//    }
//    cg::vec3 InfiniteTerrainMap::GetVertexNormal(int x, int z)
//    {
//        cg::vec3 normal;
//        int h[8];
//        //  0----1----2
//        //  |    |    |
//        //  3----h----4
//        //  |    |    |
//        //  5----6----7
//        h[0] = GetVertexHeight(x-1, z-1);
//        h[1] = GetVertexHeight(  x, z-1);
//        h[2] = GetVertexHeight(x+1, z-1);
//        
//        h[3] = GetVertexHeight(x-1, z);
//        h[5] = GetVertexHeight(  x, z);
//        h[4] = GetVertexHeight(x+1, z);
//        
//        h[5] = GetVertexHeight(x-1, z+1);
//        h[6] = GetVertexHeight(  x, z+1);
//        h[7] = GetVertexHeight(x+1, z+1);
//        
//        // Compute dx using Sobel:
//        //  -1[0] 0 1[2]
//        //  -2[3] 0 2[4]
//        //  -1[5] 0 1[7]
//        normal.x = (h[2] + 2.0*h[4] + h[7]) - (h[0] + 2.0*h[3] + h[5]);
//        
//        // Compute dy using Sobel:
//        //  -1[0] -2[1] -1[2]
//        //    0     0     0
//        //   1[5]  2[6]  1[7]
//        // @note I invert y so that i dont have to do it in shader
//        normal.y =  (h[0] + 2.0*h[1] + h[2]) - (h[5] + 2.0*h[6] + h[7]);
//        
//        normal.z = 1.0 / _normmap_strength;
//        normal = (cg::normalize3(normal) * 0.5) + 0.5;
//        return normal;
//    }
//    cg::vec3 InfiniteTerrainMap::GetVertexColor(int x, int z)
//    {
//        double f, r;
//        f = GetVertexHeight(x,z);
//        f = 255 * cg::unitize(f, 0, 200);
//        r = 255 * cg::unitize(f, 0, 20);
//        return cg::vec3(255, 255-f, 255-r);
//    }
//    float InfiniteTerrainMap::GetVertexHeight(int x, int z)
//    {
//        double f, u, s;
//        double noise = 0;
//        double nx = (x * _tile_size) / _tile_size;
//        double nz = (z * _tile_size) / _tile_size;
//        
//        for (int n=_starting_octave; n<_octave; n++)
//        {
//            u = pow(2, n);
//            s = 1.0 / u;
//            f = _frequency * u;
//            noise += cg::math::noise(nx*f, 0, nz*f) * s;
//        }
//        /*
//         * since noise range from [-1:1] dividing it
//         * by 2 and add 1/2 change its range to [0:1]
//         */
//        noise = noise * 0.5 + 0.5;
//        /*
//         * make hill like steps layers
//         */
//        noise = round(noise * _terraces) / _terraces;
//        /*
//         * make hills more steep by increasing steepness
//         */
//        noise = pow(noise, _steepness) * _strength;
//        
//        return cg::clamp(noise, 0.0f, 1.0f);
//    }
//    gfx::SharedMesh InfiniteTerrainMap::GetTile(int tx, int tz)
//    {
//        gfx::Mesh* mesh = new gfx::Mesh;
//        cg::uint tilesize = (_tile_size+1);
//        cg::uint size = tilesize * tilesize;
//        mesh->GetVertexBuffer().setbuffer(size * 2, 2, size);
//        mesh->GetVertexBuffer().GetVertexLayout().AddElem(gfx::VERTEX_POSITION, 2, 0);
//        cg::point2* vp = mesh->GetVertexBuffer().GetBuffer<cg::point2>();
//        cg::vec3 n;
//        kege::image8i img_norm = image8i(3, 24, tilesize, tilesize, new cg::ubyte[size]);
//        for (int i,x,z=0; z<tilesize;  z++)
//        {
//            for (x=0; x<tilesize; x++)
//            {
//                i = tilesize * z + x;
//                
//                vp[i].x = x;
//                vp[i].y = z;
//                
//                //n = GetVertexNormal( x,z );
//                //(*img_norm[ i ]) = n.x * 255;
//                //(*img_norm[i+1]) = n.y * 255;
//                //(*img_norm[i+2]) = n.z * 255;
//            }
//        }
//        return gfx::SharedMesh(mesh);
//    }
//    
//    InfiniteTerrainMap::InfiniteTerrainMap
//    (   int starting_octave
//     ,  int octave
//     ,  int scale
//     ,  float strength
//     ,  float steepness
//     ,  float terraces  )
//    : _normmap_strength(1.0)
//    , _frequency(1.0)
//    , _steepness(steepness)
//    , _terraces(terraces)
//    , _strength(strength)
//    , _scale(scale)
//    , _starting_octave(starting_octave)
//    , _octave(octave)
//    {}
    
    
    
    
//    void InfiniteTerrain::GenMap(double mx, double mz, int width, int height, kege::image<float>& map)
//    {
//        const int sx = (mx * (width-1));
//        const int sy = (mz * (width-1));
//        const int ex = (sx + width);
//        const int ey = (sy + width);
//        _frequency = 1.0 / (pow(2, _scale));
//        
//        map = kege::image<float>(1, 32, height, width, abstr_image::FLOAT, new float[width * height]);
//        
//        float* noise;
//        int nx,ny, x,y;
//        
//        for (y=0,ny=sy;  ny<ey;  y++,ny++)
//        {
//            for (x=0, nx=sx;  nx<ex;  x++,nx++)
//            {
//                noise = map(x,y);
//                if (noise == nullptr) continue;
//                *noise = GenNoise(nx, ny, mz);
//            }
//        }
//    }
//    
//    gfx::TerrainTile*  InfiniteTerrain::Load(int x, int z, bool queue_load)
//    {
//        if ( queue_load )
//        {
//            tasks.push( cg::var2i(x,z) );
//            return nullptr;
//        }
//        else
//        {
//            return GenerateTile( cg::var2i(x,z) );
//        }
//    }
//    
//    gfx::TerrainTile* InfiniteTerrain::GenerateTile(const cg::var2i& coord)
//    {
////        int scale = system->GetScale();
////        int size = system->GetTileSize();
////        gfx::TerrainTile* tile = new gfx::TerrainTile;
//        //tile->SetName(ds::string::strprint("terrain(%i,%i)", coord.x, coord.y));
////        tile->GetLocal().translation = cg::vec3(coord.x*size*scale, 0, coord.y*size*scale);
////        tile->GetLocal().scale  = cg::vec3(scale, 1, scale);
//        //tile->SetTcoord( coord );
//        
////        GenMap(coord.x, coord.y, size, size, tile->GetHeightmap());
//        //ComputeNormalmap( tile->GetHeightmap(), 8 );
//        //ComputeTangentmap( tile->GetHeightmap(), scale );
//        return nullptr;
//    }
//    
//    double InfiniteTerrain::GenNoise(double nx,double ny,double nz)
//    {
//        double f, u, s;
//        double noise = 0;
//        
//        for (int n=_starting_octave; n<_octave; n++)
//        {
//            u = pow(2, n);
//            s = 1.0 / u;
//            f = _frequency * u;
//            noise += cg::math::noise(nx*f, ny*f, nz*f) * s;
//        }
//        /*
//         * since noise range from [-1:1] dividing it
//         * by 2 and add 1/2 change its range to [0:1]
//         */
//        noise = noise * 0.5 + 0.5;
//        /*
//         * make hill like steps layers
//         */
//        noise = round(noise * _terraces) / _terraces;
//        /*
//         * make hills more steep by increasing steepness
//         */
//        noise = pow(noise, _steepness) * _strength;
//        
//        return cg::clamp(noise, 0.0f, 1.0f);
//        //return noise;
//    }
//    
//    void InfiniteTerrain::PopulateQueue(ds::queue<cg::var2i>& que)
//    {
//        while (!tasks.empty() && _running)
//        {
//            que.push( tasks.top() );
//            tasks.pop();
//        }
//    }
//    
//    void InfiniteTerrain::ProcessQueue(ds::queue<cg::var2i>& que)
//    {
//        gfx::TerrainTile* tile = nullptr;
//        cg::var2i coord;
//        while (!que.empty() && _running)
//        {
//            coord = que.top();
//            que.pop();
//            
//            tile = GenerateTile( coord );
//            if (tile != nullptr)
//            {
//                tile->SetLoaded( true );
//                system->ReceiveMessage( MsgTerraTile("TerrainLoader", "loaded", "TerrainTile", tile) );
//            }
//        }
//    }
//    
//    void InfiniteTerrain::Start()
//    {
//        _thread = new std::thread(&InfiniteTerrain::Run, this);
//    }
//    
//    void InfiniteTerrain::Stop()
//    {
//        _running = false;
//    }
//    
//    void InfiniteTerrain::Run()
//    {
//        _running = true;
//        while (_running)
//        {
//            ds::queue<cg::var2i> que;
//            PopulateQueue(que);
//            ProcessQueue(que);
//        }
//    }
//    
//    InfiniteTerrain::~InfiniteTerrain()
//    {
//        Stop();
//        if (_thread != nullptr)
//        {
//            if (_thread->joinable())
//                _thread->join();
//            delete _thread;
//            _thread = nullptr;
//        }
//    }
//    
//    InfiniteTerrain::InfiniteTerrain
//    (   gfx::TerrainSystem* syst
//     ,  int starting_octave
//     ,  int   octave
//     ,  int   scale
//     ,  float strength
//     ,  float steepness
//     ,  float terraces  )
//    :   system( syst )
//    ,   _thread(nullptr)
//    ,   _running(false)
//    , _normalmap_strength(1.0)
//    , _frequency(1.0)
//    , _steepness(steepness)
//    , _terraces(terraces)
//    , _strength(strength)
//    , _scale(scale)
//    , _starting_octave(starting_octave)
//    , _octave(octave)
//    {
//        Start();
//    }
}}
