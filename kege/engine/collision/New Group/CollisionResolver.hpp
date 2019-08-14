//
//  CollisionResolver.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 1/13/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef CollisionResolver_hpp
#define CollisionResolver_hpp
#include "ContactResolver.hpp"
namespace kege{namespace phx{
    
    class CollisionResolver
    {
    public:
        
        phx::ContactResolver& GenerateContactResolver();
        void ResolverCollision();
        
        virtual ~ CollisionResolver();
        CollisionResolver();
        
    protected:
        
        ds::dlist<phx::ContactResolver> contacts;
    };
}}
#endif /* CollisionResolver_hpp */
