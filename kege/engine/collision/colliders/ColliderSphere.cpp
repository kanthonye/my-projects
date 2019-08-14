/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/10/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       RigidSphere.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

//#include "../primatives/ray.hpp"
//#include "../primatives/obb.hpp"
//#include "../primatives/cone.hpp"
//#include "../primatives/aabb.hpp"
//#include "../primatives/plane.hpp"
//#include "../primatives/capsule.hpp"
//#include "../primatives/segment.hpp"
//#include "../primatives/triangle.hpp"
//#include "../primatives/cylinder.hpp"
#include "../colliders/ColliderSphere.hpp"
namespace kege{namespace cg{
    
    bool CollisionSphereSphere(cg::CollisionContacts* contacts, cg::ColliderSphere* a, cg::ColliderSphere* b)
    {
        const cg::sphere& s0 = a->GetShape();
        const cg::sphere& s1 = b->GetShape();
        // Find the vector between the objects.
        cg::vec3 norm = s0.center - s1.center;
        cg::real dist = cg::magn3sq(norm);
        // Spheres intersect if squared distance is less than squared sum of radii
        float radius = s0.radius + s1.radius;
        // See if it is large enough.
        if (dist > radius * radius)
        {
            return false;
        }
        else
        {
            // sphere collision only generate one kind of contact, and that is point contact.
            // multiple collision contact points dont happen with sphere collision
            cg::CollisionContact& contact = contacts->push_back();
            contact.collider1 = a;
            contact.collider2 = b;
            cg::collision& collision = contact.collisions.push_back();
            dist = sqrt(dist);
            collision.normal = norm / dist;
            collision.point = s0.center + collision.normal * s0.radius;
            collision.penetration  = radius - dist;
            return true;
        }
    }
    
    bool ColliderSphere::TestCollision(cg::CollisionContacts* contact, cg::ColliderCylinder* shape)
    {
        return false;
    }
    bool ColliderSphere::TestCollision(cg::CollisionContacts* contact, cg::ColliderTriangle* shape)
    {
        return false;
    }
    bool ColliderSphere::TestCollision(cg::CollisionContacts* contact, cg::ColliderSegment* shape)
    {
        return false;
    }
    bool ColliderSphere::TestCollision(cg::CollisionContacts* contact, cg::ColliderCapsule* shape)
    {
        return false;
    }
    bool ColliderSphere::TestCollision(cg::CollisionContacts* contacts, cg::ColliderSphere* shape)
    {
        return CollisionSphereSphere(contacts, this, shape);
    }
    bool ColliderSphere::TestCollision(cg::CollisionContacts* contact, cg::ColliderPlane* shape)
    {
        return false;
    }
    bool ColliderSphere::TestCollision(cg::CollisionContacts* contact, cg::ColliderAABB* shape)
    {
        return false;
    }
    bool ColliderSphere::TestCollision(cg::CollisionContacts* contact, cg::ColliderCone* shape)
    {
        return false;
    }
    bool ColliderSphere::TestCollision(cg::CollisionContacts* contact, cg::ColliderOBB* shape)
    {
        return false;
    }
    bool ColliderSphere::TestCollision(cg::CollisionContacts* contact, cg::ColliderRay* shape)
    {
        return false;
    }
    
    ColliderSphere::ColliderSphere()
    :   cg::Collider( cg::Collider::SPHERE )
    {}
}}
