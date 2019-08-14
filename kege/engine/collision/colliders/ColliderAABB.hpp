/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/27/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ColliderAABB.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef ColliderAABB_hpp
#define ColliderAABB_hpp
#include "../primatives/sphere.hpp"
#include "../colliders/Collider.hpp"
namespace kege{namespace cg{
    
    class ColliderAABB : public cg::Collider
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
        
        const cg::aabb& GetShape() const {return aabb;}
        ColliderAABB();
        
    private:
        
        cg::aabb aabb;
    };
}}
#endif /* ColliderAABB_hpp */
