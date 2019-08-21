//
//  MotionComponent.cpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/20/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "MotionComponent.hpp"
#include "Scene.hpp"
#include "Gameobject.hpp"
#include "enumtypes.hpp"
#include "Singleton.hpp"
#include "ResourceManager.hpp"
#include "PhysicsComponent.hpp"
#include "MotionController.hpp"
namespace kege{namespace cmp{
    
    void MotionComponent::HandleMessage( const kege::Message& message )
    {
        if ( body != nullptr )
        {
            switch ( message.GetType() )
            {
                case kege::MSG::MOVE_FORWARD:
                    MoveForward();
                    break;
                    
                case kege::MSG::MOVE_BACKWARD:
                    MoveBackward();
                    break;
                    
                case kege::MSG::MOVE_RIGHTWARD:
                    MoveRightward();
                    break;
                    
                case kege::MSG::MOVE_LEFTWARD:
                    MoveLeftward();
                    break;
                    
                default:
                    break;
            }
        }
    }
    bool MotionComponent::Init(kege::Scene* scene)
    {
        body = (phx::PhysicsComponent*) GetParent()->GetComponent(gfx::Component::PHYSICS);
        return true;
    }
    
    void MotionComponent::Save(kege::XML& xml)
    {
        kege::XML* xmov = xml.AddChild(new kege::XML("motion-movement"));
        
        kege::XML* child = xmov->AddChild(new kege::XML("speed"));
        child->AddAttr(new XML::attrib("float", ds::string::strprint("%f", speed)));
        
        child = xmov->AddChild(new kege::XML("inair_motion"));
        child->AddAttr(new XML::attrib("bool", ds::string::strprint("%i", inair_motion)));
        
        child = xmov->AddChild(new kege::XML("anti_gravity"));
        child->AddAttr(new XML::attrib("bool", ds::string::strprint("%i", anti_gravity)));
    }
    
    void MotionComponent::MoveBackward()
    {
        if (body == nullptr) return;
        
        if (body->IsGrounded() || (inair_motion || anti_gravity))
        {
            body->ApplyAcceleration(body->GetForward() * speed);
        }
    }
    void MotionComponent::MoveForward()
    {
        if (body == nullptr) return;
        
        if (body->IsGrounded() || (inair_motion || anti_gravity))
        {
            body->ApplyAcceleration(-body->GetForward() * speed );
        }
    }
    void MotionComponent::MoveDownward()
    {
        if (body == nullptr) return;
        
        if (body->IsGrounded() || (inair_motion || anti_gravity))
        {
            if (anti_gravity) body->ApplyAcceleration(-body->GetUp() * speed);
        }
    }
    void MotionComponent::MoveUpward()
    {
        if (body == nullptr) return;
        
        if (body->IsGrounded() || (inair_motion || anti_gravity))
        {
            if (anti_gravity) body->ApplyAcceleration(body->GetUp() * speed);
        }
    }
    void MotionComponent::MoveRightward()
    {
        if (body == nullptr) return;
        
        if (body->IsGrounded() || (inair_motion || anti_gravity))
        {
            body->ApplyAcceleration(body->GetRight() * speed);
        }
    }
    void MotionComponent::MoveLeftward()
    {
        if (body == nullptr) return;
        
        if (body->IsGrounded() || (inair_motion || anti_gravity))
        {
            body->ApplyAcceleration(-body->GetRight() * speed);
        }
    }
    
    void  MotionComponent::SetInairMotion(bool value)
    {
        inair_motion = value;
    }
    void  MotionComponent::SetFreeMotion(bool value)
    {
        anti_gravity = value;
    }
    void  MotionComponent::SetSpeed(float value)
    {
        speed = value;
    }
    
    bool  MotionComponent::IsInairMotion()const
    {
        return inair_motion;
    }
    bool  MotionComponent::IsFreeMotion()const
    {
        return anti_gravity;
    }
    float MotionComponent::GetSpeed()const
    {
        return speed;
    }
    
    MotionComponent::MotionComponent(const ds::string& name, cg::real16 speed, bool inair, bool free)
    :   gfx::Component(gfx::Component::MOTION_CONTROL, name)
    ,   body(nullptr)
    ,   speed(speed)
    ,   inair_motion(inair)
    ,   anti_gravity(free)
    {}
    
    MotionComponent::MotionComponent(cg::real16 speed, bool inair_motion, bool free_motion)
    :   gfx::Component(gfx::Component::MOTION_CONTROL)
    ,   body(nullptr)
    ,   speed(speed)
    ,   inair_motion(inair_motion)
    ,   anti_gravity(free_motion)
    {}
    
    MotionComponent::MotionComponent(const ds::string& name)
    :   gfx::Component(gfx::Component::MOTION_CONTROL, name)
    ,   body(nullptr)
    ,   speed(0.2)
    ,   inair_motion(false)
    ,   anti_gravity(false)
    {}
    
    MotionComponent::MotionComponent()
    :   gfx::Component(gfx::Component::MOTION_CONTROL)
    ,   body(nullptr)
    ,   speed(0.2)
    ,   inair_motion(false)
    ,   anti_gravity(false)
    {}
}}
