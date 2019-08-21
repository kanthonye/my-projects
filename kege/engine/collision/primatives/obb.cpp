/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       obb.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "obb.hpp"
#include "plane.hpp"
namespace kege{namespace cg{
    
    /** use AABB test to test if two cg::obb a and b intersect. */
    int OBB_vs_OBB_AABB(const cg::obb& a, const cg::obb& b)
    {
        if (cg::abs(a.center.x - b.center.x) > (a.length.x + b.length.x)) return 0;
        if (cg::abs(a.center.y - b.center.y) > (a.length.y + b.length.y)) return 0;
        if (cg::abs(a.center.z - b.center.z) > (a.length.z + b.length.z)) return 0;
        return 1;
    }
    
    /** Given point p, return point q on (or in) OBB b, closest to p */
    void CLOSEST_POINT_OBB(cg::point3& q, const cg::obb& obb, const cg::point3& p)
    {
        float dist;
        cg::vec3 d = p - obb.center;
        // Start result at center of box
        q = obb.center;
        
        // For each OBB axis...1111
        
        // x-axis...
        dist = cg::dot3(d, obb.xaxis);
        if      (dist >  obb.length.x) dist =  obb.length.x;
        else if (dist < -obb.length.x) dist = -obb.length.x;
        q += dist * obb.xaxis;
        
        // y-axis...
        dist = cg::dot3(d, obb.yaxis);
        if      (dist >  obb.length.y) dist =  obb.length.y;
        else if (dist < -obb.length.y) dist = -obb.length.y;
        q += dist * obb.yaxis;
        
        // z-axis...
        dist = cg::dot3(d, obb.zaxis);
        if      (dist >  obb.length.z) dist =  obb.length.z;
        else if (dist < -obb.length.z) dist = -obb.length.z;
        q += dist * obb.zaxis;
    }
    
    /** Given point p, return corner point q on OBB, closest to p */
    void CLOSEST_CORNER_OBB(const cg::point3& p, const cg::obb& obb, cg::point3& q)
    {
        float dist;
        cg::vec3 d = p - obb.center;
        // Start result at center of box
        q = obb.center;
        
        // x-axis...
        dist = cg::dot3(d, obb.xaxis);
        if      (dist > 0) q +=  obb.length.x * obb.xaxis;
        else if (dist < 0) q += -obb.length.x * obb.xaxis;
        
        
        // y-axis...
        dist = cg::dot3(d, obb.yaxis);
        if      (dist > 0) q +=  obb.length.y * obb.yaxis;
        else if (dist < 0) q += -obb.length.y * obb.yaxis;
        
        // z-axis...
        dist = cg::dot3(d, obb.zaxis);
        if      (dist > 0) q +=  obb.length.z * obb.zaxis;
        else if (dist < 0) q += -obb.length.z * obb.zaxis;
    }
    
    /** test if a cg::obb and cg::plane intersect. */
    int OBB_vs_PLANE(const cg::obb& b, const cg::plane& p)
    {
        // Compute the projection interval radius of b onto L(t) = b.c + t * p.n
        float r = (b.length.x * cg::abs(cg::dot3(p.n, b.xaxis)) +
                   b.length.y * cg::abs(cg::dot3(p.n, b.yaxis)) +
                   b.length.z * cg::abs(cg::dot3(p.n, b.zaxis)));
        // Compute distance of box center from plane
        float s = cg::dot3(p.n, b.center) - p.d;
        // Intersection occurs when distance s falls within [-r,+r] interval
        return cg::abs(s) < r;
    }
    
    /** test if a cg::obb and cg::plane intersect. */
    int OBB_vs_PLANE_HALFSPACE(const cg::obb& b, const cg::plane& p)
    {
        // Compute the projection interval radius of b onto L(t) = b.c + t * p.n
        float r = (b.length.x * cg::abs(cg::dot3(p.n, b.xaxis)) +
                   b.length.y * cg::abs(cg::dot3(p.n, b.yaxis)) +
                   b.length.z * cg::abs(cg::dot3(p.n, b.zaxis)));
        // Compute distance of box center from plane
        float s = cg::dot3(p.n, b.center) - p.d;
        // Intersection occurs when distance s falls within [-r,+r] interval
        return s < r;
    }
    
