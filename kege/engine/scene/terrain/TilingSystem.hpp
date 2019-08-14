//
//  TilingSystem.hpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/20/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef TilingSystem_hpp
#define TilingSystem_hpp
#include "cgm.hpp"
#include "Scene.hpp"
#include "Message.hpp"
#include "SubSystem.hpp"
namespace kege{namespace gfx{
    
    class TilingSystem : public kege::SubSystem
    {
    public:
        
        void Update(double delta_ms) override;
        void UnInit() override;
        bool Init() override;
        
        void PageOut(int x, int z);
        void PageIn(int x, int z);
        void SendPageMsg();
        
        TilingSystem(int radius, int tilesize, int scale);
        
    private:
        
        cg::var2i last;
        
        cg::point2 prev_max;
        cg::point2 prev_min;
        cg::point2 curr_max;
        cg::point2 curr_min;
        
        short tilesize;
        short region;
        short scale;
        int count;
    };
    
    typedef kege::MsgT<cg::var2i> TileMsg;
}}
#endif /* TilePager_hpp */
