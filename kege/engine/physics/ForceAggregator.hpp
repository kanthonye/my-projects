//
//  ForceAggregator.hpp
//  dev0
//
//  Created by Kenneth A Esdaile on 9/16/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef ForceAggregator_hpp
#define ForceAggregator_hpp
#include "cgm.hpp"
#include "slist.hpp"
namespace kege{namespace phx{
    class PhysicsComponent;
    
    class Force
    {
    public:
        virtual void ApplyForce(phx::PhysicsComponent& physics, float dt) = 0;
        virtual ~ Force(){}
    };
    
    
    class DragForce : public phx::Force
    {
    public:
        void ApplyForce(phx::PhysicsComponent& physics, float dt);
        DragForce(float value) : damping(-value) {}
    public:
        float damping;
    };
    
    
    class GravityForce : public phx::Force
    {
    public:
        void ApplyForce(phx::PhysicsComponent& physics, float dt);
        GravityForce(float value) : gravity(0.0, -value, 0.0) {}
    public:
        cg::vec3 gravity;
    };
    
    
    class FrictionForce : public phx::Force
    {
    public:
        void ApplyForce(phx::PhysicsComponent& physics, float dt);
        FrictionForce(float value) : coefficient(value) {}
    public:
        float coefficient; // coefficient of friction
    };
}}
#endif /* ForceAggregator_hpp */
