//
//  vec4.hpp
//  column-major
//
//  Created by Kenneth A Esdaile on 7/12/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef vec4_hpp
#define vec4_hpp
#include "../../graphics/cgmath/vec3.hpp"
namespace kege{namespace cg{
    
    class cgmvec4
    {   public:
        
        friend inline cgmvec4 operator +(cg::real k, const cgmvec4 &v);
        friend inline cgmvec4 operator -(cg::real k, const cgmvec4 &v);
        friend inline cgmvec4 operator *(cg::real k, const cgmvec4 &v);
        friend inline cgmvec4 operator /(cg::real k, const cgmvec4 &v);
        
        inline void operator () (cg::real x, cg::real y, cg::real z, cg::real w);
        inline void operator () (cg::real (*v)[4]);
        inline void operator () (cg::real val);
        
        inline cgmvec4 operator + (const cgmvec4 &v3) const;
        inline cgmvec4 operator - (const cgmvec4 &v3) const;
        inline cgmvec4 operator * (const cgmvec4 &v3) const;
        inline cgmvec4 operator / (const cgmvec4 &v3) const;
        
        inline cgmvec4 operator + (cg::real s) const;
        inline cgmvec4 operator - (cg::real s) const;
        inline cgmvec4 operator * (cg::real s) const;
        inline cgmvec4 operator / (cg::real s) const;
        
        inline void operator += (const cgmvec4 &v3);
        inline void operator -= (const cgmvec4 &v3);
        inline void operator *= (const cgmvec4 &v3);
        
        inline void operator += (cg::real s);
        inline void operator -= (cg::real s);
        inline void operator *= (cg::real s);
        inline void operator /= (cg::real s);
        
        inline cgmvec4 operator - (void)const;
        
        static const cgmvec4 forward;
        static const cgmvec4 right;
        static const cgmvec4 zero;
        static const cgmvec4 one;
        static const cgmvec4 up;
        
        cgmvec4 (cg::real x, cg::real y, cg::real z, cg::real w);
        cgmvec4 (const cgmvec3& v, cg::real w);
        cgmvec4 (cg::real const (*v)[4]);
        cgmvec4 (cg::real val);
        cgmvec4 (void){}
        
        union
        {
            float data[4];
            float rgba[4];
            struct
            {
                union
                {
                    float rgb[3];
                    cgmvec3 xyz;
                    struct
                    {
                        union
                        {
                            struct{cg::real x, y;};
                            struct{cg::real r, g;};
                            cgmvec2 xy;
                        };
                        union
                        {
                            cg::real z;
                            cg::real b;
                        };
                    };
                };
                union
                {
                    cg::real w;
                    cg::real a;
                };
            };
        };
    };
    
    typedef cgmvec4 point4;
    typedef cgmvec4 color4;
    
    inline cgmvec4::cgmvec4 (cg::real x, cg::real y, cg::real z, cg::real w)
    :   x(x) , y(y) , z(z) , w(w)
    {
    }
    
    inline cgmvec4::cgmvec4 (const cgmvec3& v, cg::real w)
    :   x(v.x) , y(v.y) , z(v.z) , w(w)
    {
    }
    
    inline cgmvec4::cgmvec4 (cg::real const (*v)[4])
    :   x((*v)[0]) , y((*v)[1]) , z((*v)[2]) , w((*v)[3])
    {
    }
    
    inline cgmvec4::cgmvec4 (cg::real v)
    :   x(v) , y(v) , z(v) , w(v)
    {
    }
    
    inline void cgmvec4::operator () (cg::real vx, cg::real vy, cg::real vz, cg::real vw)
    {
        x = vx;
        y = vy;
        z = vz;
        w = vw;
    }
    
    inline void cgmvec4::operator () (cg::real (*v)[4])
    {
        x = (*v)[0];
        y = (*v)[1];
        z = (*v)[2];
        w = (*v)[3];
    }
    
    inline void cgmvec4::operator () (cg::real val)
    {
        x = y = z = val;
    }
    
    inline cgmvec4 cgmvec4::operator + (const cgmvec4 &v)const
    {
        return cgmvec4(x+v.x, y+v.y, z+v.z, w+v.w);
    }
    
