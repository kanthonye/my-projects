//
//  CollisionOBB.cpp
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
    
    void CollisionOBB::Render(const gfx::Frustum& frustum, const ds::array<gfx::Light*>& lights)
    {
//        kege::Singleton::Get<gfx::DebugRenderer>()->RenderOBB
//        (   shape.center
//         ,  shape.length
//         ,  shape.xaxis
//         ,  shape.yaxis
//         ,  shape.zaxis
//         , cg::vec3(1.0)  );
    }
    
//    bool CollisionOBB::OnCollisionSphere(cmp::CollisionSphere& collider, phx::CollisionDetector& detector)
//    {
//        if (data != nullptr)
//        {
//            return  phx::Sphere_Intersect_OBB(detector, collider, *this);
//        }
//        return false;
//    }
//    bool CollisionOBB::OnCollisionPlane(cmp::CollisionPlane& collider, phx::CollisionDetector& detector)
//    {
//        if (data != nullptr)
//        {
//            return  phx::OBB_Intersect_Plane(detector, *this, collider);
//        }
//        return false;
//    }
//    bool CollisionOBB::OnCollisionAABB(cmp::CollisionAABB& collider, phx::CollisionDetector& detector)
//    {
//        return false;
//    }
//    bool CollisionOBB::OnCollisionOBB(cmp::CollisionOBB& collider, phx::CollisionDetector& detector)
//    {
//        if (data != nullptr)
//        {
//            return  phx::OBB_Intersect_OBB(detector, *this, collider);
//        }
//        return phx::OBB_vs_OBB(shape, collider.GetShape());
//    }
    
    void CollisionOBB::ResolveCollision(phx::ContactResolver& data)
    {}
    
    void CollisionOBB::ComputeShape(const gfx::Mesh& mesh)
    {
        cg::point3 min = mesh.GetMinPoint();
        cg::point3 max = mesh.GetMaxPoint();
        phx::OBB obb;
        
        obb.center = (max + min) * 0.5f;
        obb.xaxis  = cg::normalize3(cg::point3(max.x, min.y, min.z) - min);
        obb.yaxis  = cg::normalize3(cg::point3(min.x, max.y, min.z) - min);
        obb.zaxis  = cg::normalize3(cg::point3(min.x, min.y, max.z) - min);
        obb.length = GetParent()->GetLocal().scale * (max - min) * 0.5f;
        SetShape(obb);
    }
    
    void CollisionOBB::SetShape(const phx::OBB& obb)
    {
        shape = obb;
    }
    
    const phx::OBB& CollisionOBB::GetShape()const
    {
        return shape;
    }
    
    phx::OBB& CollisionOBB::GetShape()
    {
        return shape;
    }
    
    cg::point3 CollisionOBB::Corner(int n)const
    {
        switch (n)
        {
            case 0: return shape.center - shape.length; break;
            case 1: return cg::vec3(shape.center.x + shape.length.x, shape.center.y - shape.length.y, shape.center.z - shape.length.z); break;
            case 2: return cg::vec3(shape.center.x + shape.length.x, shape.center.y - shape.length.y, shape.center.z + shape.length.z); break;
            case 3: return cg::vec3(shape.center.x - shape.length.x, shape.center.y - shape.length.y, shape.center.z + shape.length.z); break;
            case 4: return cg::vec3(shape.center.x - shape.length.x, shape.center.y + shape.length.y, shape.center.z - shape.length.z); break;
            case 5: return cg::vec3(shape.center.x + shape.length.x, shape.center.y + shape.length.y, shape.center.z - shape.length.z); break;
            case 6: return shape.center + shape.length; break;
            case 7: return cg::vec3(shape.center.x - shape.length.x, shape.center.y + shape.length.y, shape.center.z + shape.length.z); break;
            default: break;
        }
        return cg::point3::zero;
    }
    
    void CollisionOBB::TransformShape()
    {
        if (body != nullptr)
        {
            shape.center = body->GetPosition();
        }
        else
        {
            shape.center = GetParent()->GetWorld().translation;
        }
        shape.zaxis  = body->GetForward();
        shape.xaxis  = body->GetRight();
        shape.yaxis  = body->GetUp();
    }
    
    void CollisionOBB::Save(kege::XML& xml)
    {
        kege::XML* comp = xml.AddChild(new kege::XML("collider"));
        comp = comp->AddChild(new kege::XML("OBB"));
        kege::XML* a = nullptr;
        
        a = comp->AddChild(new kege::XML("vec3"));
        a->AddAttr(new kege::XML::attrib("semantic", "dimensions"));
        a->GetText() = ds::string::strprint("%f %f %f", shape.length.x, shape.length.y, shape.length.z);
    }
    
    CollisionOBB::CollisionOBB(const cg::point3& c, float w, float h, float d, const cg::point3& x, const cg::point3& y, const cg::point3& z)
    :   cmp::CollisionComponent(kege::ENUM::_COLLIDER_OBB)
    {}
    CollisionOBB::CollisionOBB(const cg::point3& c, float w, float h, float d)
    :   cmp::CollisionComponent(kege::ENUM::_COLLIDER_OBB)
    {}
    CollisionOBB::CollisionOBB(const cg::point3& min, const cg::point3& max)
    :   cmp::CollisionComponent(kege::ENUM::_COLLIDER_OBB)
    {}
    CollisionOBB::CollisionOBB()
    :   cmp::CollisionComponent(kege::ENUM::_COLLIDER_OBB)
    {}
    
}}
