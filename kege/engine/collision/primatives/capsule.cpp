/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       capsule.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "sphere.hpp"
#include "capsule.hpp"
#include "segment.hpp"
namespace kege{namespace cg{

    /** test if a Sphere and Capsule intersect. */
    int SPHERE_vs_CAPSULE(const cg::sphere& s, const cg::capsule& capsule)
    {
        // Compute (squared) distance between sphere center and capsule line segment
        float dist2 = SQDIST_POINT_vs_SEGMENT(s.center, capsule.a, capsule.b);
        // If (squared) distance smaller than (squared) sum of radii, they collide
        float radius = s.radius + capsule.radius;
        return dist2 <= radius * radius;
    }

//    /** test if a Capsule and Capsule intersect. */
//    int CAPSULE_vs_CAPSULE(const cg::capsule& capsule1, const cg::capsule& capsule2)
//    {
//        // Compute (squared) distance between the inner structures of the capsules
//        float s, t;
//        cg::point3 c1, c2;
//        float dist2 = CLOSEST_POINT_SEGMENT_vs_SEGMENT(capsule1.a, capsule1.b, capsule2.a, capsule2.b, s, t, c1, c2);
//        // If (squared) distance smaller than (squared) sum of radii, they collide
//        float radius = capsule1.radius + capsule2.radius;
//        return dist2 <= radius * radius;
//    }
}}

