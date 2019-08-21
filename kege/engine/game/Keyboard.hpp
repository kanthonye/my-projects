//
//  Keyboard.hpp
//  KEGE_ENTITY
//
//  Created by Kenneth Esdaile on 3/22/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//
#ifndef USER_INPUTS_HPP
#define USER_INPUTS_HPP
#include "dlist.hpp"
#include <mutex>
#include <unordered_map>
#include "Keycode.hpp"
#include "../../engine/game/CoreInput.hpp"
namespace kege {
    class GameEngine;
    
    class Keyboard
    {
    public:
        
        void SetKey(int key, int scancode, int action, int mods);
        virtual void UpdateInputContext( kege::GameEngine* engine );
        
    protected:
        
        std::unordered_map<int, kege::Key> active_keys;
        std::mutex mutex_lock;
    };
}
#endif /* USER_INPUTS_HPP */
