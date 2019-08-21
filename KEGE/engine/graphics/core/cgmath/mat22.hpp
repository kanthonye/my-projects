//
//  mat22.hpp
//  vector-math
//
//  Created by Kenneth A Esdaile on 6/6/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef mat22_hpp
#define mat22_hpp
#include "../../../graphics/core/cgmath/coremath.hpp"
#include "../../../graphics/core/cgmath/vec2.hpp"
namespace kege{namespace cg{
    
    class cgmmat22
    {   public:
        
        inline void operator () (cg::real a00, cg::real a10, cg::real a01, cg::real a11);
        inline void operator () (const cgmvec2 &v0,const cgmvec2 &v1);
        inline void operator () (const cgmmat22 &m);
        inline void operator () (cg::real n);
        
        inline cgmvec2  operator *(const  cgmvec2 &v)const;
        
        inline cgmmat22 operator +(const cgmmat22 &m)const;
        inline cgmmat22 operator -(const cgmmat22 &m)const;
        inline cgmmat22 operator *(const cgmmat22 &m)const;
        
        inline cgmmat22 operator +(cg::real k)const;
        inline cgmmat22 operator -(cg::real k)const;
        inline cgmmat22 operator *(cg::real k)const;
        inline cgmmat22 operator /(cg::real k)const;
        
        inline void operator +=(const cgmmat22 &v);
        inline void operator -=(const cgmmat22 &v);
        inline void operator *=(const cgmmat22 &v);
        
        inline void operator +=(cg::real k);
        inline void operator -=(cg::real k);
        inline void operator *=(cg::real k);
        inline void operator /=(cg::real k);
        
        inline cgmmat22 (cg::real a00, cg::real a10, cg::real a01, cg::real a11);
        inline cgmmat22 (const cgmvec2 &v0, const cgmvec2 &v1);
        inline cgmmat22 (cg::real n);
        inline cgmmat22 (void){}
        
        union
        {
            struct
            {
                float m00, m01;
                float m10, m11;
            };
            cg::real data[4];
            cgmvec2  col[2];
        };
    };
    
    inline void cgmmat22::operator () (cg::real a00, cg::real a10, cg::real a01, cg::real a11)
    {
        m00=a00; m01=a01;
        m10=a10; m11=a11;
    }
    
    inline void cgmmat22::operator () (const cgmvec2 &v0,const cgmvec2 &v1)
    {
        m00=v0.x;   m10=v1.x;
        m01=v0.y;   m11=v1.y;
    }
    
    inline void cgmmat22::operator () (cg::real val)
    {
        m00 = m11 = val;
        m10 = m01 = 0.0f;
    }
    
    inline cgmvec2  cgmmat22::operator *(const  cgmvec2 &v)const
    {
        return cgmvec2(m00*v.x + m01*v.y, m10*v.x + m11*v.y);
    }
    
    inline cgmmat22 cgmmat22::operator +(const cgmmat22 &m)const
    {
        return cgmmat22(m00+m.m00, m10+m.m10, m01+m.m01, m11+m.m11);
    }
    
    inline cgmmat22 cgmmat22::operator -(const cgmmat22 &m)const
    {
        return cgmmat22(m00-m.m00, m10-m.m10, m01-m.m01, m11-m.m11);
    }
    
    inline cgmmat22 cgmmat22::operator *(const cgmmat22 &m)const
    {
        return cgmmat22
        (  m00*m.m00 + m01*m.m10
         , m10*m.m00 + m11*m.m10
         , m00*m.m01 + m01*m.m11
         , m10*m.m01 + m11*m.m11 );
    }
    
    inline cgmmat22 cgmmat22::operator +(cg::real k)const
    {
        return cgmmat22(m00+k, m10+k, m01+k, m11+k);
    }
    
    inline cgmmat22 cgmmat22::operator -(cg::real k)const
    {
        return cgmmat22(m00-k, m10-k, m01-k, m11-k);
    }
    
    inline cgmmat22 cgmmat22::operator *(cg::real k)const
    {
        return cgmmat22(m00*k, m10*k, m01*k, m11*k);
    }
    
    inline cgmmat22 cgmmat22::operator /(cg::real k)const
    {
        return cgmmat22(m00/k, m10/k, m01/k, m11/k);
    }
    
    inline void cgmmat22::operator +=(const cgmmat22 &m)
    {
        m00+=m.m00;
        m01+=m.m01;
        m10+=m.m10;
        m11+=m.m11;
    }
    
    inline void cgmmat22::operator -=(const cgmmat22 &m)
    {
        m00-=m.m00;
        m01-=m.m01;
        m10-=m.m10;
        m11-=m.m11;
    }
    
    inline void cgmmat22::operator *=(const cgmmat22 &m)
    {
        *this = *this * m;
    }
    
    inline void cgmmat22::operator +=(cg::real k)
    {
        m00+=k;
        m01+=k;
        m10+=k;
        m11+=k;
    }
    
    inline void cgmmat22::operator -=(cg::real k)
    {
        m00-=k;
        m01-=k;
        m10-=k;
        m11-=k;
    }
    
