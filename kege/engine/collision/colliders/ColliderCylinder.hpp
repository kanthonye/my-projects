/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/28/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ColliderCylinder.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef ColliderCylinder_hpp
#define ColliderCylinder_hpp
#include "../primatives/cylinder.hpp"
#include "../colliders/Collider.hpp"
namespace kege{namespace cg{
    
    class ColliderCylinder : public cg::Collider
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
        
        const cg::cylinder& GetShape() const {return cylinder;}
        ColliderCylinder();
        
    private:
        
        cg::cylinder cylinder;
    };
}}
#endif /* ColliderCylinder_hpp */
