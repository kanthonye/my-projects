/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       sphere.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "ray.hpp"
#include "obb.hpp"
#include "aabb.hpp"
#include "plane.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
namespace kege{namespace cg{
    
    
    /** test if two Sphere a and b intersect. */
    int SPHERE_vs_SPHERE(const cg::sphere& a, const cg::sphere& b)
    {
        // Calculate squared distance between centers
        cg::vec3 d = a.center - b.center;
        float dist2 = cg::dot3(d, d);
        // Spheres intersect if squared distance is less than squared sum of radii
        float radiusSum = a.radius + b.radius;
        return dist2 <= radiusSum * radiusSum;
    }
    
    /** test if a cg::sphere and cg::plane intersect. */
    int SPHERE_vs_PLANE(const cg::sphere& s, const cg::plane& p)
    {
        // For a normalized plane (|p.n| = 1), evaluating the plane equation
        // for a point gives the signed distance of the point to the plane
        float dist = cg::dot3(s.center, p.n) - p.d;
        return cg::abs(dist) <= s.radius; // If sphere center within +/-radius from plane, plane intersects sphere
    }
    
    /** Determine whether sphere s is fully behind (inside negative halfspace of) plane p */
    int INSIDE_SPHERE_vs_PLANE(const cg::sphere& s, const cg::plane& p)
    {
        float dist = cg::dot3(s.center, p.n) - p.d;
        return dist < -s.radius;
    }
    
    /** Determine whether sphere s intersects negative halfspace of plane p */
    int SPHERE_vs_PLANE_Halfspace(const cg::sphere& s, const cg::plane& p)
    {
        float dist = cg::dot3(s.center, p.n) - p.d;
        return dist <= s.radius;
    }
    
    /**
     * Returns true if sphere s intersects AABB b, false otherwise.
     * The point p on the AABB closest to the sphere center is also returned
     */
    int SPHERE_vs_AABB( cg::point3 &p, const cg::sphere& s, const cg::aabb& box)
    {
        // Find point p on AABB closest to sphere center
        CLOSEST_POINT_AABB(p, s.center, box);
        // cg::sphere and AABB intersect if the (squared) distance from sphere
        // center to point p is less than the (squared) sphere radius
        cg::vec3 v = p - s.center;
        return cg::dot3(v, v) <= s.radius * s.radius;
    }
    
    /**
     * Returns true if sphere s intersects OBB b, false otherwise.
     * The point p on the OBB closest to the sphere center is also returned
     */
    int SPHERE_vs_OBB(cg::point3& p, const cg::sphere& s, const cg::obb& box)
    {
        // Find point p on OBB closest to sphere center
        CLOSEST_POINT_OBB(p, box, s.center);
        // cg::sphere and OBB intersect if the (squared) distance from sphere
        // center to point p is less than the (squared) sphere radius
        cg::vec3 v = p - s.center;
        return cg::dot3(v, v) <= s.radius * s.radius;
    }
    
    /**
     * Returns true if sphere s intersects triangle ABC, false otherwise.
     * The point p on abc closest to the sphere center is also returned
     */
    int SPHERE_vs_TRIANGLE(const cg::sphere& s, const cg::triangle& t)
    {
        // Find point P on triangle ABC closest to sphere center
        cg::vec3 p = cg::CLOSEST_POINT_TRIANGLE(s.center, t);
        // cg::sphere and triangle intersect if the (squared) distance from sphere
        // center to point p is less than the (squared) sphere radius
        cg::vec3 v = p - s.center;
        return cg::dot3(v, v) <= s.radius * s.radius;
    }
    
    
    
    
    /** Test if ray r = p + td intersects sphere s */
    int RAY_vs_SPHERE(const cg::ray& ray, const cg::sphere& s)
    {
        cg::vec3 m = ray.origin - s.center;
        float c = cg::dot3(m, m) - s.radius * s.radius;
        // If there is definitely at least one real root, there must be an intersection
        if (c <= 0.0f) return 1;
        
        float b = cg::dot3(m, ray.dir);
        // Early exit if ray origin outside sphere and ray pointing away from sphere
        if (b > 0.0f) return 0;
        float disc = b*b - c;
        // A negative discriminant corresponds to ray missing sphere
        if (disc < 0.0f) return 0;
        // Now ray must hit sphere
        return 1;
    }
    
