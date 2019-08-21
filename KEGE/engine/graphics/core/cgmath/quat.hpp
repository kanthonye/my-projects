//
//  quat.hpp
//  column-major
//
//  Created by Kenneth A Esdaile on 7/12/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef quat_hpp
#define quat_hpp
#include "../../../graphics/core/cgmath/mat44.hpp"
namespace kege{namespace cg{
    
    class cgmquat
    {   public:
        
        friend inline cgmquat operator +(cg::real k, const cgmquat &v);
        friend inline cgmquat operator -(cg::real k, const cgmquat &v);
        friend inline cgmquat operator *(cg::real k, const cgmquat &v);
        friend inline cgmquat operator /(cg::real k, const cgmquat &v);
        
        inline void operator () (cg::real w, cg::real x, cg::real y, cg::real z);
        inline void operator () (cg::real angle, const cgmvec3& v);
        inline void operator () (cg::real const (*v)[4]);
        inline void operator () (const cgmmat33& m);
        inline void operator () (const cgmmat44& m);
        
        inline cgmquat operator + (const cgmquat &q) const;
        inline cgmquat operator - (const cgmquat &q) const;
        inline cgmquat operator * (const cgmquat &q) const;
        inline cgmquat operator / (const cgmquat &q) const;
        
        inline cgmquat operator + (cg::real s) const;
        inline cgmquat operator - (cg::real s) const;
        inline cgmquat operator * (cg::real s) const;
        inline cgmquat operator / (cg::real s) const;
        
        inline void operator += (const cgmquat &v3);
        inline void operator -= (const cgmquat &v3);
        inline void operator *= (const cgmquat &v3);
        
        inline void operator += (cg::real s);
        inline void operator -= (cg::real s);
        inline void operator *= (cg::real s);
        inline void operator /= (cg::real s);
        
        inline cgmquat operator - (void)const;
        
        cgmquat (cg::real x, cg::real y, cg::real z, cg::real w);
        cgmquat (cg::real angle, const cgmvec3& v);
        cgmquat (cg::real const (*v)[4]);
        cgmquat (const cgmmat33& n);
        cgmquat (const cgmmat44& n);
        cgmquat (void);
        
        
        union
        {
            struct{float x, y, z, w;};
            struct
            {
                cgmvec3 xyz;
                cg::real r;
            };
            float xyzw[4];
            cgmvec4 v4;
        };
    };
}}


namespace kege{namespace cg{
    
    cgmquat log(const cgmquat &q);
    
    /** normalize a quaternion.*/
    void normalize (cgmquat &p, const cgmquat &q);
    
    /** compute the inverse of a quaternion. */
    void inverse(cgmquat &result, const cgmquat &q);
    
    /** cross between two quaternion. */
    cgmquat cross(const cgmquat& q1, const cgmquat& q2);
    
    cgmquat quatsqrt(const cgmquat &pqA);
    
    /** compute a quaternions rase to a power. @return quaternion */
    cgmquat pow(const cgmquat &q, float exponent);
    
    /** convert euler angles to quaternions. @return quaternion */
    cgmquat euler_to_quat(cg::real pitch, cg::real yaw, cg::real roll);
    
    /** convert euler angles to quaternions. @return quaternion */
    inline cgmquat euler_to_quat(const cg::vec3& angles)
    {
        return euler_to_quat(angles.x, angles.y, angles.z);
    }
    
    /** compute the interpulation between two quaternions. @return quaternion */
    cgmquat slerp(const cgmquat& p,const cgmquat& q, double a);
    
    /** get the directional vectors from convert */
    void quat_to_basis(cgmvec3 &r, cgmvec3 &u, cgmvec3 &f, const cgmquat& q);
    
    /** build view matrix from basis vectors and position. */
    void view_matrix(cgmmat44& m, const cgmvec3& p, const cgmvec3& r, const cgmvec3& u, const cgmvec3& f);
    
    /** build view matrix from quaternion rotation and position. */
    void view_matrix(cgmmat44& m, const cgmquat & q, const cgmvec3& position);
    
    /** build view matrix from quaternion rotation and position. */
    cgmmat44 view_matrix(const cgmquat & q, const cgmvec3& position);
    
    /** build model matrix from quaternion rotation and position. */
    cgmmat44 model_matrix(const cgmquat & q, const cgmvec3& scale, const cgmvec3& position);
    
    /** build model matrix from quaternion rotation and position. */
    cgmmat44 model_matrix(const cgmquat & q, const cgmvec3& position);
    
