/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/11/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIModScroll.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIModScroll_hpp
#define GUIModScroll_hpp
#include "../../gui/modules/GUIModule.hpp"
namespace kege{namespace cg{
    
    class GUIModScroll : public cg::GUIModule
    {
    public:
        virtual int onEvent(const cg::GUIEventScroll& coord) = 0;
        int onEvent(const cg::GUIEvent& event) override;
        virtual ~ GUIModScroll() {}
        
    protected:
        GUIModScroll() : GUIModule( GUIEvent::MOUSE_SCROLL ) {}
    };
    
    class GUIModScrollX : public cg::GUIModScroll
    {
    public:
        int onEvent(const cg::GUIEventScroll& coord);
    };
    
    class GUIModScrollY : public cg::GUIModScroll
    {
    public:
        int onEvent(const cg::GUIEventScroll& coord);
    };
}}
#endif /* GUIModScroll_hpp */
