//
//  UsrCamLookAtComp.cpp
//  dev0
//
//  Created by Kenneth Esdaile on 8/31/17.
//  Copyright © 2017
#include "Gameobject.hpp"
#include "Scene.hpp"
#include "FallowComponent.hpp"
namespace kege{namespace cmp{
    
    bool FallowComponent::ZoomControl::onWheelMove(const kege::Cursor& cursor)
    {
        c->distance_offset.x += cursor.y * c->sensitivity.x;
        c->distance_offset.x = cg::clamp(c->distance_offset.x, c->distance_offset.y, c->distance_offset.z);
        return false;
    }
    
    bool FallowComponent::Init(kege::Scene* scene)
    {
        scene->AddMsgHandler(kege::MSG::ZOOM, this);
        physics = (phx::PhysicsComponent*) GetParent()->GetComponent(kege::ENUM::_COMPONENT_PHYSICS);
        return true;
    }
        
    void cmp::FallowComponent::Update(double dt)
    {
        if (physics == nullptr) return;
        
        target = object->GetWorld().translation;
    
//        printf("%s \n", object->GetName().c_str());
//        print(target);
//        printf("\n");
        
        cg::point3 p;
        p.x = target.x - (physics->GetForward().x * distance_offset.x);
        p.y = target.y - (physics->GetForward().y * distance_offset.x) - height_offset.x;
        p.z = target.z - (physics->GetForward().z * distance_offset.x);
        
        physics->SetPosition(p);
    }
    
    gfx::Component* cmp::FallowComponent::Duplicate()
    {
        cmp::FallowComponent* comp = new cmp::FallowComponent(object);
        comp->distance_offset = distance_offset;
        comp->height_offset = height_offset;
        comp->sensitivity = sensitivity;
        return comp;
    }
    
    cmp::FallowComponent::FallowComponent(gfx::Gameobject* object)
    :   gfx::Component(kege::ENUM::_COMPONENT_FALLOW)
    ,   object(object)
    ,   sensitivity(0.1)
    ,   distance_offset(-30,-1000,0)
    ,   height_offset(-3,-1000,0)
    ,   target(0,1,0)
    ,   height_adjust(false)
    ,   physics(nullptr)
    ,   zoom(this)
    {
    }

    
    
    void CameraZoomIn::HandleMessage( const kege::Message& message )
    {
        if (message.GetType() == kege::MSG::ZOOM_IN)
        {
            distance += sensitivity * (( const kege::MsgZoomin& ) message).val;
            distance  = cg::clamp(distance, min_distance, max_distance);
            
            gfx::Entity* player = GetScene()->GetPlayer();
            physics->GetLocalPosition().x = player->GetWorldPosition().x - (physics->GetForward().x * distance);
            physics->GetLocalPosition().z = player->GetWorldPosition().z - (physics->GetForward().z * distance);
        }
    }
    bool CameraZoomIn::Init(kege::Scene* scene)
    {
        scene->AddMsgHandler(kege::MSG::ZOOM, this);
        physics = (phx::PhysicsComponent*) GetParent()->GetComponent(kege::ENUM::_COMPONENT_PHYSICS);
        return true;
    }
    void CameraZoomIn::UnInit()
    {
        GetScene()->RemvMsgHandler(kege::MSG::ZOOM, this);
    }
    CameraZoomIn::CameraZoomIn( phx::PhysicsComponent* physics )
    :   gfx::Component( kege::ENUM::_COMPONENT_FALLOW )
    {}
    
    
}}
