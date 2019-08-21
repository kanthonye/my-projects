//
//  vec3.hpp
//  vector-math
//
//  Created by Kenneth A Esdaile on 6/6/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef vec3_hpp
#define vec3_hpp
#include "../../../graphics/core/cgmath/vec2.hpp"
namespace kege{namespace cg{
    
    class cgmvec3
    {   public:
        
        friend inline cgmvec3 operator +(cg::real k, const cgmvec3 &v);
        friend inline cgmvec3 operator -(cg::real k, const cgmvec3 &v);
        friend inline cgmvec3 operator *(cg::real k, const cgmvec3 &v);
        friend inline cgmvec3 operator /(cg::real k, const cgmvec3 &v);
        
        inline void operator () (cg::real x, cg::real y, cg::real z);
        inline void operator () (cg::real (*v)[3]);
        inline void operator () (cg::real val);
        
        inline cgmvec3 operator + (const cgmvec3 &v3) const;
        inline cgmvec3 operator - (const cgmvec3 &v3) const;
        inline cgmvec3 operator * (const cgmvec3 &v3) const;
        inline cgmvec3 operator / (const cgmvec3 &v3) const;
        
        inline cgmvec3 operator + (cg::real s) const;
        inline cgmvec3 operator - (cg::real s) const;
        inline cgmvec3 operator * (cg::real s) const;
        inline cgmvec3 operator / (cg::real s) const;
        
        inline void operator += (const cgmvec3 &v3);
        inline void operator -= (const cgmvec3 &v3);
        inline void operator *= (const cgmvec3 &v3);
        
        inline void operator += (cg::real s);
        inline void operator -= (cg::real s);
        inline void operator *= (cg::real s);
        inline void operator /= (cg::real s);
        
        inline float operator [] (unsigned short n)const;
        inline float& operator [] (unsigned short n);
        
        inline cgmvec3 operator - (void)const;
        
        cgmvec3 (cg::real x, cg::real y, cg::real z);
        cgmvec3 (cg::real const (*v)[3]);
        cgmvec3 (cg::real val);
        cgmvec3 (void){}
        
        union
        {
            cg::real data[3];
            float rgb[3];
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
        
        static const cgmvec3 forward;
        static const cgmvec3 right;
        static const cgmvec3 zero;
        static const cgmvec3 one;
        static const cgmvec3 up;
    };
    
    typedef cgmvec3 point3;
    typedef cgmvec3 color3;

    inline cgmvec3::cgmvec3 (cg::real x, cg::real y, cg::real z)
    :   x(x) , y(y) , z(z)
    {
    }
    
    inline cgmvec3::cgmvec3 (cg::real const (*v)[3])
    :   x((*v)[0]) , y((*v)[1]) , z((*v)[2])
    {
    }
    
    inline cgmvec3::cgmvec3 (cg::real v)
    :   x(v) , y(v) , z(v)
    {
    }
    
    inline void cgmvec3::operator () (cg::real vx, cg::real vy, cg::real vz)
    {
        x = vx;
        y = vy;
        z = vz;
    }
    
    inline void cgmvec3::operator () (cg::real (*v)[3])
    {
        x = (*v)[0];
        y = (*v)[1];
        z = (*v)[2];
    }
    
    inline void cgmvec3::operator () (cg::real val)
    {
        x = y = z = val;
    }
    
    inline cgmvec3 cgmvec3::operator + (const cgmvec3 &v)const
    {
        return cgmvec3(x+v.x, y+v.y, z+v.z);
    }
    
    inline cgmvec3 cgmvec3::operator - (const cgmvec3 &v)const
    {
        return cgmvec3(x-v.x, y-v.y, z-v.z);
    }
    
    inline cgmvec3 cgmvec3::operator * (const cgmvec3 &v)const
    {
        return cgmvec3(x*v.x, y*v.y, z*v.z);
    }
    
    inline cgmvec3 cgmvec3::operator / (const cgmvec3 &v)const
    {
        return cgmvec3(x/cg::assert_zero(v.x), y/cg::assert_zero(v.y), z/cg::assert_zero(v.z));
    }
    
    inline cgmvec3 cgmvec3::operator + (cg::real s)const
    {
        return cgmvec3(x+s, y+s, z+s);
    }
    
    inline cgmvec3 cgmvec3::operator - (cg::real s)const
    {
        return cgmvec3(x-s, y-s, z-s);
    }
    
    inline cgmvec3 cgmvec3::operator * (cg::real s)const
    {
        return cgmvec3(x*s, y*s, z*s);
    }
    
    inline cgmvec3 cgmvec3::operator / (cg::real s)const
    {
        return cgmvec3(x/s, y/s, z/s);
    }
    
    inline void cgmvec3::operator += (const cgmvec3 &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
    }
    
    inline void cgmvec3::operator -= (const cgmvec3 &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }
    
    inline void cgmvec3::operator *= (const cgmvec3 &v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
    }
    
