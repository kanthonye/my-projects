/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/11/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIModMouseOver.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIModMouseOver_hpp
#define GUIModMouseOver_hpp
#include "../../gui/modules/GUIModule.hpp"
namespace kege{namespace cg{
    
    /**
     * GUIModMouseOver give GUIs mouse_over ability, which enable and disbale mouse_over
     * base on where the mouse pointer is. If mouse pointer is over the GUI mouse-over
     * is enabled if not the it is disabled.
     */
    class GUIModMouseOver : public cg::GUIModule
    {
    public:
        int onEvent(const cg::GUIEventMouseMove& coord);
    };
}}
#endif /* GUIModMouseOver_hpp */
