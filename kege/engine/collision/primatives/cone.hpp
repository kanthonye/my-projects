/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       cone.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef cone_hpp
#define cone_hpp
#include "cgm.hpp"
namespace kege{namespace cg{
    
    class cone
    {
    public:
        cg::vec3 origin;
        cg::vec3 axis;
        cg::real radius;
        cg::real height;
    };
}}
#endif /* cone_hpp */