    inline void cgmvec3::operator += (cg::real s)
    {
        x += s;
        y += s;
        z += s;
    }
    
    inline void cgmvec3::operator -= (cg::real s)
    {
        x -= s;
        y -= s;
        z -= s;
    }
    
    inline void cgmvec3::operator *= (cg::real s)
    {
        x *= s;
        y *= s;
        z *= s;
    }
    
    inline void cgmvec3::operator /= (cg::real s)
    {
        x /= s;
        y /= s;
        z /= s;
    }
    
    inline float& cgmvec3::operator [] (unsigned short n)
    {
        return data[n];
    }
    inline float cgmvec3::operator [] (unsigned short n)const
    {
        return data[n];
    }
    
    inline cgmvec3 cgmvec3::operator -()const
    {
        return cgmvec3(-x,-y,-z);
    }
    
}}
    

namespace kege{namespace cg{
    
    inline cgmvec3 abs3(const cgmvec3& a)
    {
        return cgmvec3(cg::abs(a.x), cg::abs(a.y), cg::abs(a.z));
    }
    
    inline cgmvec3 floor3(const cgmvec3& v)
    {
        return cgmvec3(::floor(v.x), ::floor(v.y), ::floor(v.z));
    }
    
    inline cgmvec3 fract3(const cgmvec3& v)
    {
        return cgmvec3(cg::fract(v.x), cg::fract(v.y), cg::fract(v.z));
    }
    
    /** inline function. compute the dot product of a vectors. */
    inline double dot3(const cgmvec3 &a, const cgmvec3 &b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }
    
    /** inline function. compute the math::square magnitude of a vectors. */
    inline double magn3sq (const cgmvec3& v)
    {
        return dot3(v,v);
    }
    
    /** inline function. compute the magnitude of a vectors. */
    inline double magn3 (const cgmvec3& v)
    {
        return sqrt(dot3(v,v));
    }

    inline cgmvec3 normalize3(const cgmvec3 &a)
    {
        return a * cg::invrs( magn3(a) );
    }
    
    /*! inline function. compute the cross prouduct of two vectors. */
    inline cgmvec3 cross3 (const cgmvec3 &a, const cgmvec3 &b)
    {
        return cgmvec3( (a.y*b.z - a.z*b.y), (a.z*b.x - a.x*b.z), (a.x*b.y - a.y*b.x) );
    }
    
    /*! inline function. compute the cross prouduct of two vectors. */
    inline double triple_product (const cgmvec3 &a, const cgmvec3 &b, const cgmvec3 &c)
    {
        return a.x*(b.y*c.z - b.z*c.y) - a.y*(b.z*c.x - b.x*c.z) + a.z*(b.x*c.y - b.y*c.x);
    }
    
    /** inline function. compute the cross prouduct of two vectors. */
    inline cgmvec3 cross3(const cgmvec3 &v, cg::real x, cg::real y, cg::real z)
    {
        return cg::cross3(v, cgmvec3(x,y,z));
    }
    
    /** inline function. compute the cross prouduct of two vectors. */
    inline cgmvec3 cross3(cg::real x, cg::real y, cg::real z, const cgmvec3 &v)
    {
        return cg::cross3(cgmvec3(x,y,z), v);
    }
    
    /** inline function. compute the distance between two vectors. */
    inline double distant (const cgmvec3 &a, const cgmvec3 &b)
    {
        return sqrt( cg::sq(a.x-b.x) + cg::sq(a.y-b.y) + cg::sq(a.z-b.z) );
    }
    
    /** inline function. compute the projection of one vectors onto another, return it magnitude. */
    inline double scalar_proj(const cgmvec3 &a, const cgmvec3 &b)
    {
        return dot3(a,b) * cg::invrs( magn3(b) );
    }
    
    inline cgmvec3 vec_proj(const cgmvec3 &a, const cgmvec3 &b)
    {
        return a * cg::dot3(a,b) * cg::invrs( magn3(b) );
    }
    
    /*! compute the cross prouduct of two vectors, then normalize it. */
    inline cgmvec3 orthonormal(cgmvec3 const&B, cgmvec3 const&C)
    {
        return normalize3( cross3(B, C) );
    }
    
    /*! compute the face normal of triangle a,b,c. */
    inline cgmvec3 face_normal(const cgmvec3 &a, const cgmvec3 &b, const cgmvec3 &c)
    {
        return cg::cross3(b - a, c - a);
    }
    
    inline cgmvec3 face_orthonormal(const cgmvec3 &a, const cgmvec3 &b, const cgmvec3 &c)
    {
        return orthonormal(b - a, c - a);
    }
    
    /*! calculate the radian between two vector, and return the angle in radian. */
    inline cg::real radian(const cgmvec3 &a, const cgmvec3 &b)
    {
        return acos(dot3(a,b) * cg::invrs(magn3(a) * magn3(b)));
    }
    
