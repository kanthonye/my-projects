//
//  mat33.hpp
//  vector-math
//
//  Created by Kenneth A Esdaile on 6/6/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef mat33_hpp
#define mat33_hpp
#include "../../graphics/cgmath/vec3.hpp"
#include "../../graphics/cgmath/mat22.hpp"
namespace kege{namespace cg{
    
    class cgmmat33
    {   public:
        void operator ()
        (  cg::real a00, cg::real a10, cg::real a20
         , cg::real a01, cg::real a11, cg::real a21
         , cg::real a02, cg::real a12, cg::real a22 );
        
        void operator () (const cgmvec3 &v0,const cgmvec3 &v1,const cgmvec3 &v2);
        
        void operator ()
        (const cgmvec2 &v0, float a02,
         const cgmvec2 &v1, float a12,
         const cgmvec2 &v2, float a22);
        
        void operator () (const cgmmat22 &m);
        
        void operator () (cg::real n);
        
        inline cgmmat33 operator +(const cgmmat33 &m)const;
        inline cgmmat33 operator -(const cgmmat33 &m)const;
        inline cgmmat33 operator *(const cgmmat33 &m)const;
        inline cgmvec3  operator *(const  cgmvec3 &v)const;
        
        inline cgmmat33 operator +(cg::real k)const;
        inline cgmmat33 operator -(cg::real k)const;
        inline cgmmat33 operator *(cg::real k)const;
        inline cgmmat33 operator /(cg::real k)const;
        
        inline void operator +=(const cgmmat33 &v);
        inline void operator -=(const cgmmat33 &v);
        inline void operator *=(const cgmmat33 &v);
        
        inline void operator +=(cg::real k);
        inline void operator -=(cg::real k);
        inline void operator *=(cg::real k);
        inline void operator /=(cg::real k);
        
        inline void upper22(cgmmat22 &M)const;
        
        cgmmat33
        (  cg::real a00, cg::real a10, cg::real a20
         , cg::real a01, cg::real a11, cg::real a21
         , cg::real a02, cg::real a12, cg::real a22 );
        
        cgmmat33
        (  const cgmvec2 &v0, float a02
         , const cgmvec2 &v1, float a12
         , const cgmvec2 &v2, float a22 );
        
        cgmmat33 (const cgmvec3 &v0, const cgmvec3 &v1, const cgmvec3 &v2);
        
        cgmmat33 (const cgmmat22 &m);
        
        cgmmat33 (cg::real n);
        
        cgmmat33 (void){}
        
        union
        {
            struct
            {
                cg::real m00, m01, m02;
                cg::real m10, m11, m12;
                cg::real m20, m21, m22;
            };
            
            cg::real data[9];
            cgmvec3  row[3];
        };
    };
}}

namespace kege{namespace cg{
    
    inline cgmmat33 operator +(cg::real k, const cgmmat33 &m)
    {
        return cgmmat33
        (  k+m.m00, k+m.m10, k+m.m20
         , k+m.m01, k+m.m11, k+m.m21
         , k+m.m02, k+m.m12, k+m.m22 );
    }
    inline cgmmat33 operator -(cg::real k, const cgmmat33 &m)
    {
        return cgmmat33
        (  k-m.m00, k-m.m10, k-m.m20
         , k-m.m01, k-m.m11, k-m.m21
         , k-m.m02, k-m.m12, k-m.m22 );
    }
    inline cgmmat33 operator *(cg::real k, const cgmmat33 &m)
    {
        return cgmmat33
        (  k*m.m00, k*m.m10, k*m.m20
         , k*m.m01, k*m.m11, k*m.m21
         , k*m.m02, k*m.m12, k*m.m22 );
    }
    
