/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/20/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       CubeSystem.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "CubeSystem.hpp"
namespace kege{namespace cmp{
    
    bool CubePager::Init(kege::Scene* scene)
    {
//        gfx::Camera* camera = scene->GetCamera();
//        if (camera == nullptr) return false;
//
//        cg::vec3& position = camera->GetWorld().translation;
//        last.x = (position.x / scale) / tilesize;
//        last.y = (position.y / scale) / tilesize;
//
//        int lw = radius / tilesize;
//        curr_max.x = last.x + lw;
//        curr_max.y = last.y + lw;
//        curr_min.x = last.x - lw;
//        curr_min.y = last.y - lw;
//
//        prev_max.x = curr_max.x;
//        prev_max.y = curr_max.y;
//        prev_min.x = curr_min.x;
//        prev_min.y = curr_min.y;
//
//        count = 0;
//        for (int x, y, z=curr_min.y; z<curr_max.y; z++)
//        {
//            for (y=curr_min.y; y<curr_max.y; y++)
//            {
//                for (x=curr_min.x; x<curr_max.x; x++)
//                {
//                    PageIn( x, y, z );
//                }
//            }
//        }
        return gfx::EntityComponent::Init(scene);
    }
    
    void CubePager::Update(double delta_ms)
    {
//        gfx::Camera* camera = _scene->GetCamera();
//        if (camera == nullptr) return;
//
//        cg::vec3& position = camera->GetWorld().translation;
//
//        int size = (scale * tilesize);
//        int tx = (position.x) / size;
//        int ty = (position.y) / size;
//        int tz = (position.z) / size;
//
//        // calculate delta xz
//        int dx = tx - last.x;
//        int dy = ty - last.y;
//        int dz = tz - last.y;
//        last.x = tx;
//        last.y = tz;
//
//        if ((dx >= 1000 || dx <= -1000) ||
//            (dy >= 1000 || dy <= -1000) ||
//            (dz >= 1000 || dz <= -1000))
//        {
//            dx = dy = dz = 0;
//            last.x = dx;
//            last.y = dy;
//            last.z = dz;
//        }
//
//        if (dx != 0 || 0 != dz)
//        {
//            prev_max.x = curr_max.x;
//            prev_max.y = curr_max.y;
//            prev_max.z = curr_max.z;
//
//            prev_min.x = curr_min.x;
//            prev_min.y = curr_min.y;
//            prev_min.z = curr_min.z;
//
//            int lw = ceil(radius / tilesize);
//
//            curr_max.x = last.x + lw; // max.x
//            curr_max.y = last.y + lw; // max.y
//            curr_max.z = last.z + lw; // max.z
//
//            curr_min.x = last.x - lw; // min.x
//            curr_min.y = last.y - lw; // min.y
//            curr_min.z = last.z - lw; // min.z
//
//            SendPageMsg();
//        }
    }
    
    void CubePager::PageOut(int x, int y, int z)
    {
//        cg::var3i coord = cg::var3i( x,y,z );
//        GetParent()->SendMessage( kege::Envelope(new CubeMsg(_name, "unload", "var3i", coord )) );
    }
    
    void CubePager::PageIn(int x, int y, int z)
    {
//        count++;
//        cg::var3i coord = cg::var3i( x,y,z );
//        GetParent()->SendMessage( kege::Envelope(new CubeMsg(_name, "upload", "var3i", coord )) );
    }
    
