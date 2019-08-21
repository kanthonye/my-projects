//
//  ComponentInput.hpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 6/7/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef ComponentInput_hpp
#define ComponentInput_hpp
#include "InputListener.hpp"
#include "InputComponent.hpp"
namespace kege{namespace cmp{
    
    class ComponentInput : public kege::InputListener
    {
    public:
        bool onCursorMove(const kege::Cursor& cursor)
        {
            if (component == nullptr) return false;
            return component->onCursorMove(cursor);
        }
        bool onWheelMove(const kege::Cursor& cursor)
        {
            if (component == nullptr) return false;
            return component->onWheelMove(cursor);
        }
        bool onButton(const kege::Key& key)
        {
            if (component == nullptr) return false;
            return component->onButton(key);
        }
        bool onKey(const kege::Key& key)
        {
            if (component == nullptr) return false;
            return component->onKey(key);
        }
        ComponentInput(cmp::InputComponent* c)
        : component(c)
        {}
    private:
        
        cmp::InputComponent* component;
    };
}}
#endif /* ComponentInput_hpp */
