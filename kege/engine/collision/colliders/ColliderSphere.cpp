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
#include "../colliders/ColliderCylinder.hpp"
namespace kege{namespace gfx{
    
    bool Sphere_Intersect_Sphere(gfx::CollisionContacts* contacts, gfx::ColliderSphere* a, gfx::ColliderSphere* b)
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
            gfx::CollisionContact& contact = contacts->push_back();
            gfx::Contact& collision = contact.collisions.push_back();
            contact.collider1 = a;
            contact.collider2 = b;
            dist = sqrt(dist);
            collision.normal = norm / dist;
            collision.point = s0.center + collision.normal * s0.radius;
            collision.penetration  = radius - dist;
            return true;
        }
    }
    
    bool Sphere_Intersect_Cylinder(gfx::CollisionContacts* contacts, gfx::ColliderSphere* s0, gfx::ColliderCylinder* s1)
    {
        // Find the distance from the plane.
        const cg::cylinder& b = s1->GetShape();
        const cg::sphere& a = s0->GetShape();
        
        const cg::vec3 axis = cg::normalize3(b.b - b.a);
        
        
        // cc represent the vector from cylinder center to sphere center
        cg::vec3 cc = a.center - (b.a + b.a) * 0.5;

        // next is to compute the length of cc. this is done by vector project using the dot product
        // between cc and the cylinder front faceing aligned axis vector called axis. axis since it
        // is a unit vector, thus its not necessary to computer and divide by this length. this value
        // is stored in variable proj_cc. it is important to note that proj_cc has a direction - or +
        float proj_cc = cg::dot3( axis, cc );
        float length  = cg::abs(proj_cc);
        float height  = b.height + a.radius;
        float dist    = height - length;

        // if (dist >= 0) then the sphere is not far from the bottom or top end of the cylinder and
        // could be intersecting. thus further calculation is needed to decide intersection
        if (dist >= 0)
        {
//            // q represence a point along the cylinders axis that is on a plane the sphere center is on
//            cg::point3 q = cylind.center + cylind.axis * proj_cc;
//            // v is the vector from q to the sphere center
//            cg::point3 v = sphere.center - q;
//            // magsq is square length of v
//            float magsq  = cg::magn3sq(v);
//            float radius = (cylind.radius + sphere.radius);
//            dist = radius * radius - magsq;
//
//            // if (dist >= 0) then there is an intersection. is not then there is no intersection
//            if (dist >= 0)
//            {
//                // at this pointer there is a collision
//                phx::ContactResolver* collision = &resolver.GenerateContactResolver();
//                collision->SetPhysicsBodies(a.GetPhysicsComponent(), b.GetPhysicsComponent());
//                Contact* contact     = &collision->GenerateContact();
//
//                // if (length > cc.height) then the collision is along the top or bottom end of the cylinder
//                if (length > cylind.height)
//                {
//                    if (proj_cc < 0) // if (proj_ab < 0) the collision is on the bottom end
//                    {
//                        contact->normal  = -cylind.axis;
//                    }
//                    else // else (proj_ab >= 0) then the collision is on the top end
//                    {
//                        contact->normal  = cylind.axis;
//                    }
//                    contact->point = sphere.center - contact->normal * sphere.radius;
//                    contact->penetration = height - length;
//                }
//                else // else then the collision is along the circular side of the cylinder
//                {
//                    magsq = sqrt(magsq);
//                    contact->normal = v / magsq;
//                    contact->point  = q + contact->normal * cylind.radius;
//                    contact->penetration = radius - magsq;
//                }
//                return true;
//            }
        }
        return false;
    }
    
    bool ColliderSphere::TestCollision( gfx::CollisionContacts* contact, gfx::ColliderCylinder* shape )
    {
        return false;
    }
    bool ColliderSphere::TestCollision( gfx::CollisionContacts* contact, gfx::ColliderTriangle* shape )
    {
        return false;
    }
    bool ColliderSphere::TestCollision( gfx::CollisionContacts* contact, gfx::ColliderSegment* shape )
    {
        return false;
    }
    bool ColliderSphere::TestCollision( gfx::CollisionContacts* contact, gfx::ColliderCapsule* shape )
    {
        return false;
    }
    bool ColliderSphere::TestCollision( gfx::CollisionContacts* contacts, gfx::ColliderSphere* shape )
    {
        return Sphere_Intersect_Sphere(contacts, this, shape);
    }
    bool ColliderSphere::TestCollision( gfx::CollisionContacts* contact, gfx::ColliderPlane* shape )
    {
        return false;
    }
    bool ColliderSphere::TestCollision( gfx::CollisionContacts* contact, gfx::ColliderAABB* shape )
    {
        return false;
    }
    bool ColliderSphere::TestCollision( gfx::CollisionContacts* contact, gfx::ColliderCone* shape )
    {
        return false;
    }
    bool ColliderSphere::TestCollision( gfx::CollisionContacts* contact, gfx::ColliderOBB* shape )
    {
        return false;
    }
    bool ColliderSphere::TestCollision( gfx::CollisionContacts* contact, gfx::ColliderRay* shape )
    {
        return false;
    }
    
    ColliderSphere::ColliderSphere()
    :   gfx::Collider( gfx::Collider::SPHERE )
    {}
}}
