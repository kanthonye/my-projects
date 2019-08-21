/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/11/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIModScroller.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../gui/objects/GUIControl.hpp"
#include "../../gui/modules/GUIModScroller.hpp"
namespace kege{namespace cg{
    
    int GUIModScroller::onEvent(const cg::GUIEventMouseMove& coord)
    {
        double length = other->GetHeight() - _parent->GetParent()->GetHeight();
        double a =_parent->GetLocalPosition().x / _parent->GetParent()->GetHeight();
        other->GetLocalPosition().y = -length * a;
        return 0;
    }
}}