    inline void cgmmat22::operator *=(cg::real k)
    {
        m00*=k;
        m01*=k;
        m10*=k;
        m11*=k;
    }
    
    inline void cgmmat22::operator /=(cg::real k)
    {
        m00/=k;
        m01/=k;
        m10/=k;
        m11/=k;
    }
    
    inline cgmmat22::cgmmat22(cg::real a00, cg::real a10, cg::real a01, cg::real a11)
    :   m00(a00), m01(a01), m10(a10), m11(a11)
    {
    }
    
    inline cgmmat22::cgmmat22 (const cgmvec2 &v0, const cgmvec2 &v1)
    :   m00(v0.x), m01(v1.x), m10(v0.y), m11(v1.y)
    {
    }
    
    inline cgmmat22::cgmmat22 (cg::real val)
    :   m00(val), m01(0.0), m10(val), m11(0.0)
    {
    }
}}

namespace kege{namespace cg{
    
    inline cgmmat22 operator +(cg::real k, const cgmmat22 &m)
    {
        return cgmmat22(k+m.m00, k+m.m10, k+m.m01, k+m.m11);
    }
    
    inline cgmmat22 operator -(cg::real k, const cgmmat22 &m)
    {
        return cgmmat22(k-m.m00, k-m.m10, k-m.m01, k-m.m11);
    }
    
    inline cgmmat22 operator *(cg::real k, const cgmmat22 &m)
    {
        return cgmmat22(k*m.m00, k*m.m10, k*m.m01, k*m.m11);
    }
    
    inline cgmmat22 operator /(cg::real k, const cgmmat22 &m)
    {
        return cgmmat22
        (  k/cg::assert_zero(m.m00)
         , k/cg::assert_zero(m.m10)
         , k/cg::assert_zero(m.m01)
         , k/cg::assert_zero(m.m11)  );
    }
    
    inline cgmmat22 transpose (const cgmmat22 &m)
    {
        return cgmmat22(m.m00, m.m01, m.m10, m.m11);
    }
    
    inline cgmmat22 reflect (cg::real DEG)
    {
        float s = sin( cg::deg2rad(DEG) );
        float c = cos( cg::deg2rad(DEG) );
        return cgmmat22(c, -s, s, c);
    }
    
    inline cgmmat22 rotm22 (cg::real DEG)
    {
        float s = sin( cg::deg2rad(DEG) );
        float c = cos( cg::deg2rad(DEG) );
        return cgmmat22(c, s, -s, c);
    }
    
    /*! @brief Trace of 2x2 matrix */
    inline float trace (const cgmmat22& m)
    {
        return m.m00 + m.m11;
    }
    
    /*! @brief Determinant of 2x2 matrix */
    inline float det (const cgmmat22& m)
    {
        return m.m00 * m.m11 - m.m01 * m.m10;
    }
    
    inline cgmmat22 adj (const cgmmat22& m)
    {
        return cgmmat22(m.m11, -m.m10, -m.m01, m.m00);
    }
    
    inline cgmmat22 inverse(const cgmmat22& m)
    {
        return  cg::adj(m) * cg::invrs( cg::det(m) );
    }
}}

namespace kege{namespace cg{
    
    // matrix vs matrix
    
    inline bool operator ==(const cgmmat22 &m, const cgmmat22 &n)
    {
        return cg::det(m) == cg::det(n);
    }
    
    inline bool operator !=(const cgmmat22 &m, const cgmmat22 &n)
    {
        return cg::det(m) != cg::det(n);
    }
    
    inline bool operator >=(const cgmmat22 &m, const cgmmat22 &n)
    {
        return cg::det(m) >= cg::det(n);
    }
    inline bool operator <=(const cgmmat22 &m, const cgmmat22 &n)
    {
        return cg::det(m) <= cg::det(n);
    }
    
    inline bool operator >(const cgmmat22 &m, const cgmmat22 &n)
    {
        return cg::det(m) > cg::det(n);
    }
    inline bool operator <(const cgmmat22 &m, const cgmmat22 &n)
    {
        return cg::det(m) < cg::det(n);
    }
    
    // scalar vs matrix
    
    inline bool operator ==(cg::real k, const cgmmat22 &m)
    {
        return k == cg::det(m);
    }
    inline bool operator ==(const cgmmat22 &m, cg::real k)
    {
        return cg::det(m) == k;
    }
    
    inline bool operator !=(cg::real k, const cgmmat22 &m)
    {
        return k != cg::det(m);
    }
    inline bool operator !=(const cgmmat22 &m, cg::real k)
    {
        return cg::det(m) != k;
    }
    
    inline bool operator >=(const cgmmat22 &m, cg::real k)
    {
        return cg::det(m) >= k;
    }
    inline bool operator <=(cg::real k, const cgmmat22 &m)
    {
        return k <= cg::det(m);
    }
    
    inline bool operator >(const cgmmat22 &m, cg::real k)
    {
        return cg::det(m) > k;
    }
    inline bool operator <(cg::real k, const cgmmat22 &m)
    {
        return k < cg::det(m);
    }
    
}}
#endif /* mat22_hpp */
