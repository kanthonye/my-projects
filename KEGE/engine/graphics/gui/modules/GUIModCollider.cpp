/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/10/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIModSlideBound.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "GUIPanel.hpp"
#include "GUIVessel.hpp"
#include "GUIModCollider.hpp"
namespace kege{namespace cg{
    
    int GUIModColliderX::onAction(cg::uint event)
    {
        if ( _parent->GetParent() == nullptr )
        {
            return GUIEvent::NOTHING;
        }
        
        GUIManager* mgr = _parent->GetParent()->GetGUIMgr();
        if ( mgr == nullptr )
        {
            return GUIEvent::NOTHING;
        }
        
        double x;
        bool test_right_side = false;
        GUIWidget* other = mgr->GetHead();
        while (other != nullptr)
        {
            if (other == _parent)
            {
                other = other->GetNext();
                test_right_side = true;
                continue;
            }
            
            if ( !test_right_side )
            {
                x = other->GetLocalPosition().x + other->GetWidth();
                if (_parent->GetLocalPosition().x <= x)
                {
                    _parent->GetLocalPosition().x = x;
                }
            }
            else
            {
                x = _parent->GetLocalPosition().x + _parent->GetWidth();
                if (other->GetLocalPosition().x <= x)
                {
                    _parent->GetLocalPosition().x = other->GetLocalPosition().x - _parent->GetWidth();
                }
            }
            
            other = other->GetNext();
        }
        
        other = GetParent()->GetParent();
        if (other != nullptr)
        {
            x = other->GetWidth() - _parent->GetWidth();
            // compare current object with in the parent object bound
            if (_parent->GetLocalPosition().x <= 0.0f)
            {
                _parent->GetLocalPosition().x = 0.0f;
            }
            else if (_parent->GetLocalPosition().x >= x)
            {
                _parent->GetLocalPosition().x = x;
            }
        }
        return 0;
    }
    
    
    int GUIModSlideXBound::onAction(cg::uint event)
    {
        GUIManager* mgr = _parent->GetGUIMgr();
        if ( mgr == nullptr )
        {
            return 0;
        }
        
        GUIWidget* curr = mgr->GetHead();
        double x;
        
        while (curr != nullptr)
        {
            if (curr->GetPrev() != nullptr)
            {
                // compare previous object with current object bound
                x = curr->GetPrev()->GetLocalPosition().x + curr->GetPrev()->GetWidth();
                if (curr->GetLocalPosition().x <= x)
                {
                    curr->GetLocalPosition().x = x;
                }
            }
            
            if (curr->GetNext() != nullptr)
            {
                x = curr->GetNext()->GetLocalPosition().x - curr->GetWidth();
                // compare next object with current object bound
                if (x >= curr->GetNext()->GetLocalPosition().x)
                {
                    curr->GetLocalPosition().x = x;
                }
            }
            
            x = curr->GetLocalPosition().x + curr->GetWidth();
            // compare current object with in the parent object bound
            if (curr->GetLocalPosition().x <= 0.0f)
            {
                curr->GetLocalPosition().x = 0.0f;
            }
            else if (x >= GetParent()->GetWidth())
            {
                curr->GetLocalPosition().x = GetParent()->GetWidth() - curr->GetWidth();
            }
            curr = curr->GetNext();
        }
        return 0;
    }
    

    int GUIModSlideYBound::onAction(cg::uint event)
    {
        GUIManager* mgr = _parent->GetGUIMgr();
        if ( mgr == nullptr )
        {
            return 0;
        }
        
        GUIWidget* curr = mgr->GetHead();
        double y;
        
        while (curr != nullptr)
        {
            // compare previous object with current object bound
            if (curr->GetPrev() != nullptr)
            {
                y = -(curr->GetPrev()->GetLocalPosition().x + curr->GetPrev()->GetWidth());
                if (y <= curr->GetLocalPosition().y)
                {
                    curr->GetLocalPosition().x = y;
                }
            }
            
            // compare next object with current object bound
            y = -(curr->GetLocalPosition().y + curr->GetWidth());
            if (curr->GetNext() != nullptr)
            {
                if (y <= curr->GetNext()->GetWorldPosition().y)
                {
                    curr->GetLocalPosition().y = curr->GetNext()->GetLocalPosition().y + curr->GetWidth();
                }
            }
            
            // compare current object with in the parent object bound
            if (curr->GetLocalPosition().y <= 0.0f)
            {
                curr->GetLocalPosition().y = 0.0f;
            }
            else if (y <= -GetParent()->GetHeight())
            {
                curr->GetLocalPosition().y = -(GetParent()->GetWidth() + curr->GetWidth());
            }
            curr = curr->GetNext();
        }
        return 0;
    }
}}
