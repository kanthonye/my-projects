/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/8/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ObjectCollisions.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "CollisionSystem.hpp"
#include "ObjectCollisions.hpp"
namespace kege{namespace cg{
    
    void ObjectCollisions::ResolveCollisions(double delta)
    {
        
    }
    void ObjectCollisions::DetectCollisions(double delta)
    {
        
    }
    
    void ObjectCollisions::TestCollisions(double delta)
    {
//        contacts.clear();
//        ds::dlist<Collider*>& dynamic_colliders = system->GetDynamicCollider();
//        ds::dlist<Collider*>& static_colliders = system->GetStaticCollider();
//        ds::dlist<Collider*>::iterator i, j;
//        cg::Collider* collider;
//        for (i=dynamic_colliders.begin(); i!=nullptr; i++)
//        {
//            collider = i.element();
            // test collision between moveable and immovable objects
//            for (j=static_colliders.begin(); j!=nullptr; j++)
//            {
//                if (collider->GetLayer() != j->GetLayer())
//                    continue;
//                collider->TestCollision(&contacts, j.element() );
//            }
//            
//            // test collision between moveable objects
//            j=i;
//            j++;
//            
//            for (; j!=nullptr; j++)
//            {
//                if (collider->GetLayer() != j->GetLayer())
//                    continue;
//                collider->TestCollision(&contacts, j.element() );
//            }
//        }
    }
    
    void ObjectCollisions::UnInit()
    {
        
    }
    short ObjectCollisions::Init()
    {
        return true;
    }
    
    ObjectCollisions::~ ObjectCollisions()
    {}
    ObjectCollisions::ObjectCollisions()
    {}
}}
