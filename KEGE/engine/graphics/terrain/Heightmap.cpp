/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/18/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Heightmap.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#include "Heightmap.hpp"
#include "TerrainSystem.hpp"
#include "../../graphics/core/Graphics.hpp"
namespace kege{namespace gfx{
    
//    bool Heightmap::Init(kege::Scene* scene)
//    {
//        if (_init == true) return _init;
//
//        ds::string name = ds::string::strprint( "~/terrain/map(%i,%i).tga", _coord.x, _coord.y );
//        ds::string filename = kege::VFS::GetInstance().GetFilename( name );
//        if ((_file = fopen(filename.c_str(), "r")) == nullptr)
//        {
//            return false;
//        }
//
//        fseek(_file, 12, SEEK_SET);
//        fread(&_size, 2, 1, _file);
//        fseek(_file, 16, SEEK_SET);
//        fread(&_bpp, 1, 1, _file);
//        _header = 18; // header size
//
//        int width = _size -1;
//        width = width / _system->tile_size;
//        _root = new Region(_coord.x, _coord.y, width);
//
//        SetRadius( sqrt( cg::sq(width * _system->scale * 0.5) * 2 ) );
//        return gfx::Gameobject::Init(scene);
//    }
    
    
    cg::vec3 Heightmap::GetVertexPosition( int x, int z )const
    {
        return cg::vec3( x * _system->GetScale(), GetPixel( x,z ), z * _system->GetScale() );
    }
    
    cg::vec2 Heightmap::GetVertexTexcoord( int x, int z )const
    {
        return cg::vec2( float(x / _data.width()), float(z / _data.height()) );
    }
    
    cg::vec3 Heightmap::GetVertexTangent( int x0,int z0,  int x1,int z1,  int x2,int z2 )const
    {
        cg::vec3 v[2],p[3];
        cg::vec2 e[2],t[3];
        float r;
        
        // <---- positions for the triangle ---->
        p[0] = GetVertexPosition(x0, z0);
        p[1] = GetVertexPosition(x1, z1);
        p[2] = GetVertexPosition(x2, z2);
        
        // <---- uvcoord for the triangle ---->
        t[0] = GetVertexTexcoord(x0, z0);
        t[1] = GetVertexTexcoord(x1, z1);
        t[2] = GetVertexTexcoord(x2, z2);
        
        // <---- compute the tangent for triangle ---->
        v[0] = p[1] - p[0];
        v[1] = p[2] - p[0];
        e[0] = t[1] - t[0];
        e[1] = t[2] - t[0];
        
        r = (e[0].x * e[1].y - e[0].y * e[1].x);
        r = (r == 0.00)? 1.00: 1.0F / r;
        
        return (v[0] * e[1].y - v[1] * e[0].y) * r;
    }
    
    cg::vec3 Heightmap::GetVertexNormal( int x, int z )const
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
        return cg::normalize3( cg::vec3( dx, dy, dz ) ) * 0.5 + 0.5;
    }
    
    double Heightmap::GetPixel( cg::uint x, cg::uint z )const
    {
        if ( z >= _data.height() ) z = z % _data.height();
        if ( x >= _data.width()  ) x = x % _data.width();
        return _data( x,z );
    }
   
    TerrainSystem* Heightmap::GetSystem()
    {
        return _system;
    }
    
    int Heightmap::GetSize()const
    {
        return _data.width();
    }
    
    Heightmap::Heightmap( int x, int z, TerrainSystem* system )
    :   _system( system )
    ,   _x( x )
    ,   _z( z )
    {
        ds::string name = ds::string::strprint( "~/terrain/map(%i,%i).tga", x, z );
        ds::string filename = kege::VFS::GetInstance().GetFilename( name );
        FILE* file = fopen(filename.c_str(), "r");
        if ( file == nullptr )
        {
            return;
        }
        
        short width, height, bpp;
        fseek( file, 12, SEEK_SET );
        fread( &width, 2, 1, file );
        fread( &height, 2, 1, file );
        fseek( file, 16, SEEK_SET );
        fread( &bpp, 1, 1, file );
        fseek( file, 18, SEEK_SET );
        long size = width * height;
        _data.resize( width, height );
        double h;
        
        cg::ubyte value = 0;
        for ( int i=0; i<size; i++ )
        {
            fread( &value, 1, 1, file );
            h = double( value ) / 255.0;
            _data[ i ] = cg::lerp( system->GetMinHeight(), system->GetMaxHeight(), h );
        }
        fclose( file );
    }
    
    Heightmap::~ Heightmap()
    {
    }
}}
