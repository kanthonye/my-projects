//
//  quat.cpp
//  column-major
//
//  Created by Kenneth A Esdaile on 7/12/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#include "../../../graphics/core/cgmath/quat.hpp"
namespace kege{namespace cg{
    
    void normalize (cgmquat &p, const cgmquat &q)
    {
        float m = cg::dot(p,p);
        if (m == 0)
        {
            p.x = q.x;
            p.y = q.y;
            p.z = q.z;
            if (0.0f > q.w) p.w = -1.0f;
            else p.w = 1.0f;
        }
        else
        {
            m = 1.0f / sqrt( m );
            p.x = q.x*m;
            p.y = q.y*m;
            p.z = q.z*m;
            p.w = q.w*m;
        }
    }
    
    cgmquat log(const cgmquat &q)
    {
        float m, s;
        
        m = acosf( q.w );
        s = sinf( m );
        
        if (0.0f != s) {
            s  = m / s;
            return cgmquat(0.0f, q.x*s, q.y*s, q.z*s);
        } else {
            return cgmquat(0.0f, 0.0f, 0.0f, 0.0f);
        }
    }
    
    cgmquat slerp(const cgmquat& start, const cgmquat& end, double t)
    {
        // slerp = (q0 * sin((1-t) + theta) + q1 * sin(theta)) / sin(theta)
        // Compute the cosine of the angle between the two vectors.
        // cos(theta/2) = qa.w*qb.w + qa.x*qb.x + qa.y*qb.y+ qa.z*qb.z
        double dot = cg::dot(start, end);

        // If the dot product is negative, slerp won't take
        // the shorter path. Note that v1 and -v1 are equivalent when
        // the negation is applied to all four components. Fix by
        // reversing one quaternion.
        cgmquat q = end;
        if (dot < 0.0f)
        {
            q = -q;
            dot = -dot;
        }

        if (dot > 0.9995)
        {
            // If the inputs are too close, linearly interpolate
            return cg::lerp(start, q, t);
        }

        // Since dot is in range [0, DOT_THRESHOLD], acos is safe
        double theta_0 = acos(dot);        // theta_0 = angle between input vectors
        double theta = theta_0*t;          // theta = angle between v0 and result
        double sin_theta = sin(theta);     // compute this value only once
        double sin_theta_0 = sin(theta_0); // compute this value only once

        double s0 = cos(theta) - dot * sin_theta / sin_theta_0;  // == sin(theta_0 - theta) / sin(theta_0)
        double s1 = sin_theta / sin_theta_0;

        return (s0 * start) + (s1 * q);
    }
    
    cgmquat pow(const cgmquat &q, float exponent)
    {
        // Check for the case of an identity quaternion.
        // This will protect against divide by zero
        if (fabs(q.w) > .9999f) {
            return q;
        }
        // Extract the half angle alpha (alpha = theta/2)
        float alpha = acos(q.w);
        // Compute new alpha value
        float newAlpha = alpha * exponent;
        // Compute new w value
        cgmquat result;
        result.w = cos(newAlpha);
        // Compute new xyz values
        float mult = sin(newAlpha) / sin(alpha); result.x = q.x * mult;
        result.y = q.y * mult;
        result.z = q.z * mult;
        // Return it
        return result;
    }
    
