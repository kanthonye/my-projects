//
//  Textinput.cpp
//  dev0
//
//  Created by Kenneth A Esdaile on 8/2/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#include "InputKeys.hpp"
#include "Textinput.hpp"
namespace kege{namespace gfx{
    
    bool gfx::Textinput::onButtonComponents(gfx::GUIInput& button)
    {
        bool value = gfx::Button::onButtonComponents(button);
        
        if (value)
        {
            SetCursor();
        }
        else
        {
            RemoveCursor();
            input_action = 0;
        }
        
        return value;
    }
    
    void gfx::Textinput::RenderSelf(gfx::GUIRenderer& renderer)
    {
//        renderer.DrawGUI
//        (  GetTransform().position.x
//         , GetTransform().position.y
//         , width
//         , height
//         , color
//         , texcoord  );
        
//        renderer.DrawText
//        (  GetTransform().position.x + padding.x
//         , GetTransform().position.y + padding.y
//         , height - padding.y
//         , GetWidth()
//         , text
//         , cg::vec4(1.0)
//         , *font );
    }
    
    void gfx::Textinput::onKeyInput(const gfx::GUIInput& input)
    {
        switch (input.key)
        {
            case KEY_ENTER:
            {
                //SetButtonDown(false);
                //SetSelected(false);
                RemoveCursor();
                input_action = 0;
            }break;
                
            case KEY_BACKSLASH:
            case 0:
            {
                if (text.length() > 0 && input.action > 0)
                {
                    RemoveCursor();
                    onBackSpace(input.asciicode);
                }
            }break;
                
            case KEY_RIGHT:
            {
                if (!text.empty())
                {
                    cursor++;
                    if (cursor >= text.length()-1) cursor = int(text.length()-1);
                }
            }break;
                
            case KEY_LEFT:
            {
                cursor--;
                if (cursor < 0) cursor = 0;
            }break;
                
            default:
            {
                if (input.key >= 32 && 126 >= input.key)
                {
                    onKeyEntry(input.asciicode);
                }
            }break;
        }
    }
    
    bool gfx::Textinput::onKeySelf(const gfx::GUIInput& input)
    {
        if ( !Selected() ) return false;
        
        if ((input.action != input_action && input.action >= 1) || input.action == 2)
        {
            input_action = input.action;
            onKeyInput(input);
        }
        else if (input.action == 0)
        {
            input_action = 0;
        }
        return true;
    }
    
    void gfx::Textinput::onBackSpace(int ascii)
    {
        text.resize(text.length()-1);
        SetCursor();
    }
    
    void gfx::Textinput::onKeyEntry(int ascii)
    {
        RemoveCursor();
        text += ascii;
        SetCursor();
    }
    
    void gfx::Textinput::RemoveCursor()
    {
        if (!text.empty())
        {
            if (text[text.length()-1] == '_')
            {
                text[text.length()-1] = 0;
                text.setlength(text.length()-1);
            }
        }
    }
    void gfx::Textinput::SetCursor()
    {
        if (text.empty())
            text += '_';
        else if (text[text.length()-1] != '_')
            text += '_';
    }
    
    gfx::Textinput::Textinput(const ds::string& name, int w, int h, const cg::vec4& color, const gfx::Font* font)
    :   gfx::Button(name,w,h,color)
    ,   font(font)
    ,   cursor(0)
    {
        
    }
    gfx::Textinput::Textinput(const ds::string& name, int w, int h, const gfx::Font* font)
    :   gfx::Button(name,w,h)
    ,   font(font)
    ,   cursor(0)
    {
        
    }
    gfx::Textinput::Textinput(const ds::string& name, const gfx::Font* font)
    :   gfx::Button(name)
    ,   font(font)
    ,   cursor(0)
    {
        
    }
    gfx::Textinput:: ~ Textinput()
    {
        font = nullptr;
    }
    gfx::Textinput::Textinput()
    :   gfx::Button()
    ,   font(nullptr)
    ,   cursor(0)
    {
        
    }
}}
