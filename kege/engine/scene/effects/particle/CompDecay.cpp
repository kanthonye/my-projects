//
//  DecayComponent.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 2/16/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//
#include "Entity.hpp"
#include "CompDecay.hpp"
namespace kege{namespace gfx{
    
    void CompDecay::Update(kege::Scene& scene, float delta_ms)
    {
        lifespand -= decay * delta_ms;
        if (lifespand <= 0.001)
        {
            GetParent()->SetActive(false);
            GetParent()->SetVisible(false);
        }
    }
    
    void CompDecay::Save(kege::XML& xml)
    {
        kege::XML* comp = xml.AddChild(new kege::XML);
        comp->SetName("decay");
        comp->AddAttr(new XML::attrib("lifespand", ds::string::strprint("%f", lifespand)));
        comp->AddAttr(new XML::attrib("decay", ds::string::strprint("%f", decay)));
    }
    
    CompDecay::CompDecay(float lifespand, float decay)
    :   gfx::EntityComponent(kege::ENUM::COMP_DECAY)
    ,   lifespand(lifespand)
    ,   decay(decay)
    {
    
    }
}}