    /* convert Euler angles to quaternion */
    cgmquat euler_to_quat(cg::real pitch, cg::real yaw, cg::real roll)
    {
        float rad_pitch = cg::deg2rad(0.5f * pitch);
        float rad_yaw   = cg::deg2rad(0.5f * yaw);
        float rad_roll  = cg::deg2rad(0.5f * roll);
        
        const float cp = cos(rad_pitch);
        const float cy = cos(rad_yaw);
        const float cr = cos(rad_roll);
        
        const float sp = sin(rad_pitch);
        const float sy = sin(rad_yaw);
        const float sr = sin(rad_roll);
        
        const float w = cp * cy * cr + sp * sy * sr;
        const float x = sp * cy * cr - cp * sy * sr;
        const float y = cp * sy * cr + sp * cy * sr;
        const float z = cp * cy * sr - sp * sy * cr;
        
        return cgmquat( w, x, y, z );
    }
    
    
    cgmquat quatsqrt(const cgmquat &pqA)
    {
        cgmquat qT;
        float fx, fy, fMag, fLen;
        fLen = sqrtf(pqA.x * pqA.x + pqA.y * pqA.y + pqA.w * pqA.w);
        
        fLen = (0.0f != fLen) ? 1.0f / fLen : 1.0f;
        qT.x = pqA.x * fLen;
        qT.y = pqA.z * fLen;
        qT.z = pqA.z;
        qT.w = pqA.w * fLen;
        
        fMag = 1.0f / sqrtf( qT.w * qT.w + qT.x * qT.x );
        fx   = sqrtf( (1.0f - qT.y) * 0.5f );
        fy   = sqrtf( (1.0f + qT.y) * 0.5f );
        fLen = sqrtf( fLen );
        
        return cgmquat
        (  qT.w * fLen * fy * fMag
         , qT.x* fLen * fx * fMag
         , fLen * fy
         , qT.z  );
    }
    
//    void quat_prods(cg::real r[9], const cgmquat& q)
//    {
//        // [xx,xy,xz,xw, yy,yz,yw, zz,zw]
//        r[0] = (q.x * q.x); // xx
//        r[1] = (q.x * q.y); // xy
//        r[2] = (q.x * q.z); // xz
//        r[3] = (q.w * q.x); // xw
//        
//        r[4] = (q.y * q.y); // yy
//        r[5] = (q.y * q.z); // yz
//        r[6] = (q.w * q.y); // yw
//        
//        r[7] = (q.z * q.z); // zz
//        r[8] = (q.w * q.z); // zw
//    }
    
    // quat to directional vectors transpose
    void quat2m33
    (  cg::real& m00, cg::real& m10, cg::real& m20
     , cg::real& m01, cg::real& m11, cg::real& m21
     , cg::real& m02, cg::real& m12, cg::real& m22
     , const cgmquat& q)
    {
        // this is column major but must make row major in function quat_to_mat44
        // | 1 - 2*qy2 - 2*qz2 | 2*qx*qy - 2*qz*qw | 2*qx*qz + 2*qy*qw |
        // | 2*qx*qy + 2*qz*qw | 1 - 2*qx2 - 2*qz2 | 2*qy*qz - 2*qx*qw |
        // | 2*qx*qz - 2*qy*qw | 2*qy*qz + 2*qx*qw | 1 - 2*qx2 - 2*qy2 |
        cg::real xx = (q.x * q.x);
        cg::real xy = (q.x * q.y);
        cg::real xz = (q.x * q.z);
        cg::real xw = (q.w * q.x);
        
        cg::real yy = (q.y * q.y);
        cg::real yz = (q.y * q.z);
        cg::real yw = (q.w * q.y);
        
        cg::real zz = (q.z * q.z);
        cg::real zw = (q.w * q.z);
        
//        m00 = 1 - (yy + zz) * 2.0;
//        m01 =     (xy - zw) * 2.0;
//        m02 =     (xz + yw) * 2.0;
//
//        m10 =     (xy + zw) * 2.0;
//        m11 = 1 - (xx + zz) * 2.0;
//        m12 =     (yz - xw) * 2.0;
//
//        m20 =     (xz - yw) * 2.0;
//        m21 =     (yz + xw) * 2.0;
//        m22 = 1 - (xx + yy) * 2.0;
        
        m00 = 1 - (yy + zz) * 2.0;
        m10 =     (xy - zw) * 2.0;
        m20 =     (xz + yw) * 2.0;

        m01 =     (xy + zw) * 2.0;
        m11 = 1 - (xx + zz) * 2.0;
        m21 =     (yz - xw) * 2.0;

        m02 =     (xz - yw) * 2.0;
        m12 =     (yz + xw) * 2.0;
        m22 = 1 - (xx + yy) * 2.0;
    }
    
    void quat_to_basis(cgmvec3 &r, cgmvec3 &u, cgmvec3 &f, const cgmquat& q)
    {
        cg::quat2m33(r.x, r.y, r.z,   u.x, u.y, u.z,   f.x, f.y, f.z, q);
    }
    
    void quat_to_mat33(cgmmat33 &m, const cgmquat& q)
    {
        cg::quat2m33
        (  m.m00, m.m10, m.m20
         , m.m01, m.m11, m.m21
         , m.m02, m.m12, m.m22
         , q );
    }
    
