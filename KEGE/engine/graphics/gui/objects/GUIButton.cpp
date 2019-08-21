/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/25/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIButton.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "GUIButton.hpp"
namespace kege{namespace cg{
    
    void GUIButton::SetValue( double val )
    {
        _value = val;
    }
    double GUIButton::GetValue() const
    {
        return _value;
    }
    
    
    GUIButton::GUIButton(const ds::string& name, float x, float y, int w, int h, const cg::vec4& colr)
    :   GUIControl( GUIType::BUTTON, name, x, y, w, h, colr )
    ,   _value( 0.0 )
    {}
    GUIButton::GUIButton(const ds::string& name, int w, int h, const cg::vec4& colr)
    :   GUIControl( GUIType::BUTTON, name, w, h, colr )
    ,   _value( 0.0 )
    {}
    GUIButton::GUIButton(const ds::string& name, int w, int h)
    :   GUIControl( GUIType::BUTTON, name, w, h )
    ,   _value( 0.0 )
    {}
    GUIButton::GUIButton(const ds::string& name)
    :   GUIControl( GUIType::BUTTON, name )
    ,   _value( 0.0 )
    {}
    
    GUIButton::GUIButton(GUIType type, const ds::string& name, float x, float y, int w, int h, const cg::vec4& colr)
    :   GUIControl( type, name, x, y, w, h, colr )
    ,   _value( 0.0 )
    {}
    GUIButton::GUIButton(GUIType type, const ds::string& name, int w, int h, const cg::vec4& colr)
    :   GUIControl( type, name, w, h, colr )
    ,   _value( 0.0 )
    {}
    GUIButton::GUIButton(GUIType type, const ds::string& name, int w, int h)
    :   GUIControl( type, "", w, h )
    ,   _value( 0.0 )
    {}
    GUIButton::GUIButton(GUIType type, const ds::string& name)
    :   GUIControl( type, "" )
    ,   _value( 0.0 )
    {}
    
}}
