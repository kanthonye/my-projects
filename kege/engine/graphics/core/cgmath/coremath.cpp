//
//  core.cpp
//  vector-math
//
//  Created by Kenneth A Esdaile on 6/6/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#include "../../../graphics/core/cgmath/coremath.hpp"

namespace kege{namespace cg{
   
    double invsqrt(double x)
    {
        double hx = 0.5f * x;
        int i = *(int*)&x;         // store floating-point bits in integer
        i = 0x5f3759df - (i >> 1); // initial guess for Newton's method
        x = *(double*)&i;           // convert new bits into float
        x = x*(1.5f - hx*x*x);     // One round of Newton's method
        return x;
    }
}}
