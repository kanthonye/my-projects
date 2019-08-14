//
//  CollisionProcess.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 1/6/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef CollisionProcess_hpp
#define CollisionProcess_hpp
#include "queue.hpp"
#include "dlist.hpp"
#include "Collider.hpp"
namespace kege{namespace cg{
    typedef ds::dlist<cg::Collider*> Colliders;
    class CollisionSystem;
    
    class CollisionProcess
    {
    public:
        
        virtual void ResolveCollisions(double delta) {}
        virtual void DetectCollisions(double delta) {}
        virtual void TestCollisions(double delta) {}
        
        void Update(double delta)
        {
            DetectCollisions(delta);
            TestCollisions(delta);
            ResolveCollisions(delta);
        }
        void UnInit(){}
        short Init(){return 0;}
        
        virtual ~ CollisionProcess(){}
        
    protected:
        
        cg::CollisionSystem* system;
        friend CollisionSystem;
    };
}}
#endif /* CollisionProcess_hpp */
