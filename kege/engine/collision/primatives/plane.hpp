/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       plane.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef plane_hpp
#define plane_hpp
#include "collision.hpp"
namespace kege{namespace cg{
    
    class plane
    {
    public:
        cg::vec3 n;
        cg::real d;
    };
    
    void make_plane(cg::plane& plane, const cg::point3& a, const cg::point3& b, const cg::point3& c);
    void make_plane(cg::plane& plane, const cg::vec3& n, const cg::point3& p);
    
    /** return Dot(q, p.n) - p.d; if plane equation normalized (||p.n||==1) */
    float DIST_POINT_PLANE(const cg::point3& q, const cg::plane& p);
    
    /**
     * Intersection of Two cg::plane. Given planes p1 and p2, compute line L = p+t*d of their intersection.
     * @param p is origin of line formed from intersection
     * @param d direction of line  formed from intersection
     * @return 0 if no such line exists
     */
    int LINE_btw_PLANES(cg::ray& ray, const cg::plane& p1, const cg::plane& p2);
    
    /** Compute point p of intersection between three cg::plane p1, p2 and p3 (if at all) */
    int INTERSECTION_POINT_PLANES(cg::point3& p, const cg::plane& p1, const cg::plane& p2, const cg::plane& p3);
    
    cg::point3 CLOSEST_POINT_to_PLANE(const cg::point3& q, const cg::plane& p);
    
    // for normalize plane
    cg::point3 CLOSEST_POINT_to_PLANE_N(const cg::point3& q, const cg::plane& p);
    
    /** Intersecting Segment Against cg::plane */
    int SEGMENT_vs_PLANE(float &t, cg::point3& q, const cg::segment& l, cg::plane p);
    
    // COLLIDING A BOX AND A PLANE
    // This is the first algorithm that can return more than one contact.
    bool Collision_AABB_PLANE(cg::collisions& collisions, cg::aabb& aabb, cg::plane& plane);
    
    // COLLIDING A BOX AND A PLANE
    // This is the first algorithm that can return more than one contact.
    bool Collision_AABB_PLANE_HS(cg::collisions& collisions, cg::aabb& aabb, cg::plane& plane);
    
    // COLLIDING A BOX AND A PLANE
    // This is the first algorithm that can return more than one contact.
    bool ComputeCollision(cg::collisions& collisions, cg::obb& obb, cg::plane& plane);
    
    // COLLIDING A BOX AND A PLANE
    // This is the first algorithm that can return more than one contact.
    bool ComputeCollision_HF(cg::collisions& collisions, cg::obb& obb, cg::plane& plane);
}}
#endif /* plane_hpp */
