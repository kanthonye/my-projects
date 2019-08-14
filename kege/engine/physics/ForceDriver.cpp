//
//  ForceDriver.cpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/2/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "ForceDriver.hpp"
namespace kege{namespace phx{

    void ForceDriver::ApplyForce(phx::PhysicsComponent& physics, float dt)
    {
        for (ds::slist<phx::Force*>::iterator f=forces.begin(); f!=nullptr; f++)
        {
            f->ApplyForce(physics, dt);
        }
    }
    
    bool ForceDriver::RemForce(phx::Force* force)
    {
        for (ds::slist<phx::Force*>::iterator f=forces.begin(); f!=nullptr; f++)
        {
            if (f.element() == force)
            {
                forces.erase(f);
                return true;
            }
        }
        return false;
    }
    
    void ForceDriver::AddForce(phx::Force* force)
    {
        RemForce(force);
        forces.push_back(force);
    }
    
    ForceDriver::~ ForceDriver()
    {
        for (ds::slist<phx::Force*>::iterator f=forces.begin(); f!=nullptr; f++)
        {
            delete f.element();
        }
        forces.clear();
    }
    
}}