    /** Computes the square distance between point p and cg::obb b */
    float DISTSQ_POINT_to_OBB(const cg::point3& p, const cg::obb& b)
    {
        cg::vec3 v = p - b.center;
        float d,excess = 0.0f, sqDist = 0.0f;
        
        // Project vector from box center to p on each axis, getting the distance
        // of p along that axis, and count any excess distance outside box extents
        d = cg::dot3(v, b.xaxis);
        if      (d < -b.center.x) excess = d + b.center.x;
        else if (d >  b.center.x) excess = d - b.center.x;
        sqDist += excess * excess;
        
        excess = 0.0f;
        d = cg::dot3(v, b.yaxis);
        if      (d < -b.center.y) excess = d + b.center.y;
        else if (d >  b.center.y) excess = d - b.center.y;
        sqDist += excess * excess;
        
        excess = 0.0f;
        d = cg::dot3(v, b.zaxis);
        if      (d < -b.center.z) excess = d + b.center.z;
        else if (d >  b.center.z) excess = d - b.center.z;
        sqDist += excess * excess;
        
        return sqDist;
    }
    
    /** test if two cg::obb intersect. */
    int OBB_vs_OBB(const cg::obb &a, const cg::obb &b)
    {
        float ra, rb;
        cg::mat33 R, AbsR;
        
        R.m00 = cg::dot3(a.xaxis, b.xaxis);
        R.m01 = cg::dot3(a.xaxis, b.yaxis);
        R.m02 = cg::dot3(a.xaxis, b.zaxis);
        R.m10 = cg::dot3(a.yaxis, b.xaxis);
        R.m11 = cg::dot3(a.yaxis, b.yaxis);
        R.m12 = cg::dot3(a.yaxis, b.zaxis);
        R.m20 = cg::dot3(a.zaxis, b.xaxis);
        R.m21 = cg::dot3(a.zaxis, b.yaxis);
        R.m22 = cg::dot3(a.zaxis, b.zaxis);
        
        // Compute translation vector t
        cg::vec3 t = b.center - a.center;
        // Bring translation into a’s coordinate frame
        t = cg::vec3(cg::dot3(t, a.xaxis), cg::dot3(t, a.zaxis), cg::dot3(t, a.zaxis));
        
        // Compute common subexpressions. Add in an epsilon term to
        // counteract arithmetic errors when two edges are parallel and
        // their cross product is (near) null (see text for details)
        AbsR.m00 = cg::abs(R.m00) + EPSILON;
        AbsR.m01 = cg::abs(R.m01) + EPSILON;
        AbsR.m02 = cg::abs(R.m02) + EPSILON;
        AbsR.m10 = cg::abs(R.m10) + EPSILON;
        AbsR.m11 = cg::abs(R.m11) + EPSILON;
        AbsR.m12 = cg::abs(R.m12) + EPSILON;
        AbsR.m20 = cg::abs(R.m20) + EPSILON;
        AbsR.m21 = cg::abs(R.m21) + EPSILON;
        AbsR.m22 = cg::abs(R.m22) + EPSILON;
        
        
        // Test axes L = A0, L = A1, L = A2
        ra = a.center.x;
        rb = b.center.x * AbsR.m00 + b.center.y * AbsR.m01 + b.center.z * AbsR.m02;
        if (cg::abs(t.x) > ra + rb) return 0;
        
        ra = a.center.y;
        rb = b.center.x * AbsR.m10 + b.center.y * AbsR.m11 + b.center.z * AbsR.m12;
        if (cg::abs(t.y) > ra + rb) return 0;
        
        ra = a.center.z;
        rb = b.center.x * AbsR.m20 + b.center.y * AbsR.m21 + b.center.z * AbsR.m22;
        if (cg::abs(t.z) > ra + rb) return 0;
        
        
        // Test axes L = B0, L = B1, L = B2
        rb = b.center.x;
        ra = a.center.x * AbsR.m00 + a.center.y * AbsR.m10 + a.center.z * AbsR.m20;
        if (cg::abs(t.x * R.m00 + t.y * R.m10 + t.z * R.m20) > ra + rb) return 0;
        
        rb = b.center.x;
        ra = a.center.x * AbsR.m01 + a.center.y * AbsR.m11 + a.center.z * AbsR.m21;
        if (cg::abs(t.x * R.m01 + t.y * R.m11 + t.z * R.m21) > ra + rb) return 0;
        
        rb = b.center.x;
        ra = a.center.x * AbsR.m02 + a.center.y * AbsR.m12 + a.center.z * AbsR.m22;
        if (cg::abs(t.x * R.m02 + t.y * R.m12 + t.z * R.m22) > ra + rb) return 0;
        
        
        // Test axis L = A0 x B0
        ra = a.center.y * AbsR.m20 + a.center.z * AbsR.m10;
        rb = b.center.y * AbsR.m02 + b.center.z * AbsR.m01;
        if (cg::abs(t.z * R.m10 - t.y * R.m20) > ra + rb) return 0;
        // Test axis L = A0 x B1
        ra = a.center.y * AbsR.m21 + a.center.z * AbsR.m11;
        rb = b.center.x * AbsR.m02 + b.center.z * AbsR.m00;
        if (cg::abs(t.z * R.m11 - t.y * R.m21) > ra + rb) return 0;
        // Test axis L = A0 x B2
        ra = a.center.y * AbsR.m22 + a.center.z * AbsR.m12;
        rb = b.center.x * AbsR.m01 + b.center.y * AbsR.m00;
        if (cg::abs(t.z * R.m12 - t.y * R.m22) > ra + rb) return 0;
        
        
        // Test axis L = A1 x B0
        ra = a.center.x * AbsR.m20 + a.center.z * AbsR.m00;
        rb = b.center.y * AbsR.m12 + b.center.z * AbsR.m11;
        if (cg::abs(t.x * R.m20 - t.z * R.m00) > ra + rb) return 0;
        // Test axis L = A1 x B1
        ra = a.center.x * AbsR.m21 + a.center.z * AbsR.m01;
        rb = b.center.x * AbsR.m12 + b.center.z * AbsR.m10;
        if (cg::abs(t.x * R.m21 - t.z * R.m01) > ra + rb) return 0;
        // Test axis L = A1 x B2
        ra = a.center.x * AbsR.m22 + a.center.z * AbsR.m02;
        rb = b.center.x * AbsR.m11 + b.center.y * AbsR.m10;
        if (cg::abs(t.x * R.m22 - t.z * R.m02) > ra + rb) return 0;
        
        
        // Test axis L = A2 x B0
        ra = a.center.x * AbsR.m10 + a.center.y * AbsR.m00;
        rb = b.center.y * AbsR.m22 + b.center.z * AbsR.m21;
        if (cg::abs(t.y * R.m00 - t.x * R.m10) > ra + rb) return 0;
        // Test axis L = A2 x B1
        ra = a.center.x * AbsR.m11 + a.center.y * AbsR.m01;
        rb = b.center.x * AbsR.m22 + b.center.z * AbsR.m20;
        if (cg::abs(t.y * R.m01 - t.x * R.m11) > ra + rb) return 0;
        // Test axis L = A2 x B2
        ra = a.center.x * AbsR.m12 + a.center.y * AbsR.m02;
        rb = b.center.x * AbsR.m21 + b.center.y * AbsR.m20;
        if (cg::abs(t.y * R.m02 - t.x * R.m12) > ra + rb) return 0;
        
        // Since no separating axis is found, the OBBs must be intersecting
        return 1;
    }
    
