//
//  Mouse.cpp
//  KEGE_ENTITY
//
//  Created by Kenneth Esdaile on 3/22/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//

#include "Mouse.hpp"
#include "Keyboard.hpp"
#include "GameEngine.hpp"
namespace kege {
    
//    void MouseKeys::SetKey(int key, int action, int mods)
//    {
//        std::lock_guard<std::mutex> scopelock(mutex_lock);
//        /* keys that are already pressed are stored into the mekmap and is updated */
//        kege::Key& km = active_keys[ key ];
//        km.Set(key, action, mods);
//    }
//    
//    void MouseKeys::UpdateInputContexts(ds::dlist<kege::CoreInput*>& contexts)
//    {
//        for (ds::dlist<kege::CoreInput*>::iterator i=contexts.begin(); i!=nullptr; i++)
//        {
//            UpdateInputContext( i.element() );
//        }
//    }
    void MousePointer::SetPosition(double xpos, double ypos)
    {
        x = xpos;
        y = ypos;
    }
    
    void MousePointer::UpdateInputContext( kege::GameEngine* engine )
    {
        cursor.Update(x, y);
        if (cursor.Moved())
        {
            engine->MouseCursorEvent(cursor);
        }
    }
    
    const kege::Cursor& MousePointer::GetPointer()const
    {
        return cursor;
    }
    
    MousePointer::MousePointer()
    :   x(0.0)
    ,   y(0.0)
    {}
    
    
    
    
    void Mousekeys::UpdateInputContext( kege::GameEngine* engine )
    {
        std::lock_guard<std::mutex> scopelock(mutex_lock);
        for (std::unordered_map<int, kege::Key>::iterator k=active_keys.begin(); k!=active_keys.end(); k++)
        {
            engine->MouseButtonEvent( k->second );
            if (k->second.action == 0)
            {
                active_keys.erase( k );
            }
        }
    }
    
    
    void MouseWheel::UpdateInputContext( kege::GameEngine* engine )
    {
        cursor.Update(x, y);
        if (cursor.Moved())
        {
            engine->MouseWheelEvent( cursor );
        }
    }
}