    inline cgmmat33 operator /(cg::real k, const cgmmat33 &m)
    {
        return cgmmat33
        (  k/cg::assert_zero(m.m00), k/cg::assert_zero(m.m10), k/cg::assert_zero(m.m20)
         , k/cg::assert_zero(m.m01), k/cg::assert_zero(m.m11), k/cg::assert_zero(m.m21)
         , k/cg::assert_zero(m.m02), k/cg::assert_zero(m.m12), k/cg::assert_zero(m.m22)  );
    }
    
    inline cg::real trace (const cgmmat33& m)
    {
        return ( m.m00 + m.m11 + m.m22 );
    }
    
    inline cgmmat33 transpose (const cgmmat33 &m)
    {
        return cgmmat33
        (  m.m00, m.m01, m.m02
         , m.m10, m.m11, m.m12
         , m.m20, m.m21, m.m22 );
    }
    
    inline cgmmat33 translate(cg::real x, cg::real y)
    {
        return cgmmat33
        (  1.0f, 0.0f, x
         , 0.0f, 1.0f, y
         , 0.0f, 0.0f, 1.0f);
    }
    
    inline cgmmat33 translate (const cgmvec2 v)
    {
        return translate(v.x, v.y);
    }
    
    inline cgmmat33 scale (cg::real x, cg::real y)
    {
        return cgmmat33
        (  x   , 0.0f, 0.0f
         , 0.0f, y   , 0.0f
         , 0.0f, 0.0f, 1.0f);
    }
    
    inline cgmmat33 scale (const cgmvec2 v)
    {
        return scale(v.x, v.y);
    }
    
    inline cgmmat33 reflectY (cg::real x, cg::real y)
    {
        return cgmmat33
        ( -1.0f, 0.0f, x
         , 0.0f, 1.0f, y
         , 0.0 , 0.0 , 1.0f);
    }
    
    inline cgmmat33 reflectY (const cgmvec2 v)
    {
        return reflectY(v.x, v.y);
    }
    
    inline cgmmat33 reflectX (cg::real x, cg::real y)
    {
        return cgmmat33
        (  1.0f, 0.0f, x
         , 0.0f, 1.0f, y
         , 0.0f, 0.0f, 1.0f);
    }
    
    inline cgmmat33 reflectX (const cgmvec2 v)
    {
        return reflectX(v.x, v.y);
    }
    
    inline cgmmat33 rotm33X (cg::real DEG)
    {
        float s = sin( cg::deg2rad(DEG) );
        float c = cos( cg::deg2rad(DEG) );
        return cgmmat33
        (  1.0f, 0.0f, 0.0f
         , 0.0f,  c  , -s
         , 0.0f,  s  , c);
    }
    
    inline cgmmat33 rotm33Y (cg::real DEG)
    {
        float s = sin( cg::deg2rad(DEG) );
        float c = cos( cg::deg2rad(DEG) );
        return cgmmat33
        (  c   , 0.0f, -s
         , 0.0f, 1.0f, 0.0f
         , s   , 0.0f, c);
    }
    
    inline cgmmat33 rotm33Z (cg::real DEG)
    {
        float s = sin( cg::deg2rad(DEG) );
        float c = cos( cg::deg2rad(DEG) );
        return cgmmat33
        (   c  , -s  , 0.0f
         ,  s  ,  c  , 0.0f
         , 0.0f, 0.0f, 1.0f);
    }
    
    /*! @brief Determinant of 3x3 matrix */
    inline double det (const cgmmat33& m)
    {
        return (m.m00 * (m.m11 * m.m22 - m.m21 * m.m12) -
                m.m10 * (m.m01 * m.m22 - m.m21 * m.m02) +
                m.m20 * (m.m01 * m.m12 - m.m11 * m.m02));
    }
    
