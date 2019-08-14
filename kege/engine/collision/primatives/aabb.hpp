/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       AABB.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef AABB_hpp
#define AABB_hpp
#include "cgm.hpp"
#include "collision.hpp"
namespace kege{namespace cg{
    
    class aabb
    {
    public:
        cg::point3 min;
        cg::point3 max;
    };
    
    void CLOSEST_POINT_AABB(cg::point3& q, const cg::point3& p, const cg::aabb& a);
    float SQDIST_AABB_to_POINT(const cg::aabb& b, const cg::point3& p);
    int AABB_vs_AABB(const cg::aabb& a,  const cg::aabb& b);
    int AABB_vs_POINT(const cg::aabb& a,  const cg::point3& b);
    int AABB_vs_PLANE_HALFSPACE(const cg::aabb& b, const cg::plane& p);
    int AABB_vs_PLANE(cg::aabb b, cg::plane p);
    int AABB_vs_SEGMENT(const cg::segment& s, const cg::aabb& b);
    
    bool AABB_AABB_Collision(cg::collisions& collisions, const cg::aabb& shape1, const cg::aabb& shape2);
    int AABB_RAY_Collision(cg::collisions& collisions, const cg::aabb& a, const cg::ray& ray);
}}
#endif /* AABB_hpp */
