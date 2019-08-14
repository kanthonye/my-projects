/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       plane.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "ray.hpp"
#include "obb.hpp"
#include "aabb.hpp"
#include "plane.hpp"
#include "segment.hpp"
namespace kege{namespace cg{
    
    void make_plane(cg::plane& plane, const cg::point3& a, const cg::point3& b, const cg::point3& c)
    {
        plane.n = cg::cross3(a-b, a-c);
        plane.d = cg::dot3(plane.n, a);
        plane.n = cg::normalize3(plane.n);
    }
    
    void make_plane(cg::plane& plane, const cg::vec3& n, const cg::point3& p)
    {
        plane.n = n;
        plane.d = cg::dot3(n, p);
        plane.n = cg::normalize3(n);
    }
    
    /** return Dot(q, p.n) - p.d; if plane equation normalized (||p.n||==1) */
    float DIST_POINT_PLANE(const cg::point3& q, const cg::plane& p)
    {
        return (cg::dot3(p.n, q) - p.d) / cg::dot3(p.n, p.n);
    }
    
    /**
     * Intersection of Two cg::plane. Given planes p1 and p2, compute line L = p+t*d of their intersection.
     * @param p is origin of line formed from intersection
     * @param d direction of line  formed from intersection
     * @return 0 if no such line exists
     */
    int LINE_btw_PLANES(cg::ray& ray, const cg::plane& p1, const cg::plane& p2)
    {
        // Compute direction of intersection line
        ray.dir = cg::cross3(p1.n, p2.n);
        // If d is (near) zero, the planes are parallel (and separated)
        // or coincident, so they’re not considered intersecting
        float denom = cg::dot3(ray.dir, ray.dir);
        if (denom < EPSILON) return 0;
        // Compute point on intersection line
        ray.origin = cg::cross3(p1.d*p2.n - p2.d*p1.n, ray.dir) / denom;
        return 1;
    }
    
    /** Compute point p of intersection between three cg::plane p1, p2 and p3 (if at all) */
    int INTERSECTION_POINT_PLANES(cg::point3& p, const cg::plane& p1, const cg::plane& p2, const cg::plane& p3)
    {
        cg::vec3 m1 = cg::vec3(p1.n.x, p2.n.x, p3.n.x);
        cg::vec3 m2 = cg::vec3(p1.n.y, p2.n.y, p3.n.y);
        cg::vec3 m3 = cg::vec3(p1.n.z, p2.n.z, p3.n.z);
        cg::vec3 u = cg::cross3(m2, m3);
        float denom = cg::dot3(m1, u);
        if (cg::abs(denom) < EPSILON) return 0; // Planes do not intersect in a point
        cg::vec3 d(p1.d, p2.d, p3.d);
        cg::vec3 v = cg::cross3(m1, d);
        float ood = 1.0f / denom;
        p.x =  cg::dot3( d, u) * ood;
        p.y =  cg::dot3(m3, v) * ood;
        p.z = -cg::dot3(m2, v) * ood;
        return 1;
    }
    
    
    cg::point3 CLOSEST_POINT_to_PLANE(const cg::point3& q, const cg::plane& p)
    {
        float t = (cg::dot3(p.n, q) - p.d) / cg::dot3(p.n, p.n);
        return q - t * p.n;
    }
    
    // for normalize plane
    cg::point3 CLOSEST_POINT_to_PLANE_N(const cg::point3& q, const cg::plane& p)
    {
        float t = cg::dot3(p.n, q) - p.d;
        return q - t * p.n;
    }
    
    /** Intersecting Segment Against cg::plane */
    int SEGMENT_vs_PLANE(float &t, cg::point3& q, const cg::segment& l, cg::plane p)
    {
        // Compute the t value for the directed line ab intersecting the plane
        cg::vec3 ab = l.b - l.a;
        t = (p.d - cg::dot3(p.n, l.a)) / cg::dot3(p.n, ab);
        // If t in [0..1] compute and return intersection point
        if (t >= 0.0f && t <= 1.0f)
        {
            q = l.a + t * ab;
            return 1;
        }
        // Else no intersection
        return 0;
    }
    
    void ComputeCorners(cg::point3 vertices[8], cg::aabb& aabb)
    {
        vertices[0] = cg::point3(aabb.min.x, aabb.min.y, aabb.min.z);
        vertices[1] = cg::point3(aabb.max.x, aabb.min.y, aabb.min.z);
        vertices[2] = cg::point3(aabb.max.x, aabb.min.y, aabb.max.z);
        vertices[3] = cg::point3(aabb.min.x, aabb.min.y, aabb.max.z);
        vertices[4] = cg::point3(aabb.max.x, aabb.max.y, aabb.max.z);
        vertices[5] = cg::point3(aabb.max.x, aabb.max.y, aabb.min.z);
        vertices[6] = cg::point3(aabb.min.x, aabb.max.y, aabb.min.z);
        vertices[7] = cg::point3(aabb.min.x, aabb.max.y, aabb.max.z);
    }
    
