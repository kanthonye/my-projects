//
//  Animation2D.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 2/16/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "Animation.hpp"
namespace kege{ namespace gfx{
    
    void Animation::Animate(float dt)
    {
        double u = 0;
        if (anim_length <= anim_time)
        {
            if (!repeatable)
            {
                return;
            }
            else
            {
                anim_time -= anim_length;
            }
        }
        anim_time += dt;
        anim_time = cg::min(anim_time, anim_length);
        
        u = anim_time / anim_length;
        u = total_frame * u;
        
        curr_frame = u;
        next_frame = (curr_frame+1) % total_frame;
        frame_time = u - double(curr_frame);
    }
    
    Animation::Animation(bool rep, int ff, int lf, float al)
    :   first_frame(ff)
    ,   last_frame(lf)
    ,   curr_frame(0)
    ,   next_frame(0)
    ,   id(0)
    ,   frame_time(0)
    ,   anim_length(al)
    ,   repeatable(rep)
    ,   total_frame(1)
    {
        
    }
    Animation::Animation()
    :   first_frame(0)
    ,   last_frame(0)
    ,   curr_frame(0)
    ,   next_frame(0)
    ,   id(0)
    ,   frame_time(0)
    ,   anim_length(0)
    ,   anim_time(0.0)
    ,   repeatable(0)
    ,   total_frame(1)
    {
    }
}}
