//
//  mat44.hpp
//  column-major
//
//  Created by Kenneth A Esdaile on 7/12/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef mat44_hpp
#define mat44_hpp
#include "../../graphics/cgmath/vec4.hpp"
#include "../../graphics/cgmath/mat33.hpp"
namespace kege{namespace cg{
    
    class cgmmat44
    {   public:
        void operator ()
        (  cg::real a00, cg::real a10, cg::real a20, cg::real a30
         , cg::real a01, cg::real a11, cg::real a21, cg::real a31
         , cg::real a02, cg::real a12, cg::real a22, cg::real a32
         , cg::real a03, cg::real a13, cg::real a23, cg::real a33 );
        
        void operator () (const cgmvec3 &v0,const cgmvec3 &v1,const cgmvec3 &v2);
        
        void operator ()
        (const cgmvec3 &v0, float a02,
         const cgmvec3 &v1, float a12,
         const cgmvec3 &v2, float a22);
        
        void operator () (const cgmmat33 &m);
        
        void operator () (cg::real n);
        
        inline cgmmat44 operator +(const cgmmat44 &m)const;
        inline cgmmat44 operator -(const cgmmat44 &m)const;
        inline cgmmat44 operator *(const cgmmat44 &m)const;
        inline cgmvec4  operator *(const  cgmvec4 &v)const;
        
        inline cgmmat44 operator +(cg::real k)const;
        inline cgmmat44 operator -(cg::real k)const;
        inline cgmmat44 operator *(cg::real k)const;
        inline cgmmat44 operator /(cg::real k)const;
        
        inline void operator +=(const cgmmat44 &v);
        inline void operator -=(const cgmmat44 &v);
        inline void operator *=(const cgmmat44 &v);
        
        inline void operator +=(cg::real k);
        inline void operator -=(cg::real k);
        inline void operator *=(cg::real k);
        inline void operator /=(cg::real k);
        
        inline void upper22(cgmmat22 &M)const;
        
        cgmmat44
        (  cg::real a00, cg::real a10, cg::real a20, cg::real a30
         , cg::real a01, cg::real a11, cg::real a21, cg::real a31
         , cg::real a02, cg::real a12, cg::real a22, cg::real a32
         , cg::real a03, cg::real a13, cg::real a23, cg::real a33 );
        
        cgmmat44
        (  const cgmvec3 &v0, float a02
         , const cgmvec3 &v1, float a12
         , const cgmvec3 &v2, float a22
         , const cgmvec3 &v3, float a33 );
        
        cgmmat44
        (  const cgmvec3 &r, cg::real a30
         , const cgmvec3 &u, cg::real a31
         , const cgmvec3 &f, cg::real a32);
        
        cgmmat44 (const cgmvec3 &v0, const cgmvec3 &v1, const cgmvec3 &v2);
        
        cgmmat44 (const cgmmat33 &m);
        
        cgmmat44 (cg::real n);
        
        cgmmat44 (void){}
        
        union
        {
            struct
            {
                cg::real m00, m01, m02, m03;
                cg::real m10, m11, m12, m13;
                cg::real m20, m21, m22, m23;
                cg::real m30, m31, m32, m33;
            };
            cg::real data[16];
            cgmvec4  cols[4];
        };
    };
}}

namespace kege{namespace cg{
    
    inline cgmmat44 operator +(cg::real k, const cgmmat44 &m)
    {
        return cgmmat44
        (  k+m.m00, k+m.m10, k+m.m20, k+m.m30
         , k+m.m01, k+m.m11, k+m.m21, k+m.m31
         , k+m.m02, k+m.m12, k+m.m22, k+m.m32
         , k+m.m03, k+m.m13, k+m.m23, k+m.m33 );
    }
    inline cgmmat44 operator -(cg::real k, const cgmmat44 &m)
    {
        return cgmmat44
        (  k-m.m00, k-m.m10, k-m.m20, k-m.m30
         , k-m.m01, k-m.m11, k-m.m21, k-m.m31
         , k-m.m02, k-m.m12, k-m.m22, k-m.m32
         , k-m.m03, k-m.m13, k-m.m23, k-m.m33 );
    }
    inline cgmmat44 operator *(cg::real k, const cgmmat44 &m)
    {
        return cgmmat44
        (  k*m.m00, k*m.m10, k*m.m20, k*m.m30
         , k*m.m01, k*m.m11, k*m.m21, k*m.m31
         , k*m.m02, k*m.m12, k*m.m22, k*m.m32
         , k*m.m03, k*m.m13, k*m.m23, k*m.m33 );
    }
    
