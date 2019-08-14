/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       cylinder.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef cylinder_hpp
#define cylinder_hpp
#include "collision.hpp"
namespace kege{namespace cg{
    
    class cylinder
    {
    public:
        cg::vec3 a, b;
        cg::real radius;
        cg::real height;
    };
}}
#endif /* cylinder_hpp */
