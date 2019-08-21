/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/11/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIText.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../gui/objects/GUIText.hpp"
#include "../../gui/objects/GUIRenderer.hpp"
namespace kege{namespace cg{
    
    GUIText::GUIText(int x, int y, const cg::vec4& colr, const ds::string& text)
    :   GUIWidget( GUIType::TEXT, "", x,y, 100,14, colr )
    ,   _text( text )
    ,   _letter_spacing( 5 )
    ,   _word_spacing( 10 )
    ,   _font_size( 14 )
    ,   _font_id( 0 )
    ,   _wrap_around( false )
    {
        
    }
  
    void GUIText::Render(GUIRenderer* renderer) const
    {
        if ( !_visible )
            return;
        
        renderer->DrawText( this );
    }
    
    GUIText::GUIText()
    :   GUIWidget( GUIType::TEXT, "" )
    ,   _letter_spacing( 5 )
    ,   _word_spacing( 10 )
    ,   _font_size( 14 )
    ,   _font_id( 0 )
    ,   _wrap_around( false )
    {}
}}
