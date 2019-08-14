//
//  mat44.cpp
//  column-major
//
//  Created by Kenneth A Esdaile on 7/12/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#include "../../graphics/cgmath/mat44.hpp"
namespace kege{namespace cg{
    
    cgmvec3 euler_angle(const cgmmat44 &m)
    {
        //check for gimbal lock
        if (EPSILON > cg::abs(m.m02 - (-1.0f)))
        {
            cg::real x = 0; //gimbal lock, value of x doesn't matter
            cg::real y = _PI_ / 2;
            cg::real z = x + atan2(m.m10, m.m20);
            return { x, y, z };
        }
        else if (EPSILON > cg::abs(m.m02 - 1.0f))
        {
            cg::real x = 0;
            cg::real y = -_PI_ / 2;
            cg::real z = -x + atan2(-m.m10, -m.m20);
            return { x, y, z };
        }
        else
        { //two solutions exist
            cg::real x1  = -asin(m.m02);
            cg::real x2  = _PI_ - x1;
            
            cg::real cx1 = cos(x2);
            cg::real cx2 = cos(x2);
            
            cg::real y1 = atan2(m.m12 / cx1, m.m22 / cx1);
            cg::real y2 = atan2(m.m12 / cx2, m.m22 / cx2);
            cg::real z1 = atan2(m.m01 / cx1, m.m00 / cx1);
            cg::real z2 = atan2(m.m01 / cx2, m.m00 / cx2);
            
            //choose one solution to return
            //for example the "shortest" rotation
            if ((cg::abs(x1) + cg::abs(y1) + cg::abs(z1)) <=
                (cg::abs(x2) + cg::abs(y2) + cg::abs(z2)))
            {
                return cgmvec3( x1, y1, z1 );
            }
            else
            {
                return cgmvec3( x2, y2, z2 );
            }
        }
    }
    void lookat(cgmmat44& m, const cgmvec3 &eye, const cgmvec3 &target, const cgmvec3 &up)
    {
        // forward-vector
        m.m02 = target.x - eye.x;
        m.m12 = target.y - eye.y;
        m.m22 = target.z - eye.z;
        
        float distsq = cg::invrs(m.m02*m.m02 + m.m12*m.m12 + m.m22*m.m22);
        distsq = sqrtf( distsq );
        m.m02 *= distsq;
        m.m12 *= distsq;
        m.m22 *= distsq;
        
        // right-vector - crossprod of up and forward
        m.m00 = (up.y*m.m22 - up.z*m.m12);
        m.m10 = (up.z*m.m02 - up.x*m.m22);
        m.m20 = (up.x*m.m12 - up.y*m.m02);
        
        // up-vector - crossprod of right and forward
        m.m01 = (m.m12*m.m20 - m.m22*m.m10);
        m.m11 = (m.m22*m.m00 - m.m02*m.m20);
        m.m21 = (m.m02*m.m10 - m.m12*m.m00);
        
        // position-vector
        m.m30 = -(eye.x*m.m00 + eye.y*m.m10 + eye.z*m.m20);
        m.m31 = -(eye.x*m.m01 + eye.y*m.m11 + eye.z*m.m21);
        m.m32 = -(eye.x*m.m02 + eye.y*m.m12 + eye.z*m.m22);
    }
    
    cgmmat44 persp_proj(cg::real fov, cg::real aspect, cg::real znear, cg::real zfar)
    {
        cg::real ymax = znear * tan(cg::deg2rad(fov/2.0));
        cg::real xmax = ymax * aspect;
        return persp_proj(-xmax, xmax, ymax, -ymax, znear, zfar);
    }
    
    cgmmat44 perspproj(cg::real fov, cg::real aspect, cg::real znear, cg::real zfar)
    {
        cg::real ymax = znear * tan(cg::deg2rad(fov/2.0));
        cg::real xmax = ymax * aspect;
        return perspproj(-xmax, xmax, ymax, -ymax, znear, zfar);
    }
    
}}
