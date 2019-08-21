//
//  GUISpinner.cpp
//  dev0
//
//  Created by Kenneth A Esdaile on 8/3/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//
#include "Numberic.hpp"
#include "GUISpinner.hpp"
#include "ButtonComponents.hpp"
#include "Singleton.hpp"
#include "ResourceManager.hpp"
namespace kege{ namespace gfx{
    
    bool gfx::Spinner::onButtonChildren(gfx::GUIInput& input)
    {
        if (gfx::GUI::onButtonChildren(input))
        {
            if (up->Selected())
            {
                Increase();
            }
            if (dn->Selected())
            {
                Decrease();
            }
            return true;
        }
        return false;
    }
    
    bool gfx::Spinner::InitializeSelf()
    {
        cg::vec4 c0 = cg::vec4(color.xyz * 0.5, 1.0);
        
        Asset<gfx::Font> monaco;
        kege::ResourceManager* mgr = kege::Singleton::Get<kege::ResourceManager>();
        if (mgr != nullptr)
        {
            kege::Resource<gfx::Font>* res = mgr->GetResource<gfx::Font>();
            monaco = res->Load(mgr, "monaco.fnt");
        }
        
        numberic = new gfx::Numberic("numeric", GetWidth()-20, GetHeight()-5, color, &(*monaco));
        numberic->AddComponent(new gfx::ui::MenuButton);
        AddChild(numberic);
        
        kege::shared<gfx::GUI> buttons = AddChild(new gfx::GUI("buttons", 20, GetHeight(), color));
        buttons->GetTransform().GetLocal().position.x = numberic->GetWidth();
        
        up = buttons->AddChild(new gfx::Button("up", 20, GetHeight()*0.5-1, c0));
        up->AddComponent(new gfx::ui::ClickButtonBR);
        
        dn = buttons->AddChild(new gfx::Button("dn", 20, GetHeight()*0.5-1, c0));
        dn->AddComponent(new gfx::ui::ClickButtonBR);
        dn->GetTransform().GetLocal().position.y = -up->GetHeight()-2;
        return true;
    }
    
    void gfx::Spinner::SetValue(double val)
    {
        numberic->SetValue(val);
    }
    
    double gfx::Spinner::GetValue()const
    {
        return numberic->GetValue();
    }
    
    void gfx::Spinner::Increase()
    {
        numberic->SetValue(numberic->GetValue() + incr_valu);
    }
    
    void gfx::Spinner::Decrease()
    {
        numberic->SetValue(numberic->GetValue() - incr_valu);
    }
    
    gfx::Spinner::Spinner(const ds::string& name, int w, int h, const cg::vec4& color)
    :   gfx::Panel(name, w, h, color)
    ,   numberic(nullptr)
    ,   up(nullptr)
    ,   dn(nullptr)
    ,   incr_valu(1.0)
    {
    }
    
    gfx::Spinner::Spinner(const ds::string& name, int w, int h)
    :   gfx::Panel(name, w, h)
    ,   numberic(nullptr)
    ,   up(nullptr)
    ,   dn(nullptr)
    ,   incr_valu(1.0)
    {
    }
    
    gfx::Spinner::Spinner(const ds::string& name)
    :   gfx::Panel(name)
    ,   numberic(nullptr)
    ,   up(nullptr)
    ,   dn(nullptr)
    ,   incr_valu(1.0)
    {
    }
    
    gfx::Spinner:: ~ Spinner()
    {
        numberic = nullptr;
    }
    
    gfx::Spinner::Spinner()
    :   gfx::Panel()
    ,   numberic(nullptr)
    ,   up(nullptr)
    ,   dn(nullptr)
    ,   incr_valu(1.0)
    {
    }

}}
