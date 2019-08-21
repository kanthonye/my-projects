/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/10/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIModSlider.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../gui/objects/GUIControl.hpp"
#include "../../gui/modules/GUIModSlider.hpp"
namespace kege{namespace cg{
    
    int GUIModSlider::onEvent(const cg::GUIEventGrab& coord)
    {
        if (_parent->GetState() == GUIEvent::GRABBING)
        {
            double length = GetLength();
            if (length != 0)
            {
                float progress = GetProgression();
                progress = cg::clamp(progress, 0, length);
                
                double value = ((_maxval - _minval) / length) * progress + _minval;
                _parent->SetValue( value );
                _parent->onAction( GUIEvent::VALUE_CHANGE );
                
                //printf("%f\n", value);
                return GUIEvent::GRABBING;
            }
        }
        return GUIEvent::NOTHING;
    }
    GUIModSlider::GUIModSlider(double minval, double maxval, float min_offset, float max_offset)
    :   _minval(minval)
    ,   _maxval(maxval)
    ,   _min_offset(min_offset)
    ,   _max_offset(max_offset)
    {}
    
    
    
    
    
    double GUIModSliderX::GetProgression()
    {
        return _parent->GetLocalPosition().x - _min_offset;
    }
    
    double GUIModSliderX::GetLength()
    {
        if ( _parent->GetParent() == nullptr)
        {
            return 0.0;
        }
        return (double) _parent->GetParent()->GetWidth() - (_max_offset + _parent->GetWidth());
    }
    
    
    
    double GUIModSliderY::GetProgression()
    {
        return _parent->GetLocalPosition().y + _min_offset;
    }
    double GUIModSliderY::GetLength()
    {
        if ( _parent->GetParent() == nullptr)
        {
            return 0.0;
        }
        return (double) _parent->GetParent()->GetHeight() - (_max_offset + _parent->GetHeight());
    }
}}
