//
//  Keyboard.cpp
//  KEGE_ENTITY
//
//  Created by Kenneth Esdaile on 3/22/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//
#include "Keyboard.hpp"
#include "GameEngine.hpp"
namespace kege {
    
    void Keyboard::SetKey(int key, int scancode, int action, int mods)
    {
        std::lock_guard<std::mutex> scopelock(mutex_lock);
        /* keys that are already pressed are stored into the mekmap and is updated */
        kege::Key& km = active_keys[ key ];
        km.Set(key, action, mods);
    }
    
    void Keyboard::UpdateInputContext( kege::GameEngine* engine )
    {
        std::lock_guard<std::mutex> scopelock(mutex_lock);
        for (std::unordered_map<int, kege::Key>::iterator k=active_keys.begin(); k!=active_keys.end(); k++)
        {
            engine->KeyboardEvent( k->second );
            if (k->second.action == 0)
            {
                active_keys.erase( k );
            }
        }
    }
    
}


