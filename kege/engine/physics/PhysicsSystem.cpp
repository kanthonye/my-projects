/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/26/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       PhysicsSystem.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "Scene.hpp"
#include "Entity.hpp"
#include "PhysicsComponent.hpp"
#include "PhysicsSystem.hpp"
#include "TerrainSystem.hpp"
namespace kege {namespace phx{
    
    void PhysicsSystem::AddPhysicsObject(phx::PhysicsComponent* object)
    {
        physics_objetcs.push_back(object);
    }
    
    void PhysicsSystem::Update(double delta)
    {
        gfx::TerrainSystem* system = (gfx::TerrainSystem*) GetScene()->GetSystem("TerrainSystem");
        gfx::Terrain* terrain = (system != nullptr) ? system->GetTerrain() : nullptr;
        double terrain_height;
        
        cg::vec3 acceleration;
        for (phx::PhysicsComponent* body = PhysicsComponent::head; body!=nullptr; body = body->next)
        {
            force_driver.ApplyForce(*body, delta);
            
            if (body->GetParent() == nullptr)
            {
                continue;
            }
            
            acceleration = body->net_force * body->inv_mass;
            body->linear_velocity += acceleration;
            body->position += body->linear_velocity * delta;
            body->linear_momentum = body->linear_velocity * body->mass;
            body->net_force = 0.0;
            
            
            if ( terrain != nullptr )
            {
                terrain_height = terrain->GetHeightmapHeight( body->position );
                if ( body->position.y <= terrain_height )
                {
                    body->position.y = terrain_height;
                }
            }
            
            //body->GetParent()->GetLocal().rotation = body->rotation;
            body->GetParent()->GetLocal().translation = body->position;
            cg::quat_to_basis(body->_right, body->_up, body->_forward, body->GetParent()->GetWorld().rotation);
            //body->Update( delta );
        }
    }
    
    void PhysicsSystem::UnInit()
    {
        for (ds::dlist<phx::PhysicsComponent*>::iterator i = physics_objetcs.begin(); i!=nullptr; i++)
        {
            delete i.element();
        }
        physics_objetcs.clear();
        _init = false;
    }
    
    bool PhysicsSystem::Init()
    {
        _init = true;
        return _init;
    }
    
    
    PhysicsSystem::~ PhysicsSystem()
    {}
    
    PhysicsSystem::PhysicsSystem()
    :   kege::SubSystem("PhysicsSystem")
    {
        GetForceDriver().AddForce(new phx::DragForce(0.0125));
        //GetForceDriver().AddForce(new phx::FrictionForce(0.25));
        //GetForceDriver().AddForce(new phx::GravityForce(0.015));
    }
}}
