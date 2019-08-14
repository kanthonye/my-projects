//
//  InputDispatcher.hpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 6/7/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef InputDispatcher_hpp
#define InputDispatcher_hpp
#include <map>
#include "dlist.hpp"
#include "InputListener.hpp"
namespace kege{
    
    class InputDispatcher
    {
    public:
        
        void AddKeyboardKeyListener(int key, InputListener* listener);
        void AddMouseKeyListener(int key, InputListener* listener);
        void AddMouseCursorListener(InputListener* listener);
        void AddMouseWheelListener(InputListener* listener);
        
        bool OnMouseCursorMove(const kege::Cursor& cursor);
        bool OnScrollWheelMove(const kege::Cursor& cursor);
        bool OnMouseButtonPress(const kege::Key& key);
        bool OnKeyboardPress(const kege::Key& key);
        
    private:
        
        std::map<int, InputListeners> keyboardkeys;
        std::map<int, InputListeners> mousekeys;
        InputListeners mousecursor;
        InputListeners mousewheel;
    };
}
#endif /* InputDispatcher_hpp */
