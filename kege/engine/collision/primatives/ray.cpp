/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ray.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "ray.hpp"
#include "aabb.hpp"
namespace kege{namespace cg{
    
    
    /**
     * Intersect ray R(t) = p + t*d against AABB a. When intersecting,
     * return intersection distance tmin and point q of intersection
     */
    int Collision_AABB_RAY(cg::collisions& collisions, const cg::aabb& a, const cg::ray& ray)
    {
        int  i = 0;
        int whichPlane;
        char inside = TRUE;
        char quadrant[3];
        double maxT[3];
        double candidatePlane[3];
        const char NUMDIM = 3;
        const char RIGHT  = 0;
        const char LEFT   = 1;
        const char MIDDLE = 2;
        /* Find candidate planes; this loop can be avoided if
         rays cast all from the eye(assume perpsective view) */
        for (i=0; i<NUMDIM; i++)
        {
            if(ray.origin[i] < a.min[i])
            {
                quadrant[i] = LEFT;
                candidatePlane[i] = a.min[i];
                inside = FALSE;
            }
            else if (ray.origin[i] > a.max[i])
            {
                quadrant[i] = RIGHT;
                candidatePlane[i] = a.max[i];
                inside = FALSE;
            }
            else
            {
                quadrant[i] = MIDDLE;
            }
        }
        cg::point3 point;
        /* Ray origin inside bounding box */
        if(inside)
        {
            point = ray.origin;
            return (TRUE);
        }
        
        
        /* Calculate T distances to candidate planes */
        for (i = 0; i < NUMDIM; i++)
        {
            if (quadrant[i] != MIDDLE && ray.dir[i] !=0.)
                maxT[i] = (candidatePlane[i]-ray.origin[i]) / ray.dir[i];
            else
                maxT[i] = -1.;
        }
        /* Get largest of the maxT's for final choice of intersection */
        whichPlane = 0;
        for (i = 1; i < NUMDIM; i++)
        {
            if (maxT[whichPlane] < maxT[i])
                whichPlane = i;
        }
        /* Check final candidate actually inside box */
        if (maxT[whichPlane] < 0.) return (FALSE);
        for (i = 0; i < NUMDIM; i++)
        {
            if (whichPlane != i)
            {
                point[i] = ray.origin[i] + maxT[whichPlane] *ray.dir[i];
                if (point[i] < a.min[i] || point[i] > a.max[i])
                    return (FALSE);
            }
            else
            {
                point[i] = candidatePlane[i];
            }
        }
        
        cg::collision* collision = &collisions.push_back();
        collision->penetration = 0;
        collision->point = point;
        collision->normal = -ray.dir;
        return (TRUE); /* ray hits box */
    }
}}
