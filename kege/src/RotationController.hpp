//
//  RotationController.hpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/20/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef RotationController_hpp
#define RotationController_hpp
#include "InputListener.hpp"
#include "RotationComponent.hpp"
namespace kege{namespace cmp{

    class RotationController : public gfx::Component
    {
    public:
        
        void HandleMessage( const kege::Message& message );
        void Rotate(double x, double y, double z);
        bool Init( kege::Scene* scene );
        void UnInit();
        
        ~ RotationController();
        RotationController();
        
    private:
        
        phx::PhysicsComponent* _body;
        double _rx, _ry, _rz;
        bool _rotate;
    };
}}
#endif /* RotationController_hpp */