    // COLLIDING A BOX AND A PLANE
    // This is the first algorithm that can return more than one contact.
    bool Collision_AABB_PLANE(cg::collisions& collisions, cg::aabb& aabb, cg::plane& plane)
    {
        if ( !cg::AABB_vs_PLANE(aabb, plane) )
        {
            return false;
        }
        
        cg::point3 vertices[8];
        ComputeCorners(vertices, aabb);
        
        for (short i=0; i<8; i++)
        {
            float distance = cg::dot3(vertices[i], plane.n);
            
            float radius = vertices[i].x * cg::abs(plane.n.x);
            radius += vertices[i].y * cg::abs(plane.n.y);
            radius += vertices[i].z * cg::abs(plane.n.x);
            
            // Check if we’re within radius.
            if (distance * distance > radius * radius)
                continue ;
            
            cg::collision* collision = &collisions.push_back();
            collision->point = vertices[i] + plane.n * (distance - plane.d);
            collision->penetration = plane.d - distance;
            collision->normal = plane.n;
        }
        return true;
    }
    
    // COLLIDING A BOX AND A PLANE
    // This is the first algorithm that can return more than one contact.
    bool Collision_AABB_PLANE_HS(cg::collisions& collisions, cg::aabb& aabb, cg::plane& plane)
    {
        if ( !cg::AABB_vs_PLANE(aabb, plane) )
        {
            return false;
        }
        
        cg::point3 vertices[8];
        ComputeCorners(vertices, aabb);
        
        for (short i=0; i<8; i++)
        {
            float distance = cg::dot3(vertices[i], plane.n);
            
            if (distance - plane.d >= 0)
                continue;
            
            cg::collision* collision = &collisions.push_back();
            collision->point = vertices[i] + plane.n * (distance - plane.d);
            collision->penetration = plane.d - distance;
            collision->normal = plane.n;
            break;
        }
        return true;
    }
    
    
    void ComputeCorners(cg::point3 vertices[8], const cg::obb& obb)
    {
        vertices[0] = obb.center + (obb.xaxis * -obb.length.x) - (obb.yaxis * obb.length.y) - (obb.zaxis * obb.length.z);
        vertices[1] = obb.center + (obb.xaxis *  obb.length.x) - (obb.yaxis * obb.length.y) - (obb.zaxis * obb.length.z);
        vertices[2] = obb.center + (obb.xaxis * -obb.length.x) - (obb.yaxis * obb.length.y) + (obb.zaxis * obb.length.z);
        vertices[3] = obb.center + (obb.xaxis *  obb.length.x) - (obb.yaxis * obb.length.y) + (obb.zaxis * obb.length.z);
        
        vertices[4] = obb.center + (obb.xaxis * -obb.length.x) + (obb.yaxis * obb.length.y) - (obb.zaxis * obb.length.z);
        vertices[5] = obb.center + (obb.xaxis *  obb.length.x) + (obb.yaxis * obb.length.y) - (obb.zaxis * obb.length.z);
        vertices[6] = obb.center + (obb.xaxis * -obb.length.x) + (obb.yaxis * obb.length.y) + (obb.zaxis * obb.length.z);
        vertices[7] = obb.center + (obb.xaxis *  obb.length.x) + (obb.yaxis * obb.length.y) + (obb.zaxis * obb.length.z);
        
    }
    
    // COLLIDING A BOX AND A PLANE
    // This is the first algorithm that can return more than one contact.
    bool ComputeCollision(cg::collisions& collisions, cg::obb& obb, cg::plane& plane)
    {
        if (!cg::OBB_vs_PLANE_HALFSPACE(obb, plane))
            return false;
        
        cg::point3 vertices[8];
        ComputeCorners(vertices, obb);
        
        bool value = false;
        for (short i=0; i<8; i++)
        {
            float distance = cg::dot3(vertices[i], plane.n);
            
            
            float radius = vertices[i].x * cg::abs(plane.n.x) + vertices[i].y * cg::abs(plane.n.y) + vertices[i].z * cg::abs(plane.n.x);
            // Check if we’re within radius.
            if (distance * distance > radius * radius)
                continue;
            
            cg::collision* collision = &collisions.push_back();
            collision->point   = vertices[i] + plane.n * (distance - plane.d);
            collision->normal  = plane.n;
            collision->penetration = plane.d - distance;
            value = true;
            
            //kege::Singleton::Get<gfx::DebugRenderer>()->RenderAABB(contact->point - cg::vec3(0.25), contact->point + cg::vec3(0.25), cg::vec3(1));
            break;
        }
        return value;
    }
    
    // COLLIDING A BOX AND A PLANE
    // This is the first algorithm that can return more than one contact.
    bool ComputeCollision_HF(cg::collisions& collisions, cg::obb& obb, cg::plane& plane)
    {
        if (!cg::OBB_vs_PLANE_HALFSPACE(obb, plane))
            return false;
        
        cg::point3 vertices[8];
        ComputeCorners(vertices, obb);
        
        bool value = false;
        for (short i=0; i<8; i++)
        {
            float distance = cg::dot3(vertices[i], plane.n);
            if (distance - plane.d >= 0)
                continue;
            
            cg::collision* collision = &collisions.push_back();
            collision->point   = vertices[i] + plane.n * (distance - plane.d);
            collision->normal  = plane.n;
            collision->penetration = plane.d - distance;
            value = true;
            //break;
        }
        return value;
    }
}}
