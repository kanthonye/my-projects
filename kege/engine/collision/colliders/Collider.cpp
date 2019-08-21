//
//  Collider.cpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 6/8/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "../colliders/Collider.hpp"
namespace kege{namespace gfx{
    
    void Collider::UpdateOrientation(const gfx::Transform& world)
    {
        _world = world * _local;
        for (ds::dlist< Collider* >::iterator child=_colliders.begin(); child!=nullptr; child++)
        {
            child->UpdateOrientation( _world );
        }
    }

    bool Collider::TestCollision(gfx::CollisionContacts* contact, const Collider* collider)
    {
        switch ( collider->GetType() )
        {
            default: break;
                
            case gfx::Collider::SPHERE:
                return TestCollision(contact, (gfx::ColliderSphere*) collider);
                
            case gfx::Collider::AABB:
                return TestCollision(contact, (gfx::ColliderAABB*) collider );
                
            case gfx::Collider::OBB:
                return TestCollision(contact, (gfx::ColliderOBB*) collider );
                
            case gfx::Collider::RAY:
                return TestCollision(contact, (gfx::ColliderRay*) collider );
                
            case gfx::Collider::SEGMENT:
                return TestCollision(contact, (gfx::ColliderSegment*) collider );
                
            case gfx::Collider::PLANE:
                return TestCollision(contact, (gfx::ColliderPlane*) collider );
                
            case gfx::Collider::CYLINDER:
                return TestCollision(contact, (gfx::ColliderCylinder*) collider );
                
            case gfx::Collider::CONE:
                return TestCollision(contact, (gfx::ColliderCone*) collider );
                
            case gfx::Collider::CAPSULE:
                return TestCollision(contact, (gfx::ColliderCapsule*) collider );
        }
        return false;
    }
    
    Collider::~ Collider()
    {
        for (ds::dlist< Collider* >::iterator child=_colliders.begin(); child!=nullptr; child++)
        {
            delete child.element();
        }
        _colliders.clear();
    }
    
}}
