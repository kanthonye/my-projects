//
//  JumpComponent.cpp
//  dev0
//
//  Created by Kenneth A Esdaile on 9/8/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#include "Scene.hpp"
#include "Gameobject.hpp"
#include "MotionController.hpp"
#include "JumpComponent.hpp"
namespace kege{namespace cmp{
    
    bool JumpComponent::Init(kege::Scene& scene)
    {
        //body = (phx::PhysicsComponent*) GetParent()->GetComponent( gfx::Component::PHYSICS );
        return true;
    }
    void JumpComponent::Save(kege::XML& xml)
    {
        kege::XML* xjmp = xml.AddChild(new kege::XML("motion-jump"));
        xjmp->AddAttr(new XML::attrib("jump_power", ds::string::strprint("%f", jump_power)));
    }
    
    void JumpComponent::Jump()
    {
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
    
    JumpComponent::JumpComponent(cg::real16 jump_power, const ds::string& name)
    :   gfx::Component(gfx::Component::JUMP, name)
    ,   jump_power(jump_power)
    ,   body(nullptr)
    {
    }
    
    JumpComponent::JumpComponent(cg::real16 jump_power)
    :   gfx::Component(gfx::Component::JUMP)
    ,   jump_power(jump_power)
    ,   body(nullptr)
    {
    }
    
    JumpComponent::JumpComponent()
    :   gfx::Component(gfx::Component::JUMP)
    ,   jump_power(6)
    ,   body(nullptr)
    {}
}}
