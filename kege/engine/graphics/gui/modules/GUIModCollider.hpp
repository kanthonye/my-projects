/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/10/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIModSlideBound.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIModSlideBound_hpp
#define GUIModSlideBound_hpp
#include "../../gui/modules/GUIModule.hpp"
namespace kege{namespace cg{
    
    class GUIModSlideBound : public cg::GUIModule
    {
    public:
        GUIModSlideBound()
        :   GUIModule( GUIEvent::GRABBING )
        {}
    };
    
    class GUIModColliderX : public cg::GUIModSlideBound
    {
    public:
        int onAction(cg::uint event) override;
    };
    
    class GUIModSlideXBound : public cg::GUIModSlideBound
    {
    public:
        int onAction(cg::uint event) override;
    };
    
    
    class GUIModSlideYBound : public cg::GUIModSlideBound
    {
    public:
        int onAction(cg::uint event) override;
    };
}}
#endif /* GUIModSlideBound_hpp */
