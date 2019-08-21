//
//  InputListener.cpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 6/7/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "InputListener.hpp"
#include "InputDispatcher.hpp"
namespace kege{
    
    InputListener:: ~ InputListener()
    {
        if (dispatcher != nullptr)
        {
            dispatcher->Remove(this);
        }
    }
    
    
    bool InputListeners::onKeyboardKey(const kege::Key& key)
    {
        for (ds::dlist<InputListener*>::iterator i=inputs.begin(); i!=nullptr; i++)
        {
            i->onKey(key);
        }
        return false;
    }
    bool InputListeners::onMouseKey(const kege::Key& key)
    {
        for (ds::dlist<InputListener*>::iterator i=inputs.begin(); i!=nullptr; i++)
        {
            i->onButton(key);
        }
        return false;
    }
    bool InputListeners::onMouseCursorMove(const kege::Cursor& cursor)
    {
        for (ds::dlist<InputListener*>::iterator i=inputs.begin(); i!=nullptr; i++)
        {
            i->onCursorMove(cursor);
        }
        return false;
    }
    bool InputListeners::onMouseWheelMove(const kege::Cursor& cursor)
    {
        for (ds::dlist<InputListener*>::iterator i=inputs.begin(); i!=nullptr; i++)
        {
            i->onWheelMove(cursor);
        }
        return false;
    }
    void InputListeners::Remove(InputListener* listener)
    {
        for (ds::dlist<InputListener*>::iterator i=inputs.begin(); i!=nullptr; i++)
        {
            if (i.element() == listener)
            {
                inputs.erase(i);
                listener->dispatcher = nullptr;
                break;
            };
        }
    }
    void InputListeners::Add(InputListener* listener)
    {
        for (ds::dlist<InputListener*>::iterator i=inputs.begin(); i!=nullptr; i++)
            if (i.element() == listener) return;
        inputs.push_back(listener);
        listener->dispatcher = this;
    }
    InputListeners::~ InputListeners()
    {
        for (ds::dlist<InputListener*>::iterator i=inputs.begin(); i!=nullptr; i++)
            i->dispatcher = nullptr;
        inputs.clear();
    }
}
