//
//  CollisionCone.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 1/10/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//
#include "DebugRenderer.hpp"
#include "Gameobject.hpp"
#include "CollisionOBB.hpp"
#include "CollisionAABB.hpp"
#include "CollisionPlane.hpp"
#include "CollisionSphere.hpp"
#include "CollisionCone.hpp"
#include "CollisionCylinder.hpp"
#include "CollisionDetector.hpp"
namespace kege{namespace cmp{
    
    void CollisionCone::Render(const gfx::Frustum& frustum, const ds::array<gfx::Light*>& lights)
    {
        //kege::Singleton::Get<gfx::DebugRenderer>()->RenderAABB(shape.min, shape.max, cg::vec3(1.0));
        //kege::Singleton::Get<gfx::DebugRenderer>()->RenderAABB(shape.min-cg::vec3(0.1), shape.min+cg::vec3(0.1), cg::vec3(1,1,0));
        //kege::Singleton::Get<gfx::DebugRenderer>()->RenderAABB(shape.max-cg::vec3(0.1), shape.max+cg::vec3(0.1), cg::vec3(1,1,0));
    }
    
//    bool CollisionCone::OnCollisionSphere(cmp::CollisionSphere& collider, phx::CollisionDetector& detector)
//    {
////        if (data != nullptr)
////        {
////            return  phx::AABB_Intersect_Sphere(detector, *this, collider);
////        }
////        return phx::SPHERE_vs_AABB(collider.GetShape(), shape);
//        return false;
//    }
//    
//    bool CollisionCone::OnCollisionPlane(cmp::CollisionPlane& collider, phx::CollisionDetector& detector)
//    {
////        if (data != nullptr)
////        {
////            return phx::AABB_Intersect_Plane(detector, *this, collider);
////        }
////        return phx::AABB_vs_PLANE(shape, collider.GetShape());
//        return false;
//    }
//    
//    bool CollisionCone::OnCollisionAABB(cmp::CollisionAABB& collider, phx::CollisionDetector& detector)
//    {
////        if (data != nullptr)
////        {
////            return phx::AABB_Intersect_AABB(detector, *this, collider);
////        }
////        return phx::AABB_vs_AABB(shape, collider.GetShape());
//        return false;
//    }
//    bool CollisionCone::OnCollisionOBB(cmp::CollisionOBB& collider, phx::CollisionDetector& detector)
//    {
//        //        cg::point3 p;
//        //        return phx::SPHERE_vs_OBB(shape, collider.GetShape(), p);
//        return false;
//    }
//    
    bool CollisionCone::OnCollisionRay(const cg::point3& p, const cg::vec3& r)
    {
//        float t;
//        cg::vec3 q;
//        return phx::RAY_vs_AABB(p, r, shape, t, q);
        return false;
    }
    
    void CollisionCone::ResolveCollision(phx::ContactResolver& data)
    {
        
    }
    
    void CollisionCone::ComputeShape(const gfx::Mesh& mesh)
    {
        shape.origin    = (mesh.GetMinPoint()   + mesh.GetMaxPoint())   * 0.5;
        shape.origin.y -= (mesh.GetMaxPoint().y - mesh.GetMinPoint().y) * 0.5;
        shape.radius    = (mesh.GetMaxPoint().x - mesh.GetMinPoint().x) * 0.5;
        shape.height    = mesh.GetMaxPoint().y  - mesh.GetMinPoint().y;
        shape.axis      = cg::vec3::up;
    }
    void CollisionCone::SetShape(const phx::Cone& aabb)
    {
        shape = aabb;
    }
    
    const phx::Cone& CollisionCone::GetShape()const
    {
        return shape;
    }
    
    phx::Cone& CollisionCone::GetShape()
    {
        return shape;
    }
   
    void CollisionCone::TransformShape()
    {
        if (body != nullptr)
        {
            shape.origin = body->GetPosition();
        }else
        {
            shape.origin = GetParent()->GetWorld().translation;
        }
        shape.axis = body->GetUp();
    }
    
    
    CollisionCone::CollisionCone(const cg::point3& c,const cg::point3& n, float h, float r)
    :   cmp::CollisionComponent(kege::ENUM::_COLLISION_CONE)
    ,   shape(c, n, h, r)
    {}
    
    CollisionCone::CollisionCone()
    :   cmp::CollisionComponent(kege::ENUM::_COLLISION_CONE)
    ,   shape()
    {}
}}
