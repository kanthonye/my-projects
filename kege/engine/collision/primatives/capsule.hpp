/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       capsule.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef capsule_hpp
#define capsule_hpp
#include "cgm.hpp"
namespace kege{namespace cg{
    
    class capsule
    {
    public:
        cg::point3 a,b;
        cg::real radius;
    };
}}
#endif /* capsule_hpp */
