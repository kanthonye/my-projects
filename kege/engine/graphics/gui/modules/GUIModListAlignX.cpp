/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/25/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIModHoriList.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "GUIPanel.hpp"
#include "GUIModListAlignX.hpp"
namespace kege{namespace cg{

    int GUIModListAlignX::onEvent(const cg::GUIEvent& event)
    {
        if ( event._type == GUIEvent::GUI_ADD )
        {
            GUIWidget* object = ((const cg::GUIMsgAdd&) event).object;
            GetParent()->SetWidth( cg::max(GetParent()->GetWidth(), object->GetWidth()) );
            object->GetLocalPosition().y = GetParent()->GetHeight();
            GetParent()->SetHeight( GetParent()->GetHeight() + object->GetHeight() + 1 );
            return GUIEvent::GUI_ADD;
        }
//        if ( event._type == GUIEvent::GUI_CHILD )
//        {
//            const cg::GUIMsgChild& msg = ((const cg::GUIMsgChild&) event);
//            if (msg.add == true)
//            {
//                GetParent()->SetWidth( cg::max(GetParent()->GetWidth(), msg.widget->GetWidth()) );
//                msg.widget->GetLocalPosition().y = GetParent()->GetHeight();
//                GetParent()->SetHeight( GetParent()->GetHeight() + msg.widget->GetHeight() + 1 );
//            }
//            else
//            {
//                
//            }
//            return GUIEvent::GUI_ADD;
//        }
        
        return GUIEvent::NOTHING;
    }
}}
