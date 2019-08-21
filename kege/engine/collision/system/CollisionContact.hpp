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
namespace kege{namespace gfx{
    class Collider;
    
    
    
    struct Contact
    {
        cg::vec3 point;  /* Holds the position of the contact in world coordinates. */
        cg::vec3 normal; /* Holds the direction of the contact in world coordinates. */
        
        /*
         * Holds the depth of penetration at the contact point. If both
         * bodies are specified then the contact point should be midway
         * between the inter-penetrating points.
         */
        cg::real penetration;
    };
    typedef ds::dlist< Contact > CollisionData;
    
    
    
    class CollisionContact
    {
    public:
        
        gfx::CollisionData collisions;
        gfx::Collider* collider1;
        gfx::Collider* collider2;
        
    };
    typedef ds::dlist< CollisionContact > CollisionContacts;
}}
#endif /* CollisionContact_hpp */
