//
//  GUISpinner.hpp
//  dev0
//
//  Created by Kenneth A Esdaile on 8/3/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef GUISpinner_hpp
#define GUISpinner_hpp
#include "GUIPanel.hpp"
namespace kege{ namespace gfx{
    
    class Spinner : public gfx::Panel
    {
    public:
        
        virtual bool onButtonChildren(gfx::GUIInput& button);
        virtual bool InitializeSelf();
        void SetValue(double val);
        double GetValue()const;
        void Increase();
        void Decrease();
        
        Spinner(const ds::string& name, int w, int h, const cg::vec4& color);
        Spinner(const ds::string& name, int w, int h);
        Spinner(const ds::string& name);
        virtual ~ Spinner();
        Spinner();
        
    public:
        
        gfx::Numberic* numberic;
        kege::shared<gfx::GUI> up;
        kege::shared<gfx::GUI> dn;
        float incr_valu;
    };
}}
#endif /* GUISpinner_hpp */