    inline cgmvec4 cgmvec4::operator - (const cgmvec4 &v)const
    {
        return cgmvec4(x-v.x, y-v.y, z-v.z, w-v.w);
    }
    
    inline cgmvec4 cgmvec4::operator * (const cgmvec4 &v)const
    {
        return cgmvec4(x*v.x, y*v.y, z*v.z, w*v.w);
    }
    
    inline cgmvec4 cgmvec4::operator / (const cgmvec4 &v)const
    {
        return cgmvec4
        (  x/cg::assert_zero(v.x)
         , y/cg::assert_zero(v.y)
         , z/cg::assert_zero(v.z)
         , w/cg::assert_zero(v.w) );
    }
    
    inline cgmvec4 cgmvec4::operator + (cg::real s)const
    {
        return cgmvec4(x+s, y+s, z+s, w+s);
    }
    
    inline cgmvec4 cgmvec4::operator - (cg::real s)const
    {
        return cgmvec4(x-s, y-s, z-s, w-s);
    }
    
    inline cgmvec4 cgmvec4::operator * (cg::real s)const
    {
        return cgmvec4(x*s, y*s, z*s, w*s);
    }
    
    inline cgmvec4 cgmvec4::operator / (cg::real s)const
    {
        return cgmvec4(x/s, y/s, z/s, w/s);
    }
    
    inline void cgmvec4::operator += (const cgmvec4 &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
    }
    
    inline void cgmvec4::operator -= (const cgmvec4 &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
    }
    
    inline void cgmvec4::operator *= (const cgmvec4 &v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;
    }
    
    inline void cgmvec4::operator += (cg::real s)
    {
        x += s;
        y += s;
        z += s;
        w += s;
    }
    
    inline void cgmvec4::operator -= (cg::real s)
    {
        x -= s;
        y -= s;
        z -= s;
        w -= s;
    }
    
    inline void cgmvec4::operator *= (cg::real s)
    {
        x *= s;
        y *= s;
        z *= s;
        w *= s;
    }
    
    inline void cgmvec4::operator /= (cg::real s)
    {
        x /= s;
        y /= s;
        z /= s;
        w /= s;
    }
}}


namespace kege{namespace cg{
    
    inline cgmvec4 abs4(const cgmvec4& a)
    {
        return cgmvec4(cg::abs(a.x), cg::abs(a.y), cg::abs(a.z), cg::abs(a.w));
    }
    
    inline cgmvec4 floor4(const cgmvec4& v)
    {
        return cgmvec4(::floor(v.x), ::floor(v.y), ::floor(v.z), ::floor(v.w));
    }
    
    inline cgmvec4 fract4(const cgmvec4& v)
    {
        return cgmvec4(cg::fract(v.x), cg::fract(v.y), cg::fract(v.z), cg::fract(v.w));
    }
    
    /** inline function. compute the dot product of a vectors. */
    inline double dot4 (const cgmvec4 &a, const cgmvec4 &b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
    }
    
    /** inline function. compute the math::square magnitude of a vectors. */
    inline double magn4sq (const cgmvec4& v)
    {
        return dot4(v,v);
    }
    
    /** inline function. compute the magnitude of a vectors. */
    inline double magn4 (const cgmvec4& v)
    {
        return sqrt(dot4(v,v));
    }
    
    inline cgmvec4 normalize4 (const cgmvec4 &a)
    {
        return a * cg::invrs( magn4(a) );
    }
    
    /** inline function. compute the distance between two vectors. */
    inline double dist4 (const cgmvec4 &a, const cgmvec4 &b)
    {
        return sqrt(cg::sq(a.x-b.x) + cg::sq(a.y-b.y) + cg::sq(a.z-b.z) + cg::sq(a.w-b.w));
    }
  
    inline cgmvec4 rgba(unsigned red, unsigned green, unsigned blue)
    {
        return cgmvec4
        (  cg::real(red)   * _1_DIV_255
         , cg::real(green) * _1_DIV_255
         , cg::real(blue)  * _1_DIV_255
         , 255.0 * _1_DIV_255  );
    }
    
