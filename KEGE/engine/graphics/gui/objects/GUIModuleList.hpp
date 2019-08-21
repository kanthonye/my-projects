/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/23/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIModuleList.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIModuleList_hpp
#define GUIModuleList_hpp
#include <map>
#include <vector>
#include "../../gui/objects/GUIWidget.hpp"
namespace kege{namespace cg{
    class GUILayer;
    
    class GUIModuleList : public std::vector<GUIModule*>
    {
    public:
        
        template<class EventT> int onEvent( const EventT& event )
        {
            int res,state = GUIEvent::NOTHING;
            for (iterator i=begin(); i!=end(); i++)
            {
                res = (*i)->onEvent( event );
                if ( res != GUIEvent::NOTHING )
                {
                    state = res;
                }
            }
            return state;
        }
        
        
        bool Find( const cg::GUIModule* model );
        int onEvent( const cg::GUIEvent &event );
        int onAction( cg::uint event );
        void UnInit();
        int Init();
    };
}}
#endif /* GUIModuleList_hpp */
