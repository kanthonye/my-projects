/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 *  MyFirstGame
 *  Frustum.h
 *  Created by Kenneth Anthony Esdaile on 9/11/15.
 *   Copyright (c) 2015 kae. All rights reserved.
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#ifndef __KEGE_Frustum__
#define __KEGE_Frustum__
#include <stdio.h>
#include <stdlib.h>
#include "mat44.hpp"
namespace kege{namespace gfx{
    class Camera;
    
    
    class Plane
    {
    public:
        
        int TestAABB(float mx, float my, float mz, float nx, float ny, float nz)const;
        int TestAABB(cg::point3 const& min,cg::point3 const& max)const;
        
        int TestRect(float x, float y, float z, float width, float height, float depth)const;
        int TestRect(const cg::point3& center, float w,float h,float d)const;
        
        int TestCube(float x, float y, float z, float size)const;
        int TestCube(const cg::point3& center, float size)const;
        
        int TestSphere(float x, float y, float z, float radius)const;
        int TestSphere(const cg::point3& center, float radius)const;
        
        int TestLine(cg::point3 const& a,cg::point3 const& b)const;
        
        int TestPoint(float x, float y, float z)const;
        int TestPoint(const cg::point3& max)const;
        
        float Distance(float x, float y, float z)const;
        
        int TestPolygon(int numpoints, cg::point3 const* pointlist)const;
        
        Plane(const cg::point3& a,const cg::point3& b,const cg::point3& c,const cg::point3& d);
        Plane();
        
        cg::point3 p;
        cg::vec3   n;
    };
}}

namespace kege{namespace gfx{
    class Camera;
    
    class Frustum
    {
    public:
        
        int TestAABB(float mx, float my, float mz, float nx, float ny, float nz)const;
        int TestAABB(cg::point3 const& min,cg::point3 const& max)const;
        
        int TestRect(float x, float y, float z, float width, float height, float depth)const;
        int TestRect(const cg::point3& center, float w,float h,float d)const;
        
        int TestSphere(float x, float y, float z, float radius)const;
        int TestSphere(const cg::point3& center, float radius)const;
        
        int TestCube(float x, float y, float z, float size)const;
        int TestCube(const cg::point3& center, float size)const;
        
        int TestPoint(float x, float y, float z)const;
        int TestPoint(const cg::point3& max)const;
        
        int TestLine(cg::point3 const& a,cg::point3 const& b)const;
        
        int TestPolygon(int numpoints, cg::point3 const* pointlist)const;
        
        
        const Plane& GetAbovePlane()const;
        const Plane& GetBelowPlane()const;
        const Plane& GetRightPlane()const;
        const Plane& GetLeftPlane()const;
        const Plane& GetNearPlane()const;
        const Plane& GetFarPlane()const;
        
        cg::point3 const& GetCenter()const;
        float GetRadius()const;
        
        void SetFrustum(const gfx::Camera& camera);
        
        void SetFrustum
        (  float aspect, float fov, float near, float far
         , const cg::point3 &position
         , const cg::vec3& forward
         , const cg::vec3& right
         , const cg::vec3& up);
        
        Frustum
        (  float aspect, float fov, float near, float far
         , const cg::point3 &position
         , const cg::vec3& forward
         , const cg::vec3& right
         , const cg::vec3& up);
        
        Frustum(const gfx::Camera& camera);
        Frustum();
        
        enum
        {
            L=0, R=1, N=2, F=3, B=4, T=5,
            OUTSIDE = 0,
            INTERSECT,
            INSIDE
        };
        
        cg::point3 ftl;
        cg::point3 ftr;
        cg::point3 fbl;
        cg::point3 fbr;
        
        cg::point3 ntl;
        cg::point3 ntr;
        cg::point3 nbl;
        cg::point3 nbr;
        
    private:
        
        union CameraFrustum
        {
            Plane planes[6];
            
            struct
            {
                Plane left;
                Plane right;
                Plane near;
                Plane far;
                Plane below;
                Plane above;
            };
            CameraFrustum(){}
        }frustum;
        
        cg::point3 center;
        float radius;
    };
    
    
    int aabb_vs_point(const cg::point3& min, const cg::point3& max, const cg::point3& p);
    int frustum_in_aabb(const cg::point3& min, const cg::point3& max,  const gfx::Frustum& frustum);
}}
#endif /* defined(__MyFirstGame__Frustum__) */







