//
//  ComputeCollision.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 1/13/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "Gameobject.hpp"
#include "CollisionOBB.hpp"
#include "CollisionAABB.hpp"
#include "CollisionSphere.hpp"
#include "CollisionPlane.hpp"
#include "CollisionCone.hpp"
#include "CollisionCylinder.hpp"
#include "CollisionComponent.hpp"
#include "PhysicsComponent.hpp"
#include "CollisionResolver.hpp"
#include "ComputeCollision.hpp"

#include "DebugRenderer.hpp"
namespace kege{namespace phx{
    
    
    bool ComputeCollision(phx::CollisionResolver& resolver, cmp::CollisionSphere& a, cmp::CollisionOBB& b)
    {
        const phx::Sphere& sphere = a.GetShape();
        const phx::OBB& obb = b.GetShape();
        
        float l,r,w;
        
        cg::point3 p;
        phx::CLOSEST_POINT_to_OBB(sphere.center, obb, p);
        cg::vec3 v = sphere.center - obb.center;
        cg::vec3 q = obb.center - p;
        
        cg::vec3 e = cg::normalize3(v);
        l = cg::dot3(e,v);
        w = cg::abs(cg::dot3(e,q));
        r = sphere.radius;
        
        l = (w + r) - l;
        if (l < 0) return false;
        
//        phx::ContactResolver* collision = &resolver.GenerateContactResolver();
//        collision->SetPhysicsBodies(a.GetPhysicsComponent(), b.GetPhysicsComponent());
//        Contact* contact     = &collision->GenerateContact();
//        contact->normal      = e;
//        contact->penetration = l;
//        contact->point       = p;
//
//        kege::Singleton::Get<gfx::DebugRenderer>()->RenderAABB(p - cg::vec3(0.25), p + cg::vec3(0.25), cg::vec3(1));
        return true;
    }
    
    
    
    
    
