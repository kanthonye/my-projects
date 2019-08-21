//
//  CollisionAABB.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/23/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//
#include "Gameobject.hpp"
#include "DebugRenderer.hpp"
#include "CollisionOBB.hpp"
#include "CollisionAABB.hpp"
#include "CollisionPlane.hpp"
#include "CollisionSphere.hpp"
#include "CollisionCone.hpp"
#include "CollisionCylinder.hpp"
#include "CollisionDetector.hpp"
namespace kege{namespace cmp{
    
    void CollisionAABB::Render(const gfx::Frustum& frustum, const ds::array<gfx::Light*>& lights)
    {
        //kege::Singleton::Get<gfx::DebugRenderer>()->RenderAABB(shape.min, shape.max, cg::vec3(1.0));
    }
    
//    bool CollisionAABB::OnCollisionSphere(cmp::CollisionSphere& collider, phx::CollisionDetector& detector)
//    {
//        if (data != nullptr)
//        {
//            return  phx::AABB_Intersect_Sphere(detector, *this, collider);
//        }
//        return phx::SPHERE_vs_AABB(collider.GetShape(), shape);
//    }
//    
//    bool CollisionAABB::OnCollisionPlane(cmp::CollisionPlane& collider, phx::CollisionDetector& detector)
//    {
//        if (data != nullptr)
//        {
//            return phx::AABB_Intersect_Plane(detector, *this, collider);
//        }
//        return phx::AABB_vs_PLANE(shape, collider.GetShape());
//    }
//    
//    bool CollisionAABB::OnCollisionAABB(cmp::CollisionAABB& collider, phx::CollisionDetector& detector)
//    {
//        if (data != nullptr)
//        {
//            return phx::AABB_Intersect_AABB(detector, *this, collider);
//        }
//        return phx::AABB_vs_AABB(shape, collider.GetShape());
//    }
//    bool CollisionAABB::OnCollisionOBB(cmp::CollisionOBB& collider, phx::CollisionDetector& detector)
//    {
////        cg::point3 p;
////        return phx::SPHERE_vs_OBB(shape, collider.GetShape(), p);
//        return false;
//    }
//    
    bool CollisionAABB::OnCollisionRay(const cg::point3& p, const cg::vec3& r)
    {
        float t;
        cg::vec3 q;
        return phx::RAY_vs_AABB(p, r, shape, t, q);
    }
    
    void CollisionAABB::ResolveCollision(phx::ContactResolver& data)
    {
        
    }
    
    cg::point3 CollisionAABB::ClosestPointAABB(const cg::point3& p)
    {
        cg::point3 q;
        // For each coordinate axis, if the point coordinate value is
        // outside box, clamp it to the box, else keep it as is
        q.x = p.x;
        if      (p.x <= shape.min.x) q.x = shape.min.x;
        else if (p.x >= shape.max.x) q.x = shape.max.x;
        
        q.y = p.y;
        if      (p.y <= shape.min.y) q.y = shape.min.y;
        else if (p.y >= shape.max.y) q.y = shape.max.y;
        
        q.z = p.z;
        if      (p.z <= shape.min.z) q.z = shape.min.z;
        else if (p.z >= shape.max.z) q.z = shape.max.z;
        return q;
    }
    
    
    void CollisionAABB::ComputeShape(const gfx::Mesh& mesh)
    {
        shape.min = mesh.GetMinPoint();
        shape.max = mesh.GetMaxPoint();
        length   = (shape.max - shape.min) * 0.5;
    }
    void CollisionAABB::SetShape(const phx::AABB& aabb)
    {
        shape = aabb;
    }
    
    const phx::AABB& CollisionAABB::GetShape()const
    {
        return shape;
    }
    
    phx::AABB& CollisionAABB::GetShape()
    {
        return shape;
    }
    
    
    cg::point3 CollisionAABB::Corner(int n)const
    {
        switch (n)
        {
            case 0: return shape.min; break;
            case 1: return cg::vec3(shape.max.x, shape.min.y, shape.min.z); break;
            case 2: return cg::vec3(shape.max.x, shape.min.y, shape.max.z); break;
            case 3: return cg::vec3(shape.min.x, shape.min.y, shape.max.z); break;
                
            case 4: return cg::vec3(shape.min.x, shape.max.y, shape.min.z); break;
            case 5: return cg::vec3(shape.max.x, shape.max.y, shape.max.z); break;
            case 6: return shape.max; break;
            case 7: return cg::vec3(shape.min.x, shape.max.y, shape.min.z); break;
            default: break;
        }
        return cg::point3::zero;
    }
    
    void CollisionAABB::TransformShape()
    {
        const gfx::Transform* transf = GetParent()->GetWorld();
        if (body != nullptr)
        {
            shape.min = body->GetPosition() - transf->scale * length;
            shape.max = body->GetPosition() + transf->scale * length;
        }
        else
        {
            shape.min = transf->translation - transf->scale * length;
            shape.max = transf->translation + transf->scale * length;
        }
    }
    
    
    void CollisionAABB::Save(kege::XML& xml)
    {
        kege::XML* comp = xml.AddChild(new kege::XML("collider"));
        comp = comp->AddChild(new kege::XML("aabb"));
        kege::XML* a = nullptr;
        
        a = comp->AddChild(new kege::XML("vec3"));
        a->AddAttr(new kege::XML::attrib("type", "min"));
        a->GetText() = ds::string::strprint("%f %f %f", shape.min.x, shape.min.y, shape.min.z);
        
        a = comp->AddChild(new kege::XML("vec3"));
        a->AddAttr(new kege::XML::attrib("type", "max"));
        a->GetText() = ds::string::strprint("%f %f %f", shape.max.x, shape.max.y, shape.max.z);
    }
    
    CollisionAABB::CollisionAABB(const cg::point3& c, float w, float h, float d)
    :   cmp::CollisionComponent(kege::ENUM::_COLLIDER_AABB)
    ,   shape(c, w,h,d)
    ,   length(0.0f)
    {}
    
    CollisionAABB::CollisionAABB(const cg::point3& min, const cg::point3& max)
    :   cmp::CollisionComponent(kege::ENUM::_COLLIDER_AABB)
    ,   shape(min, max)
    ,   length(0.0f)
    {}
    
    CollisionAABB::CollisionAABB()
    :   cmp::CollisionComponent(kege::ENUM::_COLLIDER_AABB)
    ,   shape()
    ,   length(0.0f)
    {}
}}
