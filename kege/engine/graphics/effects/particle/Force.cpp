//
//  Force.cpp
//  dev0
//
//  Created by Kenneth A Esdaile on 5/30/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//
#include "Force.hpp"
#include "Gameobject.hpp"
#include "Rigidbody2D.hpp"
namespace kege{namespace gfx{
    
    void Gravity::ApplyForce(const cg::point3& p, phx::PhysicsComponent* body)
    {
        body->ApplyAcceleration(force);
    }
    Gravity::Gravity()
    :   force(0.0, -9.802 / 1000.0, 0.0)
    {}
    
    void Damping::ApplyForce(const cg::point3& p, phx::PhysicsComponent* body)
    {
        float radius = 1;//body->GetParent()->GetRadius();
        // cross-sectional area
        float area_circle = 3.14159 * radius * radius;
        // note that the velocity of the particle is normalized
        cg::vec3 drag = area_circle * body->GetLinearVelocity() * _AIR_DENSITY;
        body->ApplyAcceleration(-drag);
    }
    Damping::Damping()
    {}
    
    
    
    void Wind::ApplyForce(const cg::point3& p, phx::PhysicsComponent* body)
    {
        float radius = 1;//body->GetParent()->GetRadius();
        float area_circle = 3.14159 * radius * radius;
        float wind_speed = 0.5 * _AIR_DENSITY * speed * speed * area_circle * _AIRDRAG_COEFFICIENT;
        cg::vec3 wind = ((direction * wind_speed) / body->GetMass());
        body->ApplyAcceleration(wind);
    }
    Wind::Wind(const cg::vec3& dir, float speed)
    :   direction(dir)
    ,   speed(speed)
    {}
    Wind::Wind()
    :   direction(0.0)
    ,   speed(1.5)
    {}
    
    
    
    void AttractionForce::ApplyForce(const cg::point3& p, phx::PhysicsComponent* particle)
    {
        cg::vec3 v = p - particle->GetPosition();
        float s = cg::magn3(v);
        if (s >= 0.0005) v =  v / isnan(s);
        s = (s / radius);
        if (s > 1 ) return;
        particle->IncreaseLinearVelocity((v + cg::cross3(v,cg::vec3::up)) * s * 0.125);
    }
    AttractionForce::AttractionForce()
    :   center(0.0)
    ,   radius(300)
    ,   mass(1.0)
    {}
}}


