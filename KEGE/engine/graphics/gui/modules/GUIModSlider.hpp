/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/10/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIModSlider.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIModSlider_hpp
#define GUIModSlider_hpp
#include "../../gui/modules/GUIModGrab.hpp"
namespace kege{namespace cg{
    
    class GUIModSlider : public cg::GUIModGrab
    {
    public:
        
        int onEvent(const cg::GUIEventGrab& coord);
        virtual double GetProgression() = 0;
        virtual double GetLength() = 0;
        
    protected:
        
        GUIModSlider(double minval, double maxval, float min_offset, float max_offset);
        
    protected:
        
        double _minval;
        double _maxval;
        float _min_offset;
        float _max_offset;
    };
    
    class GUIModSliderX : public cg::GUIModSlider
    {
    public:
        GUIModSliderX(double minval, double maxval, float l_offset, float p_offset)
        :   GUIModSlider(minval, maxval, l_offset, p_offset )
        {}
        double GetProgression();
        double GetLength();
    };
    
    class GUIModSliderY : public cg::GUIModSlider
    {
    public:
        GUIModSliderY(double minval, double maxval, float l_offset, float p_offset)
        :   GUIModSlider(minval, maxval, l_offset, p_offset )
        {}
        double GetProgression();
        double GetLength();
    };
    
    
    
    template<typename var> class SliderValue : public cg::GUIModule
    {
    public:
        
        int onAction(cg::uint event)
        {
            *value = GetParent()->GetValue();
            return GUIEvent::NOTHING;
        }
        SliderValue(var* v)
        :   GUIModule( GUIEvent::VALUE_CHANGE )
        ,   value( v )
        {}
        var* value;
    };
}}
#endif /* GUIModSlider_hpp */
