/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/10/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIAction.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIAction_hpp
#define GUIAction_hpp
#include "../../gui/modules/GUIModule.hpp"
namespace kege{namespace cg{
    
    class GUIAction : public GUIModule
    {
    private:
        int onEvent(const cg::GUIEvent& event) {return 0;}
        
    public:
        virtual void onEvent(cg::uint event) {}
        GUIAction(GUIEvent::Type event)
        :   GUIModule( event )
        {}
        virtual ~ GUIAction(){}
    };
}}
#endif /* GUIAction_hpp */
