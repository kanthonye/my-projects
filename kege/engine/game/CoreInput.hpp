/*!
 *  @author     Kenneth Anthony Esdaile
 *  @date       created on 4/23/19
 *  @copyright  Copyright (c) 2014 kae. All rights reserved.
 *  @file       CoreInput.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef CoreInput_hpp
#define CoreInput_hpp
#include "InputDispatcher.hpp"
namespace kege{
    
    class CoreInput
    {
    public:
        
        virtual void OnMouseCursorMove(const kege::Cursor& cursor) = 0;
        virtual void OnScrollWheelMove(const kege::Cursor& cursor) = 0;
        virtual void OnMouseButtonPress(const kege::Key& key) = 0;
        virtual void OnKeyboardPress(const kege::Key& key) = 0;
        virtual~ CoreInput(){}
    };
}
#endif /* CoreInput_hpp */
