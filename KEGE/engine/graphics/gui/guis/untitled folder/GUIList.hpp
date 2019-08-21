//
//  GUIList.hpp
//  dev0
//
//  Created by Kenneth A Esdaile on 3/14/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef GUIList_hpp
#define GUIList_hpp
#include "Button.hpp"
namespace kege{ namespace gfx{
    
    class GUIList : public gfx::GUI
    {
    public:
        
        virtual bool onButtonChildren(gfx::GUIInput& button);
        
        kege::shared<gfx::GUI> RemoveElement(const ds::string& name);
        kege::shared<gfx::GUI> GetElement(const ds::string& name);
        kege::shared<gfx::GUI> AddElement(const kege::shared<gfx::GUI>& node);
        bool RemoveElement(gfx::GUI* node);
        
        const kege::shared<gfx::GUI>& GetSelectedElement()const;
        kege::shared<gfx::GUI>& GetSelectedElement();
        
        GUIList(const ds::string& name, int w, int h, const cg::vec4& color);
        GUIList(const ds::string& name, int w, int h);
        GUIList(const ds::string& name);
        virtual ~ GUIList();
        GUIList();
        
    protected:
        
        void onCreate();
        
        kege::shared<gfx::GUI> list;
        kege::shared<gfx::GUI> selection;
        kege::shared<gfx::GUI> curr;
    };
}}
#endif /* GUIList_hpp */
