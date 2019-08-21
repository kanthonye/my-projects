//
//  SceneCollision.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/28/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef SceneCollision_hpp
#define SceneCollision_hpp
#include "SubSystem.hpp"
#include "Collider.hpp"
#include "CollisionProcess.hpp"
#include "CollisionResolver.hpp"
namespace kege{namespace gfx{
    
    class CollisionSystem : public kege::SubSystem
    {
    public:
        
        void AddCollider(gfx::Collider* collider);
        
        ds::dlist< gfx::Collider* >& GetDynamicCollider();
        ds::dlist< gfx::Collider* >& GetStaticCollider();
        
        void Update(double time_delta);
        void UnInit();
        bool Init();
        
        virtual ~ CollisionSystem();
        CollisionSystem();
        
    protected:
        
        ds::dlist< gfx::CollisionProcess* > processes;
        ds::dlist< gfx::Collider* > immovable;
        ds::dlist< gfx::Collider* > movables;
    };
}}
#endif /* SceneCollision_hpp */

