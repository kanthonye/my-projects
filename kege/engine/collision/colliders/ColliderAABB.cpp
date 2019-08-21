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
namespace kege{namespace gfx{
    
    bool AABB_Intersect_AABB(gfx::CollisionContacts* contacts, gfx::ColliderAABB* a, gfx::ColliderAABB* b)
    {
//        const cg::aabb& a0 = a->GetShape();
//        const cg::aabb& a1 = b->GetShape();
        return true;
    }
    
    bool ColliderAABB::TestCollision(gfx::CollisionContacts* contacts, gfx::ColliderCylinder* shape)
    {
        return false;
    }
    bool ColliderAABB::TestCollision(gfx::CollisionContacts* contacts, gfx::ColliderTriangle* shape)
    {
        return false;
    }
    bool ColliderAABB::TestCollision(gfx::CollisionContacts* contacts, gfx::ColliderSegment* shape)
    {
        return false;
    }
    bool ColliderAABB::TestCollision(gfx::CollisionContacts* contacts, gfx::ColliderCapsule* shape)
    {
        return false;
    }
    bool ColliderAABB::TestCollision(gfx::CollisionContacts* contacts, gfx::ColliderSphere* shape)
    {
        return false;
    }
    bool ColliderAABB::TestCollision(gfx::CollisionContacts* contacts, gfx::ColliderPlane* shape)
    {
        return false;
    }
    bool ColliderAABB::TestCollision(gfx::CollisionContacts* contacts, gfx::ColliderAABB* shape)
    {
        return gfx::AABB_Intersect_AABB(contacts, this, shape);
    }
    bool ColliderAABB::TestCollision(gfx::CollisionContacts* contacts, gfx::ColliderCone* shape)
    {
        return false;
    }
    bool ColliderAABB::TestCollision(gfx::CollisionContacts* contacts, gfx::ColliderOBB* shape)
    {
        return false;
    }
    bool ColliderAABB::TestCollision(gfx::CollisionContacts* contacts, gfx::ColliderRay* shape)
    {
        return false;
    }
    
    ColliderAABB::ColliderAABB()
    :   gfx::Collider( gfx::Collider::AABB )
    {}
}}
