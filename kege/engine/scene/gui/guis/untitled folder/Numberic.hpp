//
//  Numberic.hpp
//  dev0
//
//  Created by Kenneth A Esdaile on 8/2/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef Numberic_hpp
#define Numberic_hpp
#include "Textinput.hpp"
namespace kege{namespace gfx{

    class Numberic : public gfx::Textinput
    {   bool period,minus;
    public:
        
        virtual void onBackSpace(int ascii);
        virtual void onKeyEntry(int ascii);
        
        void SetValue(double val);
        double GetValue()const;
        Numberic(const ds::string& name, int w, int h, const cg::vec4& color, const gfx::Font* font);
        Numberic(const ds::string& name, int w, int h, const gfx::Font* font);
        Numberic(const ds::string& name, const gfx::Font* font);
        virtual ~ Numberic();
        Numberic();
        
    private:
        
        double value;
    };
    
}}
#endif /* Numberic_hpp */
