//
//  core.hpp
//  vector-math
//
//  Created by Kenneth A Esdaile on 6/6/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef core_hpp
#define core_hpp
#include <cmath>
#include <time.h>
#include <stdlib.h>

#define ONE             0x1
#define ZERO            0x0
#define FALSE           0x0
#define TRUE            0x1
#define VALID           0x0
#define INVALID         0x1

#define _CLOSE_TO_ZERO_ 1e-05
#define _1_DIV_255      0.0039215686
#define _1_DIV_765      0.0013071895
#define EPSILON         1.19209e-07

#define _E_             2.71828182845904509079559829843
#define _GOLDEN_RATIO_  1.61803398874989490252573887119
#define _PI_            3.14159265358979311599796346854
#define _2PI_           6.28318530717958623199592693709
#define _PI_OVER_180_   0.01745329251994329547437168059
#define _180_OVER_PI_   57.2957795130823228646477218717
#define _PI_OVER_360_   0.00872664625
#define ONE_DEG_IN_RAD  0.01745329251

#define _sqrt_2_        1.4142135623730951454746218587
#define _sqrt_3_        0.7320508075688772935274463415
#define _sqrt_5_        2.2360679774997898050514777423
#define _sqrt_6_        2.4494897427831778813356322643
#define _sqrt_7_        2.6457513110645907161710965738
#define _sqrt_8_        2.8284271247461902909492437174
#define _sqrt_10_       3.1622776601683795227870632516
#define _sqrt_13_       3.6055512754639891248586991423
#define _sqrt_14_       3.7416573867739413294941641652
#define _sqrt_15_       3.8729833462074170213895740744
#define _1_OVER_sqrt2_  0.7071067811865474617150084668
#define _1_OVER_sqrt5_  0.4472135954999579277036048097

#define cgmvec2  vec2
#define cgmvec3  vec3
#define cgmvec4  vec4
#define cgmquat  quat
#define cgmmat22 mat22
#define cgmmat33 mat33
#define cgmmat44 mat44

// scalar math
namespace kege{namespace cg{
    
    /** check for division by zero @return 1.0 if value is zero, or value if value is not zero */
    template <typename var>
    var assert_zero(var val)
    {
        return (val == 0)? 1.0: val;
    }
    
    /** invert a value @return (1.0 / val) */
    inline double invrs(double val)
    {
        return (val == 0.0)? 1.0: 1.0 / val;
    }
    
    /** converts degree to radian @return radian */
    template <typename var>
    inline var deg2rad(var deg)
    {
        return deg * _PI_OVER_180_;
    }
    
    /** converts radian to degree @return degree */
    template <typename var>
    inline var rad2deg(var deg)
    {
        return deg * _180_OVER_PI_;
    }
    
    /** return the val*val */
    template <typename var>
    inline var sq(var v)
    {
        return v*v;
    }
    
    /** return the +val */
    template <typename var>
    inline var abs(var v)
    {
        return (v < 0x0) ? -v : v;
    }
    
    template <typename var>
    /** @brief return the fraction part of a floating point number ex: 5.125 returns 0.125 */
    inline var fract(var n)
    {
        return n - int(n);
    }
    
    /** keep value v between values a and b */
    template<typename type, typename typa, typename typb>  type clamp(type val, typa min, typb max)
    {
        return (val <= min) ? min: (val >= max)? max: val;
    }
    
    /** @brief return the smallest of the two values */
    template<typename var, typename varA>
    inline var min(var x, varA y)
    {
        return (x<y) ? x: y;
    }
    
    /** return the smallest of the three values */
    template<typename type, typename typa, typename typb>
    inline type min(type x, typa y, typb z)
    {
        return (x<y && x<z) ? x: (y<z)? y: z;
    }
    
    /** return the smallest of the four values */
    template<typename type, typename typa, typename typb, typename typc>
    inline type min(type x, typa y, typb z, typc w)
    {
        return (x<y && x<z && x<w) ? x: (y<z && y<w)? y: (z<w)? z: w;
    }
    
    /** return the largest of the two values */
    template<typename type, typename typa>  inline type max(type x, typa y)
    {
        return (x>y) ? x: y;
    }
    
    /** return the largest of the three values */
    template<typename type, typename typa, typename typb>
    inline type max(type x, typa y, typb z)
    {
        return (x>y&&x>z) ? x: (y>z)? y: z;
    }
    
    /** return the largest of the four values */
    template<typename type, typename typa, typename typb, typename typc>
    inline type max(type x, typa y, typb z, typc w)
    {
        return (x>y && x>z && x>w) ? x: (y>z && y>w)? y: (z>w)? z: w;
    }
    
