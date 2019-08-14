//
//  CollisionCylinder.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 1/8/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
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
    
    void CollisionCylinder::Render(const gfx::Frustum& frustum, const ds::array<gfx::Light*>& lights)
    {
//        kege::Singleton::Get<gfx::DebugRenderer>()->RenderOBB
//        (   shape.center
//         ,  shape.length
//         ,  shape.xaxis
//         ,  shape.yaxis
//         ,  shape.zaxis
//         , cg::vec3(1.0)  );
    }
    
//    bool CollisionCylinder::OnCollisionCylinder(cmp::CollisionCylinder& collider, phx::CollisionDetector& detector)
//    {
//        return false;
//    }
//
//    bool CollisionCylinder::OnCollisionSphere(cmp::CollisionSphere& collider, phx::CollisionDetector& detector)
//    {
//        cg::point3 p;
//        return false;//phx::SPHERE_vs_OBB(collider.GetShape(), shape, p);
//    }
//    
//    bool CollisionCylinder::OnCollisionPlane(cmp::CollisionPlane& collider, phx::CollisionDetector& detector)
//    {
//        //return phx::SPHERE_vs_PLANE(shape, ((const CollisionPlane&)collider).GetShape());
//        return false;
//    }
//    
//    bool CollisionCylinder::OnCollisionAABB(cmp::CollisionAABB& collider, phx::CollisionDetector& detector)
//    {
//        return false;
//    }
//    
//    bool CollisionCylinder::OnCollisionOBB(cmp::CollisionOBB& collider, phx::CollisionDetector& detector)
//    {
//        return false;//phx::OBB_vs_OBB(shape, collider.GetShape());
//    }
    
    void CollisionCylinder::ResolveCollision(phx::ContactResolver& data)
    {}
    
    void CollisionCylinder::ComputeShape(const gfx::Mesh& mesh)
    {
        cg::point3 min = mesh.GetMinPoint();
        cg::point3 max = mesh.GetMaxPoint();
        cg::point3 s = GetParent()->GetWorld().scale;
        
        cg::point3 lengths = (max - min) * 0.5;
        shape.height = cg::abs(cg::max(lengths.x * s.x, lengths.y * s.y));
        shape.height = cg::abs(cg::max(shape.height, lengths.z * s.y));
        
        shape.radius = cg::abs(cg::min(lengths.x * s.x, lengths.y * s.y));
        shape.radius = cg::abs(cg::min(shape.radius, lengths.z * s.z));
        shape.center = (max + min) * 0.5;
        shape.axis   = cg::point3::forward;
    }
    
    void CollisionCylinder::SetShape(const phx::Cylinder& obb)
    {
        shape = obb;
    }
    
    const phx::Cylinder& CollisionCylinder::GetShape()const
    {
        return shape;
    }
    
    phx::Cylinder& CollisionCylinder::GetShape()
    {
        return shape;
    }
   
    void CollisionCylinder::TransformShape()
    {
        if (body != nullptr)
        {
            shape.center = body->GetPosition();
        }else
        {
            shape.center = GetParent()->GetWorld().translation;
        }
        shape.axis = body->GetForward();
    }
    
    CollisionCylinder::CollisionCylinder(const cg::point3& c, const cg::vec3& d, float r, float h)
    :   cmp::CollisionComponent(kege::ENUM::_COLLISION_CYLINDER)
    ,   shape(c,d,r,h)
    {}
    CollisionCylinder::CollisionCylinder(const phx::Cylinder& cylinder)
    :   cmp::CollisionComponent(kege::ENUM::_COLLISION_CYLINDER)
    ,   shape(cylinder)
    {}
    CollisionCylinder::CollisionCylinder()
    :   cmp::CollisionComponent(kege::ENUM::_COLLISION_CYLINDER)
    {}
    
}}