    inline cgmmat33 adj (const cgmmat33& m)
    {
        return cgmmat33
        (  (m.m11 * m.m22 - m.m21 * m.m12)
         ,-(m.m10 * m.m22 - m.m20 * m.m12)
         , (m.m10 * m.m21 - m.m20 * m.m11)
         
         ,-(m.m01 * m.m22 - m.m21 * m.m02)
         , (m.m00 * m.m22 - m.m20 * m.m02)
         ,-(m.m00 * m.m21 - m.m20 * m.m01)
         
         , (m.m01 * m.m12 - m.m11 * m.m02)
         ,-(m.m00 * m.m12 - m.m10 * m.m02)
         , (m.m00 * m.m11 - m.m10 * m.m01)  );
    }
    
    inline cgmmat33 inverse(const cgmmat33& m)
    {
        return cg::adj(m) * cg::invrs( cg::det(m) );
    }
}}


namespace kege{namespace cg{
    
    // matrix vs matrix
    
    inline bool operator ==(const cgmmat33 &m, const cgmmat33 &n)
    {
        return cg::det(m) == cg::det(n);
    }
    
    inline bool operator !=(const cgmmat33 &m, const cgmmat33 &n)
    {
        return cg::det(m) != cg::det(n);
    }
    
    inline bool operator >=(const cgmmat33 &m, const cgmmat33 &n)
    {
        return cg::det(m) >= cg::det(n);
    }
    inline bool operator <=(const cgmmat33 &m, const cgmmat33 &n)
    {
        return cg::det(m) <= cg::det(n);
    }
    
    inline bool operator >(const cgmmat33 &m, const cgmmat33 &n)
    {
        return cg::det(m) > cg::det(n);
    }
    inline bool operator <(const cgmmat33 &m, const cgmmat33 &n)
    {
        return cg::det(m) < cg::det(n);
    }
    
    // scalar vs matrix
    
    inline bool operator ==(cg::real k, const cgmmat33 &m)
    {
        return k == cg::det(m);
    }
    inline bool operator ==(const cgmmat33 &m, cg::real k)
    {
        return cg::det(m) == k;
    }
    
    inline bool operator !=(cg::real k, const cgmmat33 &m)
    {
        return k != cg::det(m);
    }
    inline bool operator !=(const cgmmat33 &m, cg::real k)
    {
        return cg::det(m) != k;
    }
    
    inline bool operator >=(const cgmmat33 &m, cg::real k)
    {
        return cg::det(m) >= k;
    }
    inline bool operator <=(cg::real k, const cgmmat33 &m)
    {
        return k <= cg::det(m);
    }
    
    inline bool operator >(const cgmmat33 &m, cg::real k)
    {
        return cg::det(m) > k;
    }
    inline bool operator <(cg::real k, const cgmmat33 &m)
    {
        return k < cg::det(m);
    }
}}


namespace kege{namespace cg{
    
    inline cgmmat33::cgmmat33(const cgmvec3 &a, const cgmvec3 &b, const cgmvec3 &c  )
    {
        operator()(a, b, c);
    }
    
    inline cgmmat33::cgmmat33
    (  cg::real a00, cg::real a10, cg::real a20
     , cg::real a01, cg::real a11, cg::real a21
     , cg::real a02, cg::real a12, cg::real a22 )
    {
        operator()(a00,a10,a20, a01,a11,a21, a02,a12,a22);
    }
    
    inline cgmmat33::cgmmat33 (cg::real val)
    {
        operator()(val);
    }
    
    inline void cgmmat33::operator()(const cgmvec3 &a, const cgmvec3 &b, const cgmvec3 &c)
    {
        operator()(a.x, a.y, a.z,  b.x, b.y, b.z,  c.x, c.y, c.z);
    }
    
    inline void cgmmat33::operator()
    (  cg::real a00, cg::real a10, cg::real a20
     , cg::real a01, cg::real a11, cg::real a21
     , cg::real a02, cg::real a12, cg::real a22 )
    {
        m00=a00;  m10=a10;  m20=a20;
        m01=a01;  m11=a11;  m21=a21;
        m02=a02;  m12=a12;  m22=a22;
    }
    
