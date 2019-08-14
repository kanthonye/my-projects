/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/12/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIActListOrder.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../gui/objects/GUIPanel.hpp"
#include "../../gui/actions/GUIActListOrder.hpp"
namespace kege{namespace cg{
    
    void GUIActListOrder::onEvent(cg::uint event)
    {
        if (event == GUIEvent::PRESSED)
        {
//            if (_parent->GetType() != GUIType::PANEL)
//            {
//                return;
//            }
            GUIManager* mgr = _parent->GetGUIMgr();
            if ( mgr == nullptr ) return;
            GUIWidget* n = mgr->GetHead();
            
            while ( n != nullptr )
            {
                if (n->GetState() == _type)
                {
                    if (n != mgr->GetHead())
                    {
                        mgr->PutFirst( n );
                    }
                    break;
                }
            }
        }
    }
}}

