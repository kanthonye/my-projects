//
//  GUIList.cpp
//  dev0
//
//  Created by Kenneth A Esdaile on 3/14/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#include "GUIList.hpp"
namespace kege{ namespace gfx{
    
    void ReOrganize(kege::shared<gfx::GUI>& root)
    {
        kege::shared<gfx::GUI> ui;
        float length = 0;
        for (gfx::GUI::iterator n=root->GetChildren().begin(); n!=nullptr; n++)
        {
            ui = n.element();
            
            length += root->GetPadding().y;
            ui->GetTransform().GetLocal().GetPosition().y = length;
            length += ui->GetHeight() + root->GetPadding().w;
            // center ui
            ui->GetTransform().GetLocal().GetPosition().x = (root->GetWidth() - ui->GetWidth()) * 0.5;
        }
        root->SetHeight(length);
    }
    
    bool gfx::GUIList::onButtonChildren(gfx::GUIInput& input)
    {
        for (gfx::GUI::iterator n=list->GetChildren().begin(); n!=nullptr; n++)
        {
            if (n->onButton(input))
            {
                selection = n.element();
                break;
            }
        }
        return selection != nullptr;
    }
    
    kege::shared<gfx::GUI> gfx::GUIList::RemoveElement(const ds::string& name)
    {
        kege::shared<gfx::GUI> list = GetChild("list");
        if (list == nullptr) return nullptr;
        kege::shared<gfx::GUI> gui = list->Detach(name);
        if (gui != nullptr)
        {
            ReOrganize(list);
        }
        return gui;
    }
    
    kege::shared<gfx::GUI> gfx::GUIList::GetElement(const ds::string& name)
    {
        kege::shared<gfx::GUI> list = GetChild("list");
        if (list == nullptr) return nullptr;
        return list->GetChild(name);
    }
    
    kege::shared<gfx::GUI> gfx::GUIList::AddElement(const kege::shared<gfx::GUI>& node)
    {
        if (list == nullptr) list = AddChild(new gfx::GUI("list", GetWidth(), 0.0, cg::vec4(0.0)));
        list->AddChild(node);
        ReOrganize(list);
        SetHeight(list->GetHeight());
        return node;
    }
    
    bool gfx::GUIList::RemoveElement(gfx::GUI* node)
    {
        kege::shared<gfx::GUI> list = GetChild("list");
        if (list == nullptr) return nullptr;
        bool detached = list->Detach(node);
        if (detached)
        {
            ReOrganize(list);
        }
        return detached;
    }
    
    const kege::shared<gfx::GUI>& gfx::GUIList::GetSelectedElement()const
    {
        return selection;
    }
    
    kege::shared<gfx::GUI>& gfx::GUIList::GetSelectedElement()
    {
        return selection;
    }
    
    gfx::GUIList::GUIList(const ds::string& name, int w, int h, const cg::vec4& color)
    :   gfx::GUI(name,w,h,color)
    ,   selection(nullptr)
    ,   list(nullptr)
    {
    }
    gfx::GUIList::GUIList(const ds::string& sid, int w, int h)
    :   gfx::GUI(name,w,h)
    ,   selection(nullptr)
    ,   list(nullptr)
    {
    }
    gfx::GUIList::GUIList(const ds::string& sid)
    :   gfx::GUI(name)
    ,   selection(nullptr)
    ,   list(nullptr)
    {
    }
    gfx::GUIList:: ~ GUIList()
    {
    }
    gfx::GUIList::GUIList()
    :   gfx::GUI()
    ,   selection(nullptr)
    ,   list(nullptr)
    {
    }
    
}}




