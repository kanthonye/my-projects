/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/25/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIModSelection.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../gui/objects/GUI.hpp"
#include "../../gui/objects/GUIPanel.hpp"
#include "../../gui/modules/GUIModButton.hpp"
#include "../../gui/objects/GUIView.hpp"
#include "../../gui/modules/GUIModSelection.hpp"
namespace kege{namespace cg{
    
    int GUIModSelection::onButtonRelease(const cg::GUIEventButton& event)
    {
        int state = GUIEvent::NOTHING;
        _pressing = GUIEvent::RELEASE;
        if ( _selecttion )
        {
            _parent->SetState( GUIEvent::RELEASE );
            _selecttion = false;
            if ( curr != prev )
            {
                if (curr->TestMouseOverConst( event.x,event.y ))
                {
                    SelectGUI( curr );
                    state = GUIEvent::GUI_SELECTED;
                }
                if ( prev != nullptr )
                {
                    ReleaseGUI( prev );
                    state = GUIEvent::GUI_RELEASE;
                }
            }
        }
        return state;
    }
    
    int GUIModSelection::onButtonPressed(const cg::GUIEventButton& event)
    {
        if ( _pressing )
        {
            if ( _parent->GetState() != GUIEvent::RELEASE )
            {
                return _parent->GetState();
            }
            return GUIEvent::NOTHING;
        }
        _pressing = true;
        
        GUIManager* mgr = _parent->GetGUIMgr();
        if ( mgr == nullptr ) return 0;
        GUIWidget* elem = mgr->GetHead();
        
        if (_parent->GetType() == GUIType::PANEL)
        {
            while ( elem != nullptr )
            {
                if ( elem->TestMouseOverConst( event.x, event.y ) )
                {
                    _parent->SetState( GUIEvent::PRESSING );
                    _selecttion = true;
                    prev = curr;
                    curr = elem;
                    return _pressing;
                }
                elem = elem->GetNext();
            }
        }
        return GUIEvent::NOTHING;
    }
}}






namespace kege{namespace cg{
    
    int GUIModPressSelection::onButtonRelease(const cg::GUIEventButton& event)
    {
        _pressing = false;
        GUIManager* mgr = _parent->GetGUIMgr();
        if ( mgr == nullptr ) return 0;
        GUIWidget* elem = mgr->GetHead();
        
        _selection = false;
        int state = GUIEvent::NOTHING;
        while ( elem != nullptr )
        {
            if ( elem->TestMouseOverConst(event.x, event.y) && elem->GetState() == GUIEvent::PRESSING )
            {
                SelectGUI( elem );
                state = GUIEvent::PRESSED;
            }
            else if ( elem->GetState() != GUIEvent::RELEASE )
            {
                ReleaseGUI( elem );
            }
            elem = elem->GetNext();
        }
        return state;
    }
    
    int GUIModPressSelection::onButtonPressed(const cg::GUIEventButton& event)
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
        
        GUIManager* mgr = _parent->GetGUIMgr();
        if ( mgr == nullptr ) return 0;
        GUIWidget* elem = mgr->GetHead();
        
        int state = GUIEvent::NOTHING;
        while ( elem != nullptr )
        {
            if ( !_selection )
            {
                if ( elem->TestMouseOverConst( event.x, event.y ) )
                {
                    _selection = true;
                    elem->SetState( cg::GUIEvent::PRESSING );
                    elem->onAction( cg::GUIEvent::PRESSING );
                    GetParent()->onEvent( cg::GUIMsgPressing( elem ) );
                    state = GUIEvent::PRESSING;
                }
            }
            else if ( elem->GetState() != GUIEvent::RELEASE )
            {
                ReleaseGUI( elem );
            }
            elem = elem->GetNext();
        }
        return state;
    }
}}






namespace kege{namespace cg{
    
    int GUIModTabSelection::onButtonRelease(const cg::GUIEventButton& event)
    {
        _pressing = false;
        if ( !_selection )
        {
            if ( curr == prev && curr != nullptr)
            {
                ReleaseGUI( curr );
                prev = nullptr;
                curr = nullptr;
                return GUIEvent::RELEASE;
            }
        }
        _selection = false;
        return GUIEvent::NOTHING;
    }
    
    int GUIModTabSelection::onButtonPressed(const cg::GUIEventButton& event)
    {
        if ( _pressing )
        {
            if ( _parent->GetState() != GUIEvent::RELEASE )
            {
                return _parent->GetState();
            }
            return GUIEvent::NOTHING;
        }
        _pressing = true;
        
        GUIManager* mgr = _parent->GetGUIMgr();
        if ( mgr == nullptr ) return 0;
        GUIWidget* elem = mgr->GetHead();
        
        while ( elem != nullptr )
        {
            if ( !_selection )
            {
                if ( elem->TestMouseOverConst( event.x, event.y ) )
                {
                    _selection = true;
                    prev = curr;
                    curr = elem;
                    
                    if ( prev != nullptr && prev != curr )
                    {
                        ReleaseGUI( prev );
                    }
                    SelectGUI( curr );
                    return GUIEvent::PRESSED;
                }
                else if ( elem->GetState() == GUIEvent::PRESSED )
                {
                    ReleaseGUI( elem );
                }
            }
            elem = elem->GetNext();
        }
        return GUIEvent::NOTHING;
    }
}}
    

namespace kege{namespace cg{
    
    int GUIModColor::onEvent(const cg::GUIEvent& event)
    {
        switch ( event.GetType() )
        {
//            case GUIEvent::GUI_VALUE_CHANGE:
//            case GUIEvent::GUI_DISABLE:
//            case GUIEvent::GUI_ENABLE:
//            case GUIEvent::GUI_MOUSE_OVER:
//            case GUIEvent::GUI_RELEASE:
//            case GUIEvent::GUI_PRESSED:
//            case GUIEvent::GUI_PRESSING:
//            case GUIEvent::GUI_GRABBING:
//            case GUIEvent::GUI_SCROLLING:
            case GUIEvent::GUI_RELEASE:
            case GUIEvent::GUI_PRESSING:
            case GUIEvent::GUI_SELECTED:
                ((const GUIMsgSelection&) event).object->SetColor( color );
                break;
                
            default: break;
        }
        return GUIEvent::NOTHING;
    }
    GUIModColor::GUIModColor(GUIEvent::Type type, const cg::vec4& color)
    :   cg::GUIModule( type )
    ,   color(color)
    {}
}}
    
    

namespace kege{namespace cg{
    
    int GUIModColor2::onAction(cg::uint event)
    {
        switch ( event )
        {
            case GUIEvent::RELEASE:
            case GUIEvent::PRESSING:
            case GUIEvent::PRESSED:
                _parent->SetColor( color );
                break;
                
            default: break;
        }
        return GUIEvent::NOTHING;
    }
    GUIModColor2::GUIModColor2(GUIEvent::Type type, const cg::vec4& colr)
    :   cg::GUIModule( type )
    ,   color(colr)
    {}
}}




