//
//  TextArea.hpp
//  dev0
//
//  Created by Kenneth A Esdaile on 7/26/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef TextArea_hpp
#define TextArea_hpp
#include "Button.hpp"
namespace kege{ namespace gfx{
    
    class TextArea : public gfx::GUI
    {
    public:
        
        void AddText(const ds::string& name);
        
        TextArea(const ds::string& name, int w, int h, const cg::vec4& color);
        TextArea(const ds::string& name, int w, int h);
        TextArea(const ds::string& name);
        virtual ~ TextArea();
        TextArea();
        
    public:
        
        ds::dlist<gfx::Text*> texts;
        float letter_spacing;
        float word_spacing;
    };
}}
#endif /* TextArea_hpp */
