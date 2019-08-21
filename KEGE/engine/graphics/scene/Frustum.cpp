/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * MyFirstGame
 * Frustum.cpp
 * Created by Kenneth Anthony Esdaile on 9/11/15.
 *   Copyright (c) 2015 kae. All rights reserved.
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "Frustum.hpp"
#include "Camera.hpp"
namespace kege{namespace gfx{

    int Plane::TestAABB(float mx, float my, float mz, float nx, float ny, float nz)const
    {
        int ret = 1;
        cg::vec3 vmin, vmax;
        // X axis
        if(n.x > 0)
        {
            vmin.x = mx;
            vmax.x = nx;
        }
        else
        {
            vmin.x = nx;
            vmax.x = mx;
        }
        // Y axis
        if(n.y > 0)
        {
            vmin.y = my;
            vmax.y = ny;
        }
        else
        {
            vmin.y = ny;
            vmax.y = my;
        }
        // Z axis
        if(n.z > 0)
        {
            vmin.z = mz;
            vmax.z = nz;
        }
        else
        {
            vmin.z = nz;
            vmax.z = mz;
        }
        
//        if((n.x*vmin.x + n.y*vmin.y + n.z*vmin.z) + w > 0)
//            return OUTSIDE;
//        if((n.x*vmax.x + n.y*vmax.y + n.z*vmax.z) + w >= 0)
//            ret = INTERSECT;
        return ret;
//        if(TestPoint(mx,my,mz) >= 1)return true;
//        if(TestPoint(mx,my,nz) >= 1)return true;
//        if(TestPoint(mx,ny,mz) >= 1)return true;
//        if(TestPoint(mx,ny,nz) >= 1)return true;
//
//        if(TestPoint(nx,my,mz) >= 1)return true;
//        if(TestPoint(nx,my,nz) >= 1)return true;
//        if(TestPoint(nx,ny,mz) >= 1)return true;
//        if(TestPoint(nx,ny,nz) >= 1)return true;
//        return 0;
    }
    int Plane::TestAABB(cg::point3 const& min,cg::point3 const& max)const
    {
        return TestAABB(min.x,min.y,min.z, max.x,max.y,max.z);
    }
        
    int Plane::TestRect(float x, float y, float z, float w, float h, float d)const
    {
        if(TestPoint(x-w, y-h, z-d)) return true;
        if(TestPoint(x-w, y-h, z+d)) return true;
        if(TestPoint(x-w, y+h, z-d)) return true;
        if(TestPoint(x-w, y+h, z+d)) return true;
        
        if(TestPoint(x+w, y-h, z-d)) return true;
        if(TestPoint(x+w, y-h, z+d)) return true;
        if(TestPoint(x+w, y+h, z-d)) return true;
        if(TestPoint(x+w, y+h, z+d)) return true;
        return false;
    }
    int Plane::TestLine(cg::point3 const& a,cg::point3 const& b)const
    {
        cg::vec3 ab = b - a;
        // Project c onto ab, computing parameterized position d(t) = a + t*(b – a)
        float t = cg::dot3(p - a, ab) / cg::dot3(ab,ab);
        // If outside segment, clamp t (and therefore d) to the closest endpoint
        if (t < 0.0f) t = 0.0f;
        if (t > 1.0f) t = 1.0f;
        // Compute projected position from the clamped t
        cg::point3 d = a + t * ab;
        return TestPoint(d.x, d.y, d.z);
    }
    
    int gfx::Plane::TestRect(const cg::point3& center, float w,float h,float d)const
    {
        return TestRect(center.x, center.y, center.z, w,h,d);
    }
        
    int gfx::Plane::TestSphere(float cx, float cy, float cz, float radius)const
    {
        double dist = n.x*(cx-p.x) + n.y*(cy-p.y) + n.z*(cz-p.z);
        if (dist < -radius) return false;
        //else if ( dist < radius  ) return 2;
        return 1;
    }
    int gfx::Plane::TestSphere(const cg::point3& center, float radius)const
    {
        return TestSphere(center.x,center.y,center.z, radius);
    }
    
