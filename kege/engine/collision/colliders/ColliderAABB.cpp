/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/27/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ColliderAABB.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#include "../primatives/ray.hpp"
#include "../primatives/obb.hpp"
#include "../primatives/cone.hpp"
#include "../primatives/aabb.hpp"
#include "../primatives/plane.hpp"
#include "../primatives/capsule.hpp"
#include "../primatives/segment.hpp"
#include "../primatives/triangle.hpp"
#include "../primatives/cylinder.hpp"
#include "../colliders/ColliderAABB.hpp"
namespace kege{namespace cg{
    
    bool AABB_Intersect_AABB(cg::CollisionContacts* contacts, cg::ColliderAABB* a, cg::ColliderAABB* b)
    {
//        const cg::aabb& a0 = a->GetShape();
//        const cg::aabb& a1 = b->GetShape();
        return true;
    }
    
    bool ColliderAABB::TestCollision(cg::CollisionContacts* contacts, cg::ColliderCylinder* shape)
    {
        return false;
    }
    bool ColliderAABB::TestCollision(cg::CollisionContacts* contacts, cg::ColliderTriangle* shape)
    {
        return false;
    }
    bool ColliderAABB::TestCollision(cg::CollisionContacts* contacts, cg::ColliderSegment* shape)
    {
        return false;
    }
    bool ColliderAABB::TestCollision(cg::CollisionContacts* contacts, cg::ColliderCapsule* shape)
    {
        return false;
    }
    bool ColliderAABB::TestCollision(cg::CollisionContacts* contacts, cg::ColliderSphere* shape)
    {
        return false;
    }
    bool ColliderAABB::TestCollision(cg::CollisionContacts* contacts, cg::ColliderPlane* shape)
    {
        return false;
    }
    bool ColliderAABB::TestCollision(cg::CollisionContacts* contacts, cg::ColliderAABB* shape)
    {
        return cg::AABB_Intersect_AABB(contacts, this, shape);
    }
    bool ColliderAABB::TestCollision(cg::CollisionContacts* contacts, cg::ColliderCone* shape)
    {
        return false;
    }
    bool ColliderAABB::TestCollision(cg::CollisionContacts* contacts, cg::ColliderOBB* shape)
    {
        return false;
    }
    bool ColliderAABB::TestCollision(cg::CollisionContacts* contacts, cg::ColliderRay* shape)
    {
        return false;
    }
    
    ColliderAABB::ColliderAABB()
    :   cg::Collider( cg::Collider::AABB )
    {}
}}