    void quat2m33
    (  cg::real& rx, cg::real& ry, cg::real& rz
     , cg::real& ux, cg::real& uy, cg::real& uz
     , cg::real& fx, cg::real& fy, cg::real& fz
     , const cgmquat& q);
    
    /** converts a normalized quaternion into a rotation matrix. */
    void quat_to_mat33(cgmmat33 &mat, const cgmquat & q);
    
    /** converts a normalized quaternion into a rotation matrix. */
    void quat_to_mat44(cgmmat44 &mat, const cgmquat & q);
    
    /** converts a normalized quaternion into a rotation matrix 3x3. */
    cgmmat33 quat_to_mat33(const cgmquat & q);
    
    /** converts a normalized quaternion into a rotation matrix 4x4. */
    cgmmat44 quat_to_mat44(const cgmquat & q);
    
    /** convert from rotation matrix 3x3 to quaternion. */
    void mat33_to_quat(cgmquat &q, const cgmmat33 &m);
    
    /** convert from rotation matrix 4x4 to quaternion. */
    void mat44_to_quat(cgmquat &q, const cgmmat44 &m);
    
    /** convert from rotation to euler angles. */
    void euler_angle(const cgmquat& q, cg::real& roll, cg::real& pitch, cg::real& yaw);
    
    /** convert from rotation to euler angles. */
    inline cgmvec3 quat2euler(const cgmquat& q)
    {
        cgmvec3 euler;
        euler_angle(q, euler.x, euler.y, euler.z);
        return euler;
    }
    
    /** convert from rotation to euler angles. */
    cgmvec3 euler_angle(cgmquat const& q);
    
    /** convert quaternion to euler angle roll. @return float. */
    inline float euler_roll(const cgmquat& q)
    {
        return cg::rad2deg(atan2(2.0f * q.x * q.y + q.z * q.w, q.x * q.x + q.w * q.w - q.y * q.y - q.z * q.z));
    }
    
    /** convert quaternion to euler angle pitch. @return float */
    inline float euler_pitch(const cgmquat& q)
    {
        return cg::rad2deg(atan2(2.0f * q.y * q.z + q.w * q.x, q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z));
    }
    
    /** convert quaternion to euler angle yaw. @return float */
    inline float euler_yaw(const cgmquat& q)
    {
        return cg::rad2deg(asin(-2.0f * (q.x * q.z - q.w * q.y)));
    }
    
    
    /** build mat44 rotation matrix using quaternion axis angle rotation. */
    inline cgmquat axis_angle(cg::real angle, cg::real x, cg::real y, cg::real z)
    {
        return cg::quat(angle, cgmvec3(x,y,z));
    }
    
    inline cgmquat axis_angleX(cg::real angle)
    {
        return cg::axis_angle(angle, 1.0, 0.0, 0.0);
    }
    
    inline cgmquat axis_angleY(cg::real angle)
    {
        return cg::axis_angle(angle, 0.0, 1.0, 0.0);
    }
    
    inline cgmquat axis_angleZ(cg::real angle)
    {
        return cg::axis_angle(angle, 0.0, 0.0, 1.0);
    }
    
    /** build mat44 rotation matrix using quaternion. */
    inline cgmmat44 rotm44(cg::real angle, cg::real x, cg::real y, cg::real z)
    {
        return cg::quat_to_mat44( cg::axis_angle(angle, x,y,z) );
    }
    
    /** build mat44 rotation matrix using quaternion. */
    inline cgmmat44 rotm44(cg::real pitch, cg::real yaw, cg::real roll)
    {
        return cg::quat_to_mat44( cg::euler_to_quat(pitch,yaw,roll) );
    }
    
    inline cgmquat abs(const cgmquat& a)
    {
        return cgmquat(cg::abs(a.x), cg::abs(a.y), cg::abs(a.z), cg::abs(a.w));
    }
    
    /** dot product of two quaternion. @return float */
    inline cg::real dot (const cgmquat &a, const cgmquat &b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
    }
    
    /** inline function. compute the math::square magnitude of a vectors. */
    inline float magnsq (const cgmquat& v)
    {
        return dot(v,v);
    }
    
    /** compute the quaternion magnitude/length. @return float */
    inline float magn (const cgmquat &A)
    {
        return sqrt(dot(A, A));
    }
    
    /** compute the negation of a quaternion. @return quaternion */
    inline cgmquat conjugate (const cgmquat &q)
    {
        return cgmquat(q.w, -q.x, -q.y, -q.z);
    }
    
    /** computer the inverse of a quaternion. @return quaternion */
    inline cgmquat inverse (const cgmquat &q)
    {
        return conjugate(q) * cg::invrs(dot(q,q));
    }
    
