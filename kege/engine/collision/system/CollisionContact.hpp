/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/8/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       CollisionContact.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef CollisionContact_hpp
#define CollisionContact_hpp
#include "../primatives/collision.hpp"
namespace kege{namespace cg{
    class Collider;
    
    class CollisionContact
    {
    public:
        
        cg::collisions collisions;
        cg::Collider* collider1;
        cg::Collider* collider2;
        
    };
    
    typedef ds::dlist<CollisionContact> CollisionContacts;
}}
#endif /* CollisionContact_hpp */