    void CubePager::SendPageMsg(int y)
    {
        count = 0;
        int x=0,z=0;
        
        if (pmax.x < cmax.x)
        {
            /*     _________pmax
             *    |????|<---|-------unload
             *    |????|____|____cmax
             *    |????|    |####|
             *pmin|????|____|####|
             *         |    |####|<-upload
             *      cmin____|####|
             */
            for (x=pmax.x; x<cmax.x; x++)
                for (z=cmin.y; z<cmax.y; z++)
                    PageIn(x,y,z);
            
            for (x=pmin.x; x<cmin.x; x++)
                for (z=pmin.y; z<pmax.y; z++)
                    PageOut(x,y,z);
        }
        
        //printf("count->%i\n", count);
        if (cmin.x < pmin.x)
        {
            /*         _________o cmax
             *        |####|    |
             *upload->|####|____|____o pmax
             *        |####|    |????|
             *   cmin o####|____|????|
             *             |    |????|
             *        pmin o____|????|
             */
            for (x=cmin.x; x<pmin.x; x++)
                for (z=cmin.y; z<cmax.y; z++)
                    PageIn(x,y,z);
            
            for (x=cmax.x; x<pmax.x; x++)
                for (z=pmin.y; z<pmax.y; z++)
                    PageOut(x,y,z);
        }
        
        
        //printf("count->%i\n", count);
        if (pmax.y < cmax.y)
        {
            /*            _________o cmax
             *  upload-->|####|    |
             *       ____|####o<---|---pmax
             *      |    |    |    |
             * cmin-|--->o____|____|
             *      |    |????|
             * pmin o____|????|<----unload
             */
            for (x=cmin.x; x<pmax.x; x++)
            {
                for (z=pmax.y; z<cmax.y; z++)
                    PageIn(x,y,z);
                
                for (z=pmin.y; z<cmin.y; z++)
                    PageOut(x,y,z);
            }
        }
        
        //printf("count->%i\n", count);
        if (cmax.y < pmax.y)
        {
            /*            _________o pmax
             *  unload-->|????|    |
             *       ____|????o<---|---cmax
             *      |    |    |    |
             * pmin-|--->o____|____|
             *      |    |####|<----upload
             * cmin o____|####|
             */
            for (x=pmin.x; x<cmax.x; x++)
            {
                for (z=cmin.y; z<pmin.y; z++)
                    PageIn(x,y,z);
                
                for (z=cmax.y; z<pmax.y; z++)
                    PageOut(x,y,z);
            }
        }
        //printf("count->%i\n", count);
    }
    
    void CubePager::SendPageMsg()
    {
        int y=0,x=0,z=0;
        /*
         |      o + + + + + + + o cmax
         |      +               +
         |      +               +
         |      + o + + + + + + + o pmax     ^ +y
         |      + +             + +          |
         |      + +             + +          |
         | cmin o + + + + + + + o +   <- - - + - - ->
         |        +               +          |
         |        +               +          |
         |   pmin o + + + + + + + o          V -y
         */
        if ( pmax.y < cmax.y )
        {
            for (x=cmin.x; x<cmax.x; x++)
            {
                for (z=cmin.z; z<cmax.z; z++)
                {
                    for (y=pmax.y; y<cmax.y; y++)
                        PageIn( x,y,z );
                    
                    for (y=pmin.y; y<cmin.y; y++)
                        PageOut( x,y,z );
                }
            }
            for (y=cmin.y; y<pmax.y; y++)
            {
                SendPageMsg(y);
            }
        }
        /*
         |      o + + + + + + + o pmax
         |      +               +
         |      +               +
         |      + o + + + + + + + o cmax     ^ +y
         |      + +             + +          |
         |      + +             + +          |
         | pmin o + + + + + + + o +   <- - - + - - ->
         |        +               +          |
         |        +               +          |
         |   cmin o + + + + + + + o          V -y
         */
        else if ( pmax.y > cmax.y )
        {
            for (x=cmin.x; x<cmax.x; x++)
            {
                for (z=cmin.z; z<cmax.z; z++)
                {
                    for (y=pmax.y; y>cmax.y; y--)
                        PageOut( x,y,z );
                    
                    for (y=pmin.y; y>cmin.y; y--)
                        PageIn( x,y,z );
                }
            }
            for (y=pmin.y; y<cmax.y; y++)
            {
                SendPageMsg(y);
            }
        }
        else
        {
            for (y=cmin.y; y<cmax.y; y++)
            {
                SendPageMsg(y);
            }
        }
    }
    
    CubePager::CubePager(int radius, int size, int scale)
    :   gfx::EntityComponent(kege::ENUM::_TERRAIN_PAGER, "TilingSystem")
    ,   cmax(0.0)
    ,   cmin(0.0)
    ,   pmax(0.0)
    ,   pmin(0.0)
    ,   tilesize(size)
    ,   radius(radius)
    ,   scale(scale)
    ,   last({0,0,0})
    {}
}}

