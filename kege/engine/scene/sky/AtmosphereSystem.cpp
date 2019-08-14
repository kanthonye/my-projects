//
//  AtmosphereSystem.cpp
//  
//
//  Created by Kenneth A Esdaile on 10/28/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//
#include "GUI.hpp"
#include "myGUI.hpp"
#include "Singleton.hpp"


#include "Scene.hpp"
#include "SunObject.hpp"
#include "Graphics.hpp"
#include "../sky/SkydomeModel.hpp"
#include "../sky/AtmosphereSystem.hpp"
namespace kege {namespace gfx{

    
    static bool __set__ = false;
    void AtmosphereSystem::Update(double time_delta)
    {
        _ubo_fog->UpdateData(32, &fog);
    }
    //DayNightSystem;
    void AtmosphereSystem::UnInit()
    {
        if ( !_init ) return;
        _ubo_fog = nullptr;
        _init = false;
    }
    
    bool AtmosphereSystem::Init()
    {
        if ( _init ) return _init;
        fog[0] = cg::vec4(0.965, 0.804, 0.604, 1.0);
        fog[1] = cg::vec4(0.00125, 1.0, 0.0, 0.0);
        
        _ubo_fog = gfx::Graphics::CreateUBO(sizeof(cg::vec4)*2, &fog,  gfx::STREAM_DRAW, "FOG");
        if (_ubo_fog == nullptr) return kege::FAILED_INITIALIZATION;
        
        GetScene()->Add( new gfx::Entity("skydome", Transform(), new gfx::SkydomeModel) );
        GetScene()->Add( new gfx::SunObject );
        
        _init = true;
        return _init;
    }
    
    AtmosphereSystem::AtmosphereSystem()
    :   kege::SubSystem("AtmosphereSystem")
    {
    }
}}
