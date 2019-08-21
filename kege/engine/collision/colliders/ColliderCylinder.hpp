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
namespace kege{namespace gfx{
    
    class ColliderCylinder : public gfx::Collider
    {
    public:
        
        bool TestCollision( gfx::CollisionContacts* contact, gfx::ColliderCylinder* shape );
        bool TestCollision( gfx::CollisionContacts* contact, gfx::ColliderTriangle* shape );
        bool TestCollision( gfx::CollisionContacts* contact, gfx::ColliderSegment* shape );
        bool TestCollision( gfx::CollisionContacts* contact, gfx::ColliderCapsule* shape );
        bool TestCollision( gfx::CollisionContacts* contact, gfx::ColliderSphere* shape );
        bool TestCollision( gfx::CollisionContacts* contact, gfx::ColliderPlane* shape );
        bool TestCollision( gfx::CollisionContacts* contact, gfx::ColliderAABB* shape );
        bool TestCollision( gfx::CollisionContacts* contact, gfx::ColliderCone* shape );
        bool TestCollision( gfx::CollisionContacts* contact, gfx::ColliderOBB* shape );
        bool TestCollision( gfx::CollisionContacts* contact, gfx::ColliderRay* shape );
        
        const cg::cylinder& GetShape() const { return cylinder; }
        ColliderCylinder();
        
    private:
        
        cg::cylinder cylinder;
    };
}}
#endif /* ColliderCylinder_hpp */
