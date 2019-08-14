/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/28/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ColliderCylinder.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#include "../system/CollisionContact.hpp"
#include "../colliders/ColliderCylinder.hpp"
namespace kege{namespace cg{
    
    bool Cylinder_Intersect_Cylinder(cg::CollisionContacts* contacts, cg::ColliderCylinder* a, cg::ColliderCylinder* b)
    {
//        const cg::cylinder& c0 = a->GetShape();
//        const cg::cylinder& c1 = b->GetShape();
        
//        double   d0 = cg::abs(cg::dot3(c0.axis, c1.axis));
//        cg::vec3 v0 = c1.center - c0.center;
//        if (d0 == 1.0f) // facing parallel directions to each other
//        {
//            float d1 = cg::dot3(c0.axis, v0);
//            cg::point3 p0 = c0.center + c0.axis * d1;
//            double radius_sum = c0.radius + c1.radius;
//            cg::vec3 norm = c1.center - p0;
//            d0 = cg::dot3(norm, norm);
//
//            if (d0 <= cg::sq(radius_sum))
//            {
//                float d2 = cg::abs(d1);
//                if (d2 > c1.height && d2 <= c0.height + c1.height)
//                {
//                    phx::ContactResolver* collision = &resolver.GenerateContactResolver();
//                    collision->SetPhysicsBodies(a.GetPhysicsComponent(), b.GetPhysicsComponent());
//                    Contact* contact= &collision->GenerateContact();
//                    if (d1 < 0) contact->normal = c0.axis;
//                    else contact->normal = -c0.axis;
//                    contact->penetration = (c0.height + c1.height) - d2;
//                    contact->point       = c0.center + contact->normal * c0.height;
//                    return true;
//                }
//                else if (d2 <= c0.height + c1.height)
//                {
//                    d0 = sqrt(d0);
//                    norm = norm * cg::invrs(d0);
//
//                    phx::ContactResolver* collision = &resolver.GenerateContactResolver();
//                    collision->SetPhysicsBodies(a.GetPhysicsComponent(), b.GetPhysicsComponent());
//                    Contact* contact= &collision->GenerateContact();
//                    contact->normal      = -norm;
//                    contact->penetration = radius_sum - d0;
//                    contact->point       = c0.center + norm * c0.radius;
//                    return true;
//                }
//            }
//        }
        return false;
    }
    
    bool ColliderCylinder::TestCollision(cg::CollisionContacts* contacts, cg::ColliderCylinder* shape)
    {
        return cg::Cylinder_Intersect_Cylinder(contacts, this, shape);;
    }
    bool ColliderCylinder::TestCollision(cg::CollisionContacts* contacts, cg::ColliderTriangle* shape)
    {
        return false;
    }
    bool ColliderCylinder::TestCollision(cg::CollisionContacts* contacts, cg::ColliderSegment* shape)
    {
        return false;
    }
    bool ColliderCylinder::TestCollision(cg::CollisionContacts* contacts, cg::ColliderCapsule* shape)
    {
        return false;
    }
    bool ColliderCylinder::TestCollision(cg::CollisionContacts* contacts, cg::ColliderSphere* shape)
    {
        return false;
    }
    bool ColliderCylinder::TestCollision(cg::CollisionContacts* contact, cg::ColliderPlane* shape)
    {
        return false;
    }
    bool ColliderCylinder::TestCollision(cg::CollisionContacts* contact, cg::ColliderAABB* shape)
    {
        return false;
    }
    bool ColliderCylinder::TestCollision(cg::CollisionContacts* contact, cg::ColliderCone* shape)
    {
        return false;
    }
    bool ColliderCylinder::TestCollision(cg::CollisionContacts* contact, cg::ColliderOBB* shape)
    {
        return false;
    }
    bool ColliderCylinder::TestCollision(cg::CollisionContacts* contact, cg::ColliderRay* shape)
    {
        return false;
    }
    
    ColliderCylinder::ColliderCylinder()
    :   cg::Collider( cg::Collider::CYLINDER )
    {}
}}
