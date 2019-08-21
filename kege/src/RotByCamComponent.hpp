//
//  RotByCamEntityComponent.hpp
//  dev0
//
//  Created by Kenneth A Esdaile on 9/11/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef RotByCamComponent_hpp
#define RotByCamComponent_hpp
#include "MotionController.hpp"
#include "RotationComponent.hpp"
namespace kege{namespace cmp{
    
    /**
     UsrCamRotContr (User Camera Rotation Controller): this component
     is used to rotate an entity along the x and y axis;
     */
    class RotByCamComponent : public gfx::Component
    {
    public:
        
        class Control : public kege::InputListener
        {
        public:
            bool onButton(const kege::Key& key);
            
            Control(cmp::RotByCamComponent* c)
            :   control(c)
            ,   rotate(false)
            {}
            
            cmp::RotByCamComponent* control;
            bool rotate;
        }control;
        
        bool Init(kege::Scene* scene);
        
        RotByCamComponent(const ds::string& name, gfx::Gameobject* obj);
        RotByCamComponent(gfx::Gameobject* object);
        virtual ~ RotByCamComponent(){}
        
    protected:
        
        cmp::RotationComponent* rc;
        gfx::Gameobject* object;
    };
}}
#endif /* RotByCamComponent_hpp */
