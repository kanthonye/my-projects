/*! @author      Kenneth Esdaile
 *  @date        created on 8/12/17
 *  @copyright   Copyright © 2017 Kenneth Anthony Esdaile. All rights reserved.
 *  @file        uiTab.cpp
 *  @project     GUI */
#include "guiTab.hpp"
#include "Button.hpp"
#include "ButtonComponents.hpp"
namespace kege{ namespace gfx{
    
    bool gfx::Tab::onButtonChildren(gfx::GUIInput& input)
    {
        bool value = gfx::Button::onButtonChildren(input);
        
        kege::shared<gfx::GUI> buttons = Get("buttons/tab-buttons");
        if (*buttons)
        {
            for (gfx::GUI::iterator b=buttons->GetChildren().begin(); b!=nullptr; b++)
            {
                if (b->Selected())
                {
                    prev = curr;
                    curr = b.element();
                    if (*curr != *prev)
                    {
                        curr->SetColor(active_color);
                        ShowTab(curr->GetName());
                        
                        if (prev != nullptr)
                        {
                            prev->SetColor(inactive_color);
                            HideTab(prev->GetName());
                        }
                    }
                    //return gfx::Selection(curr, gfx::Action::GUI_SELECTED);
                    return true;
                }
            }
        }
        return value;
    }
    
    kege::shared<gfx::GUI> gfx::Tab::RemoveTab(const ds::string& name)
    {
        kege::shared<gfx::GUI> tab = GetChild("tabs");
        if (tab == nullptr) return nullptr;
        
        kege::shared<gfx::GUI> buttons = Get("buttons/tab-buttons");
        if (buttons != nullptr)
        {
            kege::shared<gfx::GUI> button = buttons->Detach(name);
//            if (button != nullptr)
//            {
//                delete button;
//                button = nullptr;
//            }
        }
        
        return tab->Detach(name);
    }
    
    kege::shared<gfx::GUI> gfx::Tab::GetTab(const ds::string& name)
    {
        kege::shared<gfx::GUI> tab = GetChild("tabs");
        if (tab == nullptr) return nullptr;
        return tab->GetChild(name);
    }
    
    bool gfx::Tab::RemoveTab(gfx::GUI* gui)
    {
        kege::shared<gfx::GUI> tab = GetChild("tabs");
        if (tab == nullptr) return nullptr;
        
        kege::shared<gfx::GUI> buttons = Get("buttons/tab-buttons");
        if (buttons != nullptr)
        {
            kege::shared<gfx::GUI> button = buttons->Detach(gui->GetName());
//            if (button != nullptr)
//            {
//                delete button;
//                button = nullptr;
//            }
        }
        
        return tab->Detach(gui);
    }
    
    kege::shared<gfx::GUI> gfx::Tab::AddTab(gfx::GUI* gui)
    {
        // get the gui that buttons are stored in
        kege::shared<gfx::GUI> buttons = GetChild("buttons");
        if (buttons != nullptr)
        {
            // get the gui that the tab buttons are stored in
            //   since other gui nodes can be attach to buttons, it easier
            //   to manager buttons if I group them in there own node
            kege::shared<gfx::GUI> tab_buttons = buttons->GetChild("tab-buttons");
            
            if (tab_buttons != nullptr)
            {
                // create and add the button to the gui button node
                gfx::Button* button = new gfx::Button(gui->GetName(), 30,20, inactive_color);
                button->AddComponent(new gfx::ui::ClickButtonAR);
                tab_buttons->AddChild(button);
                
                if (align_hori)
                {
                    button->GetTransform().GetLocal().position.x = curr_coord.x;
                    button->GetTransform().GetLocal().position.y = curr_coord.y;
                    curr_coord.x += button->GetWidth()+5;
                }
                else
                {
                    button->GetTransform().GetLocal().position.x = curr_coord.x;
                    button->GetTransform().GetLocal().position.y = curr_coord.y;
                    curr_coord.y += button->GetHeight();
                }
            }
        }
        // get the gui that tabs are stored in
        kege::shared<gfx::GUI> tabs = GetChild("tabs");
        if (tabs != nullptr)
        {
            tabs->AddChild(gui);
        }
        return gui;
    }
    
