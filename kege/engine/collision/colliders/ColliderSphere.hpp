/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/10/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       RigidSphere.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef RigidSphere_hpp
#define RigidSphere_hpp
#include "../primatives/sphere.hpp"
#include "../colliders/Collider.hpp"
namespace kege{namespace cg{
    
    class ColliderSphere : public cg::Collider
    {
    public:
        
        bool TestCollision(cg::CollisionContacts* contact, cg::ColliderCylinder* shape);
        bool TestCollision(cg::CollisionContacts* contact, cg::ColliderTriangle* shape);
        bool TestCollision(cg::CollisionContacts* contact, cg::ColliderSegment* shape);
        bool TestCollision(cg::CollisionContacts* contact, cg::ColliderCapsule* shape);
        bool TestCollision(cg::CollisionContacts* contact, cg::ColliderSphere* shape);
        bool TestCollision(cg::CollisionContacts* contact, cg::ColliderPlane* shape);
        bool TestCollision(cg::CollisionContacts* contact, cg::ColliderAABB* shape);
        bool TestCollision(cg::CollisionContacts* contact, cg::ColliderCone* shape);
        bool TestCollision(cg::CollisionContacts* contact, cg::ColliderOBB* shape);
        bool TestCollision(cg::CollisionContacts* contact, cg::ColliderRay* shape);
        
        const cg::sphere& GetShape() const {return sphere;}
        ColliderSphere();
        
    private:
        
        cg::sphere sphere;
    };
}}
#endif /* RigidSphere_hpp */
