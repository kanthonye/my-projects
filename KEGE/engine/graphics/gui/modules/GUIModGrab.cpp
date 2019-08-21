/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/11/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIModGrabbable.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../gui/objects/GUIManager.hpp"
#include "../../gui/objects/GUIControl.hpp"
#include "GUIModGrab.hpp"
namespace kege{namespace cg{
    
    int GUIModGrab::onEvent(const cg::GUIEvent& event)
    {
        if (event._type == GUIEvent::MOUSE_GRAB)
        {
            if ( _parent->GetState() == cg::GUIEvent::PRESSING || _parent->GetState() == cg::GUIEvent::GRABBING )
            {
                return onEvent( (const cg::GUIEventGrab&) event );
            }
        }
        return GUIEvent::NOTHING;
    }
    
    int GUIModGrab::onEvent(const cg::GUIEventGrab& coord)
    {
        _parent->GetLocalPosition().x += coord.x;
        _parent->GetLocalPosition().y += coord.y;
        _parent->SetState( GUIEvent::GRABBING );
        _parent->onAction( GUIEvent::GRABBING );
        return GUIEvent::GRABBING;
    }
}}
    

namespace kege{namespace cg{
    
    int GUIModGrabX::onEvent(const cg::GUIEventGrab& coord)
    {
        _parent->GetLocalPosition().x += coord.x;
        _parent->SetState( GUIEvent::GRABBING );
        _parent->onAction( GUIEvent::GRABBING );
        return GUIEvent::GRABBING;
    }
}}

namespace kege{namespace cg{
    
    int GUIModGrabY::onEvent(const cg::GUIEventGrab& coord)
    {
        _parent->GetLocalPosition().y += coord.x;
        _parent->SetState( GUIEvent::GRABBING );
        _parent->onAction( GUIEvent::GRABBING );
        return GUIEvent::GRABBING;
    }
}}
    
    

namespace kege{namespace cg{
    
    int GUIModBanner::onEvent(const cg::GUIEventGrab& coord)
    {
        _control->SetState( GUIEvent::GRABBING );
        _control->GetLocalPosition().x += coord.x;
        _control->GetLocalPosition().y += coord.y;
        return GUIEvent::GRABBING;
    }
    GUIModBanner::GUIModBanner(GUIControl* c)
    :   _control( c )
    {}
}}
    

namespace kege{namespace cg{
    
    int SliderProgression::onAction(cg::uint event)
    {
        GetParent()->GetLocalPosition().x = _s0->GetLocalPosition().x + 1;
        GetParent()->SetWidth( _s1->GetLocalPosition().x - _s0->GetLocalPosition().x + 1 );
        return GUIEvent::NOTHING;
    }
    
    int ActionNotifier::onAction(cg::uint event)
    {
        GUIManager* mgr = GetParent()->GetGUIMgr();
        if ( mgr== nullptr) return GUIEvent::NOTHING;
        GUIWidget* elem = mgr->GetHead();
        
        while ( elem != nullptr )
        {
            elem->onAction( event );
            elem = elem->GetNext();
        }
        return GUIEvent::NOTHING;
    }
    
    
    int SliderRangeGrab::onEvent(const cg::GUIEventGrab& event)
    {
        int w = _s0->GetParent()->GetWidth() -_s1->GetWidth() ;
        if (_s0->GetLocalPosition().x > 0 && _s1->GetLocalPosition().x < w)
        {
            return MoveSliders(event);
        }
        if (0 < event.x)
        {
            if (_s0->GetLocalPosition().x <= 1)
            {
                return MoveSliders(event);
            }
        }
        else if (0 > event.x)
        {
            if (_s1->GetLocalPosition().x >= w-1)
            {
                return MoveSliders(event);
            }
        }
        return GUIEvent::NOTHING;
    }
    int SliderRangeGrab::MoveSliders(const cg::GUIEventGrab& event)
    {
        _s0->SetState( cg::GUIEvent::GRABBING );
        _s1->SetState( cg::GUIEvent::GRABBING );
        _s0->onEvent( event );
        _s1->onEvent( event );
        _s0->SetState( cg::GUIEvent::RELEASE );
        _s1->SetState( cg::GUIEvent::RELEASE );
        return GUIEvent::GRABBING;
    }
    

    
}}
