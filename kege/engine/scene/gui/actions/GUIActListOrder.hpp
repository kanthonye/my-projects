/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/12/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIActListOrder.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIActListOrder_hpp
#define GUIActListOrder_hpp
#include "../../gui/actions/GUIAction.hpp"
namespace kege{namespace cg{
    
    class GUIActListOrder : public cg::GUIAction
    {
    public:
        void onEvent(cg::uint event) override;
        GUIActListOrder(GUIEvent::Type event)
        :   GUIAction( event )
        {}
    };
    
}}
#endif /* GUIActListOrder_hpp */