    // set quaternion rotation to matrix @mat.
    void quat_to_mat44(cgmmat44 &m, const cgmquat & q)
    {
        cg::quat2m33
        (  m.m00, m.m10, m.m20
         , m.m01, m.m11, m.m21
         , m.m02, m.m12, m.m22, q);
        
        m.m03 = 0.0;
        m.m13 = 0.0;
        m.m23 = 0.0;
        m.m30 = 0.0;
        m.m31 = 0.0;
        m.m32 = 0.0;
        m.m33 = 1.0;
    }
    
    cgmmat44 quat_to_mat44(const cgmquat & q)
    {
        cgmmat44 mat;
        cg::quat_to_mat44(mat,q);
        return mat;
    }
    
    cgmmat33 quat_to_mat33(const cgmquat & q)
    {
        cgmmat33 mat;
        quat_to_mat33(mat, q);
        return mat;
    }
    
    void mat33_to_quat(cgmquat &q, const cgmmat33 &m)
    {
        float trace = m.m00 + m.m11 + m.m22;
        if (trace > 0.0f)
        {
            float s = 0.5f / sqrtf(trace + 1.0f);
            q.w = 0.25f / s;
            q.x = (m.m12 - m.m21) * s;
            q.y = (m.m20 - m.m02) * s;
            q.z = (m.m01 - m.m10) * s;
        }
        // Negative diagonal
        if ( m.m00 > m.m11 && m.m00 > m.m22 )
        {
            float s = 2.0f * sqrtf(m.m00 - m.m11 - m.m22 +  1.0f);
            q.w = (m.m12 - m.m21) / s;
            q.x = 0.25f * s;
            q.y = (m.m10 + m.m01) / s;
            q.z = (m.m20 + m.m02) / s;
        }
        else if (m.m11 > m.m22)
        {
            float s = 2.0f * sqrtf(m.m11 - m.m00 - m.m22 +  1.0f);
            q.w = (m.m20 - m.m02) / s;
            q.x = (m.m10 + m.m01) / s;
            q.y = 0.25f * s;
            q.z = (m.m21 + m.m12) / s;
        }
        else
        {
            float s = 2.0f * sqrtf(m.m22 - m.m00 - m.m11 +  1.0f);
            q.w = (m.m01 - m.m10) / s;
            q.x = (m.m20 + m.m02) / s;
            q.y = (m.m21 + m.m12) / s;
            q.z = 0.25f * s;
        }
    }
    
    void mat44_to_quat(cgmquat &q, const cgmmat44 &m)
    {
        float trace = m.m00 + m.m11 + m.m22;
        if (trace > 0.0f)
        {
            float s = 0.5f / sqrtf(trace + 1.0f);
            q.w = 0.25f / s;
            q.x = (m.m12 - m.m21) * s;
            q.y = (m.m20 - m.m02) * s;
            q.z = (m.m01 - m.m10) * s;
        }
        // Negative diagonal
        if ( m.m00 > m.m11 && m.m00 > m.m22 )
        {
            float s = 2.0f * sqrtf(m.m00 - m.m11 - m.m22 +  1.0f);
            q.w = (m.m12 - m.m21) / s;
            q.x = 0.25f * s;
            q.y = (m.m10 + m.m01) / s;
            q.z = (m.m20 + m.m02) / s;
        }
        else if (m.m11 > m.m22)
        {
            float s = 2.0f * sqrtf(m.m11 - m.m00 - m.m22 +  1.0f);
            q.w = (m.m20 - m.m02) / s;
            q.x = (m.m10 + m.m01) / s;
            q.y = 0.25f * s;
            q.z = (m.m21 + m.m12) / s;
        }
        else
        {
            float s = 2.0f * sqrtf(m.m22 - m.m00 - m.m11 +  1.0f);
            q.w = (m.m01 - m.m10) / s;
            q.x = (m.m20 + m.m02) / s;
            q.y = (m.m21 + m.m12) / s;
            q.z = 0.25f * s;
        }
    }
    
    void euler_angle(const cgmquat& q, cg::real& roll, cg::real& pitch, cg::real& yaw)
    {
        // roll (x-axis rotation)
        double sinr = +2.0 * (q.w * q.x + q.y * q.z);
        double cosr = +1.0 - 2.0 * (q.x * q.x + q.y * q.y);
        roll = atan2(sinr, cosr);
        
        // pitch (y-axis rotation)
        double sinp = +2.0 * (q.w * q.y - q.z * q.x);
        if (fabs(sinp) >= 1)
            pitch = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
        else
            pitch = asin(sinp);
        
        // yaw (z-axis rotation)
        double siny = +2.0 * (q.w * q.z + q.x * q.y);
        double cosy = +1.0 - 2.0 * (q.y * q.y + q.z * q.z);
        yaw = atan2(siny, cosy);
    }
    
