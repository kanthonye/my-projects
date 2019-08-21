/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       AABB.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "ray.hpp"
#include "aabb.hpp"
#include "plane.hpp"
#include "segment.hpp"
namespace kege{namespace cg{
    
    /** Given point p, return the point q on or in AABB b that is closest to p Closest Point on AABB to Point */
    void CLOSEST_POINT_AABB(cg::point3& q, const cg::point3& p, const cg::aabb& a)
    {
        // For each coordinate axis, if the point coordinate value is
        // outside box, clamp it to the box, else keep it as is
        q.x = p.x;
        if      (p.x <= a.min.x) q.x = a.min.x;
        else if (p.x >= a.max.x) q.x = a.max.x;
        
        q.y = p.y;
        if      (p.y <= a.min.y) q.y = a.min.y;
        else if (p.y >= a.max.y) q.y = a.max.y;
        
        q.z = p.z;
        if      (p.z <= a.min.z) q.z = a.min.z;
        else if (p.z >= a.max.z) q.z = a.max.z;
    }
    
    /** Computes the square distance between a point p and an AABB b */
    float SQDIST_AABB_to_POINT(const cg::aabb& b, const cg::point3& p)
    {
        float v, sqDist = 0.0f;
        // For each axis count any excess distance outside box extents
        v = p.x;
        if (v < b.min.x) sqDist += (b.min.x - v) * (b.min.x - v);
        if (v > b.max.x) sqDist += (v - b.max.x) * (v - b.max.x);
        
        v = p.y;
        if (v < b.min.y) sqDist += (b.min.y - v) * (b.min.y - v);
        if (v > b.max.y) sqDist += (v - b.max.y) * (v - b.max.y);
        
        v = p.z;
        if (v < b.min.z) sqDist += (b.min.z - v) * (b.min.z - v);
        if (v > b.max.z) sqDist += (v - b.max.z) * (v - b.max.z);
        
        return sqDist;
    }
    
    /** test if two AABB a and b intersect. */
    int AABB_vs_AABB(const cg::aabb& a,  const cg::aabb& b)
    {
        // Exit with no intersection if separated along an axis
        if (a.max.x < b.min.x || a.min.x > b.max.x) return false;
        if (a.max.y < b.min.y || a.min.y > b.max.y) return false;
        if (a.max.z < b.min.z || a.min.z > b.max.z) return false;
        // Overlapping on all axes means AABBs are intersecting
        return true;
    }
    
    /** test if AABB and a point intersect. */
    int AABB_vs_POINT(const cg::aabb& a,  const cg::point3& b)
    {
        // Exit with no intersection if separated along an axis
        if (a.max.x < b.x || a.min.x > b.x) return false;
        if (a.max.y < b.y || a.min.y > b.y) return false;
        if (a.max.z < b.z || a.min.z > b.z) return false;
        // Overlapping on all axes means AABBs are intersecting
        return true;
    }
    
    /** test if a AABB and Plane intersect. */
    int AABB_vs_PLANE_HALFSPACE(const cg::aabb& b, const cg::plane& p)
    {
        // These two lines not necessary with a (center, extents) AABB representation
        cg::point3 c = (b.max + b.min) * 0.5f; // Compute AABB center
        cg::point3 e = b.max - c; // Compute positive extents
        // Compute the projection interval radius of b onto L(t) = b.c + t * p.n
        float r = e.x * cg::abs(p.n.x) + e.y * cg::abs(p.n.y) + e.z * cg::abs(p.n.x);
        // Compute distance of box center from plane
        float s = cg::dot3(p.n, c) - p.d;
        // Intersection occurs when distance s falls within [-r,+r] interval
        return s <= r;
    }
    
    /** test if a AABB and Plane intersect. */
    int AABB_vs_PLANE(cg::aabb b, cg::plane p)
    {
        // These two lines not necessary with a (center, extents) AABB representation
        cg::point3 c = (b.max + b.min) * 0.5f; // Compute AABB center
        cg::point3 e = b.max - c; // Compute positive extents
        // Compute the projection interval radius of b onto L(t) = b.c + t * p.n
        float r = e.x * cg::abs(p.n.x) + e.y * cg::abs(p.n.y) + e.z * cg::abs(p.n.x);
        // Compute distance of box center from plane
        float s = cg::dot3(p.n, c) - p.d;
        // Intersection occurs when distance s falls within [-r,+r] interval
        return cg::abs(s) <= r;
    }
    
