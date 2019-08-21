//
//  SceneCollision.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/28/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//
#include "Scene.hpp"
#include "Singleton.hpp"
#include "PhysicsComponent.hpp"
#include "CollisionSystem.hpp"
#include "Singleton.hpp"
#include "DebugRenderer.hpp"
namespace kege{namespace gfx{
    
    void CollisionSystem::AddCollider(gfx::Collider* collider)
    {
        if ( processes.empty() ) return;
//
//        if ( collider->GetPhysicsComponent() != nullptr )
//        {
//            movables.push_back( collider );
//        }
//        else
//        {
//            immovable.push_back( collider );
//        }
    }
    ds::dlist< gfx::Collider* >& CollisionSystem::GetDynamicCollider()
    {
        return immovable;
    }
    ds::dlist< gfx::Collider* >& CollisionSystem::GetStaticCollider()
    {
        return movables;
    }
    
    void CollisionSystem::Update(double delta)
    {
        ds::dlist< gfx::CollisionProcess* >::iterator process;
        for (process = processes.begin(); process != nullptr; process++)
        {
            process->Update( delta, this );
        }
    }
    void CollisionSystem::UnInit()
    {
        _init = false;
    }
    bool CollisionSystem::Init()
    {
        _init = true;
        return _init;
    }
    
    CollisionSystem::~ CollisionSystem()
    {
        ds::dlist< gfx::CollisionProcess* >::iterator process;
        for (process = processes.begin(); process != nullptr; process++)
            delete process.element();
        processes.clear();
        immovable.clear();
        movables.clear();
    }
    CollisionSystem::CollisionSystem()
    :   kege::SubSystem("CollisionSystem")
    {
    }
    
}}
