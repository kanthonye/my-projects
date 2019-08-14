//
//  CollisionSphere.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/27/18.
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
    
    void CollisionSphere::Render(const gfx::Frustum& frustum, const ds::array<gfx::Light*>& lights)
    {
    }
    
    bool CollisionSphere::OnCollisionRay(const cg::point3& p, const cg::vec3& r)
    {
        return phx::RAY_vs_SPHERE(p, r, shape);
    }
    
    void CollisionSphere::ResolveCollision(phx::ContactResolver& data)
    {}
    
    void CollisionSphere::ComputeShape(const gfx::Mesh& mesh)
    {
        shape.center = (mesh.GetMaxPoint() + mesh.GetMinPoint()) * 0.5;
        shape.radius = (mesh.GetMaxPoint().x - mesh.GetMinPoint().x) * 0.5 * GetParent()->GetWorld().scale.x;
        shape.radius = cg::max(shape.radius, (mesh.GetMaxPoint().y - mesh.GetMinPoint().y) * 0.5 * GetParent()->GetWorld().scale.y);
        shape.radius = cg::max(shape.radius, (mesh.GetMaxPoint().z - mesh.GetMinPoint().z) * 0.5 * GetParent()->GetWorld().scale.z);
    }
    
    void CollisionSphere::TransformShape()
    {
        if (body != nullptr)
        {
            shape.center = body->GetPosition();
        }
        else
        {
            shape.center = GetParent()->GetWorld().translation;
        }
    }
    
    void CollisionSphere::SetShape(const phx::Sphere& val)
    {
        shape = val;
    }
    
    const phx::Sphere& CollisionSphere::GetShape()const
    {
        return shape;
    }
    
    phx::Sphere& CollisionSphere::GetShape()
    {
        return shape;
    }
    
    void CollisionSphere::Save(kege::XML& xml)
    {
        kege::XML* comp = xml.AddChild(new kege::XML("collider"));
        comp = comp->AddChild(new kege::XML("sphere"));
        comp->AddAttr(new kege::XML::attrib("radius", ds::string::strprint("%f", shape.radius)));
    }
    
    CollisionSphere::CollisionSphere(const cg::point3& c, float radius)
    :   cmp::CollisionComponent(kege::ENUM::_COLLIDER_SPHERE)
    ,   shape(c, radius)
    ,   last(0.0f)
    {}
    
    CollisionSphere::CollisionSphere()
    :   cmp::CollisionComponent(kege::ENUM::_COLLIDER_SPHERE)
    ,   shape()
    ,   last(0.0f)
    {}
}}