    inline cgmquat square(const cgmquat &q1)
    {
        float s = 2.0f * q1.w;
        return cgmquat(dot(q1, q1), s*q1.x, s*q1.y, s * q1.z);
    }
    
    /** normalize a quaternion. @return quaternion */
    inline cgmquat normalize (const cgmquat &q)
    {
        float m = q.w*q.w + q.x*q.x + q.y*q.y + q.z*q.z;
        if (m == 0) return cgmquat(q.x, q.y, q.z, (0.0f > q.w) ? -1.0 : 1.0);
        return q * (1.0f / sqrt(m));
    }
    
}}

namespace kege{namespace cg{
    
    inline cgmquat cross(const cgmquat& q1, const cgmquat& q2)
    {
        return cgmquat
        (q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x,
         q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
         q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
         q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z);
    }
    
    inline cgmvec3 operator * (const cgmquat& q, const cgmvec3 &v)
    {
        cg::real m00, m10, m20;
        cg::real m01, m11, m21;
        cg::real m02, m12, m22;
        quat2m33(m00,m10,m20, m01,m11,m21, m02,m12,m22, q);
        return cgmvec3
        (  v.x * m00 + v.y * m10 + v.z * m20
         , v.x * m01 + v.y * m11 + v.z * m21
         , v.x * m02 + v.y * m12 + v.z * m22  );
    }
    
    inline cgmquat operator +(cg::real k, const cgmquat &q)
    {
        return cgmquat(k+q.w, k+q.x, k+q.y, k+q.z);
    }
    inline cgmquat operator -(cg::real k, const cgmquat &q)
    {
        return cgmquat(k-q.w, k-q.x, k-q.y, k-q.z);
    }
    inline cgmquat operator *(cg::real k, const cgmquat &q)
    {
        return cgmquat(k*q.w, k*q.x, k*q.y, k*q.z);
    }
    inline cgmquat operator /(cg::real k, const cgmquat &q)
    {
        return cgmquat
        (  k/cg::assert_zero(q.w)
         , k/cg::assert_zero(q.x)
         , k/cg::assert_zero(q.y)
         , k/cg::assert_zero(q.z) );
    }
    
    inline bool operator == (const cgmquat &v, cg::real s)
    {
        return cg::magnsq(v) == s*s;
    }
    
    inline bool operator == (cg::real s, const cgmquat &v)
    {
        return cg::magnsq(v) == s*s;
    }
    
    inline bool operator != (const cgmquat &v, cg::real s)
    {
        return cg::magnsq(v) != s*s;
    }
    
    inline bool operator != (cg::real s, const cgmquat &v)
    {
        return cg::magnsq(v) != s*s;
    }
    
    inline bool operator <= (const cgmquat &v, cg::real s)
    {
        return cg::magnsq(v) <= s*s;
    }
    
    inline bool operator >= (cg::real s, const cgmquat &v)
    {
        return cg::magnsq(v) >= s*s;
    }
    
    inline bool operator < (const cgmquat &v, cg::real s)
    {
        return cg::magnsq(v) < s*s;
    }
    
    inline bool operator > (cg::real s, const cgmquat &v)
    {
        return cg::magnsq(v) < s*s;
    }
    
    inline bool operator == (const cgmquat &l, const cgmquat &r)
    {
        return cg::magnsq(l) == cg::magnsq(r);
    }
    
    inline bool operator != (const cgmquat &l, const cgmquat &r)
    {
        return cg::magnsq(l) != cg::magnsq(r);
    }
    
    inline bool operator <= (const cgmquat &l, const cgmquat &r)
    {
        return cg::magnsq(l) <= cg::magnsq(r);
    }
    
    inline bool operator >= (const cgmquat &l, const cgmquat &r)
    {
        return cg::magnsq(l) >= cg::magnsq(r);
    }
    
    inline bool operator < (const cgmquat &l, const cgmquat &r)
    {
        return cg::magnsq(l) <= cg::magnsq(r);
    }
    
    inline bool operator > (const cgmquat &l, const cgmquat &r)
    {
        return cg::magnsq(l) >= cg::magnsq(r);
    }
}}

namespace kege{namespace cg{
    
    
    inline cgmquat::cgmquat (cg::real w, cg::real x, cg::real y, cg::real z)
    :  x(x) , y(y) , z(z) , w(w)
    {}
    
    inline cgmquat::cgmquat (cg::real angle, const cgmvec3& v)
    {
        this->operator()(angle, v);
    }
    
