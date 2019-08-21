//
//  Numberic.cpp
//  dev0
//
//  Created by Kenneth A Esdaile on 8/2/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#include "Numberic.hpp"
namespace kege{namespace gfx{
    
    void gfx::Numberic::onBackSpace(int ascii)
    {
        if (period && text[text.length()-1] == '.')
        {
            period = false;
        }
        else if (minus && text[text.length()-1] == '-')
        {
            minus = false;
        }
        gfx::Textinput::onBackSpace(ascii);
    }
    void gfx::Numberic::onKeyEntry(int ascii)
    {
        RemoveCursor();
        if (ascii=='-')
        {
            if (!text.empty()) return;
            if (text.empty()) minus = true;
        }
        
        if (ascii=='.')
        {
            if (!period) period = true;
            else return;
        }
        
        if ((ascii >= '0' && '9' >= ascii) || (ascii=='-') || ascii=='.')
        {
            text += ascii;
            value = atof(text.c_str());
        }
        SetCursor();
    }
    
    void gfx::Numberic::SetValue(double val)
    {
        value = val;
        char data[64];
        sprintf(data, "%.4f", value);
        text = data;
    }
    double gfx::Numberic::GetValue()const
    {
        return value;
    }
    
    gfx::Numberic::Numberic(const ds::string& name, int w, int h, const cg::vec4& color, const gfx::Font* font)
    :   gfx::Textinput(name,w,h,color,font)
    {}
    
    gfx::Numberic::Numberic(const ds::string& name, int w, int h, const gfx::Font* font)
    :   gfx::Textinput(name,w,h,font)
    {}
    
    gfx::Numberic::Numberic(const ds::string& name, const gfx::Font* font)
    :   gfx::Textinput(name,font)
    {}
    
    gfx::Numberic:: ~ Numberic()
    {}
    
    gfx::Numberic::Numberic()
    :   gfx::Textinput()
    {}
    
}}
