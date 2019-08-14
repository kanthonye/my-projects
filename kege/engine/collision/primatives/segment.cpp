/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       segment.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "plane.hpp"
#include "segment.hpp"
#include "triangle.hpp"
namespace kege{namespace cg{
    
    /** Returns the squared distance between point c and segment ab */
    float SQDIST_POINT_vs_SEGMENT(const cg::vec3& p, const cg::vec3& sa, const cg::vec3& sb)
    {
        const cg::vec3& ab = sb - sa;
        const cg::vec3& ac = p - sa;
        const cg::vec3& bc = p - sb;
        float e = cg::dot3(ac, ab);
        // Handle cases where c projects outside ab
        if (e <= 0.0f)
        {
            return cg::dot3(ac, ac);
        }
        float f = cg::dot3(ab, ab);
        if (e >= f)
        {
            return cg::dot3(bc, bc);
        }
        // Handle cases where c projects onto ab
        return cg::dot3(ac, ac) - e * e / f;
    }
    
    
    /**
     * Given segment s and point p, computes closest point d on s.
     * Also returns t for the position of d, d(t) = a + t*(b - a)
     */
    void CLOSEST_POINT_to_SEGMENT(float &t, cg::point3 &d, const cg::point3& p, const cg::segment& s)
    {
        cg::vec3 ab = s.b - s.a;
        // Project c onto ab, computing parameterized position d(t) = a + t*(b – a)
        t = cg::dot3(p - s.a, ab) / cg::dot3(ab, ab);
        // If outside segment, clamp t (and therefore d) to the closest endpoint
        if (t < 0.0f) t = 0.0f;
        if (t > 1.0f) t = 1.0f;
        // Compute projected position from the clamped t
        d = s.a + t * ab;
    }
    
    /**
     * Computes closest points C1 and C2 of S1(s)=P1+s*(Q1-P1) and
     * S2(t)=P2+t*(Q2-P2), returning s and t. Function result is squared
     * distance between between S1(s) and S2(t)
     */
    float CLOSEST_POINT_btw_SEGMENTS(float &t1, float &t2, cg::segment& s, const cg::segment& p, const cg::segment& q)
    {
        cg::vec3 d1 = q.a - p.a; // Direction vector of segment S1
        cg::vec3 d2 = q.b - p.b; // Direction vector of segment S2
        cg::vec3 r  = p.a - p.b;
        float a = cg::dot3(d1, d1); // Squared length of segment S1, always nonnegative
        float e = cg::dot3(d2, d2); // Squared length of segment S2, always nonnegative
        float f = cg::dot3(d2, r);
        
        // Check if either or both segments degenerate into points
        if (a <= EPSILON && e <= EPSILON)
        {
            // Both segments degenerate into points
            t1 = t2 = 0.0f;
            s.a = p.a;
            s.b = p.b;
            cg::vec3 k  = s.a - s.b;
            return cg::dot3(k,k);
        }
        if (a <= EPSILON)
        {
            // First segment degenerates into a point
            t1 = 0.0f;
            t2 = f/e; // s = 0 = > t = (b*s + f) / e = f / e
            t2 = cg::clamp(t2, 0.0f, 1.0f);
        }
        else
        {
            float c = cg::dot3(d1, r);
            if (e <= EPSILON)
            {
                // Second segment degenerates into a point
                t2 = 0.0f;
                t1 = cg::clamp(-c/a,0.0f,1.0f); //t=0=>s=(b*t-c)/a=-c/a
                
            }
            else
            {
                // The general nondegenerate case starts here
                float b = cg::dot3(d1, d2);
                float denom = a*e-b*b; // Always nonnegative
                // If segments not parallel, compute closest point on L1 to L2 and
                // clamp to segment S1. Else pick arbitrary s (here 0)
                if (denom != 0.0f)
                {
                    t1 = cg::clamp((b*f - c*e) / denom, 0.0f, 1.0f);
                }
                else t1 = 0.0f;
                // Compute point on L2 closest to S1(s) using
                // t = Dot((P1 + D1*s) - P2,D2) / Dot(D2,D2) = (b*s + f) / e
                t2 = (b*t1 + f) / e;
                // If t in [0,1] done. Else clamp t, recompute s for the new value
                // of t using s = Dot((P2 + D2*t) - P1,D1) / Dot(D1,D1)= (t*b - c) / a // and clamp s to [0, 1]
                if (t2 < 0.0f)
                {
                    t2 = 0.0f;
                    t1 = cg::clamp(-c / a, 0.0f, 1.0f);
                }
                else if (t2 > 1.0f)
                {
                    t2 = 1.0f;
                    t1 = cg::clamp((b - c) / a, 0.0f, 1.0f);
                }
            }
        }
        s.a = p.a + d1 * t1;
        s.b = p.b + d2 * t2;
        cg::vec3 k  = s.a - s.b;
        return cg::dot3(k,k);
    }
    