    /* convert Euler angles to quaternion */
    cgmvec3 euler_angle(cgmquat const& q)
    {
        float yaw = (2.0f * (q.w*q.x + q.z*q.y)) / (q.z*q.z - q.y*q.y - q.x*q.x + q.w*q.w);
        yaw = cg::deg2rad( atan(yaw) );
        
        float pitch = (q.w*q.y - q.x*q.z);
        pitch = cg::deg2rad( asin(pitch) );
        
        float roll = (2.0f *(q.x*q.y + q.w*q.z) / (q.z*q.z + q.y*q.y - q.x*q.x - q.w*q.w));
        roll = cg::deg2rad( atan(roll) );
        
        return cgmvec3(pitch, yaw, roll);
    }
    
    void view_matrix(cgmmat44& m, const cgmvec3& p, const cgmvec3& r, const cgmvec3& u, const cgmvec3& f)
    {
        m.m00 = r.x;
        m.m10 = r.y;
        m.m20 = r.z;
        m.m30 = -cg::dot3(r, p);
        
        m.m01 = u.x;
        m.m11 = u.y;
        m.m21 = u.z;
        m.m31 = -cg::dot3(u, p);
        
        m.m02 = f.x;
        m.m12 = f.y;
        m.m22 = f.z;
        m.m32 = -cg::dot3(f, p);
        
        m.m03 = 0.0f;
        m.m13 = 0.0f;
        m.m23 = 0.0f;
        m.m33 = 1.0f;
    }
    
    /** build view matrix from quaternion rotation and position. */
    void view_matrix(cgmmat44& m, const cgmquat & q, const cgmvec3& eye)
    {
        cg::quat2m33
        (  m.m00, m.m10, m.m20
         , m.m01, m.m11, m.m21
         , m.m02, m.m12, m.m22, q);
        
        m.m30 = -(eye.x*m.m00 + eye.y*m.m10 + eye.z*m.m20);
        m.m31 = -(eye.x*m.m01 + eye.y*m.m11 + eye.z*m.m21);
        m.m32 = -(eye.x*m.m02 + eye.y*m.m12 + eye.z*m.m22);
        
        m.m03 = 0.0f;
        m.m13 = 0.0f;
        m.m23 = 0.0f;
        m.m33 = 1.0f;
    }
    
    /** build view matrix from quaternion rotation and position. */
    cgmmat44 view_matrix(const cgmquat & q, const cgmvec3& eye)
    {
        cgmmat44 m;
        view_matrix(m, q, eye);
        return m;
    }
    
    /** build model matrix from quaternion rotation and position. */
    cgmmat44 model_matrix(const cgmquat & q, const cgmvec3& position)
    {
        cgmmat44 m;
        cg::quat2m33
        (  m.m00, m.m10, m.m20
         , m.m01, m.m11, m.m21
         , m.m02, m.m12, m.m22, q);
        
        m.m30 = position.x;
        m.m31 = position.y;
        m.m32 = position.z;
        m.m03 = 0.0f;
        m.m13 = 0.0f;
        m.m23 = 0.0f;
        m.m33 = 1.0f;
        
        return m;
    }
    
    cgmmat44 model_matrix(const cgmquat & q, const cgmvec3& scale, const cgmvec3& position)
    {
        cgmmat44 m;
        cg::quat2m33
        (  m.m00, m.m10, m.m20
         , m.m01, m.m11, m.m21
         , m.m02, m.m12, m.m22, q);
        
        m.m00 *= scale.x;
        m.m10 *= scale.x;
        m.m20 *= scale.x;
        m.m30 = position.x;
        
        m.m01 *= scale.y;
        m.m11 *= scale.y;
        m.m21 *= scale.y;
        m.m31 = position.y;
        
        m.m02 *= scale.z;
        m.m12 *= scale.z;
        m.m22 *= scale.z;
        m.m32 = position.z;
        
        m.m03 = 0.0f;
        m.m13 = 0.0f;
        m.m23 = 0.0f;
        m.m33 = 1.0f;
        return m;
    }
}}
