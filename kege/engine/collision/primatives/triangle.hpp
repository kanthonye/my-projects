/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       triangle.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef triangle_hpp
#define triangle_hpp
#include "cgm.hpp"
namespace kege{namespace cg{
    
    class triangle
    {
    public:
        cg::point3 a;
        cg::point3 b;
        cg::point3 c;
    };
    
    /** Test if 2D point P lies inside the counterclockwise 2D triangle ABC */
    int PointInTriangle(const cg::point2& p, const cg::point2& a, const cg::point2& b, const cg::point2& c);
    
    /** Test if point P lies inside the counterclockwise triangle ABC */
    int POINT_in_TRIANGLE(const cg::point3& p, const cg::triangle& t);
    
    
    /** Given point p and triangle abc return point closest on triangle closest to point p. */
    cg::point3 CLOSEST_POINT_TRIANGLE(const cg::point3& p, const cg::triangle& t);
    
    /**
     * Intersecting Line Against Triangle
     * Given line pq and ccw triangle abc, return whether line pierces triangle. If
     * so, also return the barycentric coordinates (u,v,w) of the intersection point
     */
    int LINE_vs_TRIANGLE(const cg::segment& l, const cg::triangle& t, float &u, float &v, float &w);
    
    /**
     * Intersecting Ray or Segment Against Triangle
     * Given segment pq and triangle abc, returns whether segment intersects
     * triangle and if so, also returns the barycentric coordinates (u,v,w)
     * of the intersection point
     */
    int SEGMENT_vs_TRIANGLE(const cg::segment& s, const cg::triangle& k, float &u, float &v, float &w, float &t);
}}
#endif /* triangle_hpp */
