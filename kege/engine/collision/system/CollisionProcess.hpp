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
namespace kege{namespace gfx{
    typedef ds::dlist<gfx::Collider*> Colliders;
    class CollisionSystem;
    
    class CollisionProcess
    {
    public:
        
        virtual void Update( double delta, gfx::CollisionSystem* system ) = 0;
        virtual void  UnInit() = 0;
        virtual short Init() = 0;
        virtual ~ CollisionProcess(){}
    };
}}
#endif /* CollisionProcess_hpp */
