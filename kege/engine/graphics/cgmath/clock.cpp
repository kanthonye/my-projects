//
//  clock.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/15/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#include <chrono>
#include "clock.hpp"
namespace kege{namespace cg{
    double GetTimeTick()
    {
        static long prev_tick = 0;
        static long curr_tick = 0;
        std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
        curr_tick = ms.count();
        if (prev_tick == 0) prev_tick = curr_tick;
        double delta = curr_tick - prev_tick;
        prev_tick = curr_tick;
        return delta;
    }
    
    double GetCurrentTime()
    {
        return std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count();
    }

}}
