//
//  vec2.hpp
//  vector-math
//
//  Created by Kenneth A Esdaile on 6/6/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef vec2_hpp
#define vec2_hpp
#include "../../../graphics/core/cgmath/coremath.hpp"
namespace kege{namespace cg{
    
    class cgmvec2
    {   public:
        
        inline void operator () (const cg::real x, const cg::real y);
        inline void operator () (const cg::real val);
        
        inline cgmvec2 operator + (const cgmvec2 &v2)const;
        inline cgmvec2 operator - (const cgmvec2 &v2)const;
        inline cgmvec2 operator * (const cgmvec2 &v2)const;
        
        inline cgmvec2 operator + (const cg::real s)const;
        inline cgmvec2 operator - (const cg::real s)const;
        inline cgmvec2 operator * (const cg::real s)const;
        inline cgmvec2 operator / (const cg::real s)const;
        inline cgmvec2 operator - (void)const;
        
        inline void operator += (const cgmvec2 &v);
        inline void operator -= (const cgmvec2 &v);
        inline void operator *= (const cgmvec2 &v);
        
        inline void operator += (const cg::real s);
        inline void operator -= (const cg::real s);
        inline void operator *= (const cg::real s);
        inline void operator /= (const cg::real s);
        
        //cg::real  operator[](ushort n)const;
        //cg::real& operator[](ushort n);
        
        cgmvec2 (const cg::real x, const cg::real y);
        cgmvec2 (const cg::real (*v)[2]);
        cgmvec2 (const cg::real val);
        cgmvec2 (void);
        
        union
        {
            struct{cg::real x,y;};
            cg::real data[2];
        };
    };
    
    typedef cgmvec2 point2;
    
    inline void cgmvec2::operator () (cg::real px, cg::real py)
    {
        x = px;
        y = py;
    }

    inline void cgmvec2::operator () (const cg::real val)
    {
        x = val;
        y = val;
    }
    
    inline cgmvec2 cgmvec2::operator + (const cgmvec2 &v)const
    {
        return cgmvec2(x+v.x, y+v.y);
    }
    
    inline cgmvec2 cgmvec2::operator - (const cgmvec2 &v)const
    {
        return cgmvec2(x-v.x, y-v.y);
    }
    
    inline cgmvec2 cgmvec2::operator * (const cgmvec2 &v)const
    {
        return cgmvec2(x*v.x, y*v.y);
    }
    
    inline cgmvec2 cgmvec2::operator - (void)const
    {
        return cgmvec2(-x, -y);
    }
    
    inline cgmvec2 cgmvec2::operator + (cg::real s)const
    {
        return cgmvec2(x+s, y+s);
    }
    
    inline cgmvec2 cgmvec2::operator - (cg::real s)const
    {
        return cgmvec2(x-s, y-s);
    }
    
    inline cgmvec2 cgmvec2::operator * (cg::real s)const
    {
        return cgmvec2(x*s, y*s);
    }
    
    inline cgmvec2 cgmvec2::operator / (cg::real s)const
    {
        return cgmvec2(x/s, y/s);
    }
    
    inline void cgmvec2::operator += (const cgmvec2 &v)
    {
        x += v.x;
        y += v.y;
    }
    
    inline void cgmvec2::operator -= (const cgmvec2 &v)
    {
        x -= v.x;
        y -= v.y;
    }
    
    inline void cgmvec2::operator *= (const cgmvec2 &v)
    {
        x *= v.x;
        y *= v.y;
    }
    
    inline void cgmvec2::operator += (cg::real s)
    {
        x += s;
        y += s;
    }
    
    inline void cgmvec2::operator -= (cg::real s)
    {
        x -= s;
        y -= s;
    }
    
    inline void cgmvec2::operator *= (cg::real s)
    {
        x *= s;
        y *= s;
    }
    
    inline void cgmvec2::operator /= (cg::real s)
    {
        x /= s;
        y /= s;
    }
    
    inline cgmvec2::cgmvec2 (const cg::real (*v)[2])
    :   x(*v[0])
    ,   y(*v[1])
    {
    }
    
    inline cgmvec2::cgmvec2 (cg::real vx, cg::real vy)
    :   x(vx)
    ,   y(vy)
    {
    }
    
    inline cgmvec2::cgmvec2 (const cg::real val)
    :   x(val)
    ,   y(val)
    {
    }
    
    inline cgmvec2::cgmvec2 (void)
    {
    }
}}
    

namespace kege{namespace cg{
    
    inline bool operator == (const cgmvec2& l, const cgmvec2& r)
    {
        return (l.x==r.x && l.y==r.y);
    }
    
    inline bool operator != (const cgmvec2& l, const cgmvec2& r)
    {
        return (l.x!=r.x && l.y!=r.y);
    }
    
    inline bool operator <= (const cgmvec2& l, const cgmvec2& r)
    {
        return (l.x*l.x + l.y*l.y) <= (r.x*r.x + r.y*r.y);
    }
    
    inline bool operator >= (const cgmvec2& l, const cgmvec2& r)
    {
        return (l.x*l.x + l.y*l.y) >= (r.x*r.x + r.y*r.y);
    }
    
    inline bool operator < (const cgmvec2& l, const cgmvec2& r)
    {
        return (l.x*l.x + l.y*l.y) < (r.x*r.x + r.y*r.y);
    }
    
