/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/11/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIModMouseOver.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../gui/objects/GUIControl.hpp"
#include "../../gui/modules/GUIModMouseOver.hpp"
namespace kege{namespace cg{
    
    int GUIModMouseOver::onEvent(const cg::GUIEventMouseMove& coord)
    {
        if ( _parent->TestMouseOver(coord.x, coord.y) )
        {
            _parent->onEvent( cg::GUIEvent::MOUSE_OVER );
            return cg::GUIEvent::MOUSE_OVER;
        }
        return cg::GUIEvent::NOTHING;
    }
}}