    /**
     * Intersects ray r = p + td, |d| = 1, with sphere s and, if intersecting,
     * returns t value of intersection and intersection point q
     */
    int RAY_vs_SPHERE(cg::collisions& collisions, const cg::ray& ray, const cg::sphere& s)
    {
        cg::vec3 dir = ray.origin - s.center;
        float c = cg::dot3(dir, dir) - s.radius * s.radius;
        // If there is definitely at least one real root, there must be an intersection
        if (c <= 0.0f) return true;
        
        float b = cg::dot3(dir, ray.dir);
        // if ray ray_pos outside sphere and ray_dir is pointing away from sphere, then sphere is behind
        if (b > 0.0f) return false;
        float disc = b*b - c;
        // A negative discriminant corresponds to ray missing sphere
        if (disc < 0.0f) return false;
        
        cg::collision* collision = &collisions.push_back();
        // Ray now found to intersect sphere, compute smallest t value of intersection
        collision->penetration = -b - sqrt(disc);
        // If t is negative, ray started inside sphere so clamp t to zero
        if (collision->penetration < 0.0f) collision->penetration = 0.0f;
        collision->point = ray.origin + ray.dir * collision->penetration;
        return true;
    }

    // COLLIDING A SPHERE AND A BOX
    bool ComputeCollision(cg::collisions& collisions, const cg::sphere& sphere, const cg::aabb& aabb)
    {
        cg::vec3 closest_point;
        cg::CLOSEST_POINT_AABB(closest_point, sphere.center, aabb);
        
        cg::vec3 norm = closest_point - sphere.center;
        cg::real dist = cg::magn3sq(norm);
        
        // Check we’re in contact.
        if (dist > sphere.radius * sphere.radius)
        {
            return 0;
        }
        
        dist = sqrt(dist);
        cg::collision* collision = &collisions.push_back();
        collision->normal      = norm / dist;
        collision->point       = sphere.center + norm * dist;
        collision->penetration = sphere.radius - dist;
        return 1;
    }
    
    bool CollisionSphereSphere(cg::collisions& collisions, const cg::sphere& one, const cg::sphere& two)
    {
        // Find the vector between the objects.
        cg::vec3 norm = one.center  - two.center;
        cg::real dist = cg::magn3sq(norm);
        // Spheres intersect if squared distance is less than squared sum of radii
        float radius = one.radius + two.radius;
        // See if it is large enough.
        if (dist > radius * radius)
        {
            return false;
        }
        
        dist = sqrt(dist);
        // We manually create the normal, because we have the size to hand.
        cg::collision* collision = &collisions.push_back();
        collision->normal       = norm / dist;
        collision->point        = one.center + collision->normal * one.radius;
        collision->penetration  = (one.radius + two.radius) - dist;
        return true;
    }
    
    bool CollisionSpherePlaneHS(cg::collisions& collisions, const cg::sphere& sphere, const cg::plane& plane)
    {
        // Find the distance from the plane.
        float dist = cg::dot3(plane.n, sphere.center);
        dist = dist - sphere.radius - plane.d;
        
        if (dist >= 0) return 0;
        
        cg::collision* collision = &collisions.push_back();
        collision->normal      = plane.n;
        collision->penetration = -dist;
        collision->point       = sphere.center - plane.n * (dist + sphere.radius);
        return 1;
    }
    
    bool CollisionSpherePlane(cg::collisions& collisions, const cg::sphere& sphere, const cg::plane& plane)
    {
        // Find the distance from the plane.
        float dist = cg::dot3(plane.n, sphere.center);
        
        dist = dist - plane.d;
        if (dist * dist > sphere.radius * sphere.radius)
        {
            return 0;
        }
        // Check which side of the plane we’re on.
        cg::vec3 normal = plane.n;
        float penetration = -dist;
        if (dist < 0)
        {
            normal *= -1;
            penetration = -penetration;
        }
        penetration += sphere.radius;
        // Create the contact - it has a normal in the plane direction.
        cg::collision* collision = &collisions.push_back();
        collision->normal      = normal;
        collision->penetration = penetration;
        collision->point       = sphere.center - plane.n * dist;
        return 1;
    }
}}
