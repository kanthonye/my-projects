//
//  InputDispatcher.cpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 6/7/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "InputDispatcher.hpp"
namespace kege{
    
    bool InputDispatcher::OnMouseCursorMove(const kege::Cursor& cursor)
    {
        return mousecursor.onMouseCursorMove(cursor);
    }
    bool InputDispatcher::OnScrollWheelMove(const kege::Cursor& cursor)
    {
        return mousewheel.onMouseWheelMove(cursor);
    }
    bool InputDispatcher::OnMouseButtonPress(const kege::Key& key)
    {
        std::map<int, InputListeners>::iterator m = mousekeys.find(key.key);
        if (m == mousekeys.end()) return false;
        return m->second.onMouseKey(key);
    }
    bool InputDispatcher::OnKeyboardPress(const kege::Key& key)
    {
        std::map<int, InputListeners>::iterator m = keyboardkeys.find(key.key);
        if (m == keyboardkeys.end()) return false;
        return m->second.onKeyboardKey(key);
    }
    
    void InputDispatcher::AddKeyboardKeyListener(int key, InputListener* listener)
    {
        keyboardkeys[key].Add(listener);
    }
    void InputDispatcher::AddMouseKeyListener(int key, InputListener* listener)
    {
        mousekeys[key].Add(listener);
    }
    void InputDispatcher::AddMouseCursorListener(InputListener* listener)
    {
        mousecursor.Add(listener);
    }
    void InputDispatcher::AddMouseWheelListener(InputListener* listener)
    {
        mousewheel.Add(listener);
    }
}
