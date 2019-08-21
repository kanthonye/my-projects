/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       sphere.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef sphere_hpp
#define sphere_hpp
#include "collision.hpp"
namespace kege{namespace cg{
    
    class sphere
    {
    public:
        cg::point3 center;
        cg::real radius;
    };
    
    /** test if two Sphere a and b intersect. */
    int SPHERE_vs_SPHERE(const cg::sphere& a, const cg::sphere& b);
    
    /** test if a cg::sphere and cg::plane intersect. */
    int SPHERE_vs_PLANE(const cg::sphere& s, const cg::plane& p);
    
    /** Determine whether sphere s is fully behind (inside negative halfspace of) plane p */
    int INSIDE_SPHERE_vs_PLANE(const cg::sphere& s, const cg::plane& p);
    
    /** Determine whether sphere s intersects negative halfspace of plane p */
    int SPHERE_vs_PLANE_Halfspace(const cg::sphere& s, const cg::plane& p);
    
    /**
     * Returns true if sphere s intersects AABB b, false otherwise.
     * The point p on the AABB closest to the sphere center is also returned
     */
    int SPHERE_vs_AABB( cg::point3 &p, const cg::sphere& s, const cg::aabb& box);
    
    /**
     * Returns true if sphere s intersects OBB b, false otherwise.
     * The point p on the OBB closest to the sphere center is also returned
     */
    int SPHERE_vs_OBB(cg::point3& p, const cg::sphere& s, const cg::obb& box);
    
    /**
     * Returns true if sphere s intersects triangle ABC, false otherwise.
     * The point p on abc closest to the sphere center is also returned
     */
    int SPHERE_vs_TRIANGLE(const cg::sphere& s, const cg::triangle& t);
    
    
    
    
    /** Test if ray r = p + td intersects sphere s */
    int RAY_vs_SPHERE(const cg::ray& ray, const cg::sphere& s);
    
    /**
     * Intersects ray r = p + td, |d| = 1, with sphere s and, if intersecting,
     * returns t value of intersection and intersection point q
     */
    int RAY_vs_SPHERE(cg::collisions& collisions, const cg::ray& ray, const cg::sphere& s);
    
    // COLLIDING A SPHERE AND A BOX
    bool ComputeCollision(cg::collisions& collisions, const cg::sphere& sphere, const cg::aabb& aabb);
    bool CollisionSphereSphere(cg::collisions& collisions, const cg::sphere& one, const cg::sphere& two);
    bool CollisionSpherePlaneHS(cg::collisions& collisions, const cg::sphere& sphere, const cg::plane& plane);
    bool CollisionSpherePlane(cg::collisions& collisions, const cg::sphere& sphere, const cg::plane& plane);
}}
#endif /* sphere_hpp */
