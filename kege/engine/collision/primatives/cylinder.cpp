/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       cylinder.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "plane.hpp"
#include "cylinder.hpp"
namespace kege{namespace cg{
    
    /**
     * Intersecting Ray or Segment Against Cylinder
     * Intersect segment S(t)=sa+t(sb-sa), 0<=t<=1 against cylinder specified by p, q and r
     */
    int SEGMENT_vs_CYLINDER(const cg::point3& sa, const cg::point3& sb, const cg::point3& p, const cg::point3& q, float r, float &t)
    {
        cg::vec3 d = q - p, m = sa - p, n = sb - sa;
        float md = cg::dot3(m, d);
        float nd = cg::dot3(n, d);
        float dd = cg::dot3(d, d);
        // Test if segment fully outside either endcap of cylinder
        if (md < 0.0f && md + nd < 0.0f) return 0; // Segment outside ’p’ side of cylinder
        if (md > dd && md + nd > dd) return 0; // Segment outside ’q’ side of cylinder
        float nn = cg::dot3(n, n);
        float mn = cg::dot3(m, n);
        float a = dd * nn - nd * nd;
        float k = cg::dot3(m, m) - r * r;
        float c = dd * k - md * md;
        if (cg::abs(a) < EPSILON)
        {
            // Segment runs parallel to cylinder axis
            if (c > 0.0f) return 0; // ’a’ and thus the segment lie outside cylinder
            // Now known that segment intersects cylinder; figure out how it intersects
            if (md < 0.0f) t = -mn / nn; // Intersect segment against ’p’ endcap
            else if (md > dd) t = (nd - mn) / nn; // Intersect segment against ’q’ endcap
            else t = 0.0f; // ’a’ lies inside cylinder
            return 1;
        }
        float b = dd * mn - nd * md;
        float discr = b * b - a * c;
        if (discr < 0.0f) return 0; // No real roots; no intersection
        t = (-b - sqrt(discr)) / a;
        if (t < 0.0f || t > 1.0f) return 0; // Intersection lies outside segment
        if (md + t * nd < 0.0f)
        {
            // Intersection outside cylinder on ’p’ side
            if (nd <= 0.0f) return 0; // Segment pointing away from endcap
            t = -md / nd;
            // Keep intersection if Dot(S(t) - p, S(t) - p) <= r∧2
            return k + 2 * t * (mn + t * nn) <= 0.0f;
        }
        else if (md + t * nd > dd)
        {
            // Intersection outside cylinder on ’q’ side
            if (nd >= 0.0f) return 0; // Segment pointing away from endcap
            t = (dd - md) / nd;
            // Keep intersection if dot(S(t) - q, S(t) - q) <= r∧2
            return k + dd - 2 * md + t * (2 * (mn - nd) + t * nn) <= 0.0f;
        }
        // Segment intersects cylinder between the endcaps; t is correct
        return 1;
    }
    
    bool CollisionCylinderPlane(cg::collisions& collisions, cg::cylinder& c, cg::plane& p)
    {
//        float d0 = cg::dot3(p.n, c.axis);
//        if (d0 == 0.0f)
//        {
//            d0 = cg::dot3(p.n, c.center) - p.d;
//            if (d0 <= c.radius)
//            {
//                cg::collision* collision = &collisions.push_back();
//                collision->normal      = p.n;
//                collision->penetration = c.radius - d0;
//                collision->point       = c.center - p.n * c.radius;
//                return true;
//            }
//        }
//        else
//        {
//            float d1 = cg::dot3(p.n, c.center);
//            cg::point3 p0 = c.center - p.n * d1; // point on  plane
//            cg::point3 v0 = p0 - c.center;
//            cg::point3 axis = c.axis;
//            
//            if (d0 < 0) axis *= -1.0f;
//            
//            cg::point3 p1;
//            float d2 = cg::dot3(axis, v0);
//            p1 = c.center - axis * d2; // point on  plane
//            v0 = cg::cross3(p.n, axis);
//            v0 = cg::cross3(v0, axis);
//            p1 = c.center - axis * c.height; // point on  plane
//            p1 = p1 + v0 * c.radius; // assumed intersection point
//            d0 = cg::dot3(p.n, p1) - p.d;
//            if (d0 <= 0)
//            {
//                cg::collision* collision = &collisions.push_back();
//                collision->normal = p.n;
//                collision->penetration = cg::abs(d0);
//                collision->point = p1 + p.n * collision->penetration;
//                return true;
//            }
//        }
        return false;
    }
}}
