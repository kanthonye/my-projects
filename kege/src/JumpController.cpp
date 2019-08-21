//
//  JumpController.cpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/20/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "Scene.hpp"
#include "Gameobject.hpp"
#include "JumpController.hpp"
namespace kege{namespace cmp{
    
    void JumpController::HandleMessage( const kege::Message& message )
    {
        if (message.GetType() == kege::MSG::JUMP)
        {
            Jump();
        }
    }
    bool JumpController::Init(kege::Scene* scene)
    {
        scene->AddMsgHandler(kege::MSG::JUMP, this);
        return gfx::Component::Init(scene);
    }
    void JumpController::UnInit()
    {
        GetScene()->RemvMsgHandler(kege::MSG::JUMP, this);
    }
    void JumpController::Jump()
    {
        phx::PhysicsComponent* body = (phx::PhysicsComponent*) GetParent()->GetComponent( gfx::Component::PHYSICS );
        if (body == nullptr) return;
        if (body->IsGrounded())
        {
            /*
             * the equation for this is as fallow:
             *
             *    F = ma = m(v/t) = (mv) / t
             *
             * ApplyAcceleration() will multiply the jump_power acceleration vector by the mass
             * of the object, thus make it a force, and add that to the objects net force.
             */
            body->ApplyAcceleration(body->GetUp() * jump_power);
            body->SetGrounded(false);
        }
    }
    JumpController::JumpController()
    :   gfx::Component(gfx::Component::JUMP)
    {}
}}
