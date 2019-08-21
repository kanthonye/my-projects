//
//  MotionController.cpp
//  dev0
//
//  Created by Kenneth A Esdaile on 8/22/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#include "Scene.hpp"
#include "Gameobject.hpp"
#include "enumtypes.hpp"
#include "ResourceManager.hpp"
#include "MotionController.hpp"
#include "PhysicsComponent.hpp"
namespace kege{namespace cmp{

    void MotionController::HandleMessage(const kege::Message& message)
    {
        if ( _body->IsGrounded() && message.GetType() == kege::MSG::COMMAND )
        {
            const kege::MsgCommand& msg = ( const kege::MsgCommand& ) message;
            switch ( msg.command )
            {
                case kege::MSG::MOVE_FORWARD:
                    _body->ApplyAcceleration( -_body->GetForward() * _speed );
                    break;
                    
                case kege::MSG::MOVE_BACKWARD:
                    _body->ApplyAcceleration( _body->GetForward() * _speed );
                    break;
                    
                case kege::MSG::MOVE_RIGHTWARD:
                    _body->ApplyAcceleration( _body->GetRight() * _speed );
                    break;
                    
                case kege::MSG::MOVE_LEFTWARD:
                    _body->ApplyAcceleration( -_body->GetRight() * _speed );
                    break;
                    
                default:
                    break;
            }
        }
    }
    bool MotionController::Init( kege::Scene* scene )
    {
        gfx::Component::Init(scene);
        if ( _init )
        {
            _body = ( phx::PhysicsComponent* ) GetParent()->GetComponent( gfx::Component::PHYSICS );
            scene->AddMsgHandler( kege::MSG::MOVE_BACKWARD,  this );
            scene->AddMsgHandler( kege::MSG::MOVE_FORWARD,   this );
            scene->AddMsgHandler( kege::MSG::MOVE_RIGHTWARD, this );
            scene->AddMsgHandler( kege::MSG::MOVE_LEFTWARD,  this );
        }
        return _init;
    }
    void MotionController::UnInit()
    {
        if ( _init )
        {
            GetScene()->RemvMsgHandler( kege::MSG::MOVE_BACKWARD,  this );
            GetScene()->RemvMsgHandler( kege::MSG::MOVE_FORWARD,   this );
            GetScene()->RemvMsgHandler( kege::MSG::MOVE_RIGHTWARD, this );
            GetScene()->RemvMsgHandler( kege::MSG::MOVE_LEFTWARD,  this );
            Component::UnInit();
        }
    }
    
    MotionController::~ MotionController()
    {
        UnInit();
    }
    
    MotionController::MotionController()
    :   gfx::Component( gfx::Component::MOTION_CONTROL )
    ,   _body( nullptr )
    ,   _speed( 0.2 )
    {}
}}