    bool gfx::Tab::ShowTab(const ds::string& name)
    {
        kege::shared<gfx::GUI> tab = GetChild("tabs");
        if (tab == nullptr) return false;
        tab = tab->GetChild(name);
        if (tab == nullptr) return false;
        tab->Show();
        return true;
    }
    
    bool gfx::Tab::HideTab(const ds::string& name)
    {
        kege::shared<gfx::GUI> tab = GetChild("tabs");
        if (tab == nullptr) return false;
        tab = tab->GetChild(name);
        if (tab == nullptr) return false;
        tab->Hide();
        return true;
    }
    
    void gfx::Tab::SetInactiveColor(const cg::vec4& colr)
    {
        inactive_color = colr;
    }
    
    const cg::vec4& gfx::Tab::GetInactiveColor()const
    {
        return inactive_color;
    }
    
    cg::vec4& gfx::Tab::GetInactiveColor()
    {
        return inactive_color;
    }
    
    void gfx::Tab::SetActiveColor(const cg::vec4&  colr)
    {
        active_color = colr;
    }
    
    const cg::vec4& gfx::Tab::GetActiveColor()const
    {
        return active_color;
    }
    
    cg::vec4& gfx::Tab::GetActiveColor()
    {
        return active_color;
    }
    
    void gfx::Tab::SetAlignHori(bool val)
    {
        align_hori = val;
    }
    
    bool gfx::Tab::GetAlignHori()const
    {
        return align_hori;
    }

    bool gfx::Tab::InitializeSelf()
    {
        kege::shared<gfx::GUI> buttons = AddChild( new gfx::GUI("buttons", GetWidth(),20, cg::vec4(0.0)) );
        if (buttons != nullptr)
        {
            buttons->AddChild(new gfx::GUI("tab-buttons", GetWidth(), 20, cg::vec4(0.0)));
        }
        buttons = AddChild( new gfx::GUI("tabs", GetWidth(), GetHeight()-20, cg::vec4(0.0)) );
        buttons->GetTransform().GetLocal().position.y = -20;
        return gfx::Button::InitializeComponents();
    }
    
    gfx::Tab::Tab(const ds::string& name, int w, int h, const cg::vec4& colr)
    :   gfx::Button(name, w,h, colr)
    ,   inactive_color(0.3,0.3,0.3,1.0)
    ,   active_color(0.5,0.5,0.5,1.0)
    ,   curr_coord(0.0)
    ,   curr(nullptr)
    ,   prev(nullptr)
    ,   align_hori(true)
    {
    }
    
    gfx::Tab::Tab(const ds::string& name, int w, int h)
    :   gfx::Button(name, w,h)
    ,   inactive_color(0.3,0.3,0.3,1.0)
    ,   active_color(0.5,0.5,0.5,1.0)
    ,   curr_coord(0.0)
    ,   curr(nullptr)
    ,   prev(nullptr)
    ,   align_hori(true)
    {
    }
    
    gfx::Tab::Tab(const ds::string& name)
    :   gfx::Button(name)
    ,   inactive_color(0.3,0.3,0.3,1.0)
    ,   active_color(0.5,0.5,0.5,1.0)
    ,   curr_coord(0.0)
    ,   curr(nullptr)
    ,   prev(nullptr)
    ,   align_hori(true)
    {
    }
    
    gfx::Tab:: ~ Tab()
    {
    }
    
    gfx::Tab::Tab()
    :   gfx::Button()
    ,   inactive_color(0.3,0.3,0.3,1.0)
    ,   active_color(0.5,0.5,0.5,1.0)
    ,   curr_coord(0.0)
    ,   curr(nullptr)
    ,   prev(nullptr)
    ,   align_hori(true)
    {
    }
}}