    /** cycle function loop a value between values min and max */
    template<typename type, typename typa, typename typb>
    type cycle(type val, typa min, typb max)
    {
        return (val > max)? val-max : (val < min) ? min-val : val;
        //if (val > max) return val-max;
        //if (val < min) return min-val;
        //return val;
    }
    
    /** linear interpulate between values a and b using t. t being {0 <= t <= 1} */
    template<typename type, typename typa>  inline type lerp(type a, typa b, double t)
    {
        return (b - a) * t + a;
        //return (type(0x1) - t) * a + t * b;
    }
    
    /** linear interpulate between values a and b using t. t being {0 <= t <= 1} */
    template<typename type>  inline void swap(type& a, type& b, type& t)
    {
        t=a;
        a=b;
        b=t;
    }
    
    /** start is starting speed, end is the final speed, step is the speed to increment by */
    inline float smoothing(float start, const float end,const float step)
    {
        //if(start >= -step && start <= step) start = 0.0f;
        float ds = end - start;
        return (ds > step) ? (start + step) : ( (ds < -step) ? (start - step) : end );
    }
    
    inline float smoothin(float start, const float end,const float step)
    {
        if (start >= -step && start <= step) start = 0.0f;
        float ds = end - start;
        return (ds > step)? start + step: end;
    }
    
    inline float smoothout(float start, const float end,const float step)
    {
        if (start >= -step && start <= step) start = 0.0f;
        float ds = end - start;
        return (ds < step)? start - step: end;
    }
    
    template<typename typa, typename typb, typename typc>
    inline typa unitize(typa val, typb min, typc max)
    {
        val = cg::clamp(val, min, max);
        return (val - min) / (max - min);
    }
    
    /** flip an image or array along its horizontal */
    template<typename type> void flip_hori(int width, int height, type* m)
    {
        type temp;
        long a,b,wz,x,z;
        long w  = width-1;
        long hw = width/2;
        for (z=0; z<height; z++)
        {
            wz = (width*z);
            for (x=0; x<hw; x++)
            {
                a = wz + x;
                b = wz + w - x;
                temp = m[a];
                m[a] = m[b];
                m[b] = temp;
            }
        }
    }
    
    /** flip an image or array along its vertical */
    template<typename type> void flip_vert(int width, int height, type* m)
    {
        type temp;
        long a,b,x,z;
        long h  = height-1;
        long hh = height/2;
        for (x=0; x<width; x++)
        {
            for (z=0; z<hh; z++)
            {
                a = (width * z) + x;
                b = (width * (h-z)) + x;
                temp = m[a];
                m[a] = m[b];
                m[b] = temp;
            }
        }
    }
    
    inline double unitize(double val, double minval, double maxval)
    {
        double length = maxval - minval;
        return cg::min(1.0, cg::max(0.0, ((length - (maxval - val)) / length)));
    }
    
    double invsqrt(double x);
}}


namespace kege{namespace cg{
    
    typedef float          real;
    typedef float          real16;
    typedef double         real32;
    
    typedef long           int64;
    typedef int            int32;
    typedef short          int16;
    typedef char           int8;
    typedef char           byte;
    
    typedef unsigned int   uint;
    typedef unsigned char  uchar;
    typedef unsigned short ushort;
    typedef unsigned long  ulong;
    
    typedef unsigned long  uint64;
    typedef unsigned int   uint32;
    typedef unsigned short uint16;
    typedef unsigned char  uint8;
    typedef unsigned char  ubyte;
    
    template<typename typ> struct var4
    {
        typ x,y,z,w;
        
        var4(typ x, typ y, typ z, typ w)
        :   x(x) , y(y) , z(z) , w(w)
        {
        }
        
        var4(typ v)
        :   x(v) , y(v) , z(v), w(v)
        {
        }
        
        var4()
        {
        }
        
        inline var4 operator + (const var4 &v)const
        {
            return var4(x+v.x, y+v.y, z+v.z, w+v.w);
        }
        
        inline var4 operator - (const var4 &v)const
        {
            return var4(x-v.x, y-v.y, z-v.z, w-v.w);
        }
        
        inline var4 operator * (const var4 &v)const
        {
            return var4(x*v.x, y*v.y, z*v.z, w*v.w);
        }
        
        inline var4 operator / (const var4 &v)const
        {
            return var4
            (  x/cg::assert_zero(v.x)
             , y/cg::assert_zero(v.y)
             , z/cg::assert_zero(v.z)
             , w/cg::assert_zero(v.w) );
        }
        
        inline var4 operator + (cg::real s)const
        {
            return var4(x+s, y+s, z+s, w+s);
        }
        
        inline var4 operator - (cg::real s)const
        {
            return var4(x-s, y-s, z-s, w-s);
        }
        
        inline var4 operator * (cg::real s)const
        {
            return var4(x*s, y*s, z*s, w*s);
        }
        
        inline var4 operator / (cg::real s)const
        {
            return var4(x/s, y/s, z/s, w/s);
        }
        
        inline void operator += (cg::real s)
        {
            x += s;
            y += s;
            z += s;
            w += s;
        }
        
        inline void operator -= (cg::real s)
        {
            x -= s;
            y -= s;
            z -= s;
            w -= s;
        }
        
        inline void operator *= (cg::real s)
        {
            x *= s;
            y *= s;
            z *= s;
            w *= s;
        }
        
        inline void operator /= (cg::real s)
        {
            x /= s;
            y /= s;
            z /= s;
            w /= s;
        }
    };
    
