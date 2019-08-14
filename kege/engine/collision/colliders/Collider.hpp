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
namespace kege{namespace cg{
    
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
        
        virtual bool TestCollision(cg::CollisionContacts* contact, cg::ColliderCylinder* shape) {return false;}
        virtual bool TestCollision(cg::CollisionContacts* contact, cg::ColliderTriangle* shape) {return false;}
        virtual bool TestCollision(cg::CollisionContacts* contact, cg::ColliderSegment* shape) {return false;}
        virtual bool TestCollision(cg::CollisionContacts* contact, cg::ColliderCapsule* shape) {return false;}
        virtual bool TestCollision(cg::CollisionContacts* contact, cg::ColliderSphere* shape) {return false;}
        virtual bool TestCollision(cg::CollisionContacts* contact, cg::ColliderPlane* shape) {return false;}
        virtual bool TestCollision(cg::CollisionContacts* contact, cg::ColliderAABB* shape) {return false;}
        virtual bool TestCollision(cg::CollisionContacts* contact, cg::ColliderCone* shape) {return false;}
        virtual bool TestCollision(cg::CollisionContacts* contact, cg::ColliderOBB* shape) {return false;}
        virtual bool TestCollision(cg::CollisionContacts* contact, cg::ColliderRay* shape) {return false;}
        virtual bool TestCollision(cg::CollisionContacts* contact, const Collider* collider);
        
        virtual void UpdateOrientation(const gfx::Transform& world);
        cg::Collider::Type GetType() const {return type;}
        
        Collider(cg::Collider::Type t)
        :   type(t)
        {}
        
        virtual ~ Collider();
    protected:
        
        ds::dlist< Collider* > _colliders;
        gfx::Transform _world, _local;
        cg::Collider::Type type;
    };
}}
#endif /* Collider_hpp */
