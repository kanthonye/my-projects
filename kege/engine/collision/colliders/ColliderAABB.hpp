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
namespace kege{namespace gfx{
    
    class ColliderAABB : public gfx::Collider
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
        
        const cg::aabb& GetShape() const {return aabb;}
        ColliderAABB();
        
    private:
        
        cg::aabb aabb;
    };
}}
#endif /* ColliderAABB_hpp */
