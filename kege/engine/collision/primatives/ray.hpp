/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ray.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef ray_hpp
#define ray_hpp
#include "cgm.hpp"
namespace kege{namespace cg{
    
    class ray
    {
    public:
        cg::point3 origin;
        cg::point3 dir;
    };
}}
#endif /* ray_hpp */
