//
//  CollisionComponent.cpp
//  dev0
//
//  Created by Kenneth A Esdaile on 8/2/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//
#include "Scene.hpp"
#include "Gameobject.hpp"
#include "Singleton.hpp"
#include "RenderComponent.hpp"
#include "CollisionComponent.hpp"
#include "CollisionSystem.hpp"
namespace kege{namespace cmp{
    
    bool CollisionComponent::Init(kege::Scene* scene)
    {
        //_collider->UpdateOrientation( GetWorld() );
        return true;
    }
    
    CollisionComponent::CollisionComponent(cg::Collider* collider)
    :   gfx::EntityComponent(kege::ENUM::_COLLIDER_COMPONANT)
    ,   _body(nullptr)
    ,   _collider(collider)
    ,   _layer(0)
    ,   next(nullptr)
    ,   prev(nullptr)
    {
        if (head == nullptr)
        {
            tail = head = this;
        }
        else
        {
            tail->next = this;
            this->prev = tail;
            tail = this;
        }
    }
    
    CollisionComponent::~ CollisionComponent()
    {
        if (prev != nullptr && next != nullptr)
        {
            prev->next = next;
            next->prev = prev;
        }
        else if (this != head)
        {
            head = next;
        }
        else if (this != tail)
        {
            tail = prev;
        }
    }
    
    CollisionComponent* CollisionComponent::head = nullptr;
    CollisionComponent* CollisionComponent::tail = nullptr;
}}
