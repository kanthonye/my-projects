//
//  Collider.hpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 6/8/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef Collider_hpp
#define Collider_hpp
#include "cgm.hpp"
#include "ray.hpp"
#include "obb.hpp"
#include "cone.hpp"
#include "aabb.hpp"
#include "sphere.hpp"
#include "segment.hpp"
#include "capsule.hpp"
#include "triangle.hpp"
#include "cylinder.hpp"
#include "Transform.hpp"
#include "CollisionContact.hpp"
namespace kege{namespace gfx{
    
    class ColliderCylinder;
    class ColliderTriangle;
    class ColliderCapsule;
    class ColliderSegment;
    class ColliderSphere;
    class ColliderPlane;
    class ColliderCone;
    class ColliderAABB;
    class ColliderRay;
    class ColliderOBB;
    
    class Collider
    {
    public:
        
        enum Type
        {
            POLYGON,
            CYLINDER,
            TRIANGLE,
            SEGMENT,
            CAPSULE,
            SPHERE,
            PLANE,
            CONE,
            AABB,
            RAY,
            OBB
        };
        
    public:
        
        virtual bool TestCollision(gfx::CollisionContacts* contact, gfx::ColliderCylinder* shape) {return false;}
        virtual bool TestCollision(gfx::CollisionContacts* contact, gfx::ColliderTriangle* shape) {return false;}
        virtual bool TestCollision(gfx::CollisionContacts* contact, gfx::ColliderSegment* shape) {return false;}
        virtual bool TestCollision(gfx::CollisionContacts* contact, gfx::ColliderCapsule* shape) {return false;}
        virtual bool TestCollision(gfx::CollisionContacts* contact, gfx::ColliderSphere* shape) {return false;}
        virtual bool TestCollision(gfx::CollisionContacts* contact, gfx::ColliderPlane* shape) {return false;}
        virtual bool TestCollision(gfx::CollisionContacts* contact, gfx::ColliderAABB* shape) {return false;}
        virtual bool TestCollision(gfx::CollisionContacts* contact, gfx::ColliderCone* shape) {return false;}
        virtual bool TestCollision(gfx::CollisionContacts* contact, gfx::ColliderOBB* shape) {return false;}
        virtual bool TestCollision(gfx::CollisionContacts* contact, gfx::ColliderRay* shape) {return false;}
        virtual bool TestCollision(gfx::CollisionContacts* contact, const Collider* collider);
        
        virtual void UpdateOrientation(const gfx::Transform& world);
        gfx::Collider::Type GetType() const {return type;}
        
        Collider(gfx::Collider::Type t)
        :   type(t)
        {}
        
        virtual ~ Collider();
    protected:
        
        ds::dlist< Collider* > _colliders;
        gfx::Transform _world, _local;
        gfx::Collider::Type type;
    };
}}

namespace kege{namespace shared{
    typedef mem::shared< gfx::Collider > Collider;
}}
#endif /* Collider_hpp */
