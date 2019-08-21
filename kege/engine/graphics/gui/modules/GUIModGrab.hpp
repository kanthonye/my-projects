/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/11/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIModGrabbable.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIModGrab_hpp
#define GUIModGrab_hpp
#include "../../gui/modules/GUIModule.hpp"
namespace kege{namespace cg{
    
    class GUIModGrab : public cg::GUIModule
    {
    public:
        
        virtual int onEvent(const cg::GUIEventGrab& coord);
        int onEvent(const cg::GUIEvent& event) override;
        GUIModGrab() : GUIModule( GUIEvent::MOUSE_GRAB ) {}
    };
    
    
    class GUIModGrabX : public cg::GUIModGrab
    {
    public:
        int onEvent(const cg::GUIEventGrab& coord) override;
    };
    
    
    class GUIModGrabY : public cg::GUIModGrab
    {
    public:
        int onEvent(const cg::GUIEventGrab& coord) override;
    };
    
    
    class GUIModBanner : public cg::GUIModGrab
    {
    public:
        int onEvent(const cg::GUIEventGrab& coord) override;
        GUIModBanner(GUIControl* control);
        GUIControl* _control;
    };
    
    
    class ActionNotifier : public cg::GUIModule
    {
    public:
        int onAction(cg::uint event) override;
        
        ActionNotifier(GUIEvent::Type typ)
        :   GUIModule( typ )
        {}
    };
    
    class SliderProgression : public cg::GUIModule
    {
    public:
        int onAction(cg::uint event) override;
        SliderProgression(GUIWidget* s0, GUIWidget* s1)
        :   GUIModule( GUIEvent::GRABBING )
        ,   _s0(s0)
        ,   _s1(s1)
        {}
        GUIWidget* _s0;
        GUIWidget* _s1;
    };
    
    class SliderRangeGrab : public cg::GUIModGrab
    {
    public:
        int onEvent(const cg::GUIEventGrab& coord) override;
        int MoveSliders(const cg::GUIEventGrab& event);
        SliderRangeGrab(GUIControl* s0, GUIControl* s1)
        :   _s0(s0)
        ,   _s1(s1)
        {}
        GUIControl* _s0;
        GUIControl* _s1;
    };
}}
#endif /* GUIModGrab_hpp */
