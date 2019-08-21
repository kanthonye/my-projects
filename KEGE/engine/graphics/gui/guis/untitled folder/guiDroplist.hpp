//
//  guiDroplist.hpp
//  dev0
//
//  Created by Kenneth A Esdaile on 8/1/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef guiDroplist_hpp
#define guiDroplist_hpp
#include "Button.hpp"
namespace kege{ namespace gfx{
    
    class Droplist : public gfx::GUI
    {
    public:
        
        virtual bool onButtonChildren(gfx::GUIInput& button);
        
        kege::shared<gfx::GUI> RemoveElement(const ds::string& name);
        kege::shared<gfx::GUI> GetElement(const ds::string& name);
        kege::shared<gfx::GUI> AddElement(gfx::GUI* gui);
        bool RemoveElement(gfx::GUI* gui);
        
        void Calapse();
        void Expand();
        
        bool InitializeSelf();
        
        Droplist(const ds::string& name, int w, int h, const cg::vec4& color);
        Droplist(const ds::string& name, int w, int h);
        Droplist(const ds::string& name);
        virtual ~ Droplist();
        Droplist();
        
    protected:
        
        kege::shared<gfx::GUI> button;
        kege::shared<gfx::GUI> list;
        short length;
        bool openlist;
        
    private:
        
        void Construct();
    };
}}
#endif /* guiDroplist_hpp */