    inline bool operator > (const cgmvec2& l, const cgmvec2& r)
    {
        return (l.x*l.x + l.y*l.y) > (r.x*r.x + r.y*r.y);
    }
    
    inline bool operator == (const cgmvec2 &v, const cg::real s)
    {
        return (v.x*v.x + v.y*v.y) == s*s;
    }
    
    inline bool operator == (const cg::real s, const cgmvec2 &v)
    {
        return (v.x*v.x + v.y*v.y) == s*s;
    }
    
    inline bool operator != (const cgmvec2 &v, const cg::real s)
    {
        return (v.x*v.x + v.y*v.y) != s*s;
    }
    
    inline bool operator != (const cg::real s, const cgmvec2 &v)
    {
        return (v.x*v.x + v.y*v.y) != s*s;
    }
    
    inline bool operator <= (const cgmvec2& v, const cg::real s)
    {
        return (v.x*v.x + v.y*v.y) <= s*s;
    }
    
    inline bool operator >= (const cg::real s, const cgmvec2& v)
    {
        return (v.x*v.x + v.y*v.y) >= s*s;
    }
    
    inline bool operator < (const cgmvec2& v, const cg::real s)
    {
        return (v.x*v.x + v.y*v.y) < s*s;
    }
    
    inline bool operator > (const cg::real s, const cgmvec2& v)
    {
        return (v.x*v.x + v.y*v.y) < s*s;
    }
}}

namespace kege{namespace cg{
    
    inline cg::real dot2(const cgmvec2 &a, const cgmvec2 &b)
    {
        return (a.x * b.x) + (a.y * b.y);
    }
    
    inline float cross2(const cgmvec2& u, const cgmvec2& v)
    {
        return u.y * v.x - u.x * v.y;
    }
    
    inline cg::real magn2sq (const cgmvec2 & A)
    {
        return cg::dot2(A, A);
    }
    
    inline cg::real magn2(const cgmvec2 & A)
    {
        return sqrt(dot2(A, A));
    }
    
    inline cg::real distant2(const cgmvec2 &A, const cgmvec2 &B)
    {
        return sqrt( cg::sq(A.x-B.x) + cg::sq(A.y-B.y) );
    }
    
    inline cgmvec2 center2(const cgmvec2 &A, const cgmvec2 &B, const cgmvec2 &C)
    {
        return cgmvec2((A.x + B.x + C.x)/2.0f, (A.y + B.y + C.y)/2.0f);
    }
    
    inline cg::real area_of_triangle(const cgmvec2 &A, const cgmvec2 &B)
    {
        return (cg::magn2(A) * cg::magn2(B))/2.0f;
    }
    
    inline cg::real angle2(const cgmvec2 &A, const cgmvec2 &B)
    {
        return 1.0f / ( cos( cg::deg2rad( cg::dot2(A,B) / ( cg::magn2(A) * cg::magn2(B)))));
    }
    
    inline cg::real angle2(const cgmvec2 &A)
    {
        cgmvec2 b = cgmvec2(A.x, 0.0f);
        return 1.0f / ( cos( cg::deg2rad( cg::dot2(A,b) / ( cg::magn2(A) * cg::magn2(b)))));
    }
    
    inline cgmvec2 normalize2(const cgmvec2 &A)
    {
        cg::real  m = cg::magn2(A);
        m = (m==0)? 1.0f: 1.0f/m;
        return cgmvec2(A.x*m, A.y*m);
    }
    
    inline cg::real cosAngle2(const cgmvec2 &A)
    {
        cgmvec2 b;
        if (A.x != 0 || A.y != 0) return 0;
        b = cgmvec2(A.x, 0.0f);
        return cg::dot2(A, b) / (cg::magn2(A) * cg::magn2(b));
    }
    
    inline cg::real sinAngle2(const cgmvec2 &A)
    {
        cgmvec2 b;
        if (A.x != 0 || A.y != 0) return 0;
        b = cgmvec2(0.0f, A.y);
        return cg::dot2(A, b) / (cg::magn2(A) * cg::magn2(b));
    }
    
    inline cgmvec2 rotate2(cg::real rad, cgmvec2 &p)
    {
        cg::real c = cosf(rad);
        cg::real s = sinf(rad);
        return cgmvec2(c*p.x + s*p.y, c*p.y - s*p.x);
    }
    
    inline cgmvec2 translate2(cgmvec2 &vertex, cg::real x, cg::real y)
    {
        return cgmvec2(vertex.x+x, vertex.y+y);
    }
    
    inline cgmvec2 scale2(cgmvec2 &vertex, cg::real sx, cg::real sy)
    {
        return cgmvec2(vertex.x*sx, vertex.y*sy);
    }
    
    inline cgmvec2 floor2(const cgmvec2& v)
    {
        return cgmvec2(floor(v.x), floor(v.y));
    }
    
    inline cg::real scalar_proj2(const cgmvec2 &A, const cgmvec2 &B)
    {
        return ( cg::dot2(A,B) * cg::invrs(cg::magn2(B)));
    }
    
    inline cgmvec2 vec_proj2(const cgmvec2 &a, const cgmvec2 &b)
    {
        return (a * cg::dot2(a,b)) * cg::invrs(cg::magn2(a));
    }
}}
#endif /* vec2_hpp */
