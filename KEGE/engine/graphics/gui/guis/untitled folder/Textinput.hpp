//
//  Textinput.hpp
//  dev0
//
//  Created by Kenneth A Esdaile on 8/2/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef Textinput_hpp
#define Textinput_hpp
#include "Button.hpp"
namespace kege{namespace gfx{
    
    class Textinput : public gfx::Button
    {
    public:
        
        virtual bool onButtonComponents(gfx::GUIInput& button);
        virtual void onKeyInput(const gfx::GUIInput& key);
        virtual bool onKeySelf(const gfx::GUIInput& key);
        virtual void onBackSpace(int ascii);
        virtual void onKeyEntry(int ascii);
        
        virtual void RenderSelf(gfx::GUIRenderer& renderer);
        
        Textinput(const ds::string& name, int w, int h, const cg::vec4& color, const gfx::Font* font);
        Textinput(const ds::string& name, int w, int h, const gfx::Font* font);
        Textinput(const ds::string& name, const gfx::Font* font);
        virtual ~ Textinput();
        Textinput();
        
        void RemoveCursor();
        void SetCursor();
    protected:
        
        const gfx::Font* font;
        ds::string text;
        short input_action;
        short cursor;
    };
}}
#endif /* Textinput_hpp */
