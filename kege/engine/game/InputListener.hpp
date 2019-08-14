//
//  InputListener.hpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 6/7/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef InputListener_hpp
#define InputListener_hpp
#include <map>
#include "dlist.hpp"
#include "Keycode.hpp"
namespace kege{
    class InputListeners;
    
    class InputListener
    {
    public:
        virtual bool onCursorMove(const kege::Cursor& cursor){return false;}
        virtual bool onWheelMove(const kege::Cursor& cursor){return false;}
        virtual bool onButton(const kege::Key& key){return false;}
        virtual bool onKey(const kege::Key& key){return false;}
        virtual ~ InputListener();
        
    protected:
        InputListener():dispatcher(nullptr){}
        
    private:
        InputListeners* dispatcher;
        friend InputListeners;
    };
    
    class InputListeners : public InputListener
    {
    public:
        bool onKeyboardKey(const kege::Key& key);
        bool onMouseKey(const kege::Key& key);
        bool onMouseCursorMove(const kege::Cursor& cursor);
        bool onMouseWheelMove(const kege::Cursor& cursor);
        
        void Remove(InputListener* listener);
        void Add(InputListener* listener);
        ~ InputListeners();
    private:
        ds::dlist<InputListener*> inputs;
    };
}
#endif /* InputListener_hpp */
