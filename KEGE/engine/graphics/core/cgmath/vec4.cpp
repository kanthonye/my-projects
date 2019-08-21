//
//  vec4.cpp
//  column-major
//
//  Created by Kenneth A Esdaile on 7/12/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#include "../../../graphics/core/cgmath/vec4.hpp"
namespace kege{namespace cg{
    
    const cgmvec4 cgmvec4::forward = cgmvec4(0.0, 0.0, 1.0, 1.0);
    const cgmvec4 cgmvec4::right = cgmvec4(1.0, 0.0, 0.0, 1.0);
    const cgmvec4 cgmvec4::up = cgmvec4(0.0, 1.0, 0.0, 1.0);
    const cgmvec4 cgmvec4::zero = cgmvec4(0.0);
    const cgmvec4 cgmvec4::one = cgmvec4(1.0);
}}
