//
//  vec3.cpp
//  vector-math
//
//  Created by Kenneth A Esdaile on 6/6/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#include "../../graphics/cgmath/vec3.hpp"
namespace kege{namespace cg{
    
    cgmvec3 calc_center(const cgmvec3 *a, const int size)
    {
        cgmvec3 res(0.0f);
        for (int i=0; i<size; i++) res += a[i];
        return res * cg::invrs(size);
    }
    
    void calc_dir_vecs(cg::vec3& forward, cg::vec3& right, cg::vec3& up, const float x, const float y)
    {
        float cosPitch = cos(cg::deg2rad(x));
        float sinPitch = sin(cg::deg2rad(x));
        float cosYaw = cos(cg::deg2rad(y));
        float sinYaw = sin(cg::deg2rad(y));
        
        forward( sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw );
        up( sinYaw * sinPitch, cosPitch, cosYaw * sinPitch );
        right( cosYaw, 0, -sinYaw );
    }
    
    const cgmvec3 cgmvec3::forward = cgmvec3(0.0, 0.0, 1.0);
    const cgmvec3 cgmvec3::right = cgmvec3(1.0, 0.0, 0.0);
    const cgmvec3 cgmvec3::zero = cgmvec3(0.0);
    const cgmvec3 cgmvec3::one = cgmvec3(1.0);
    const cgmvec3 cgmvec3::up = cgmvec3(0.0, 1.0, 0.0);
}}
