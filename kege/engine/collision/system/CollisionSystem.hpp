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
namespace kege{namespace cg{
    class CollisionDetector;
    
    class CollisionSystem : public kege::SubSystem
    {
    public:
        
        void AddCollider(cg::Collider* collider);
        
        ds::dlist<Collider*>& GetDynamicCollider();
        ds::dlist<Collider*>& GetStaticCollider();
        
        void Update(double time_delta);
        void UnInit();
        bool Init();
        
        virtual ~ CollisionSystem();
        CollisionSystem();
        
    protected:
        
        ds::dlist<cg::CollisionProcess*> processes;
        ds::dlist<Collider*> immovable;
        ds::dlist<Collider*> movables;
    };
}}
#endif /* SceneCollision_hpp */

