//
//  RotByCamComponent.cpp
//  dev0
//
//  Created by Kenneth A Esdaile on 9/11/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//
#include "Scene.hpp"
#include "Gameobject.hpp"
#include "enumtypes.hpp"
#include "RotByCamComponent.hpp"
namespace kege{namespace cmp{
    
    bool RotByCamComponent::Control::onButton(const kege::Key& key)
    {
        if (key.key == BUTTON_RIGHT && key.action)
        {
             //cg::quat r = cg::quat(control->rc->GetRotationAngles().x, cg::vec3::up);
            //control->object->GetLocal().rotation = r;
            return true;
        }
        return false;
    }
    
    bool RotByCamComponent::Init(kege::Scene* scene)
    {
        //scene->AddMsgHandler(cg::uint msgtyp, kege::Object *object)
        //rc = (cmp::RotationComponent*) GetParent()->GetComponent(kege::ENUM::_COMPONENT_ROTATION);
        return true;
    }
    
    RotByCamComponent::RotByCamComponent(const ds::string& name, gfx::Gameobject* obj)
    :   gfx::Component(kege::ENUM::_ROTBYCAM_COMPONENT, name)
    ,   object(obj)
    ,   control(this)
    {
        
    }
    RotByCamComponent::RotByCamComponent(gfx::Gameobject* obj)
    :   gfx::Component(kege::ENUM::_ROTBYCAM_COMPONENT)
    ,   object(obj)
    ,   control(this)
    {
        
    }
    
}}
