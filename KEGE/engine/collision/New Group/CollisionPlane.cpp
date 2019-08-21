//
//  CollisionPlane.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 1/3/19.
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
    
    void CollisionPlane::Render(const gfx::Frustum& frustum, const ds::array<gfx::Light*>& lights)
    {
//        kege::Singleton::Get<gfx::DebugRenderer>()->RenderOBB
//        (   shape.center
//         ,  shape.length
//         ,  shape.xaxis
//         ,  shape.yaxis
//         ,  shape.zaxis
//         , cg::vec3(1.0)  );
    }
    
    void CollisionPlane::ResolveCollision(phx::ContactResolver& data)
    {}
    
    void CollisionPlane::ComputeShape(const gfx::Mesh& mesh)
    {
        cg::point3 center = (mesh.GetMaxPoint().x + mesh.GetMinPoint()) * 0.5;
        cg::point3 normal = cg::vec3::up;
        SetShape(phx::Plane(normal, center));
    }
    
    void CollisionPlane::SetShape(const phx::Plane& value)
    {
        shape = value;
    }
    
    const phx::Plane& CollisionPlane::GetShape()const
    {
        return shape;
    }
    
    phx::Plane& CollisionPlane::GetShape()
    {
        return shape;
    }
    
    void CollisionPlane::SetHalfSpace(bool value)
    {
        halfspace = value;
    }
    bool CollisionPlane::IsHalfSpace()const
    {
        return halfspace;
    }
    void CollisionPlane::TransformShape()
    {
        if (body != nullptr)
        {
            SetShape(phx::Plane(shape.n, body->GetPosition()));
        }
        else
        {
            SetShape(phx::Plane(shape.n, GetParent()->GetWorld().translation));
        }
    }
    
    CollisionPlane::CollisionPlane(const cg::point3& a, const cg::point3& b, const cg::point3& c, bool hs)
    :   cmp::CollisionComponent(kege::ENUM::_COLLIDER_PLANE)
    ,   shape(a,b,c)
    ,   halfspace(hs)
    {
    }
    CollisionPlane::CollisionPlane(const cg::vec3& n, const cg::point3& p, bool hs)
    :   cmp::CollisionComponent(kege::ENUM::_COLLIDER_PLANE)
    ,   shape(n,p)
    ,   halfspace(hs)
    {}
    CollisionPlane::CollisionPlane()
    :   cmp::CollisionComponent(kege::ENUM::_COLLIDER_PLANE)
    ,   halfspace(true)
    {}
    
}}
