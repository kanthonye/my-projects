//
//  InputComponent.hpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 6/7/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef InputComponent_hpp
#define InputComponent_hpp
#include "Component.hpp"
#include "InputDispatcher.hpp"
namespace kege{namespace cmp{

    class InputComponent : public gfx::Component
    {
    public:
        
        virtual bool onCursorMove(const kege::Cursor& cursor){return false;}
        virtual bool onWheelMove(const kege::Cursor& cursor){return false;}
        virtual bool onButton(const kege::Key& key){return false;}
        virtual bool onKey(const kege::Key& key){return false;}
        virtual ~ InputComponent() {}
    protected:
        InputComponent() : gfx::Component(kege::ENUM::_COMPONENT_INPUT) {}
    };
}}
#endif /* InputComponent_hpp */