    bool Collision_OBB_OBB(cg::collisions& collisions, const cg::obb& obbA, const cg::obb &obbB)
    {
        float x,y,z, i,k,j;
        cg::vec3 q,r,s;
        cg::vec3 v = obbB.center - obbA.center;
        
        q = obbB.xaxis * obbB.length.x;
        r = obbB.yaxis * obbB.length.y;
        s = obbB.zaxis * obbB.length.z;
        
        x  = obbA.length.x;
        x += cg::abs(cg::dot3(obbA.xaxis, q));
        x += cg::abs(cg::dot3(obbA.xaxis, r));
        x += cg::abs(cg::dot3(obbA.xaxis, s));
        i  = cg::abs(cg::dot3(obbA.xaxis, v));
        
        if (i > x) return false;
        
        y  = obbA.length.y;
        y += cg::abs(cg::dot3(obbA.yaxis, q));
        y += cg::abs(cg::dot3(obbA.yaxis, r));
        y += cg::abs(cg::dot3(obbA.yaxis, s));
        j  = cg::abs(cg::dot3(obbA.yaxis, v));
        
        if (j > y) return false;
        
        z  = obbA.length.z;
        z += cg::abs(cg::dot3(obbA.zaxis, q));
        z += cg::abs(cg::dot3(obbA.zaxis, r));
        z += cg::abs(cg::dot3(obbA.zaxis, s));
        k  = cg::abs(cg::dot3(obbA.zaxis, v));
        
        if (k > z) return false;
        
        float u[3];
        q = obbA.xaxis * obbA.length.x;
        r = obbA.yaxis * obbA.length.y;
        s = obbA.zaxis * obbA.length.z;
        
        x  = obbB.length.x;
        x += cg::abs(cg::dot3(obbB.xaxis, q));
        x += cg::abs(cg::dot3(obbB.xaxis, r));
        x += cg::abs(cg::dot3(obbB.xaxis, s));
        u[0] = cg::dot3(obbB.xaxis, v);
        i = cg::abs(u[0]);
        
        if (i > x) return false;
        
        y  = obbB.length.y;
        y += cg::abs(cg::dot3(obbB.yaxis, q));
        y += cg::abs(cg::dot3(obbB.yaxis, r));
        y += cg::abs(cg::dot3(obbB.yaxis, s));
        u[1] = cg::dot3(obbB.yaxis, v);
        j = cg::abs(u[1]);
        
        if (j > y) return false;
        
        z  = obbB.length.z;
        z += cg::abs(cg::dot3(obbB.zaxis, q));
        z += cg::abs(cg::dot3(obbB.zaxis, r));
        z += cg::abs(cg::dot3(obbB.zaxis, s));
        u[2] = cg::dot3(obbB.zaxis, v);
        k = cg::abs(u[2]);
        
        if (k > z) return false;
        
        
        cg::collision* collision = &collisions.push_back();
        
        if (i >= j && i >= k)
        {
            if (u[0] <= 0) collision->normal = obbB.xaxis;
            else collision->normal = -obbB.xaxis;
            collision->penetration = x - i;
        }
        else if (j >= i && j >= k)
        {
            if (u[1] <= 0) collision->normal = obbB.yaxis;
            else collision->normal = -obbB.yaxis;
            collision->penetration = y - j;
        }
        else if (k >= i && k >= j)
        {
            if (u[2] <= 0) collision->normal = obbB.zaxis;
            else collision->normal = -obbB.zaxis;
            collision->penetration = z - k;
        }
        else
        {
            collision->normal = 0.0f;
            //printf("contact->normal = 0.0f\n");
        }
        
        collision->point = obbB.center;
        if      (u[0] >  obbB.length.x) u[0] =  obbB.length.x;
        else if (u[0] < -obbB.length.x) u[0] = -obbB.length.x;
        if      (u[1] >  obbB.length.y) u[1] =  obbB.length.y;
        else if (u[1] < -obbB.length.y) u[1] = -obbB.length.y;
        if      (u[2] >  obbB.length.z) u[2] =  obbB.length.z;
        else if (u[2] < -obbB.length.z) u[2] = -obbB.length.z;
        collision->point -= u[0] * obbB.xaxis;
        collision->point -= u[1] * obbB.yaxis;
        collision->point -= u[2] * obbB.zaxis;
        
        return true;
    }
    
}}
