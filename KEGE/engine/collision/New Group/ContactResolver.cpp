//
//  ContactResolver.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 1/13/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "ContactResolver.hpp"
namespace kege{namespace phx{
    
    void ContactResolver::ApplyImpulse(const cg::vec3& impluse, const cg::vec3& normal, float penetration, phx::PhysicsComponent* body)
    {
        if (body != nullptr)
        {
            // applying inpluse
            if (cg::dot3(impluse, body->GetLinearVelocity()) < 0.0f)
            {
                body->IncreaseLinearVelocity(impluse * body->GetInvMass());
                body->IncreasePosition(penetration * normal);
            }
            else
            {
                body->IncreaseLinearVelocity(-impluse * body->GetInvMass());
                body->IncreasePosition(-penetration * normal);
            }
            
            if (cg::dot3(normal,  cg::vec3::up))
            {
                body->SetGrounded(true);
            }
        }
    }
    
    void ContactResolver::SetPhysicsBodies(phx::PhysicsComponent* a, phx::PhysicsComponent* b)
    {
        physics[0] = a;
        physics[1] = b;
        
        if (physics[0] != nullptr && physics[1] != nullptr)
        {
            restitution = physics[0]->GetRestitution();
            restitution = cg::min(restitution, physics[1]->GetRestitution());
        }
        else if (physics[0] != nullptr)
        {
            restitution = physics[0]->GetRestitution();
        }
        else if (physics[1] != nullptr)
        {
            restitution = physics[1]->GetRestitution();
        }
    }
    
    cg::vec3 ContactResolver::GetRelativeVelocity()
    {
        if (physics[0] != nullptr && physics[1] != nullptr)
        {
            return physics[1]->GetLinearVelocity() - physics[0]->GetLinearVelocity();
        }
        else if (physics[0] != nullptr)
        {
            return physics[0]->GetLinearVelocity();
        }
        else if (physics[1] != nullptr)
        {
            return physics[1]->GetLinearVelocity();
        }
        return cg::vec3::up;
    }
    
    float ContactResolver::GetInverseMassSum()
    {
        if (physics[0] != nullptr && physics[1] != nullptr)
        {
            return physics[0]->GetInvMass() + physics[1]->GetInvMass();
        }
        else if (physics[0] != nullptr)
        {
            return physics[0]->GetInvMass();
        }
        else if (physics[1] != nullptr)
        {
            return physics[1]->GetInvMass();
        }
        return 1.0f;
    }
    
    void ContactResolver::ResolverContacts()
    {
        cg::vec3 relative_velocity = GetRelativeVelocity();
        phx::Contact* contact;
        cg::vec3 impluse;
        
        float invrs_mass = GetInverseMassSum();
        float velAlongNormal;
        float force;
        float inormsq;
        
        for (ds::dlist<phx::Contact>::iterator i=contacts.begin(); i!=nullptr; i++)
        {
            contact = &i.element();
            
            // Calculate relative velocity
            // Calculate relative velocity in terms of the normal direction
            velAlongNormal = cg::dot3(relative_velocity, contact->normal);
            
            // if velocities are separating do not resolve
            if (velAlongNormal > 0)
                continue;
            
            // Calculate impluse
            inormsq = cg::invrs(cg::dot3(contact->normal, contact->normal));
            force   = -(1.0f + restitution) * velAlongNormal * inormsq * invrs_mass;
            impluse = contact->normal * force;
            
            ApplyImpulse(impluse, contact->normal, contact->penetration, physics[0]);
            ApplyImpulse(impluse, contact->normal, contact->penetration, physics[1]);
        }
        contacts.clear();
    }
    
    phx::Contact& ContactResolver::GenerateContact()
    {
        return contacts.push_back();
    }
    
    ContactResolver:: ~ ContactResolver()
    {
        physics[0] = nullptr;
        physics[1] = nullptr;
        contacts.clear();
    }
    ContactResolver::ContactResolver()
    :   restitution(0.0f)
    ,   friction(0.0f)
    {
        physics[0] = nullptr;
        physics[1] = nullptr;
    }
    
}}