    template<typename typ> struct var3
    {
        typ x,y,z;
        
        var3(typ x, typ y, typ z)
        :   x(x) , y(y) , z(z)
        {
        }
        
        var3(typ v)
        :   x(v) , y(v) , z(v)
        {
        }
        
        var3()
        {
        }
        
        inline var3 operator + (const var3 &v)const
        {
            return var3(x+v.x, y+v.y, z+v.z);
        }
        
        inline var3 operator - (const var3 &v)const
        {
            return var3(x-v.x, y-v.y, z-v.z);
        }
        
        inline var3 operator * (const var3 &v)const
        {
            return var3(x*v.x, y*v.y, z*v.z);
        }
        
        inline var3 operator / (const var3 &v)const
        {
            return var3
            (  x/cg::assert_zero(v.x)
             , y/cg::assert_zero(v.y)
             , z/cg::assert_zero(v.z) );
        }
        
        inline var3 operator + (cg::real s)const
        {
            return var3(x+s, y+s, z+s);
        }
        
        inline var3 operator - (cg::real s)const
        {
            return var3(x-s, y-s, z-s);
        }
        
        inline var3 operator * (cg::real s)const
        {
            return var3(x*s, y*s, z*s);
        }
        
        inline var3 operator / (cg::real s)const
        {
            return var3(x/s, y/s, z/s);
        }
        
        inline void operator += (cg::real s)
        {
            x += s;
            y += s;
            z += s;
        }
        
        inline void operator -= (cg::real s)
        {
            x -= s;
            y -= s;
            z -= s;
        }
        
        inline void operator *= (cg::real s)
        {
            x *= s;
            y *= s;
            z *= s;
        }
        
        inline void operator /= (cg::real s)
        {
            x /= s;
            y /= s;
            z /= s;
        }
    };
    template<typename typ> struct var2
    {
        typ x,y;
        
        var2(typ x, typ y)
        :   x(x) , y(y)
        {
        }
        
        var2(typ v)
        :   x(v) , y(v)
        {
        }
        
        var2()
        {
        }
        
        inline var2 operator + (const var2 &v)const
        {
            return var2(x+v.x, y+v.y);
        }
        
        inline var2 operator - (const var2 &v)const
        {
            return var2(x-v.x, y-v.y);
        }
        
        inline var2 operator * (const var2 &v)const
        {
            return var2(x*v.x, y*v.y);
        }
        
        inline var2 operator / (const var2 &v)const
        {
            return var2
            (  x/cg::assert_zero(v.x)
             , y/cg::assert_zero(v.y) );
        }
        
        inline var2 operator + (cg::real s)const
        {
            return var2(x+s, y+s);
        }
        
        inline var2 operator - (cg::real s)const
        {
            return var2(x-s, y-s);
        }
        
        inline var2 operator * (cg::real s)const
        {
            return var2(x*s, y*s);
        }
        
        inline var2 operator / (cg::real s)const
        {
            return var2(x/s, y/s);
        }
        
        inline void operator += (cg::real s)
        {
            x += s;
            y += s;
        }
        
        inline void operator -= (cg::real s)
        {
            x -= s;
            y -= s;
        }
        
        inline void operator *= (cg::real s)
        {
            x *= s;
            y *= s;
        }
        
        inline void operator /= (cg::real s)
        {
            x /= s;
            y /= s;
        }
    };
    
    typedef var2<int> var2i;
    typedef var3<int> var3i;
    typedef var4<int> var4i;
    typedef var2<int> int2;
    typedef var3<int> int3;
    typedef var4<int> int4;
}}
#endif /* core_hpp */
