/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       segment.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef segment_hpp
#define segment_hpp
#include "collision.hpp"
namespace kege{namespace cg{
    
    class segment
    {
    public:
        cg::point3 a;
        cg::point3 b;
    };
    
    /** Returns the squared distance between point c and segment ab */
    float  SQDIST_POINT_vs_SEGMENT(const cg::vec3& p, const cg::vec3& sa, const cg::vec3& sb);
    
    
    /**
     * Given segment s and point p, computes closest point d on s.
     * Also returns t for the position of d, d(t) = a + t*(b - a)
     */
    void CLOSEST_POINT_to_SEGMENT(float &t, cg::point3 &d, const cg::point3& p, const cg::segment& s);
    
    /**
     * Computes closest points C1 and C2 of S1(s)=P1+s*(Q1-P1) and
     * S2(t)=P2+t*(Q2-P2), returning s and t. Function result is squared
     * distance between between S1(s) and S2(t)
     */
    float CLOSEST_POINT_btw_SEGMENTS(float &t1, float &t2, cg::segment& s, const cg::segment& p, const cg::segment& q);
    
    /**
     * Intersecting Line Against Quadrilateral
     * Given line p0-p1 and ccw quadrilateral abcd, return whether the line
     * pierces the triangle. If so, also return the point r of intersection
     */
    int LINE_vs_QUAD(const cg::segment& l, const cg::point3& q0, const cg::point3& q1, const cg::point3& q2, const cg::point3& q3, cg::point3 &r);
    
    /**
     * Intersect Ray or Segment Against Convex Polyhedron
     * Intersect segment S(t)=A+t(B-A), 0<=t<=1 against convex polyhedron specified
     * by the n halfspaces defined by the planes p[]. On exit tfirst and tlast
     * define the intersection, if any
     */
    int SEGMENT_vs_POLYHEDRON(const cg::segment& l, const cg::plane p[], int n, float &tfirst, float &tlast);
}}
#endif /* segment_hpp */