    inline void cgmmat33::operator () (cg::real val)
    {
        m01 = m02 = m10 = m12 = m20 = m21 = 0.0f;
        m00 = m11 = m22 = val;
    }
    
    inline cgmmat33 cgmmat33::operator +(const cgmmat33 &m)const
    {
        return cgmmat33
        (  m00+m.m00, m10+m.m10, m20+m.m20
         , m01+m.m01, m11+m.m11, m21+m.m21
         , m02+m.m02, m12+m.m12, m22+m.m22 );
    }
    
    inline cgmmat33 cgmmat33::operator -(const cgmmat33 &m)const
    {
        return cgmmat33
        (  m00-m.m00, m10-m.m10, m20-m.m20
         , m01-m.m01, m11-m.m11, m21-m.m21
         , m02-m.m02, m12-m.m12, m22-m.m22 );
    }
    
    inline cgmmat33 cgmmat33::operator *(const cgmmat33 &m)const
    {
        return cgmmat33
        (  (m00*m.m00) + (m01*m.m10) + (m02*m.m20)
         , (m00*m.m10) + (m10*m.m11) + (m20*m.m12)
         , (m00*m.m20) + (m10*m.m21) + (m20*m.m22)
         
         , (m01*m.m00) + (m11*m.m01) + (m21*m.m02)
         , (m01*m.m10) + (m11*m.m11) + (m21*m.m12)
         , (m01*m.m20) + (m11*m.m21) + (m21*m.m22)
         
         , (m02*m.m00) + (m12*m.m01) + (m22*m.m02)
         , (m02*m.m10) + (m12*m.m11) + (m22*m.m12)
         , (m02*m.m20) + (m12*m.m21) + (m22*m.m22) );
    }
    
    inline cgmvec3 cgmmat33::operator *(const cgmvec3 &v)const
    {
        return cgmvec3
        (  v.x * m00 + v.y * m10 + v.z * m20
         , v.x * m01 + v.y * m11 + v.z * m21
         , v.x * m02 + v.y * m12 + v.z * m22  );
    }
    
    inline cgmmat33 cgmmat33::operator +(cg::real k)const
    {
        return cgmmat33
        (  m00+k, m10+k, m20+k
         , m01+k, m11+k, m21+k
         , m02+k, m12+k, m22+k  );
    }
    
    inline cgmmat33 cgmmat33::operator -(cg::real k)const
    {
        return cgmmat33
        (  m00-k, m10-k, m20-k
         , m01-k, m11-k, m21-k
         , m02-k, m12-k, m22-k  );
    }
    
    inline cgmmat33 cgmmat33::operator *(cg::real k)const
    {
        return cgmmat33
        (  m00*k, m10*k, m20*k
         , m01*k, m11*k, m21*k
         , m02*k, m12*k, m22*k  );
    }
    
    inline cgmmat33 cgmmat33::operator /(cg::real k)const
    {
        return cgmmat33
        (  m00/k, m10/k, m20/k
         , m01/k, m11/k, m21/k
         , m02/k, m12/k, m22/k  );
    }
    
    inline void cgmmat33::operator +=(const cgmmat33 &m)
    {
        operator=(*this + m);
    }
    inline void cgmmat33::operator -=(const cgmmat33 &m)
    {
        operator=(*this - m);
    }
    inline void cgmmat33::operator *=(const cgmmat33 &m)
    {
        operator=(*this * m);
    }
    
    inline void cgmmat33::operator +=(cg::real k)
    {
        operator=(*this + k);
    }
    
    inline void cgmmat33::operator -=(cg::real k)
    {
        operator=(*this - k);
    }
    
    inline void cgmmat33::operator *=(cg::real k)
    {
        operator=(*this * k);
    }
    
    inline void cgmmat33::operator /=(cg::real k)
    {
        operator=(*this / k);
    }
}}
#endif /* mat33_hpp */
