//
//  MotionController.hpp
//  dev0
//
//  Created by Kenneth A Esdaile on 8/22/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef MotionController_hpp
#define MotionController_hpp
#include "InputListener.hpp"
#include "MotionComponent.hpp"
namespace kege{namespace cmp{

    /**
     * @b MotionController control the motions of the @b MotionComponent via external input
     * or ai-input.
     */
    class MotionController : public gfx::Component
    {
    public:
        
        void HandleMessage( const kege::Message& message );
        bool Init( kege::Scene* scene );
        void UnInit();
        ~ MotionController();
        MotionController();
        
    private:
        
        phx::PhysicsComponent* _body;
        float _speed;
    };
}}
#endif /* MotionController_hpp */