    inline cgmmat44 operator /(cg::real k, const cgmmat44 &m)
    {
        return cgmmat44
        (  k/cg::assert_zero(m.m00), k/cg::assert_zero(m.m10)
         , k/cg::assert_zero(m.m20), k/cg::assert_zero(m.m30)
         
         , k/cg::assert_zero(m.m01), k/cg::assert_zero(m.m11)
         , k/cg::assert_zero(m.m21), k/cg::assert_zero(m.m31)
         
         , k/cg::assert_zero(m.m02), k/cg::assert_zero(m.m12)
         , k/cg::assert_zero(m.m22), k/cg::assert_zero(m.m32)
         
         , k/cg::assert_zero(m.m03), k/cg::assert_zero(m.m13)
         , k/cg::assert_zero(m.m23), k/cg::assert_zero(m.m33)  );
    }
    
    inline cg::real trace (const cgmmat44& m)
    {
        return ( m.m00 + m.m11 + m.m22 + m.m33 );
    }
    
    inline cgmmat44 transpose (const cgmmat44 &m)
    {
        return cgmmat44
        (  m.m00, m.m01, m.m02, m.m03
         , m.m10, m.m11, m.m12, m.m13
         , m.m20, m.m21, m.m22, m.m23
         , m.m30, m.m31, m.m32, m.m33 );
    }
    
