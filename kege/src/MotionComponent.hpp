//
//  MotionComponent.hpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/20/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef MotionComponent_hpp
#define MotionComponent_hpp
#include "Component.hpp"
#include "PhysicsComponent.hpp"
namespace kege{namespace cmp{
    
    /**
     * @b MotionComponent is a component that contains functions that drives Rigidbody component
     * in any direction. The @b Rigidbody component is necessary to make a @b Gameobject movable.
     * @b MotionController is used along to control how these movement functions of the
     * @b MotionComponent are invoked
     */
    class MotionComponent : public gfx::Component
    {
    public:
        
        void HandleMessage( const kege::Message& message );
        bool Init(kege::Scene* scene);
        void Save(kege::XML& xml);
        
        void  SetInairMotion(bool value);
        void  SetFreeMotion(bool value);
        void  SetSpeed(float value);
        
        bool  IsInairMotion()const;
        bool  IsFreeMotion()const;
        float GetSpeed()const;
        
        void MoveBackward();
        void MoveForward();
        void MoveDownward();
        void MoveUpward();
        void MoveRightward();
        void MoveLeftward();
        
        MotionComponent(const ds::string& name, cg::real16 speed, bool inair_motion, bool anti_gravity);
        MotionComponent(cg::real16 speed, bool inair_motion, bool anti_gravity);
        MotionComponent(const ds::string& name);
        MotionComponent();
        
    protected:
        
        phx::PhysicsComponent* body;
        
        float speed;
        bool  inair_motion;
        bool  anti_gravity;
    };
}}
#endif /* MotionComponent_hpp */
