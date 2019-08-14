//
//  print.hpp
//  column-major
//
//  Created by Kenneth A Esdaile on 7/12/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef print_hpp
#define print_hpp
#include <stdio.h>
#include "../../graphics/cgmath/mat22.hpp"
#include "../../graphics/cgmath/mat33.hpp"
#include "../../graphics/cgmath/mat44.hpp"
void print(const kege::cg::mat33& m);
void print(const kege::cg::cgmmat44& m);
void print(const kege::cg::vec4& m);
void print(const kege::cg::vec3& m);
void print(const kege::cg::vec2& m);
void print(const kege::cg::mat22& m);


namespace kege{namespace cg{
    void print(char const* format, ...);
}}
#endif /* print_hpp */
