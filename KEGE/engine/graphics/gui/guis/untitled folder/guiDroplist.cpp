//
//  guiDroplist.cpp
//  dev0
//
//  Created by Kenneth A Esdaile on 8/1/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//
#include "GUILabel.hpp"
#include "Button.hpp"
#include "ButtonComponents.hpp"
#include "guiDroplist.hpp"
#include "Singleton.hpp"
#include "ResourceManager.hpp"
namespace kege{ namespace gfx{
    
    bool gfx::Droplist::onButtonChildren(gfx::GUIInput& input)
    {
        bool value = gfx::GUI::onButtonChildren(input);
        
        if (button->IsState(gfx::GUI::SELECTED) && !openlist)
        {
            openlist = true;
            Expand();
        }
        else if (button->IsState(gfx::GUI::RELEASE) && openlist)
        {
            openlist = false;
            Calapse();
        }
        else if (mouseover && openlist)
        {
            Expand();
        }
        
        return value;
    }
    
    kege::shared<gfx::GUI> gfx::Droplist::RemoveElement(const ds::string& name)
    {
        kege::shared<gfx::GUI> detach = list->Detach(name);
        if (openlist)
        {
            Expand();
        }
        return detach;
    }
    
    kege::shared<gfx::GUI> gfx::Droplist::GetElement(const ds::string& name)
    {
        return list->GetChild(name);
    }
    
    kege::shared<gfx::GUI> gfx::Droplist::AddElement(gfx::GUI* gui)
    {
        if (openlist)
        {
            gui->GetTransform().GetLocal().position.y = length;
            length += gui->GetHeight();
            gui->Show();
        }
        else
        {
            gui->GetTransform().GetLocal().position.y = 0;
            gui->Hide();
        }
        return list->AddChild(gui);
    }
    
    bool gfx::Droplist::RemoveElement(gfx::GUI* gui)
    {
        return list->Detach(gui);
    }
    
    void gfx::Droplist::Calapse()
    {
        for (gfx::GUI::iterator b=list->GetChildren().begin(); b!=nullptr; b++)
        {
            b->Hide();
            b->GetTransform().GetLocal().position.y = 0;
        }
        length = 0;
        list->SetHeight(length);
        SetHeight(button->GetHeight() + padding.y + padding.w);
    }
    
    void gfx::Droplist::Expand()
    {
        length = 0;
        for (gfx::GUI::iterator b=list->GetChildren().begin(); b!=nullptr; b++)
        {
            b->Show();
            length += padding.y;
            b->GetTransform().GetLocal().position.y = length;
            b->GetTransform().GetLocal().position.x = padding.x;
            length += b->GetHeight() + padding.w;
        }
        list->SetHeight(length);
        SetHeight(button->GetHeight() + list->GetHeight());
    }
    
    bool gfx::Droplist::InitializeSelf()
    {
        SetPadding(cg::vec4(0,1,0,1));
        button = AddChild( new gfx::Button("button", GetWidth()-padding.x, 20, color) );
        button->AddComponent(new gfx::ui::StateButtonAR);
        button->SetImgCoord(cg::vec4(0.305, 0.8027, 0.41, 0.123));
        
//        Asset<gfx::Font> monaco;
//        kege::ResourceManager* mgr = kege::Singleton::Get<kege::ResourceManager>();
//        if (mgr != nullptr)
//        {
//            kege::Resource<gfx::Font>* res = mgr->GetResource<gfx::Font>();
//            monaco = res->Load(mgr, "monaco.fnt");
//        }
//
//        if (monaco != nullptr) {
//            cg::vec4 colr = cg::vec4(color.xyz * 4, 1.0);
//            gfx::GUI* label = Attach(new gfx::Label(name, button->GetWidth(),GetHeight()-5, colr, monaco));
//            label->GetTransform().GetLocal().position.y = (label->GetHeight() - GetHeight()) * 0.5;
//            label->GetTransform().GetLocal().position.x = 4;
//        }
        
        color.xyz *= 0.5;
        
        this->list = AddChild( new gfx::GUI("list", GetWidth()-padding.x, 0, color) );
        this->list->GetTransform().GetLocal().position.y = 20;
        list->SetImgCoord(cg::vec4(0.305, 0.8027, 0.41, 0.123));
        
        return gfx::GUI::InitializeComponents();;
    }
    
    gfx::Droplist::Droplist(const ds::string& name, int w, int h, const cg::vec4& colr)
    :   gfx::GUI(name, w, h, colr)
    ,   button(nullptr)
    ,   list(nullptr)
    ,   length(0)
    ,   openlist(false)
    {
        InitializeSelf();
    }
    
    gfx::Droplist::Droplist(const ds::string& name, int w, int h)
    :   gfx::GUI(name, w, h)
    ,   button(nullptr)
    ,   list(nullptr)
    ,   length(0)
    ,   openlist(false)
    {
        InitializeSelf();
    }
    
    gfx::Droplist::Droplist(const ds::string& name)
    :   gfx::GUI(name)
    ,   button(nullptr)
    ,   list(nullptr)
    ,   length(0)
    ,   openlist(false)
    {
        InitializeSelf();
    }
    
    gfx::Droplist:: ~ Droplist()
    {
        list = nullptr;
        button = nullptr;
    }
    
    gfx::Droplist::Droplist()
    :   gfx::GUI()
    ,   button(nullptr)
    ,   list(nullptr)
    ,   length(0)
    ,   openlist(false)
    {
        InitializeSelf();
    }
    
}}
