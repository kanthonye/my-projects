//
//  RotationController.cpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/20/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "enumtypes.hpp"
#include "Scene.hpp"
#include "Entity.hpp"
#include "InputDispatcher.hpp"
#include "RotationController.hpp"
namespace kege{namespace cmp{

    void RotationController::HandleMessage( const kege::Message& message )
    {
        if ( message.GetType() == kege::MSG::ROTATE_XY )
        {
            if ( _rotate == true )
            {
                const kege::MsgRotateXY& msg = (( const kege::MsgRotateXY& )message);
                Rotate(msg.x, msg.y, 0);
            }
        }
        else if ( message.GetType() == kege::MSG::COMMAND )
        {
            const kege::MsgCommand& msg = ( const kege::MsgCommand& ) message;
            if ( msg.command == kege::MSG::ROTATE )
            {
                _rotate = msg.action;
            }
        }
    }
    void RotationController::Rotate(double x, double y, double z)
    {
        _rx += cg::clamp(x, -3600.0, 3600.0);
        _ry += cg::clamp(y, -3600.0, 3600.0);
        _rx = cg::cycle(_rx, -360.0, 360.0);
        _ry = cg::clamp(_ry, -90.0, 90.0);
        
        //body->SetOrientation( cg::axis_angleX(ry) * cg::axis_angleY(rx) );
        GetParent()->GetLocal().rotation = cg::axis_angleX( _ry ) * cg::axis_angleY( _rx );
    }
    bool RotationController::Init(kege::Scene* scene)
    {
        if ( !_init )
        {
            Component::Init( scene );
            scene->AddMsgHandler( kege::MSG::ROTATE_XY, this );
            scene->AddMsgHandler( kege::MSG::ROTATE, this );
        }
        return _init;
    }
    void RotationController::UnInit()
    {
        if ( _init )
        {
            GetScene()->AddMsgHandler( kege::MSG::ROTATE_XY, this );
            GetScene()->AddMsgHandler( kege::MSG::ROTATE, this );
            Component::UnInit();
        }
    }
    cmp::RotationController::~ RotationController()
    {
        UnInit();
    }
    cmp::RotationController::RotationController()
    :   gfx::Component(gfx::Component::ROTATION_CONTROL)
    ,   _body( nullptr )
    ,   _rotate( false )
    ,   _rx( 0.0 )
    ,   _ry( 0.0 )
    ,   _rz( 0.0 )
    {}
}}
