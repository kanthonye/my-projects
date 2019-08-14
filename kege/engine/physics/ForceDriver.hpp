//
//  ForceDriver.hpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/2/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef ForceDriver_hpp
#define ForceDriver_hpp
#include "ForceAggregator.hpp"
namespace kege{namespace phx{
  
    class ForceDriver
    {
    public:
        
        void ApplyForce(phx::PhysicsComponent& physics, float dt);
        bool RemForce(phx::Force* force);
        void AddForce(phx::Force* force);
        
        ~ ForceDriver();
        ForceDriver(){}
        
        
    private:
        
        ds::slist<phx::Force*> forces;
    };
}}
#endif /* ForceDriver_hpp */
