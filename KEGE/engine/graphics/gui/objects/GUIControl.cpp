/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/25/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIControl.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "GUIControl.hpp"
namespace kege{namespace cg{
    
    int  GUIControl::HandleEvent( const cg::GUIEvent &event )
    {
        GUIModulMap::iterator m = _modules.find( event.GetType() );
        if (m == _modules.end())
        {
            return GUIEvent::NOTHING;
        }
        return m->second.onEvent( event );
    }
    
    int GUIControl::onEvent( const cg::GUIEvent &event )
    {
        return HandleEvent( event );
    }
    
    int GUIControl::onAction(cg::uint event)
    {
        GUIModulMap::iterator m = _modules.find( event );
        if (m == _modules.end())
        {
            return 0;
        }
        return m->second.onAction( event );
    }
    
    
    
    GUIModuleList* GUIControl::GetModules( GUIEvent::Type type )
    {
        GUIModulMap::iterator m = _modules.find( type );
        if (m == _modules.end())
        {
            return nullptr;
        }
        return &m->second;
    }
    
    GUIModule* GUIControl::AddModule( GUIModule* module )
    {
        GUIModulMap::iterator m = _modules.find( module->_type );
        if (m != _modules.end())
        {
            if ( m->second.Find( module ) )
            {
                return module;
            }
        }
        _modules[ module->_type ].push_back( module );
        module->SetParent( this );
        return module;
    }
    
    bool GUIControl::TestMouseOver(double x, double y)
    {
        _mouse_over = TestMouseOverConst( x,y );
        return _mouse_over;
    }
    
    void GUIControl::SetMouseOver( bool val )
    {
        _mouse_over = val;
    }
    bool GUIControl::GetMouseOver() const
    {
        return _mouse_over;
    }
    
    void GUIControl::SetState(short value)
    {
        _state = value;
    }
    
    short GUIControl::GetState() const
    {
        return _state;
    }
    
    void GUIControl::SetEnable(short value)
    {
        _enable = value;
    }
    bool GUIControl::GetEnable() const
    {
        return _enable;
    }
    
    GUIControl:: ~ GUIControl()
    {
        GUIModuleList::iterator i;
        GUIModulMap::iterator m;
        for (m = _modules.begin(); m != _modules.end(); m++)
        {
            m->second.UnInit();
            for (i=m->second.begin(); i!=m->second.end(); i++)
            {
                delete (*i);
            }
            m->second.clear();
        }
        _modules.clear();
    }
    
    GUIControl::GUIControl(GUIType type, const ds::string& name, float x, float y, int w, int h, const cg::vec4& colr)
    :   GUIWidget( type, name, x, y, w, h, colr )
    ,   _mouse_over( false )
    ,   _enable( true )
    ,   _state( GUIEvent::RELEASE )
    {}
    
    GUIControl::GUIControl(GUIType type, const ds::string& name, int w, int h, const cg::vec4& colr)
    :   GUIWidget( type, name, w, h, colr )
    ,   _mouse_over( false )
    ,   _enable( true )
    ,   _state( GUIEvent::RELEASE )
    {}
    
    GUIControl::GUIControl(GUIType type, const ds::string& name, int w, int h)
    :   GUIWidget( type, name, w, h )
    ,   _mouse_over( false )
    ,   _enable( true )
    ,   _state( GUIEvent::RELEASE )
    {}
    
    GUIControl::GUIControl(GUIType type, const ds::string& name)
    :   GUIWidget( type, name )
    ,   _mouse_over( false )
    ,   _enable( true )
    ,   _state( GUIEvent::RELEASE )
    {}
    
}}