    /**
     * Intersecting Line Against Quadrilateral
     * Given line p0-p1 and ccw quadrilateral abcd, return whether the line
     * pierces the triangle. If so, also return the point r of intersection
     */
    int LINE_vs_QUAD(const cg::point3& p0, const cg::point3& p1, const cg::point3& q0, const cg::point3& q1, const cg::point3& q2, const cg::point3& q3, cg::point3 &r)
    {
        cg::vec3 l0 = p1 - p0;
        cg::vec3 l1 = q0 - p0;
        cg::vec3 l2 = q1 - p0;
        cg::vec3 l3 = q2 - p0;
        // Determine which triangle to test against by testing against diagonal first
        cg::vec3 m = cg::cross3(l3, l0);
        float v = cg::dot3(l1, m); // ScalarTriple(pq, pa, pc);
        if (v >= 0.0f)
        {
            // Test intersection against triangle abc
            float u = -cg::dot3(l2, m); // ScalarTriple(pq, pc, pb);
            if (u < 0.0f) return 0;
            float w = cg::triple_product(l0, l2, l1);
            if (w < 0.0f) return 0;
            // Compute r, r = u*a + v*b + w*c, from barycentric coordinates (u, v, w)
            float denom = 1.0f / (u + v + w);
            u *= denom;
            v *= denom;
            w *= denom; // w = 1.0f - u - v;
            r = u*q0 + v*q1 + w*q2;
        }
        else
        {
            // Test intersection against triangle dac
            cg::vec3 pd = q3 - p0;
            float u = cg::dot3(pd, m); // ScalarTriple(pq, pd, pc);
            if (u < 0.0f) return 0;
            float w = cg::triple_product(l0, l1, pd);
            if (w < 0.0f) return 0;
            v = -v;
            // Compute r, r = u*a + v*d + w*c, from barycentric coordinates (u, v, w)
            float denom = 1.0f / (u + v + w);
            u *= denom;
            v *= denom;
            w *= denom; // w = 1.0f - u - v;
            r = u*q0 + v*q3 + w*q2;
        }
        return 1;
    }
    
    /**
     * Intersect Ray or Segment Against Convex Polyhedron
     * Intersect segment S(t)=A+t(B-A), 0<=t<=1 against convex polyhedron specified
     * by the n halfspaces defined by the planes p[]. On exit tfirst and tlast
     * define the intersection, if any
     */
    int SEGMENT_vs_POLYHEDRON(const cg::segment& l, const cg::plane p[], int n, float &tfirst, float &tlast)
    {
        
        float denom, dist, t;
        // Compute direction vector for the segment
        cg::vec3 d = l.b - l.a;
        // Set initial interval to being the whole segment. For a ray, tlast should be
        // set to +FLT_MAX. For a line, additionally tfirst should be set to –FLT_MAX
        tfirst = 0.0f;
        tlast  = 1.0f;
        // Intersect segment against each plane
        for (int i = 0; i < n; i++)
        {
            denom = cg::dot3(p[i].n, d);
            dist = p[i].d - cg::dot3(p[i].n, l.a);
            // Test if segment runs parallel to the plane
            if (denom == 0.0f) {
                // If so, return “no intersection” if segment lies outside plane
                if (dist > 0.0f) return 0;
            } else
            {
                // Compute parameterized t value for intersection with current plane
                t = dist / denom;
                if (denom < 0.0f)
                {
                    // When entering halfspace, update tfirst if t is larger
                    if (t > tfirst) tfirst = t;
                }
                else
                {
                    // When exiting halfspace, update tlast if t is smaller
                    if (t < tlast) tlast = t;
                }
                // Exit with “no intersection” if intersection becomes empty
                if (tfirst > tlast) return 0;
            }
        }
        // A nonzero logical intersection, so the segment intersects the polyhedron
        return 1;
    }
}}