    int gfx::Plane::TestCube(float x, float y, float z, float size)const
    {
        return TestRect(x,y,z, size,size,size);
    }
    int gfx::Plane::TestCube(const cg::point3& center, float size)const
    {
        return TestRect(center.x,center.y,center.z, size,size,size);
    }
    
    float gfx::Plane::Distance(float px, float py, float pz)const
    {  // if less than zero point is behind plane
        double x = px-p.x;
        double y = py-p.y;
        double z = pz-p.z;
        return (n.x*x + n.y*y + n.z*z) /  sqrt(x*x + y*y + z*z);
    }
    
    int gfx::Plane::TestPoint(float px, float py, float pz)const
    {  // if less than zero point is behind plane
        return cg::dot3(cg::vec3(px-p.x, py-p.y, pz-p.z), n) >= 0;
    }
    
    int gfx::Plane::TestPoint(const cg::point3& p)const
    {
        return TestPoint(p.x, p.y, p.z);
    }
    
    int gfx::Plane::TestPolygon(int numpoints, cg::point3 const* pointlist)const
    {
        for(int p = 0; p < numpoints; p++ )
            if (TestPoint(pointlist[p]) >= 1) return true;
        return true;
    }
    
    gfx::Plane::Plane(const cg::point3 &q, const cg::point3 &r, const cg::point3 &s, const cg::point3& t)
    {
        double ax = q.x-r.x;
        double ay = q.y-r.y;
        double az = q.z-r.z;
        
        double bx = s.x-r.x;
        double by = s.y-r.y;
        double bz = s.z-r.z;
        
        double nx = ay*bz - az*by;
        double ny = az*bx - ax*bz;
        double nz = ax*by - ay*bx;
        
        bx = nx*nx + ny*ny + nz*nz;
        
        if (bx != 0)
        {
            bx = 1.0f / sqrtf(bx);
            n.x = nx * bx;
            n.y = ny * bx;
            n.z = nz * bx;
            //w = (p.x*x + p.y*y + p.z*z);
        }else{
            n.x = nx;
            n.y = ny;
            n.z = nz;
        }
        
        p = (s + q + r + t) * 0.25;
    }
    
    gfx::Plane::Plane()
    {}
}}
    
    

    


namespace kege{namespace gfx{
    
    int Frustum::TestSphere(const cg::point3& centr, float r)const
    {
        float dist = cg::distant(centr, center);
        if (dist > r + radius)
            return OUTSIDE;
        
        int result = INSIDE;
        
        for (int i=0; i<6; i++)
        {
            if ( !frustum.planes[i].TestSphere(center.x,center.y,center.z, radius) )
            {
                return false;
            }
        }
        return result;
    }
    