    /*! calculate the angle between two vector, and return the angle in angle. */
    inline cg::real angle(const cgmvec3 &a, const cgmvec3 &b)
    {
        return cg::rad2deg( radian(a,b) );
    }
    
    /*! compute the angle between a vectors and the zx-plane. */
    inline float radian(const cgmvec3 &a)
    {
        return cg::radian(a, cgmvec3(a.x, 0.0f, a.z));
    }
    
    /*! compute the angle between a vectors and the zx-plane. */
    inline float angle(const cgmvec3 &a)
    {
        return cg::rad2deg( cg::radian(a) );
    }
    
    /*! compute the false length of a vector : but very fast */
    inline double psuedo_length(const cgmvec3 &a)
    {
        return cg::abs(a.x) + cg::abs(a.y) + cg::abs(a.z);
    }
    
    inline cgmvec3 rgb(unsigned red, unsigned green, unsigned blue)
    {
        return cgmvec3(cg::real(red) * _1_DIV_255, cg::real(green) * _1_DIV_255, cg::real(blue) * _1_DIV_255);
    }
    
    inline cgmvec3 hex2rgb(unsigned int n)
    {
        return cgmvec3(((n >> 24) & 0xFF)*_1_DIV_255, ((n >> 16) & 0xFF)*_1_DIV_255, ((n >>  8) & 0xFF)*_1_DIV_255);
    }
    
    inline unsigned int rgb2hex(cgmvec3 const& v)
    {
        return ((int(v.x*255) & 0xff) << 24) + ((int(v.y*255) & 0xff) << 16) + ((int(v.z*255) & 0xff) << 8);
    }
    
    inline cgmvec3 color(short r,short g,short b)
    {
        return cgmvec3(float(r*_1_DIV_255), float(g*_1_DIV_255), float(b*_1_DIV_255));
    }
    
    cgmvec3 center(const cgmvec3 *A, const int size);
    
    void calc_dir_vecs(cg::vec3& forward, cg::vec3& right, cg::vec3& up, const float x, const float y);
}}
    

namespace kege{namespace cg{
    
    inline cgmvec3 operator +(cg::real k, const cgmvec3 &v)
    {
        return cgmvec3(k+v.x, k+v.y, k+v.z);
    }
    
    inline cgmvec3 operator -(cg::real k, const cgmvec3 &v)
    {
        return cgmvec3(k-v.x, k-v.y, k-v.z);
    }
    
    inline cgmvec3 operator *(cg::real k, const cgmvec3 &v)
    {
        return cgmvec3(k*v.x, k*v.y, k*v.z);
    }
    
    inline cgmvec3 operator /(cg::real k, const cgmvec3 &v)
    {
        return cgmvec3(k/cg::assert_zero(v.x), k/cg::assert_zero(v.y), k/cg::assert_zero(v.z));
    }
    
    inline bool operator == (const cgmvec3 &v, cg::real s)
    {
        return cg::magn3sq(v) == s*s;
    }
    
    inline bool operator == (cg::real s, const cgmvec3 &v)
    {
        return cg::magn3sq(v) == s*s;
    }
    
    inline bool operator != (const cgmvec3 &v, cg::real s)
    {
        return cg::magn3sq(v) != s*s;
    }
    
    inline bool operator != (cg::real s, const cgmvec3 &v)
    {
        return cg::magn3sq(v) != s*s;
    }
    
    inline bool operator <= (const cgmvec3 &v, cg::real s)
    {
        return cg::magn3sq(v) <= s*s;
    }
    
    inline bool operator >= (cg::real s, const cgmvec3 &v)
    {
        return cg::magn3sq(v) >= s*s;
    }
    
    inline bool operator < (const cgmvec3 &v, cg::real s)
    {
        return cg::magn3sq(v) < s*s;
    }
    
    inline bool operator > (cg::real s, const cgmvec3 &v)
    {
        return cg::magn3sq(v) < s*s;
    }
    
    inline bool operator == (const cgmvec3 &l, const cgmvec3 &r)
    {
        return cg::magn3sq(l) == cg::magn3sq(r);
    }
    
    inline bool operator != (const cgmvec3 &l, const cgmvec3 &r)
    {
        return cg::magn3sq(l) != cg::magn3sq(r);
    }
    
    inline bool operator <= (const cgmvec3 &l, const cgmvec3 &r)
    {
        return cg::magn3sq(l) <= cg::magn3sq(r);
    }
    
    inline bool operator >= (const cgmvec3 &l, const cgmvec3 &r)
    {
        return cg::magn3sq(l) >= cg::magn3sq(r);
    }
    
    inline bool operator < (const cgmvec3 &l, const cgmvec3 &r)
    {
        return cg::magn3sq(l) <= cg::magn3sq(r);
    }
    
    inline bool operator > (const cgmvec3 &l, const cgmvec3 &r)
    {
        return cg::magn3sq(l) >= cg::magn3sq(r);
    }
}}
#endif /* vec3_hpp */
