/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/23/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIModuleList.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "GUIModuleList.hpp"
namespace kege{namespace cg{
    
    bool GUIModuleList::Find( const cg::GUIModule* model )
    {
        for (iterator i=begin(); i!=end(); i++)
        {
            if ( model == (*i) )
            {
                return true;
            }
        }
        return false;
    }
    
    int GUIModuleList::onEvent( const cg::GUIEvent &event )
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
    
    int GUIModuleList::onAction( cg::uint event )
    {
        short res,state = GUIEvent::NOTHING;
        for (iterator i=begin(); i!=end(); i++)
        {
            res = (*i)->onAction( event );
            if ( res != GUIEvent::NOTHING )
            {
                state = res;
            }
        }
        return state;
    }
    
    int GUIModuleList::Init()
    {
        for (iterator i=begin(); i!=end(); i++)
        {
            (*i)->Init();
        }
        return kege::SUCCESSFUL_INITIALIZATION;
    }
    void GUIModuleList::UnInit()
    {
        for (iterator i=begin(); i!=end(); i++)
        {
            (*i)->UnInit();
        }
    }
}}
