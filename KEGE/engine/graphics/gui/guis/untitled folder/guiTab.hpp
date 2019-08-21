/*! @author      Kenneth Esdaile
 *  @date        created on 8/12/17
 *  @copyright   Copyright © 2017 Kenneth Anthony Esdaile. All rights reserved.
 *  @file        guiTab.hpp
 *  @project     GUI */

#ifndef guiTab_hpp
#define guiTab_hpp
#include "Button.hpp"
namespace kege{ namespace gfx{
    
    class Tab : public gfx::Button
    {
    public:
        
        virtual bool onButtonChildren(gfx::GUIInput& button);
        virtual bool InitializeSelf();
        
        kege::shared<gfx::GUI> RemoveTab(const ds::string& name);
        kege::shared<gfx::GUI> GetTab(const ds::string& name);
        kege::shared<gfx::GUI> AddTab(gfx::GUI* gui);
        bool RemoveTab(gfx::GUI* gui);
        
        bool ShowTab(const ds::string& name);
        bool HideTab(const ds::string& name);
        
        void SetInactiveColor(const cg::vec4& colr);
        const cg::vec4& GetInactiveColor()const;
        cg::vec4& GetInactiveColor();
        
        void SetActiveColor(const cg::vec4& colr);
        const cg::vec4& GetActiveColor()const;
        cg::vec4& GetActiveColor();
        
        void SetAlignHori(bool val);
        bool GetAlignHori()const;
        
        Tab(const ds::string& name, int w, int h, const cg::vec4& color);
        Tab(const ds::string& name, int w, int h);
        Tab(const ds::string& name);
        virtual ~ Tab();
        Tab();
        
    protected:
        
        cg::vec4 inactive_color;
        cg::vec4 active_color;
        cg::vec2 curr_coord;
        
        kege::shared<gfx::GUI> curr;
        kege::shared<gfx::GUI> prev;
        
        bool align_hori;
    };
}}
#endif /* guiTab_hpp */
