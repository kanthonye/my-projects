/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/11/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIModScroll.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../gui/objects/GUIControl.hpp"
#include "../../gui/modules/GUIModScroll.hpp"
namespace kege{namespace cg{
    
    int GUIModScroll::onEvent(const cg::GUIEvent& event)
    {
        if (event._type == GUIEvent::MOUSE_SCROLL)
        {
            return onEvent( (const cg::GUIEventScroll&) event );
        }
        return 0;
    }
    
    int GUIModScrollX::onEvent(const cg::GUIEventScroll& coord)
    {
        if ( _parent->GetState() == cg::GUIEvent::PRESSING
            || _parent->GetState() == cg::GUIEvent::PRESSED )
        {
            _parent->GetLocalPosition().x += coord.x;
            return GUIEvent::GRABBING;
        }
        return 0;
    }
    
    int GUIModScrollY::onEvent(const cg::GUIEventScroll& coord)
    {
        if ( _parent->GetState() == cg::GUIEvent::PRESSING
            || _parent->GetState() == cg::GUIEvent::PRESSED )
        {
            _parent->GetLocalPosition().y += coord.x;
            return GUIEvent::GRABBING;
        }
        return 0;
    }
}}

