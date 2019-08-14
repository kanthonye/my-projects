//
//  Mouse.hpp
//  KEGE_ENTITY
//
//  Created by Kenneth Esdaile on 3/22/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef Mouse_hpp
#define Mouse_hpp
#include "dlist.hpp"
#include <mutex>
#include <unordered_map>
#include "Logger.hpp"
#include "Keycode.hpp"
#include "Keyboard.hpp"
#include "../../engine/game/CoreInput.hpp"
namespace kege{
    class GameEngine;
    
    class Mousekeys : public kege::Keyboard
    {
    public:
        
        void UpdateInputContext( kege::GameEngine* engine );
    };
    
    
    
    class MousePointer
    {
    public:
        
        void SetPosition(double xpos, double ypos);
        
        virtual void UpdateInputContext( kege::GameEngine* engine );
        
        const kege::Cursor& GetPointer()const;
        
        MousePointer();
        
    protected:
        
        kege::Cursor cursor;
        double x,y;
    };
    
    
    
    class MouseWheel : public MousePointer
    {
    public:
        
        void UpdateInputContext( kege::GameEngine* engine );
    };
}
#endif /* Mouse_hpp */
