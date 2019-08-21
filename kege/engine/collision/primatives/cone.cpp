/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       cone.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "aabb.hpp"
#include "cone.hpp"
#include "sphere.hpp"
namespace kege{namespace cg{
    
    bool ComputeCollision(cg::collisions& collisions, cg::aabb& aabb, cg::cone& cone)
    {
        cg::point3 point;
        cg::CLOSEST_POINT_AABB(point, cone.origin, aabb);
        
        /*
         compute center point in cone that makes a line with sphere center, a line that is perpendicular to cone direction vector
         */
        cg::vec3 norm = point - cone.origin;
        /*
         using vector project technique with unit vector cone.axis give project length of vector (norm)
         variable (dist) holds project length
         */
        float  height = cg::dot3(cone.axis, norm);
        /*
         center is the disk center point in cone that make line with sphere.center.
         */
        cg::point3 p0 = cone.origin + cone.axis * height;
        /*
         center and sphere.center makes line that is perpendicular with cone.axis.
         square length of line
         */
        double length = cg::magn3sq(point - p0);
        /*
         ckeck if sphere is in cylinder bound of cone. if sphere is on or inside cone circular bound then continue testing
         */
        if (cg::sq(cone.radius) - length < 0) return false;
        
        cg::point3 center = (aabb.max + aabb.min) * 0.5f;
        cg::vec3 v = point - center;
        float size = (aabb.min.y - aabb.max.y) * 0.5f;
        /*
         first check is to see if sphere is in front of cone
         other wise the sphere maybe intersecting the lower parts of cone
         */
        if (v.y <= size)
        {
            /*
             length hold the triangle proportion base distance below center point
             */
            cg::point3 p1;
            float cone_slope = sqrt(cg::sq(cone.radius) + cg::sq(cone.height));
            /*
             length hold the triangle proportion base distance below center point
             */
            length = sqrt(length);
            length = (cone.radius * length) / cone.height;
            /*
             computer point p0 that will make the surface normal vecotr with sphere center
             */
            p1 = p0 - cone.axis * length;
            
            /*
             using proportational triangles to compute distance between p[0] and cone surface
             */
            norm = p1 - cone.origin;
            float simu_slope = cone.height - cg::dot3(cone.axis, norm);
            float dist = (cone.radius * simu_slope) / cone_slope;
            
            /*
             compute surface normal
             */
            norm = point - p1;
            length = cg::magn3(norm);
            
            if (length == 0)
            {
                norm = cone.axis;
                size = cone.height - height;
                length = 1.0f;
            }
            else
            {
                size = dist - length;
            }
            
            if (size >= 0)
            {
                cg::collision* collision = &collisions.push_back();
                collision->penetration = size;
                collision->normal = norm / length;
                collision->point = p1 + collision->normal * dist;
                return true;
            }
        }
        /*
         if distance height is less than sphere radius, then sphere is intersecting the botton end of the cone
         */
        else if (-v.y >= -size)
        {
            cg::collision* collision = &collisions.push_back();
            collision->penetration = aabb.max.y - cone.origin.y;
            collision->normal = -cone.axis;
            collision->point = point;
            return true;
        }
        else if (height == 0)
        {
            cg::collision* collision = &collisions.push_back();
            collision->penetration = cg::invrs(sqrt(length));
            collision->normal = norm / collision->penetration;
            collision->point = point;
            return true;
        }
        
        return false;
    }
    
    bool ComputeCollision(cg::collisions& collisions, cg::sphere& sphere, cg::cone& cone)
    {
        /*
         compute center point in cone that makes a line with sphere center, a line that is perpendicular to cone direction vector
         */
        cg::vec3 line = sphere.center - cone.origin;
        /*
         using vector project technique with unit vector cone.axis give project length of vector (norm)
         variable (dist) holds project length
         */
        float  dist = cg::dot3(cone.axis, line);
        /*
         center is the disk center point in cone that make line with sphere.center.
         */
        cg::point3 center = cone.origin + cone.axis * dist;
        /*
         center and sphere.center makes line that is perpendicular with cone.axis
         */
        line = sphere.center - center;
        /*
         square length of line
         */
        double line_length = cg::dot3(line, line);
        /*
         compute distance between dist and cone
         */
        double length = cg::sq(cone.radius + sphere.radius) - line_length;
        /*
         ckeck if sphere is in cylinder bound of cone. if sphere is on or inside cone circular bound then continue testing
         */
        if (length >= 0)
        {
            length = cg::abs(dist);
            /*
             first check is to see if sphere is in front of cone
             other wise the sphere maybe intersecting the lower parts of cone
             */
            if (length <= (sphere.radius + cone.height) && dist >= 0.0f)
            {
                cg::point3 p[3];
                float hypotenuse[2];
                /*
                 length hold the triangle proportion base distance below center point
                 */
                length = sqrt(line_length);
                length = (cone.radius * length) / cone.height;
                /*
                 computer point p0 that will make the surface normal vecotr with sphere center
                 */
                p[0]  = center - cone.axis * length;
                /*
                 using proportational triangles to compute distance between p[0] and cone surface
                 */
                hypotenuse[0] = sqrt(cg::sq(cone.radius) + cg::sq(cone.height));
                hypotenuse[1] = cone.height - cg::dot3(cone.axis, p[0] - cone.origin);
                length = (cone.radius * hypotenuse[1]) / hypotenuse[0];
                /*
                 compute surface normal
                 */
                line = cg::normalize3(sphere.center - p[0]);
                /*
                 compute intersection points on cone and sphere
                 */
                p[1] = p[0] + line * length;
                p[2] = sphere.center - line * sphere.radius;
                dist = cg::dot3(line, p[1] - p[2]);
                /*
                 if distance between both intersection points is greater than zero then sphere intersect cone
                 */
                //printf("%f (%f %f %f)\n",hypotenuse[1], line.x, line.y, line.z);
                //kege::Singleton::Get<gfx::DebugRenderer>()->RenderLine(p[1], p[1]+line*3, cg::vec3::one);
                if (dist >= 0)
                {
                    cg::collision* collision = &collisions.push_back();
                    collision->penetration = dist;
                    collision->normal      = line;
                    collision->point       = p[1];
                    return true;
                }
            }
            /*
             if distance height is less than sphere radius, then sphere is intersecting the botton end of the cone
             */
            float penetration = sphere.radius - length;
            if (penetration >= 0.0f)
            {
                cg::collision* collision = &collisions.push_back();
                collision->normal      = -cone.axis;
                collision->penetration = penetration;
                collision->point       = sphere.center + cone.axis * sphere.radius;
                return true;
            }
        }
        return false;
    }
}}
