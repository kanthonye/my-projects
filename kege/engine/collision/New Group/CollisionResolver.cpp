//
//  CollisionResolver.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 1/13/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "CollisionResolver.hpp"
namespace kege{namespace phx{
    
    void CollisionResolver::ResolverCollision()
    {
        for (ds::dlist<phx::ContactResolver>::iterator i=contacts.begin(); i!=nullptr; i++)
        {
            i.element().ResolverContacts();
        }
        contacts.clear();
    }
    
    phx::ContactResolver& CollisionResolver::GenerateContactResolver()
    {
        return contacts.push_back();
    }
    
    CollisionResolver:: ~ CollisionResolver()
    {
        contacts.clear();
    }
    CollisionResolver::CollisionResolver()
    {
    }
    
}}