    /** Computes the square distance between point p and OBB b */
    float DISTSQ_POINT_On_OBB(const cg::point3& p, const OBB& b)
    {
        cg::vec3 v = p - b.center;
        float d,excess = 0.0f, sqDist = 0.0f;
        
        // Project vector from box center to p on each axis, getting the distance
        // of p along that axis, and count any excess distance outside box extents
        d = cg::dot3(v, b.xaxis);
        if      (d < -b.center.x) excess = d + b.center.x;
        else if (d >  b.center.x) excess = d - b.center.x;
        
        
        excess = 0.0f;
        d = cg::dot3(v, b.yaxis);
        if      (d < -b.center.y) excess = d + b.center.y;
        else if (d >  b.center.y) excess = d - b.center.y;
        sqDist += excess * excess;
        
        excess = 0.0f;
        d = cg::dot3(v, b.zaxis);
        if      (d < -b.center.z) excess = d + b.center.z;
        else if (d >  b.center.z) excess = d - b.center.z;
        sqDist += excess * excess;
        
        return sqDist;
    }
    
    
    bool ComputeCollision(cmp::CollisionOBB& a, const cg::point3& p, cg::vec3& fnorm, float& depth)
    {
        const phx::OBB& obb = a.GetShape();
        float m,t,l;
        depth = 0.0f;
        cg::vec3 v = p - obb.center;
        
        m = cg::dot3(obb.xaxis, v);
        l = cg::abs(m);
        t = obb.length.x - l;
        if (t < 0.0f) return false;
        
        depth = l;
        if (m >= 0) fnorm = obb.xaxis;
        else fnorm = -obb.xaxis;
        
        m = cg::dot3(obb.yaxis, v);
        l = cg::abs(m);
        t = obb.length.y - l;
        if (t < 0.0f) return false;
        
        if (depth < l)
        {
            depth = l;
            if (m >= 0) fnorm = obb.yaxis;
            else fnorm = -obb.yaxis;
        }
        
        m = cg::dot3(obb.zaxis, v);
        l = cg::abs(m);
        t = obb.length.z - l;
        if (t < 0.0f) return false;
        
        if (depth < l)
        {
            depth = l;
            if (m >= 0) fnorm = obb.zaxis;
            else fnorm = -obb.zaxis;
        }
        return true;
    }
    
    
    
    
    bool ComputeCollision(phx::CollisionResolver& resolver, cmp::CollisionCylinder& a, cmp::CollisionCylinder& b)
    {
        const phx::Cylinder& c0 = a.GetShape();
        const phx::Cylinder& c1 = b.GetShape();


        double   d0 = cg::abs(cg::dot3(c0.axis, c1.axis));
        cg::vec3 v0 = c1.center - c0.center;
        if (d0 == 1.0f) // facing parallel directions to each other
        {
            float d1 = cg::dot3(c0.axis, v0);
            cg::point3 p0 = c0.center + c0.axis * d1;
            double radius_sum = c0.radius + c1.radius;
            cg::vec3 norm = c1.center - p0;
            d0 = cg::dot3(norm, norm);
            
            if (d0 <= cg::sq(radius_sum))
            {
                float d2 = cg::abs(d1);
                if (d2 > c1.height && d2 <= c0.height + c1.height)
                {
                    phx::ContactResolver* collision = &resolver.GenerateContactResolver();
                    collision->SetPhysicsBodies(a.GetPhysicsComponent(), b.GetPhysicsComponent());
                    Contact* contact= &collision->GenerateContact();
                    if (d1 < 0) contact->normal = c0.axis;
                    else contact->normal = -c0.axis;
                    contact->penetration = (c0.height + c1.height) - d2;
                    contact->point       = c0.center + contact->normal * c0.height;
                    return true;
                }
                else if (d2 <= c0.height + c1.height)
                {
                    d0 = sqrt(d0);
                    norm = norm * cg::invrs(d0);
                    
                    phx::ContactResolver* collision = &resolver.GenerateContactResolver();
                    collision->SetPhysicsBodies(a.GetPhysicsComponent(), b.GetPhysicsComponent());
                    Contact* contact= &collision->GenerateContact();
                    contact->normal      = -norm;
                    contact->penetration = radius_sum - d0;
                    contact->point       = c0.center + norm * c0.radius;
                    return true;
                }
            }
        }
        /*
        else if (d0 == 0.0f) // facing perpendicular directions to each other
        {
            d0 = cg::abs(cg::dot3(c0.axis, v0));
            float d1 = c0.radius + c1.height;
            if (d0 <= d1)
            {
                phx::ContactResolver* collision = &resolver.GenerateContactResolver();
                collision->SetPhysicsBodies(a.GetPhysicsComponent(), b.GetPhysicsComponent());
                Contact* contact= &collision->GenerateContact();
                contact->normal      = cg::normalize3(v0);
                contact->penetration = d1 - d0;
                contact->point       = c0.center - v0 * c0.radius;
                kege::Singleton::Get<gfx::DebugRenderer>()->RenderAABB(contact->point - 0.125, contact->point + 0.125, cg::vec3::one);
                return true;
            }
        }
        else
        {
            float d1 = cg::dot3(c0.axis, v0);
            float d2 = cg::dot3(c1.axis, v0);
//            d1 = cg::clamp(d1, -c0.height, c0.height);
//            d1 = cg::clamp(d2, -c1.height, c1.height);
            
            
            cg::point3 p0 = c0.center + c0.axis * d1;
            cg::point3 p1 = c1.center - c1.axis * d2;
            
            
            kege::Singleton::Get<gfx::DebugRenderer>()->RenderAABB(p0 - 0.125, p0 + 0.125, cg::vec3::one);
            kege::Singleton::Get<gfx::DebugRenderer>()->RenderAABB(p1 - 0.125, p1 + 0.125, cg::vec3::one);
            kege::Singleton::Get<gfx::DebugRenderer>()->RenderLine(c0.center, c1.center, cg::vec3::one);
            kege::Singleton::Get<gfx::DebugRenderer>()->RenderLine(p0, c1.center, cg::vec3::one);
            kege::Singleton::Get<gfx::DebugRenderer>()->RenderLine(p0, c0.center, cg::vec3::one);
            kege::Singleton::Get<gfx::DebugRenderer>()->RenderLine(p1, c0.center, cg::vec3::one);
            kege::Singleton::Get<gfx::DebugRenderer>()->RenderLine(p1, c1.center, cg::vec3::one);
            kege::Singleton::Get<gfx::DebugRenderer>()->RenderLine(c0.center, p1 + v1 * 5, cg::vec3::one);
            kege::Singleton::Get<gfx::DebugRenderer>()->RenderLine(c1.center, c1.center + u1 * 5, cg::vec3::one);
            kege::Singleton::Get<gfx::DebugRenderer>()->RenderLine(c0.center, c0.center + u1 * 5, cg::vec3::one);
        }
         */
        return false;
    }
    
    
}}
