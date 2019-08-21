/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/10/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIModButton.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../gui/objects/GUIPanel.hpp"
#include "../../gui/modules/GUIModButton.hpp"
#include "../../gui/objects/GUIView.hpp"
#include "../../gui/objects/GUI.hpp"
namespace kege{namespace cg{
    
    int GUIModButton::onEvent(const cg::GUIEvent& event)
    {
        if ( event._type == cg::GUIEvent::MOUSE_BUTTON )
        {
            const cg::GUIEventButton& button =(const GUIEventButton&) event;
            if (button.key == kege::BUTTON_LEFT)
            {
                if (button.state >= KEY_PRESS)
                {
                    return onButtonPressed( button );
                }
                else
                {
                    return onButtonRelease( button );
                }
            }
        }
        return cg::GUIEvent::NOTHING;
    }
    
    
    void GUIModButton::PressingGUI( GUIWidget* widget )
    {
        GUIWidget::SetControl( widget );
        //widget->GetSystem()->SetFocus( widget );
        widget->SetState( cg::GUIEvent::PRESSING );
        widget->onAction( cg::GUIEvent::PRESSING );
        GetParent()->onEvent( cg::GUIMsgRelease( widget ) );
    }
    void GUIModButton::ReleaseGUI(GUIWidget* widget)
    {
        GUIWidget::ReleaseControl( widget );
        //widget->GetSystem()->SetFocus( nullptr );
        widget->SetState( cg::GUIEvent::RELEASE );
        widget->onAction( cg::GUIEvent::RELEASE );
        GetParent()->onEvent( cg::GUIMsgRelease( widget ) );
    }
    void GUIModButton::SelectGUI(GUIWidget* widget)
    {
        GUIWidget::SetControl( widget );
        //widget->GetSystem()->SetFocus( widget );
        widget->SetState( cg::GUIEvent::PRESSED );
        widget->onAction( cg::GUIEvent::PRESSED );
        GetParent()->onEvent( cg::GUIMsgSelection( widget ) );
    }
}}


namespace kege{namespace cg{
    
    int GUIModButPress::onButtonRelease(const cg::GUIEventButton& event)
    {
        _pressing = false;
        if ( _selection || _parent->GetState() != GUIEvent::RELEASE )
        {
            _selection = false;
            ReleaseGUI( _parent );
            return GUIEvent::RELEASE;
        }
        return GUIEvent::NOTHING;
    }
    
    int GUIModButPress::onButtonPressed(const cg::GUIEventButton& event)
    {
        if ( _pressing || GUIControl::ControlIsActive() )
        {
            if ( _parent->GetState() != GUIEvent::RELEASE )
            {
                return _parent->GetState();
            }
            return GUIEvent::NOTHING;
        }
        _pressing = true;
        
        if ( _parent->GetState() == GUIEvent::RELEASE )
        {
            if ( _parent->TestMouseOverConst(event.x, event.y) )
            {
                _selection = true;
                PressingGUI( _parent );
                return GUIEvent::PRESSING;
            }
        }
        return GUIEvent::NOTHING;
    }
}}



namespace kege{namespace cg{
    
    int GUIModButClick::onButtonRelease(const cg::GUIEventButton& event)
    {
        _pressing = false;
        if ( _selection )
        {
            _selection = false;
            if ( _parent->TestMouseOverConst(event.x, event.y) && _parent->GetState() == GUIEvent::PRESSING )
            {
                SelectGUI( _parent );
                return GUIEvent::PRESSED;
            }
        }
        else if ( _parent->GetState() != GUIEvent::RELEASE )
        {
            ReleaseGUI( _parent );
            return GUIEvent::RELEASE;
        }
        return GUIEvent::NOTHING;
    }
    
    int GUIModButClick::onButtonPressed(const cg::GUIEventButton& event)
    {
        if ( _pressing )
        {
            if ( _selection )
            {
                return _parent->GetState();
            }
            return GUIEvent::NOTHING;
        }
        _pressing = true;
        
        if ( _parent->TestMouseOverConst(event.x, event.y) )
        {
            _selection = true;
            PressingGUI( _parent );
            return GUIEvent::PRESSING;
        }
        return GUIEvent::NOTHING;
    }
}}


namespace kege{namespace cg{
    
    int GUIModButToggle::onButtonRelease(const cg::GUIEventButton& event)
    {
        _pressing = false;
        if ( _selection )
        {
            _selection = false;
            if ( _parent->TestMouseOverConst(event.x, event.y) && _parent->GetState() == GUIEvent::PRESSING )
            {
                toggle = !toggle;
                
                if (toggle == true )
                {
                    SelectGUI( _parent );
                    return GUIEvent::PRESSED;
                }
                else if (toggle == false )
                {
                    ReleaseGUI( _parent );
                    return GUIEvent::RELEASE;
                }
            }
        }
        return GUIEvent::NOTHING;
    }
    
    int GUIModButToggle::onButtonPressed(const cg::GUIEventButton& event)
    {
        if ( _pressing )
        {
            if ( _selection )
            {
                return _parent->GetState();
            }
            return GUIEvent::NOTHING;
        }
        _pressing = true;
        
        if ( _parent->TestMouseOverConst(event.x, event.y) )
        {
            _selection = true;
            PressingGUI( _parent );
            return GUIEvent::PRESSING;
        }
        return GUIEvent::NOTHING;
    }
}}


namespace kege{namespace cg{
    
    int GUIModButFocus::onButtonRelease(const cg::GUIEventButton& event)
    {
        _pressing = false;
        _selection = false;
        if ( _parent->GetState() == GUIEvent::PRESSING )
        {
            if ( _parent->TestMouseOverConst(event.x, event.y) )
            {
                SelectGUI( _parent );
                return GUIEvent::PRESSED;
            }
            else
            {
                ReleaseGUI( _parent );
                return GUIEvent::RELEASE;
            }
        }
        return GUIEvent::NOTHING;
    }
    
    int GUIModButFocus::onButtonPressed(const cg::GUIEventButton& event)
    {
        if ( _pressing )
        {
            if ( _selection )
            {
                return _parent->GetState();
            }
            return GUIEvent::NOTHING;
        }
        _pressing = true;
        
        if ( _parent->TestMouseOverConst(event.x, event.y) )
        {
            _selection = true;
            PressingGUI( _parent );
            return GUIEvent::PRESSING;
        }
        else if (_parent->GetState() != cg::GUIEvent::RELEASE)
        {
            _selection = false;
            ReleaseGUI( _parent );
            return GUIEvent::RELEASE;
        }
        return GUIEvent::NOTHING;
    }
}}





namespace kege{namespace cg{
    
    int GUIModDispatcher::onEvent(const cg::GUIEvent& event)
    {
        if (_parent->GetType() != GUIType::PANEL)
        {
            return GUIEvent::NOTHING;
        }
        GUIManager* mgr = _parent->GetGUIMgr();
        if ( mgr == nullptr ) return -1;
        GUIWidget* gui = mgr->GetHead();
        
        int s,state = GUIEvent::NOTHING;
        while (gui != nullptr)
        {
            s = gui->onEvent( event );
            if (s >= GUIEvent::RELEASE)
            {
                state = s;
            }
            gui = gui->GetNext();
        }
        return state;
    }
}}

