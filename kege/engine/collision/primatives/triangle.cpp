/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       triangle.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "segment.hpp"
#include "triangle.hpp"
namespace kege{namespace cg{
    
    
    /** Test if 2D point P lies inside the counterclockwise 2D triangle ABC */
    int PointInTriangle(const cg::point2& p, const cg::point2& a, const cg::point2& b, const cg::point2& c)
    {
        // If P to the right of AB then outside triangle
        if (cg::cross2(p - a, b - a) < 0.0f) return 0;
        // If P to the right of BC then outside triangle
        if (cg::cross2(p - b, c - b) < 0.0f) return 0;
        // If P to the right of CA then outside triangle
        if (cg::cross2(p - c, a - c) < 0.0f) return 0;
        // Otherwise P must be in (or on) the triangle
        return 1;
    }
    
    /** Test if point P lies inside the counterclockwise triangle ABC */
    int POINT_in_TRIANGLE(const cg::point3& p, const cg::triangle& t)
    {
        cg::triangle k = t;
        // Translate point and triangle so that point lies at origin
        k.a -= p;
        k.b -= p;
        k.c -= p;
        // Compute normal vectors for triangles pab and pbc
        cg::vec3 u = cg::cross3(k.b, k.c);
        cg::vec3 v = cg::cross3(k.c, k.a);
        // Make sure they are both pointing in the same direction
        if (cg::dot3(u, v) < 0.0f) return 0;
        // Compute normal vector for triangle pca
        cg::vec3 w = cg::cross3(k.a, k.b);
        // Make sure it points in the same direction as the first two
        if (cg::dot3(u, w) < 0.0f) return 0;
        // Otherwise P must be in (or on) the triangle
        return 1;
    }
    
    
    /** Given point p and triangle abc return point closest on triangle closest to point p. */
    cg::point3 CLOSEST_POINT_TRIANGLE(const cg::point3& p, const cg::triangle& t)
    {
        cg::vec3 ab = t.b - t.a;
        cg::vec3 ac = t.c - t.a;
        cg::vec3 ap = t.c - t.b;
        float d1 = cg::dot3(ab, ap);
        float d2 = cg::dot3(ac, ap);
        if (d1 <= 0.0f && d2 <= 0.0f) return t.a; // barycentric coordinates (1,0,0)
        
        // Check if P in vertex region outside B
        cg::vec3 bp = p - t.b;
        float d3 = cg::dot3(ab, bp);
        float d4 = cg::dot3(ac, bp);
        if (d3 >= 0.0f && d4 <= d3) return t.b; // barycentric coordinates (0,1,0)
        
        // Check if P in edge region of AB, if so return projection of P onto AB
        float vc = d1*d4 - d3*d2;
        if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
        {
            float v = d1 / (d1 - d3);
            return t.a + v * ab; // barycentric coordinates (1-v,v,0)
        }
        
        // Check if P in vertex region outside C
        cg::vec3 cp = p - t.c;
        float d5 = cg::dot3(ab, cp);
        float d6 = cg::dot3(ac, cp);
        if (d6 >= 0.0f && d5 <= d6) return t.c; // barycentric coordinates (0,0,1)
        
        // Check if P in edge region of AC, if so return projection of P onto AC
        float vb = d5*d2 - d1*d6;
        if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
        {
            float w = d2 / (d2 - d6);
            return t.a + w * ac; // barycentric coordinates (1-w,0,w)
        }
        
        // Check if P in edge region of BC, if so return projection of P onto BC
        float va = d3*d6 - d5*d4;
        if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
        {
            float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
            return t.b + w * (t.c - t.b); // barycentric coordinates (0,1-w,w)
        }
        
        // P inside face region. Compute Q through its barycentric coordinates (u,v,w)
        float denom = 1.0f / (va + vb + vc);
        float v = vb * denom;
        float w = vc * denom;
        return t.a + ab * v + ac * w; //=u*a+v*b+w*c,u=va*denom=1.0f-v-w
    }
    
    /**
     * Intersecting Line Against Triangle
     * Given line pq and ccw triangle abc, return whether line pierces triangle. If
     * so, also return the barycentric coordinates (u,v,w) of the intersection point
     */
    int LINE_vs_TRIANGLE(const cg::segment& l, const cg::triangle& t, float &u, float &v, float &w)
    {
        cg::point3 pq = l.a - l.b;
        cg::point3 pa = t.a - l.a;
        cg::point3 pb = t.b - l.a;
        cg::point3 pc = t.c - l.a;
        // Test if pq is inside the edges bc, ca and ab. Done by testing
        // that the signed tetrahedral volumes, computed using scalar triple
        // products, are all positive
        u = cg::triple_product(pq, pc, pb);
        if (u < 0.0f) return 0;
        v = cg::triple_product(pq, pa, pc);
        if (v < 0.0f) return 0;
        w = cg::triple_product(pq, pb, pa);
        if (w < 0.0f) return 0;
        // Compute the barycentric coordinates (u, v, w) determining the
        // intersection point r, r = u*a + v*b + w*c
        float denom = 1.0f / (u + v + w);
        u *= denom;
        v *= denom;
        w *= denom; // w = 1.0f - u - v;
        return 1;
    }
    
    /**
     * Intersecting Ray or Segment Against Triangle
     * Given segment pq and triangle abc, returns whether segment intersects
     * triangle and if so, also returns the barycentric coordinates (u,v,w)
     * of the intersection point
     */
    int SEGMENT_vs_TRIANGLE(const cg::segment& s, const cg::triangle& k, float &u, float &v, float &w, float &t)
    {
        cg::vec3 ab = k.b - k.a;
        cg::vec3 ac = k.c - k.a;
        cg::vec3 qp = s.a - s.b;
        // Compute triangle normal. Can be precalculated or cached if
        // intersecting multiple segments against the same triangle
        cg::vec3 n = cg::cross3(ab, ac);
        // Compute denominator d. If d <= 0, segment is parallel to or points
        // away from triangle, so exit early
        float d = cg::dot3(qp, n);
        if (d <= 0.0f) return 0;
        // Compute intersection t value of pq with plane of triangle. A ray
        // intersects iff 0 <= t. Segment intersects iff 0 <= t <= 1. Delay
        // dividing by d until intersection has been found to pierce triangle
        cg::vec3 ap = s.a - k.a;
        t = cg::dot3(ap, n);
        if (t < 0.0f) return 0;
        if (t > d) return 0; // For segment; exclude this code line for a ray test
        // Compute barycentric coordinate components and test if within bounds
        cg::vec3 e = cg::cross3(qp, ap);
        v = cg::dot3(ac, e);
        if (v < 0.0f || v > d) return 0;
        w = -cg::dot3(ab, e);
        if (w < 0.0f || v + w > d) return 0;
        // Segment/ray intersects triangle. Perform delayed division and
        // compute the last barycentric coordinate component
        float ood = 1.0f / d;
        t *= ood;
        v *= ood;
        w *= ood;
        u = 1.0f - v - w;
        return 1;
    }
}}