    /** Test if segment specified by points p0 and p1 intersects AABB b */
    int AABB_vs_SEGMENT(const cg::segment& s, const cg::aabb& b)
    {
        cg::point3 c = (b.min + b.max) * 0.5f;
        cg::vec3 e = b.max - c;
        cg::point3 m = (s.a + s.b) * 0.5f;
        cg::vec3 d = s.b - m;
        m = m - c;
        
        // Try world coordinate axes as separating axes
        float adx = cg::abs(d.x);
        if (cg::abs(m.x) > e.x + adx) return 0;
        float ady = cg::abs(d.y);
        if (cg::abs(m.y) > e.y + ady) return 0;
        float adz = cg::abs(d.z);
        if (cg::abs(m.z) > e.z + adz) return 0;
        // Add in an epsilon term to counteract arithmetic errors when segment is
        // (near) parallel to a coordinate axis (see text for detail)
        adx += EPSILON;
        ady += EPSILON;
        adz += EPSILON;
        // Try cross products of segment direction vector with coordinate axes
        if (cg::abs(m.y * d.z - m.z * d.y) > e.y * adz + e.z * ady) return 0;
        if (cg::abs(m.z * d.x - m.x * d.z) > e.x * adz + e.z * adx) return 0;
        if (cg::abs(m.x * d.y - m.y * d.x) > e.x * ady + e.y * adx) return 0;
        // No separating axis found; segment must be overlapping AABB
        return 1;
    }
    
    bool AABB_AABB_Collision(cg::collisions& collisions, const cg::aabb& shape1, const cg::aabb& shape2)
    {
        if ( !cg::AABB_vs_AABB(shape1, shape2) )
        {
            return false;
        }
        cg::collision* collision = &collisions.push_back();
        
        cg::vec3 center1 = (shape1.max - shape1.min) * 0.5;
        cg::vec3 center2 = (shape2.max - shape2.min) * 0.5;
        cg::vec3 n = center2 - center1;
        cg::vec3 N = cg::abs3(n);
        
        cg::CLOSEST_POINT_AABB(collision->point, center1, shape2);
        
        // Calculate half extents along y axis for each object, then calculate overlap on y axis
        float y_overlap = center1.y + center1.y - cg::abs(n.y);
        
        // is the object colliding from the x-axis or the z-axis
        if(N.x >= N.z)
        {
            // Find out which axis is axis of least penetration
            if(N.x > N.y)
            {
                // Point towards B knowing that n points from A to B
                if (n.x > 0)
                {
                    collision->normal(-1,0,0);
                }
                else
                {
                    collision->normal(1,0,0);
                }
                
                // Calculate half extents along x axis for each object.
                // Calculate overlap on x axis
                float x_overlap = center1.x + center2.x - abs(n.x);
                collision->penetration = x_overlap;
            }
            else
            {
                // Point toward B knowing that n points from A to B
                if (n.y > 0)
                {
                    collision->normal(0,-1,0);
                }
                else
                {
                    collision->normal(0,1,0);
                }
                collision->penetration = y_overlap;
            }
        }
        else if(N.x <= N.z)
        {
            // Find out which axis is axis of least penetration
            if(N.z > N.y)
            {
                // Point towards B knowing that n points from A to B
                if (n.z > 0)
                {
                    collision->normal(0,0,-1);
                }
                else
                {
                    collision->normal(0,0,1);
                }
                
                // Calculate half extents along z axis for each object
                float z_overlap = center1.z + center2.z - abs(n.z);
                collision->penetration = z_overlap;
            }
            else
            {
                // if the object is colliding from below or above
                if (n.y > 0)
                {
                    collision->normal(0,-1,0);
                }
                else
                {
                    collision->normal(0,1,0);
                }
                collision->penetration = y_overlap;
            }
        }
        return true;
    }
}}