    int Frustum::TestPoint(float x, float y, float z) const
    {
        if (! frustum.far.TestPoint(x,y,z)) return OUTSIDE;
        if (! frustum.near.TestPoint(x,y,z)) return OUTSIDE;
        if (! frustum.left.TestPoint(x,y,z)) return OUTSIDE;
        if (! frustum.right.TestPoint(x,y,z)) return OUTSIDE;
        if (! frustum.above.TestPoint(x,y,z)) return OUTSIDE;
        if (! frustum.below.TestPoint(x,y,z)) return OUTSIDE;
        return INSIDE;
    }
    int Frustum::TestPoint(const cg::point3& p) const
    {
        if (Frustum::TestPoint(p.x,p.y,p.z) >= 1)
            return INSIDE;
        return OUTSIDE;
    }
    int Frustum::TestAABB(float mx, float my, float mz, float nx, float ny, float nz)const
    {
        if (frustum.left.TestPoint(mx,my,mz) && frustum.right.TestPoint(mx,my,mz))
        {
            if (frustum.far.TestPoint(mx,my,mz) && frustum.below.TestPoint(mx,my,mz)) return INTERSECT;
            return OUTSIDE;
        }
        if (frustum.left.TestPoint(nx,ny,nz) && frustum.right.TestPoint(nx,ny,nz))
        {
            if (frustum.far.TestPoint(nx,ny,nz) && frustum.below.TestPoint(nx,ny,nz)) return INTERSECT;
            return OUTSIDE;
        }
        if (frustum.left.TestPoint(mx,my,mz) && frustum.below.TestPoint(mx,my,mz))
        {
            if (frustum.left.TestPoint(mx,my,mz) && frustum.right.TestPoint(mx,my,mz)) return INTERSECT;
            return OUTSIDE;
        }
        if (frustum.far.TestPoint(nx,ny,nz) && frustum.below.TestPoint(nx,ny,nz))
        {
            if (frustum.left.TestPoint(nx,ny,nz) && frustum.right.TestPoint(nx,ny,nz)) return INTERSECT;
            return OUTSIDE;
        }
       
        return OUTSIDE;
    }
    int gfx::Frustum::TestAABB(cg::point3 const& min,cg::point3 const& max)const
    {
        int a=0,b=0;
        for (int i=0; i<6; i++)
        {
            if(frustum.planes[i].TestPoint(min.x, min.y, min.z))
                a++;
            else b++;
            if(frustum.planes[i].TestPoint(min.x, max.y, min.z))
                a++;
            else b++;
            if(frustum.planes[i].TestPoint(max.x, min.y, min.z))
                a++;
            else b++;
            if(frustum.planes[i].TestPoint(max.x, max.y, min.z))
                a++;
            else b++;
            
            if(frustum.planes[i].TestPoint(max.x, max.y, max.z))
                a++;
            else b++;
            if(frustum.planes[i].TestPoint(max.x, min.y, max.z))
                a++;
            else b++;
            if(frustum.planes[i].TestPoint(min.x, max.y, max.z))
                a++;
            else b++;
            if(frustum.planes[i].TestPoint(min.x, min.y, max.z))
                a++;
            else b++;
            
            if (b == 8)
            {
                return OUTSIDE;
            }
        }
        
        if (a == 48)
        {
            return INSIDE;
        }
        return INTERSECT;
    }
    int Frustum::TestRect(float x, float y, float z, float w, float h, float d) const
    {
        if(TestPoint(x-w, y-h, z-d)) return INTERSECT;
        if(TestPoint(x+w, y-h, z-d)) return INTERSECT;
        if(TestPoint(x-w, y+h, z-d)) return INTERSECT;
        if(TestPoint(x+w, y+h, z-d)) return INTERSECT;
        if(TestPoint(x-w, y-h, z+d)) return INTERSECT;
        if(TestPoint(x+w, y-h, z+d)) return INTERSECT;
        if(TestPoint(x-w, y+h, z+d)) return INTERSECT;
        if(TestPoint(x+w, y+h, z+d)) return INTERSECT;
        
        
//        float r = cg::math::max(w,cg::math::max(d,h));
//        float dx = center.x-x;
//        float dy = center.y-y;
//        float dz = center.z-z;
//        float dist = sqrt(dx*dx+dy*dy+dz*dz);
//        if (dist <= radius+r)
//        {
//            return INTERSECT
//        }
        return OUTSIDE;
    }
    int Frustum::TestRect(const cg::point3& center, float w, float h, float d) const
    {
        return Frustum::TestRect(center.x,center.y,center.z, w,h,d);
    }
    int Frustum::TestCube( float x, float y, float z, float size ) const
    {
        return Frustum::TestRect(x,y,z, size,size,size);
    }
    int Frustum::TestCube(const cg::point3& center, float size) const
    {
        return Frustum::TestRect(center.x,center.y,center.z, size,size,size);
    }
    
    int Frustum::TestPolygon(int numpoints, cg::point3 const* points)const
    {
        for(int p = 0; p < numpoints; p++ )
            if (Frustum::TestPoint(points[p]) >= 1) return INSIDE;
        return OUTSIDE;
    }
    
