//
//  System.cpp
//  Particles
//
//  Created by Kenneth A Esdaile on 5/11/20.
//  Copyright © 2020 Kenneth A Esdaile. All rights reserved.
//
#include "System.hpp"
namespace kege{
    
    uint BaseSystem::GetType() const
    {
        return _syst_type;
    }
    
    void BaseSystem::Shutdown()
    {
        KEGE_INFO[ "SYSTEM" ][ "SHUTDOWN" ]( GetType(), " shutting-down %s...", GetName().c_str() );
        _init = true;
    }
    
    bool BaseSystem::IsInit()const
    {
        return _init;
    }
    
    bool BaseSystem::Init()
    {
        KEGE_INFO[ "SYSTEM" ][ "INIT" ]( GetType(), " initializing %s...", GetName().c_str() );
        _init = true;
        _init = true;
        return true;
    }

    const string& BaseSystem::GetName() const
    {
        return _name;
    }
    
    int BaseSystem::GET_SYSTEM_TOTAL_TYPES()
    {
        return _system_total_types;
    }
    
    BaseSystem::~BaseSystem()
    {
    }

    int BaseSystem::_system_total_types = 0;
}
