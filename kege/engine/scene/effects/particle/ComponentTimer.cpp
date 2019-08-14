//
//  EmissionTimer.cpp
//  dev0
//
//  Created by Kenneth A Esdaile on 9/12/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//
#include "enumtypes.hpp"
#include "Entity.hpp"
#include "ComponentTimer.hpp"
#define  MAX_PARTICLE_SIZE 4096
namespace kege{namespace gfx{
    
    
    void gfx::ComponentTimer::Update(float delta_ms)
    {
        timespand += delta_ms;
        if (timespand >= timelength)
        {
            //timespand / timelength;
            //msg.value = cg::math::min(total, 4096);
            int val = 1;
            
            GetParent()->HandleMessage( kege::MsgT<int>("ComponentTimer", "timer", "int", val) );
            timespand -= timelength;
        }
    }
    void gfx::ComponentTimer::SetTimelength(unsigned short sec, unsigned short count)
    {
        SetTimelength(double(sec) / double(count));
    }
    void gfx::ComponentTimer::SetTimelength(double sec)
    {
        timelength = sec;
    }
    void gfx::ComponentTimer::SetRepeatable(bool rep)
    {
        repeatable = rep;
    }
    bool gfx::ComponentTimer::GetRepeatable()const
    {
        return repeatable;
    }
    
    void gfx::ComponentTimer::HandleMessage(const kege::Message& message)
    {
        return;
    }
    
    void ComponentTimer::Save(kege::XML& xml)
    {
        kege::XML* comp = xml.AddChild(new kege::XML);
        comp->SetName("Timer");
        comp->AddAttr(new XML::attrib("repeatable", (repeatable)?"true":"false"));
        comp->AddAttr(new XML::attrib("length", ds::string::strprint("%f", timelength)));
    }
    
    ComponentTimer::ComponentTimer(unsigned short sec, unsigned short count)
    :   gfx::EntityComponent(kege::ENUM::_COMPONENT_TIMER)
    ,   timelength(0)
    ,   timespand(0)
    {
        SetTimelength(sec, count);
    }
    
    ComponentTimer::ComponentTimer()
    :   gfx::EntityComponent(kege::ENUM::_COMPONENT_TIMER)
    ,   timelength(0)
    ,   timespand(0)
    {
        SetTimelength(1, 1);
    }
    
    ComponentTimer::~ ComponentTimer()
    {
    }
}}