    const Plane& Frustum::GetAbovePlane()const
    {
        return frustum.above;
    }
    const Plane& Frustum::GetBelowPlane()const
    {
        return frustum.below;
    }
    const Plane& Frustum::GetRightPlane()const
    {
        return frustum.right;
    }
    const Plane& Frustum::GetLeftPlane()const
    {
        return frustum.left;
    }
    const Plane& Frustum::GetNearPlane()const
    {
        return frustum.near;
    }
    const Plane& Frustum::GetFarPlane()const
    {
        return frustum.far;
    }
    
    cg::point3 const& Frustum::GetCenter()const
    {
        return center;
    }
    
    void Frustum::SetFrustum
    (   float aspect, float fov, float near, float far
     ,  const cg::point3 &position
     ,  const cg::vec3& forward
     ,  const cg::vec3& right
     ,  const cg::vec3& up)
    {
        float tang = tanf( cg::deg2rad(fov)*0.5 );
        float nh = near * tang;
        float fh = far * tang;
        float nw = nh * aspect;
        float fw = fh * aspect;
        
        cg::point3 near_centr = position - forward * near;
        cg::point3 farr_centr = position - forward * far;
        
        ftr = farr_centr + right*fw + up*fh;
        fbr = farr_centr + right*fw - up*fh;
        ftl = farr_centr - right*fw + up*fh;
        fbl = farr_centr - right*fw - up*fh;
        
        ntr = near_centr + right*nw + up*nh;
        nbr = near_centr + right*nw - up*nh;
        ntl = near_centr - right*nw + up*nh;
        nbl = near_centr - right*nw - up*nh;
        
        frustum.left  = Plane(ntl, ftl, fbl, nbl);
        frustum.right = Plane(ntr, nbr, fbr, ftr);
        frustum.near  = Plane(ntl, nbl, nbr, ntr);
        frustum.far   = Plane(ftr, fbr, fbl, ftl);
        frustum.below = Plane(nbl, fbl, fbr, nbr);
        frustum.above = Plane(ntr, ftr, ftl, ntl);
        
        center = (farr_centr + near_centr) * 0.5;
        radius = cg::distant(center, ftr);
    }
   
    void gfx::Frustum::SetFrustum(const gfx::Camera& camera)
    {
//        SetFrustum 
//        (   camera.GetAspectRatio()
//         ,  camera.GetFieldOfView()
//         ,  camera.GetNearView()
//         ,  camera.GetFarView()
//         ,  camera.GetWorld().translation
//         ,  camera.GetForward()
//         ,  camera.GetRight()
//         ,  camera.GetUp());
    }
    
    Frustum::Frustum
    (  float aspect, float fov, float near, float far
     , const cg::point3 &position
     , const cg::vec3& forward
     , const cg::vec3& right
     , const cg::vec3& up)
    {
        SetFrustum(aspect, fov, near, far, position, forward, right, up);
    }
    Frustum::Frustum(const gfx::Camera& camera)
    {
        //SetFrustum(camera);
    }
    Frustum::Frustum()
    {}
    
    
    
    int aabb_vs_point(const cg::point3& min, const cg::point3& max, const cg::point3& p)
    {
        if (max.x < p.x || min.x > p.x) return false;
        if (max.y < p.y || min.y > p.y) return false;
        if (max.z < p.z || min.z > p.z) return false;
        return true;
    }
    
    int frustum_in_aabb(const cg::point3& min, const cg::point3& max,  const gfx::Frustum& frustum)
    {
        if (aabb_vs_point(min, max, frustum.ftl)) return true;
        if (aabb_vs_point(min, max, frustum.ftr)) return true;
        if (aabb_vs_point(min, max, frustum.fbl)) return true;
        if (aabb_vs_point(min, max, frustum.fbr)) return true;
        
        if (aabb_vs_point(min, max, frustum.ntl)) return true;
        if (aabb_vs_point(min, max, frustum.ntr)) return true;
        if (aabb_vs_point(min, max, frustum.nbl)) return true;
        if (aabb_vs_point(min, max, frustum.nbr)) return true;
        return false;
    }
    
    
}}
