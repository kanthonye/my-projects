//
//  ForceAggregator.cpp
//  dev0
//
//  Created by Kenneth A Esdaile on 9/16/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#include "PhysicsComponent.hpp"
#include "ForceAggregator.hpp"
namespace kege{namespace phx{
    
    void DragForce::ApplyForce(phx::PhysicsComponent& body, float dt)
    {
        //if (!body.IsGrounded())
        {
            // TODO: need to calc surface area to do drag force
            body.ApplyAcceleration(body.GetLinearVelocity() * cg::vec3(damping,damping,damping));
        }
    }
    
    void GravityForce::ApplyForce(phx::PhysicsComponent& body, float dt)
    {
        body.ApplyForce(body.GetMass() * gravity);
    }
    
    void FrictionForce::ApplyForce(phx::PhysicsComponent& body, float dt)
    {
        if (body.IsGrounded())
        {
            body.ApplyAcceleration( -body.GetLinearVelocity() * coefficient );
        }
    }
}}
