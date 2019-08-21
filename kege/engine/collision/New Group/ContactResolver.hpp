//
//  ContactResolver.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 1/13/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef ContactResolver_hpp
#define ContactResolver_hpp
#include "CollisionComponent.hpp"
namespace kege{namespace phx{
    
    /**
     * A contact represents two bodies in contact. Resolving a
     * contact removes their interpenetration, and applies sufficient
     * impulse to keep them apart. Colliding bodies may also rebound.
     * Contacts can be used to represent positional joints, by making
     * the contact constraint keep the bodies in their correct
     * orientation.
     */
    struct Contact
    {
        /*
         * Holds the position of the contact in world coordinates.
         */
        cg::point3 point;
        
        /*
         * Holds the direction of the contact in world coordinates.
         */
        cg::vec3 normal;
        
        /*
         * Holds the depth of penetration at the contact point. If both
         * bodies are specified then the contact point should be midway
         * between the inter-penetrating points.
         */
        cg::real penetration;
        
        Contact()
        :   penetration(0.0f)
        {}
    };
    
    class ContactResolver
    {
    public:
        
        void ApplyImpulse(const cg::vec3& impluse, const cg::vec3& normal, float penetration, phx::PhysicsComponent* physics);
        void SetPhysicsBodies(phx::PhysicsComponent* a, phx::PhysicsComponent* b);
        cg::vec3 GetRelativeVelocity();
        float GetInverseMassSum();
        void ResolverContacts();
        
        phx::Contact& GenerateContact();
        virtual ~ ContactResolver();
        ContactResolver();
        
    protected:
        
        ds::dlist<phx::Contact> contacts;
        phx::PhysicsComponent* physics[2];
        cg::real restitution;
        cg::real friction;
    };
}}
#endif /* ContactResolver_hpp */
