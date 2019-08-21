/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/25/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIModHoriList.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIModHoriList_hpp
#define GUIModHoriList_hpp
#include "../../gui/modules/GUIModule.hpp"
#include "../../gui/objects/GUIManager.hpp"
namespace kege{namespace cg{
    
    class GUIModListAlignX : public cg::GUIModule
    {
    public:
        
        int onEvent(const cg::GUIEvent& event) override;
        
        GUIModListAlignX()
        :   GUIModule( GUIEvent::GUI_ADD )
        {}
        
        // holds the gui order
        //GUIManager _mgr;
    };
}}
#endif /* GUIModHoriList_hpp */
