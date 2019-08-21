//
//  Collider.hpp
//  dev0
//
//  Created by Kenneth A Esdaile on 8/2/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//
#ifndef CollisionComponent_hpp
#define CollisionComponent_hpp
#include "../colliders/Collider.hpp"
#include "../../physics/PhysicsComponent.hpp"
namespace kege{namespace gfx{
    
    class CollisionComponent : public gfx::Component
    {
    public:
        
        const phx::PhysicsComponent* GetPhysicsComponent() const {return _body;}
        phx::PhysicsComponent* GetPhysicsComponent() {return _body;}
        
        void GetCollider(gfx::Collider* collider) {_collider = collider;}
        const gfx::Collider* GetCollider() const  {return _collider;}
        gfx::Collider* GetCollider()  {return _collider;}
        
        bool Init(kege::Scene* scene);
        
        void SetLayer(cg::uint value) {_layer = value;}
        cg::uint GetLayer()const {return _layer;}
        
        CollisionComponent(gfx::Collider* collider);
        ~ CollisionComponent();
        
    protected:
        
        phx::PhysicsComponent* _body;
        gfx::Collider* _collider;
        cg::uint _layer;
        
        static CollisionComponent* head;
        static CollisionComponent* tail;
        CollisionComponent* next;
        CollisionComponent* prev;
    };
}}
#endif /* Collider_hpp */
