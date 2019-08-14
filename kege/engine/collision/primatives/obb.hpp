/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       obb.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef obb_hpp
#define obb_hpp
#include "collision.hpp"
namespace kege{namespace cg{
    
    class obb
    {
    public:
        cg::point3 length;
        cg::point3 center;
        cg::vec3 xaxis;
        cg::vec3 yaxis;
        cg::vec3 zaxis;
    };
    
    
    int OBB_vs_OBB_AABB(const cg::obb& a, const cg::obb& b);
    void CLOSEST_POINT_OBB(cg::point3& q, const cg::obb& obb, const cg::point3& p);
    void CLOSEST_CORNER_OBB(const cg::point3& p, const cg::obb& obb, cg::point3& q);
    int OBB_vs_PLANE(const cg::obb& b, const cg::plane& p);
    int OBB_vs_PLANE_HALFSPACE(const cg::obb& b, const cg::plane& p);
    float DISTSQ_POINT_to_OBB(const cg::point3& p, const cg::obb& b);
    int OBB_vs_OBB(const cg::obb &a, const cg::obb &b);
    bool Collision_OBB_OBB(cg::collisions& collisions, const cg::obb& obbA, const cg::obb &obbB);
}}
#endif /* obb_hpp */
