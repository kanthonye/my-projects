//
//  TilingSystem.cpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/20/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "TilingSystem.hpp"
namespace kege{namespace gfx{
    
    void TilingSystem::Update(double delta_ms)
    {
        gfx::Camera* camera = GetScene()->GetCamera();
        if (camera == nullptr) return;
        
        cg::vec3& position = camera->GetWorld().translation;
        
        int size = (scale * tilesize);
        int tx = (position.x) / size;
        int tz = (position.z) / size;
        
        // calculate delta xz
        int dx = tx - last.x;
        int dz = tz - last.y;
        last.x = tx;
        last.y = tz;
        
        if (dx >= 1000 || dx <= -1000 || dz >= 1000 || dz <= -1000)
        {
            last.x = 0;
            last.y = 0;
            dx = dz = 0;
        }
        
        if (dx != 0 || 0 != dz)
        {
            prev_max.x = curr_max.x;
            prev_max.y = curr_max.y;
            prev_min.x = curr_min.x;
            prev_min.y = curr_min.y;
            
            int lw = ceil( (region * 0.5) / tilesize );
            
            curr_max.x = last.x + lw; // max.x
            curr_max.y = last.y + lw; // max.z
            curr_min.x = last.x - lw; // min.x
            curr_min.y = last.y - lw; // min.z
            SendPageMsg();
        }
    }
    
    void TilingSystem::UnInit()
    {
        _init = false;
    }
    
    bool TilingSystem::Init()
    {
        if ( _init ) return _init;
        
        gfx::Camera* camera = GetScene()->GetCamera();
        if (camera == nullptr) return false;
        
        cg::vec3& position = camera->GetWorld().translation;
        last.x = (position.x / scale) / tilesize;
        last.y = (position.y / scale) / tilesize;
        
        int lw = ceil( (region * 0.5) / tilesize );
        curr_max.x = last.x + lw;
        curr_max.y = last.y + lw;
        curr_min.x = last.x - lw;
        curr_min.y = last.y - lw;
        
        prev_max.x = curr_max.x;
        prev_max.y = curr_max.y;
        prev_min.x = curr_min.x;
        prev_min.y = curr_min.y;
        
        count = 0;
        for (int x,z=curr_min.y; z<curr_max.y; z++)
        {
            for (x=curr_min.x; x<curr_max.x; x++)
            {
                PageIn(x,z);
            }
        }
        _init = true;
        return _init;
    }
    
    void TilingSystem::PageOut(int x, int z)
    {
        cg::var2i coord = cg::var2i(x,z);
        GetScene()->HandleMessage( TileMsg(GetStrType(), "unload", "var2i", coord ) );
    }
    
    void TilingSystem::PageIn(int x, int z)
    {
        count++;
        cg::var2i coord = cg::var2i(x,z);
        GetScene()->HandleMessage( TileMsg(GetStrType(), "upload", "var2i", coord ) );
    }
    
    void TilingSystem::SendPageMsg()
    {
        count = 0;
        int x=0,z=0;
        
        if (prev_max.x < curr_max.x)
        {
            /*     _________pmax
             *    |????|<---|-------unload
             *    |????|____|____cmax
             *    |????|    |####|
             *pmin|????|____|####|
             *         |    |####|<-upload
             *      cmin____|####|
             */
            for (x=prev_max.x; x<curr_max.x; x++)
                for (z=curr_min.y; z<curr_max.y; z++)
                    PageIn(x,z);
            
            for (x=prev_min.x; x<curr_min.x; x++)
                for (z=prev_min.y; z<prev_max.y; z++)
                    PageOut(x,z);
        }
        
        //printf("count->%i\n", count);
        if (curr_min.x < prev_min.x)
        {
            /*         _________o cmax
             *        |####|    |
             *upload->|####|____|____o pmax
             *        |####|    |????|
             *   cmin o####|____|????|
             *             |    |????|
             *        pmin o____|????|
             */
            for (x=curr_min.x; x<prev_min.x; x++)
                for (z=curr_min.y; z<curr_max.y; z++)
                    PageIn(x,z);
            
            for (x=curr_max.x; x<prev_max.x; x++)
                for (z=prev_min.y; z<prev_max.y; z++)
                    PageOut(x,z);
        }
        
        
        //printf("count->%i\n", count);
        if (prev_max.y < curr_max.y)
        {
            /*            _________o cmax
             *  upload-->|####|    |
             *       ____|####o<---|---pmax
             *      |    |    |    |
             * cmin-|--->o____|____|
             *      |    |????|
             * pmin o____|????|<----unload
             */
            for (x=curr_min.x; x<prev_max.x; x++)
            {
                for (z=prev_max.y; z<curr_max.y; z++)
                    PageIn(x,z);
                
                for (z=prev_min.y; z<curr_min.y; z++)
                    PageOut(x,z);
            }
        }
        
        //printf("count->%i\n", count);
        if (curr_max.y < prev_max.y)
        {
            /*            _________o pmax
             *  unload-->|????|    |
             *       ____|????o<---|---cmax
             *      |    |    |    |
             * pmin-|--->o____|____|
             *      |    |####|<----upload
             * cmin o____|####|
             */
            for (x=prev_min.x; x<curr_max.x; x++)
            {
                for (z=curr_min.y; z<prev_min.y; z++)
                    PageIn(x,z);
                
                for (z=curr_max.y; z<prev_max.y; z++)
                    PageOut(x,z);
            }
        }
        //printf("count->%i\n", count);
    }
    
    TilingSystem::TilingSystem(int region, int size, int scale)
    :   kege::SubSystem("TilingSystem")
    ,   curr_max(0.0)
    ,   curr_min(0.0)
    ,   prev_max(0.0)
    ,   prev_min(0.0)
    ,   tilesize(size)
    ,   region(region)
    ,   scale(scale)
    ,   last({0,0})
    {}
}}
