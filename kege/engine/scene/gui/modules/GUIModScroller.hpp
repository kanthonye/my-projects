/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/11/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIModScroller.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIModScroller_hpp
#define GUIModScroller_hpp
#include "../../gui/modules/GUIModule.hpp"
namespace kege{namespace cg{
    
    class GUIModScroller : public cg::GUIModule
    {
    public:
        int onEvent(const cg::GUIEventMouseMove& coord);
        GUIModScroller(GUIWidget* other);
        GUIWidget* other;
    };
}}
#endif /* GUIModScroller_hpp */