    inline cgmmat44 translate(cg::real x, cg::real y, cg::real z)
    {
        return cgmmat44
        (  1.0f, 0.0f, 0.0f, x
         , 0.0f, 1.0f, 0.0f, y
         , 0.0f, 0.0f, 1.0f, z
         , 0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    inline cgmmat44 translate(const cgmvec3& p)
    {
        return cg::translate(p.x, p.y, p.z);
    }
    
    inline cgmmat44 scale (cg::real x, cg::real y, cg::real z)
    {
        return cgmmat44
        (  x   , 0.0f, 0.0f, 0.0f
         , 0.0f, y   , 0.0f, 0.0f
         , 0.0f, 0.0f, z   , 0.0f
         , 0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    inline cgmmat44 scale (const cgmvec3 v)
    {
        return cg::scale(v.x, v.y, v.z);
    }
    
    //    inline cgmmat44 reflectY (cg::real x, cg::real y, cg::real z)
    //    {
    //        return cgmmat44
    //        ( -1.0f, 0.0f, x
    //         , 0.0f, 1.0f, y
    //         , 0.0 , 0.0 , 1.0f);
    //    }
    //
    //    inline cgmmat44 reflectY (const cgmvec2 v)
    //    {
    //        return reflectY(v.x, v.y);
    //    }
    //
    //    inline cgmmat44 reflectX (cg::real x, cg::real y)
    //    {
    //        return cgmmat44
    //        (  1.0f, 0.0f, x
    //         , 0.0f, 1.0f, y
    //         , 0.0f, 0.0f, 1.0f);
    //    }
    //
    //    inline cgmmat44 reflectX (const cgmvec2 v)
    //    {
    //        return reflectX(v.x, v.y);
    //    }
    
    inline cgmmat44 rotm44X (cg::real DEG)
    {
        float s = sin( cg::deg2rad(DEG) );
        float c = cos( cg::deg2rad(DEG) );
        return cgmmat44
        (  1.0f, 0.0f, 0.0f, 0.0f
         , 0.0f,  c  , -s  , 0.0f
         , 0.0f,  s  ,  c  , 0.0f
         , 0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    inline cgmmat44 rotm44Y (cg::real DEG)
    {
        float s = sin( cg::deg2rad(DEG) );
        float c = cos( cg::deg2rad(DEG) );
        return cgmmat44
        (   c  , 0.0f,  s  , 0.0f
         , 0.0f, 1.0f, 0.0f, 0.0f
         , -s  , 0.0f,  c  , 0.0f
         , 0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    inline cgmmat44 rotm44Z (cg::real DEG)
    {
        float s = sin( cg::deg2rad(DEG) );
        float c = cos( cg::deg2rad(DEG) );
        return cgmmat44
        (   c  , -s  , 0.0f, 0.0f
         ,  s  ,  c  , 0.0f, 0.0f
         , 0.0f, 0.0f, 1.0f, 0.0f
         , 0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    /*! @brief Determinant of 4x4 matrix */
    inline float det (const cgmmat44& m)
    {
        return
        ( m.m00 * cg::det(cg::mat33(m.m11, m.m21, m.m31, m.m12, m.m22, m.m32, m.m13, m.m23, m.m33))
         -m.m10 * cg::det(cg::mat33(m.m01, m.m21, m.m31, m.m02, m.m22, m.m32, m.m03, m.m23, m.m33))
         +m.m20 * cg::det(cg::mat33(m.m01, m.m11, m.m31, m.m02, m.m12, m.m32, m.m03, m.m13, m.m33))
         -m.m30 * cg::det(cg::mat33(m.m01, m.m11, m.m21, m.m02, m.m12, m.m22, m.m03, m.m13, m.m23)) );
    }
    
    inline cgmmat44 adj (const cgmmat44& m)
    {
        return cgmmat44
        (  cg::det(cg::mat33(m.m11, m.m21, m.m31, m.m12, m.m22, m.m32, m.m13, m.m23, m.m33))
         ,-cg::det(cg::mat33(m.m10, m.m20, m.m30, m.m12, m.m22, m.m32, m.m13, m.m23, m.m33))
         , cg::det(cg::mat33(m.m10, m.m20, m.m30, m.m11, m.m21, m.m31, m.m13, m.m23, m.m33))
         ,-cg::det(cg::mat33(m.m10, m.m20, m.m30, m.m11, m.m21, m.m31, m.m12, m.m22, m.m32))
         
         ,-cg::det(cg::mat33(m.m01, m.m21, m.m31, m.m02, m.m22, m.m32, m.m03, m.m23, m.m33))
         , cg::det(cg::mat33(m.m00, m.m20, m.m30, m.m02, m.m22, m.m32, m.m03, m.m23, m.m33))
         ,-cg::det(cg::mat33(m.m00, m.m20, m.m30, m.m01, m.m21, m.m31, m.m03, m.m23, m.m33))
         , cg::det(cg::mat33(m.m00, m.m20, m.m30, m.m01, m.m21, m.m31, m.m02, m.m22, m.m32))
         
         , cg::det(cg::mat33(m.m01, m.m11, m.m31, m.m02, m.m12, m.m32, m.m03, m.m13, m.m33))
         ,-cg::det(cg::mat33(m.m00, m.m10, m.m30, m.m02, m.m12, m.m32, m.m03, m.m13, m.m33))
         , cg::det(cg::mat33(m.m00, m.m10, m.m30, m.m01, m.m11, m.m31, m.m03, m.m13, m.m33))
         ,-cg::det(cg::mat33(m.m00, m.m10, m.m30, m.m01, m.m11, m.m31, m.m02, m.m12, m.m32))
         
         ,-cg::det(cg::mat33(m.m01, m.m11, m.m21, m.m02, m.m12, m.m22, m.m03, m.m13, m.m23))
         , cg::det(cg::mat33(m.m00, m.m10, m.m20, m.m02, m.m12, m.m22, m.m03, m.m13, m.m23))
         ,-cg::det(cg::mat33(m.m00, m.m10, m.m20, m.m01, m.m11, m.m21, m.m03, m.m13, m.m23))
         , cg::det(cg::mat33(m.m00, m.m10, m.m20, m.m01, m.m11, m.m21, m.m02, m.m12, m.m22)) );
    }
    
    inline cgmmat44 inverse(const cgmmat44& m)
    {
        return cg::adj(m) * cg::invrs( cg::det(m) );
    }
    
    
    /**
     build perspective projection matrix
     @return mat44
     */
    inline cgmmat44 perspproj(cg::real l, cg::real r, cg::real t, cg::real b, cg::real n, cg::real f)
    {
        return cgmmat44
        (  (2.0*n) / (r-l), 0.0            ,  (r+l)/(r-l),  0.0
         , 0.0            , (2.0*n) / (t-b),  (t+b)/(t-b),  0.0
         , 0.0            , 0.0            , -(f+n)/(f-n), -(2.0*f*n) / (f-n)
         , 0.0            , 0.0            , -1.0        ,  0.0  );
    }
    
    /**
     build perspective projection matrix
     @return mat44
     */
    cgmmat44 perspproj(cg::real fov, cg::real aspect, cg::real znear, cg::real zfar);
    
    /**
     optimize version of @b perspproj(...)
     @note use only if @b(r=-l), @b(t=-b) where r+l=0, t+b=0 and r-l=width and t-b=height
     @return perspective projection matrix
     */
    inline cgmmat44 persp_proj(cg::real l, cg::real r, cg::real t, cg::real b, cg::real n, cg::real f)
    {
        return cgmmat44
        (  (2.0*n) / (r-l), 0.0            ,  0.0        ,  0.0
         , 0.0            , (2.0*n) / (t-b),  0.0        ,  0.0
         , 0.0            , 0.0            , -(f+n)/(f-n), -(2.0*f*n) / (f-n)
         , 0.0            , 0.0            , -1.0        ,  0.0  );
    }
    
    /**
     build perspective projection matrix
     @note this is an optimize version of @b perspproj().
     Use only if @b r=-l, @b t=-b where  @b r+l=0, @b t+b=0 and  @b r-l=width and  @b t-b=height
     @return mat44
     */
    cgmmat44 persp_proj(cg::real fov, cg::real aspect, cg::real znear, cg::real zfar);
    
    /**
     build orthographic projection matrix
     @return mat44
     */
    inline cgmmat44 orthoproj(cg::real l, cg::real r, cg::real t, cg::real b, cg::real n, cg::real f)
    {
        return cgmmat44
        (  2.0 / (r-l), 0.0        ,  0.0        ,  (r+l)/(r-l)
         , 0.0        , 2.0 / (t-b),  0.0        ,  (t+b)/(t-b)
         , 0.0        , 0.0        , -2.0 / (f-n), -(f+n)/(f-n)
         , 0.0        , 0.0        ,  0.0        ,  1.0  );
        
//        return cgmmat44
//        (  2.0 / (r-l), 0.0        ,  0.0        ,  0.0
//         , 0.0        , 2.0 / (t-b),  0.0        ,  0.0
//         , 0.0        , 0.0        , -2.0 / (f-n), -(f+n)/(f-n)
//         , 0.0        , 0.0        ,  0.0        ,  1.0  );
    }
    
    
    /**
     build orthographic projection matrix
     @note this is an optimize version of @b orthoproj().
     Use only if @b r=-l, @b t=-b where  @b r+l=0, @b t+b=0 and  @b r-l=width and  @b t-b=height
     @return mat44
     */
    inline cgmmat44 ortho_proj(cg::real l, cg::real r, cg::real t, cg::real b, cg::real n, cg::real f)
    {
        return cgmmat44
        (  2.0 / (r-l), 0.0        ,  0.0        ,  0.0
         , 0.0        , 2.0 / (t-b),  0.0        ,  0.0
         , 0.0        , 0.0        , -2.0 / (f-n), -(f+n)/(f-n)
         , 0.0        , 0.0        ,  0.0        ,  1.0  );
    }
    
    void lookat(cgmmat44& m, const cgmvec3 &eye, const cgmvec3 &target, const cgmvec3 &up);
}}


namespace kege{namespace cg{
    
    // matrix vs matrix
    
    inline bool operator ==(const cgmmat44 &m, const cgmmat44 &n)
    {
        return cg::det(m) == cg::det(n);
    }
    
    inline bool operator !=(const cgmmat44 &m, const cgmmat44 &n)
    {
        return cg::det(m) != cg::det(n);
    }
    
    inline bool operator >=(const cgmmat44 &m, const cgmmat44 &n)
    {
        return cg::det(m) >= cg::det(n);
    }
    inline bool operator <=(const cgmmat44 &m, const cgmmat44 &n)
    {
        return cg::det(m) <= cg::det(n);
    }
    
    inline bool operator >(const cgmmat44 &m, const cgmmat44 &n)
    {
        return cg::det(m) > cg::det(n);
    }
    inline bool operator <(const cgmmat44 &m, const cgmmat44 &n)
    {
        return cg::det(m) < cg::det(n);
    }
    
    // scalar vs matrix
    
    inline bool operator ==(cg::real k, const cgmmat44 &m)
    {
        return k == cg::det(m);
    }
    inline bool operator ==(const cgmmat44 &m, cg::real k)
    {
        return cg::det(m) == k;
    }
    
    inline bool operator !=(cg::real k, const cgmmat44 &m)
    {
        return k != cg::det(m);
    }
    inline bool operator !=(const cgmmat44 &m, cg::real k)
    {
        return cg::det(m) != k;
    }
    
    inline bool operator >=(const cgmmat44 &m, cg::real k)
    {
        return cg::det(m) >= k;
    }
    inline bool operator <=(cg::real k, const cgmmat44 &m)
    {
        return k <= cg::det(m);
    }
    
    inline bool operator >(const cgmmat44 &m, cg::real k)
    {
        return cg::det(m) > k;
    }
    inline bool operator <(cg::real k, const cgmmat44 &m)
    {
        return k < cg::det(m);
    }
    
//    inline cgmmat44 operator *(const cgmmat44 &m, const cgmmat44 &n)
//    {
//        return cgmmat44
//        (  (m.m00*n.m00) + (m.m01*n.m10) + (m.m02*n.m20) + (m.m03*n.m30)
//         , (m.m10*n.m00) + (m.m11*n.m10) + (m.m12*n.m20) + (m.m13*n.m30)
//         , (m.m20*n.m00) + (m.m21*n.m10) + (m.m22*n.m20) + (m.m23*n.m30)
//         , (m.m30*n.m00) + (m.m31*n.m10) + (m.m32*n.m20) + (m.m33*n.m30)
//         
//         , (m.m00*n.m01) + (m.m01*n.m11) + (m.m02*n.m21) + (m.m03*n.m31)
//         , (m.m10*n.m01) + (m.m11*n.m11) + (m.m12*n.m21) + (m.m13*n.m31)
//         , (m.m20*n.m01) + (m.m21*n.m11) + (m.m22*n.m21) + (m.m23*n.m31)
//         , (m.m30*n.m01) + (m.m31*n.m11) + (m.m32*n.m21) + (m.m33*n.m31)
//         
//         , (m.m00*n.m02) + (m.m01*n.m12) + (m.m02*n.m22) + (m.m03*n.m32)
//         , (m.m10*n.m02) + (m.m11*n.m12) + (m.m12*n.m22) + (m.m13*n.m32)
//         , (m.m20*n.m02) + (m.m21*n.m12) + (m.m22*n.m22) + (m.m23*n.m32)
//         , (m.m30*n.m02) + (m.m31*n.m12) + (m.m32*n.m22) + (m.m33*n.m32)
//         
//         , (m.m00*n.m03) + (m.m01*n.m13) + (m.m02*n.m23) + (m.m03*n.m33)
//         , (m.m10*n.m03) + (m.m11*n.m13) + (m.m12*n.m23) + (m.m13*n.m33)
//         , (m.m20*n.m03) + (m.m21*n.m13) + (m.m22*n.m23) + (m.m23*n.m33)
//         , (m.m30*n.m03) + (m.m31*n.m13) + (m.m32*n.m23) + (m.m33*n.m33) );
//    }
}}


namespace kege{namespace cg{
    
    inline cgmmat44::cgmmat44
    (  const cgmvec3 &r, cg::real a30
     , const cgmvec3 &u, cg::real a31
     , const cgmvec3 &f, cg::real a32)
    {
        m00=r.x;  m10=r.y;  m20=r.z;  m30=a30;
        m01=u.x;  m11=u.y;  m21=u.z;  m31=a31;
        m02=f.x;  m12=f.y;  m22=f.z;  m32=a32;
        m03= m13=  m23= 0.0;
        m33=1.0;
    }
    
    inline cgmmat44::cgmmat44(const cgmvec3 &a, const cgmvec3 &b, const cgmvec3 &c  )
    {
        operator()(a, b, c);
    }
    
    inline cgmmat44::cgmmat44
    (  cg::real a00, cg::real a10, cg::real a20, cg::real a30
     , cg::real a01, cg::real a11, cg::real a21, cg::real a31
     , cg::real a02, cg::real a12, cg::real a22, cg::real a32
     , cg::real a03, cg::real a13, cg::real a23, cg::real a33 )
    {
        operator()
        (  a00, a10, a20, a30
         , a01, a11, a21, a31
         , a02, a12, a22, a32
         , a03, a13, a23, a33  );
    }
    
    inline cgmmat44::cgmmat44 (cg::real val)
    {
        operator()(val);
    }
    
    inline void cgmmat44::operator()(const cgmvec3 &a, const cgmvec3 &b, const cgmvec3 &c)
    {
        operator()(  a.x, a.y, a.z, 0.0
                   , b.x, b.y, b.z, 0.0
                   , c.x, c.y, c.z, 0.0
                   , 0.0, 0.0, 0.0, 1.0  );
    }
    
    inline void cgmmat44::operator()
    (  cg::real a00, cg::real a10, cg::real a20, cg::real a30
     , cg::real a01, cg::real a11, cg::real a21, cg::real a31
     , cg::real a02, cg::real a12, cg::real a22, cg::real a32
     , cg::real a03, cg::real a13, cg::real a23, cg::real a33  )
    {
        m00=a00;  m10=a10;  m20=a20;  m30=a30;
        m01=a01;  m11=a11;  m21=a21;  m31=a31;
        m02=a02;  m12=a12;  m22=a22;  m32=a32;
        m03=a03;  m13=a13;  m23=a23;  m33=a33;
    }
    
    inline void cgmmat44::operator () (cg::real val)
    {
        m33= 1.0;
        m00 = m11 = m22 = val;
        m23= m13= m03= m32= m12= m02= m31= m21= m01= m30= m20= m10= 0.0;
    }
    
    inline cgmmat44 cgmmat44::operator +(const cgmmat44 &m)const
    {
        return cgmmat44
        (  m00+m.m00, m10+m.m10, m20+m.m20, m30+m.m30
         , m01+m.m01, m11+m.m11, m21+m.m21, m31+m.m31
         , m02+m.m02, m12+m.m12, m22+m.m22, m32+m.m32
         , m03+m.m03, m13+m.m13, m23+m.m23, m33+m.m33 );
    }
    
    inline cgmmat44 cgmmat44::operator -(const cgmmat44 &m)const
    {
        return cgmmat44
        (  m00-m.m00, m10-m.m10, m20-m.m20, m30-m.m30
         , m01-m.m01, m11-m.m11, m21-m.m21, m31-m.m31
         , m02-m.m02, m12-m.m12, m22-m.m22, m32-m.m32
         , m03-m.m03, m13-m.m13, m23-m.m23, m33-m.m33 );
    }
    
    inline cgmmat44 cgmmat44::operator *(const cgmmat44 &m)const
    {
        return cgmmat44
        (  (m00*m.m00) + (m01*m.m10) + (m02*m.m20) + (m03*m.m30)
         , (m10*m.m00) + (m11*m.m10) + (m12*m.m20) + (m13*m.m30)
         , (m20*m.m00) + (m21*m.m10) + (m22*m.m20) + (m23*m.m30)
         , (m30*m.m00) + (m31*m.m10) + (m32*m.m20) + (m33*m.m30)
         
         , (m00*m.m01) + (m01*m.m11) + (m02*m.m21) + (m03*m.m31)
         , (m10*m.m01) + (m11*m.m11) + (m12*m.m21) + (m13*m.m31)
         , (m20*m.m01) + (m21*m.m11) + (m22*m.m21) + (m23*m.m31)
         , (m30*m.m01) + (m31*m.m11) + (m32*m.m21) + (m33*m.m31)
         
         , (m00*m.m02) + (m01*m.m12) + (m02*m.m22) + (m03*m.m32)
         , (m10*m.m02) + (m11*m.m12) + (m12*m.m22) + (m13*m.m32)
         , (m20*m.m02) + (m21*m.m12) + (m22*m.m22) + (m23*m.m32)
         , (m30*m.m02) + (m31*m.m12) + (m32*m.m22) + (m33*m.m32)
         
         , (m00*m.m03) + (m01*m.m13) + (m02*m.m23) + (m03*m.m33)
         , (m10*m.m03) + (m11*m.m13) + (m12*m.m23) + (m13*m.m33)
         , (m20*m.m03) + (m21*m.m13) + (m22*m.m23) + (m23*m.m33)
         , (m30*m.m03) + (m31*m.m13) + (m32*m.m23) + (m33*m.m33) );
    }
    
    inline cgmvec4 cgmmat44::operator *(const cgmvec4 &v)const
    {
        return cgmvec4
        (  cg::dot4(cols[0], v)
         , cg::dot4(cols[1], v)
         , cg::dot4(cols[2], v)
         , cg::dot4(cols[3], v)  );
    }
    
    inline cgmmat44 cgmmat44::operator +(cg::real k)const
    {
        return cgmmat44
        (  m00+k, m10+k, m20+k, m30+k
         , m01+k, m11+k, m21+k, m31+k
         , m02+k, m12+k, m22+k, m32+k
         , m03+k, m13+k, m23+k, m33+k  );
    }
    
    inline cgmmat44 cgmmat44::operator -(cg::real k)const
    {
        return cgmmat44
        (  m00-k, m10-k, m20-k, m30-k
         , m01-k, m11-k, m21-k, m31-k
         , m02-k, m12-k, m22-k, m32-k
         , m03-k, m13-k, m23-k, m33-k  );
    }
    
    inline cgmmat44 cgmmat44::operator *(cg::real k)const
    {
        return cgmmat44
        (  m00*k, m10*k, m20*k, m30*k
         , m01*k, m11*k, m21*k, m31*k
         , m02*k, m12*k, m22*k, m32*k
         , m03*k, m13*k, m23*k, m33*k  );
    }
    
    inline cgmmat44 cgmmat44::operator /(cg::real k)const
    {
        return cgmmat44
        (  m00/k, m10/k, m20/k, m30/k
         , m01/k, m11/k, m21/k, m31/k
         , m02/k, m12/k, m22/k, m32/k
         , m03/k, m13/k, m23/k, m33/k  );
    }
    
    inline void cgmmat44::operator +=(const cgmmat44 &m)
    {
        operator=(*this + m);
    }
    inline void cgmmat44::operator -=(const cgmmat44 &m)
    {
        operator=(*this - m);
    }
    inline void cgmmat44::operator *=(const cgmmat44 &m)
    {
        operator=(*this * m);
    }
    
    inline void cgmmat44::operator +=(cg::real k)
    {
        operator=(*this + k);
    }
    
    inline void cgmmat44::operator -=(cg::real k)
    {
        operator=(*this - k);
    }
    
    inline void cgmmat44::operator *=(cg::real k)
    {
        operator=(*this * k);
    }
    
    inline void cgmmat44::operator /=(cg::real k)
    {
        operator=(*this / k);
    }
}}
#endif /* mat44_hpp */
