/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/12/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIActShowList.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIActShowList_hpp
#define GUIActShowList_hpp
#include "../../gui/actions/GUIAction.hpp"
namespace kege{namespace cg{
    
    class GUIActShowList : public cg::GUIAction
    {
    public:
        void onEvent(cg::uint event) override;
        GUIActShowList(GUIEvent::Type event)
        :   GUIAction( event )
        {}
    };
    
}}
#endif /* GUIActShowList_hpp */