    inline cgmquat::cgmquat (const cg::real (*v)[4])
    {
        operator()(v);
    }
    
    inline cgmquat::cgmquat(const cgmmat44& m)
    {
        cgmquat::operator()(m);
    }
    inline cgmquat::cgmquat(const cgmmat33& m)
    {
        cgmquat::operator()(m);
    }
    
    inline cgmquat::cgmquat (void)
    :  x(0.0) , y(0.0) , z(0.0) , w(1.0)
    {}
    
    inline void cgmquat::operator () (cg::real w, cg::real x, cg::real y, cg::real z)
    {
        this->w = w;
        this->x = x;
        this->y = y;
        this->z = z;
    }
    inline void cgmquat::operator () (cg::real angle, const cgmvec3& v)
    {
        cg::real radian = cg::deg2rad(angle * 0.5f);
        cg::real sinangle = sin(radian);
        this->w = cos(radian);
        this->x = v.x * sinangle;
        this->y = v.y * sinangle;
        this->z = v.z * sinangle;
    }
    inline void cgmquat::operator () (cg::real const (*v)[4])
    {
        cgmquat::operator()((*v)[3], cgmvec3((*v)[0], (*v)[1], (*v)[2]));
    }
    inline void cgmquat::operator () (const cgmmat33& m)
    {
        cg::mat33_to_quat(*this, m);
    }
    inline void cgmquat::operator () (const cgmmat44& m)
    {
        cg::mat44_to_quat(*this, m);
    }
    
    inline cgmquat cgmquat::operator + (const cgmquat &q)const
    {
        return cgmquat(w+q.w, x+q.x, y+q.y, z+q.z);
    }
    
    inline cgmquat cgmquat::operator - (const cgmquat &q)const
    {
        return cgmquat(w-q.w, x-q.x, y-q.y, z-q.z);
    }
    
    inline cgmquat cgmquat::operator * (const cgmquat &q)const
    {
        return cgmquat
        (  w*q.w - x*q.x - y*q.y - z*q.z
         , w*q.x + x*q.w + y*q.z - z*q.y
         , w*q.y - x*q.z + y*q.w + z*q.x
         , w*q.z + x*q.y - y*q.x + z*q.w  );
    }
    
    /*
    inline cgmquat operator / (cgmquat q0, cgmquat q1)
    {
        cgmquat qm = q0 * q1;
        // conjugate
        cgmquat qq  = conjugate(q0);
        // square elements
        qq = qq*qq;
        // Not too close to zero?
        float s = (0.0f != qq.w) ? 1.0f / qq.w : 1.0f;
        return cgmquat(qm.w * s, qm.x*s, qm.y*s, qm.z*s);
    }
    */
    inline cgmquat cgmquat::operator / (const cgmquat &q)const
    {
        return (*this * q) * cg::invrs( cg::sq(conjugate(*this)).w );
    }
    
    inline cgmquat cgmquat::operator + (cg::real s)const
    {
        return cgmquat(w+s, x+s, y+s, z+s);
    }
    
    inline cgmquat cgmquat::operator - (cg::real s)const
    {
        return cgmquat(w-s, x-s, y-s, z-s);
    }
    
    inline cgmquat cgmquat::operator * (cg::real s)const
    {
        return cgmquat(w*s, x*s, y*s, z*s);
    }
    
    inline cgmquat cgmquat::operator / (cg::real s)const
    {
        return cgmquat(w/s, x/s, y/s, z/s);
    }
    
    inline void cgmquat::operator += (const cgmquat &v)
    {
        this->operator()(w+v.w, x+v.x, y+v.y, z+v.z);
    }
    
    inline void cgmquat::operator -= (const cgmquat &v)
    {
        this->operator()(w-v.w, x-v.x, y-v.y, z-v.z);
    }
    
    inline void cgmquat::operator *= (const cgmquat &q)
    {
        *this = operator*(q);
    }
    
    inline void cgmquat::operator += (cg::real s)
    {
        this->operator()(w+s, x+s, y+s, z+s);
    }
    
    inline void cgmquat::operator -= (cg::real s)
    {
        x -= s;
        y -= s;
        z -= s;
        w -= s;
    }
    
    inline void cgmquat::operator *= (cg::real s)
    {
        x *= s;
        y *= s;
        z *= s;
        w *= s;
    }
    
    inline void cgmquat::operator /= (cg::real s)
    {
        x /= s;
        y /= s;
        z /= s;
        w /= s;
    }
    
    inline cgmquat cgmquat::operator - (void)const
    {
        return cgmquat(-w, -x, -y, -z);
    }
}}
#endif /* quat_hpp */
