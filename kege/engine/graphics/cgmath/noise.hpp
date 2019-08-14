//
//  noise.hpp
//  column-major
//
//  Created by Kenneth A Esdaile on 7/13/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef noise_hpp
#define noise_hpp
#include "../../graphics/cgmath/coremath.hpp"
namespace kege{namespace cg{namespace math{
    class PerlinNoise3D
    {
    public:
        
        static double noise(double x, double y, double z);
        //static double fade(double t);
        //static double lerp(double t, double a, double b);
        //static double grad(int hash, double x, double y, double z);
        PerlinNoise3D();
        
        static int permutation[256];
        static int p[512];
    };
    double noise(double x, double y, double z);
}}}
#endif /* noise_hpp */
