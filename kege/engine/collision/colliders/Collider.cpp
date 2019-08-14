//
//  Collider.cpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 6/8/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "../colliders/Collider.hpp"
namespace kege{namespace cg{
    
    void Collider::UpdateOrientation(const gfx::Transform& world)
    {
        _world = world * _local;
        for (ds::dlist< Collider* >::iterator child=_colliders.begin(); child!=nullptr; child++)
        {
            child->UpdateOrientation( _world );
        }
    }

    bool Collider::TestCollision(cg::CollisionContacts* contact, const Collider* collider)
    {
        switch ( collider->GetType() )
        {
            default: break;
                
            case cg::Collider::SPHERE:
                return TestCollision(contact, (cg::ColliderSphere*) collider);
                
            case cg::Collider::AABB:
                return TestCollision(contact, (cg::ColliderAABB*) collider );
                
            case cg::Collider::OBB:
                return TestCollision(contact, (cg::ColliderOBB*) collider );
                
            case cg::Collider::RAY:
                return TestCollision(contact, (cg::ColliderRay*) collider );
                
            case cg::Collider::SEGMENT:
                return TestCollision(contact, (cg::ColliderSegment*) collider );
                
            case cg::Collider::PLANE:
                return TestCollision(contact, (cg::ColliderPlane*) collider );
                
            case cg::Collider::CYLINDER:
                return TestCollision(contact, (cg::ColliderCylinder*) collider );
                
            case cg::Collider::CONE:
                return TestCollision(contact, (cg::ColliderCone*) collider );
                
            case cg::Collider::CAPSULE:
                return TestCollision(contact, (cg::ColliderCapsule*) collider );
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
