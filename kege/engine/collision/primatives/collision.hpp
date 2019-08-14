/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       collision.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef collision_hpp
#define collision_hpp
#include "cgm.hpp"
#include "dlist.hpp"
namespace kege{namespace cg{
    struct cylinder;
    struct triangle;
    struct capsule;
    struct segment;
    struct sphere;
    struct plane;
    struct cone;
    struct aabb;
    struct ray;
    struct obb;
    
//    class shape
//    {
//        type GetType() const {return typ;}
//        shape(const type t) : typ(t) {}
//        virtual ~ shape() {}
//    protected:
//        type typ;
//    };
    
    struct collision
    {
        /*
         * Holds the position of the contact in world coordinates.
         */
        cg::point3 point;
        
        /*
         * Holds the direction of the contact in world coordinates.
         */
        cg::vec3 normal;
        
        /*
         * Holds the depth of penetration at the contact point. If both
         * bodies are specified then the contact point should be midway
         * between the inter-penetrating points.
         */
        cg::real penetration;
    };
    
    typedef ds::dlist<collision> collisions;
}}
#endif /* collision_hpp */