    inline cgmvec4 hex2rgba(unsigned int n)
    {
        return cgmvec4
        (  ((n >> 24) & 0xFF)*_1_DIV_255
         , ((n >> 16) & 0xFF)*_1_DIV_255
         , ((n >>  8) & 0xFF)*_1_DIV_255
         , ((n >>  0) & 0xFF)*_1_DIV_255 );
    }
    
    inline unsigned int rgba2hex(cgmvec4 const& v)
    {
        return ((int(v.x*255) & 0xff) << 24) + ((int(v.y*255) & 0xff) << 16) + ((int(v.z*255) & 0xff) << 8) + ((int(v.z*255) & 0xff) << 0);
    }
    
    inline cgmvec4 color(short r,short g,short b,short a)
    {
        return cgmvec4(float(r*_1_DIV_255), float(g*_1_DIV_255), float(b*_1_DIV_255), float(a*_1_DIV_255));
    }
    
    cgmvec4 center(const cgmvec4 *A, const int size);
}}


namespace kege{namespace cg{
    
    inline cgmvec4 operator +(cg::real k, const cgmvec4 &v)
    {
        return cgmvec4(k+v.x, k+v.y, k+v.z, k+v.w);
    }
    
    inline cgmvec4 operator -(cg::real k, const cgmvec4 &v)
    {
        return cgmvec4(k-v.x, k-v.y, k-v.z, k-v.w);
    }
    
    inline cgmvec4 operator *(cg::real k, const cgmvec4 &v)
    {
        return cgmvec4(k*v.x, k*v.y, k*v.z, k*v.w);
    }
    
    inline cgmvec4 operator /(cg::real k, const cgmvec4 &v)
    {
        return cgmvec4
        (  k/cg::assert_zero(v.x)
         , k/cg::assert_zero(v.y)
         , k/cg::assert_zero(v.z)
         , k/cg::assert_zero(v.w)  );
    }
    
    inline bool operator == (const cgmvec4 &v, cg::real s)
    {
        return cg::magn4sq(v) == s*s;
    }
    
    inline bool operator == (cg::real s, const cgmvec4 &v)
    {
        return cg::magn4sq(v) == s*s;
    }
    
    inline bool operator != (const cgmvec4 &v, cg::real s)
    {
        return cg::magn4sq(v) != s*s;
    }
    
    inline bool operator != (cg::real s, const cgmvec4 &v)
    {
        return cg::magn4sq(v) != s*s;
    }
    
    inline bool operator <= (const cgmvec4 &v, cg::real s)
    {
        return cg::magn4sq(v) <= s*s;
    }
    
    inline bool operator >= (cg::real s, const cgmvec4 &v)
    {
        return cg::magn4sq(v) >= s*s;
    }
    
    inline bool operator < (const cgmvec4 &v, cg::real s)
    {
        return cg::magn4sq(v) < s*s;
    }
    
    inline bool operator > (cg::real s, const cgmvec4 &v)
    {
        return cg::magn4sq(v) < s*s;
    }
    
    inline bool operator == (const cgmvec4 &l, const cgmvec4 &r)
    {
        return (l.x == r.x) && (l.y == r.y) && (l.z == r.z) && (l.w == r.w);
    }
    
    inline bool operator != (const cgmvec4 &l, const cgmvec4 &r)
    {
        return (l.x != r.x) || (l.y != r.y) || (l.z != r.z) || (l.w != r.w);
    }
    
    inline bool operator <= (const cgmvec4 &l, const cgmvec4 &r)
    {
        return cg::magn4sq(l) <= cg::magn4sq(r);
    }
    
    inline bool operator >= (const cgmvec4 &l, const cgmvec4 &r)
    {
        return cg::magn4sq(l) >= cg::magn4sq(r);
    }
    
    inline bool operator < (const cgmvec4 &l, const cgmvec4 &r)
    {
        return cg::magn4sq(l) <= cg::magn4sq(r);
    }
    
    inline bool operator > (const cgmvec4 &l, const cgmvec4 &r)
    {
        return cg::magn4sq(l) >= cg::magn4sq(r);
    }
}}
#endif /* vec4_hpp */
