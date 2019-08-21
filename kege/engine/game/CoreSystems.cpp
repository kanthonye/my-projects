/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/25/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       CoreSystems.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "Logger.hpp"
#include "CoreSystems.hpp"
namespace kege{
    
    void CoreSystems::HandleMessage( const kege::Message& message )
    {
        for (CoreSystems::iterator sys=systems.begin(); sys!=nullptr; sys++)
        {
            kege::CoreSystem* s = sys.element();
            s->HandleMessage( message );
        }
    }
    
    kege::CoreSystem* CoreSystems::RemSystem(const ds::string& stype)
    {
        for (CoreSystems::iterator sys=systems.begin(); sys!=nullptr; sys++)
        {
            if (sys->GetStrType() == stype)
            {
                kege::CoreSystem* s = sys.element();
                systems.erase(sys);
                return s;
            }
        }
        return nullptr;
    }
    
    kege::CoreSystem* CoreSystems::GetSystem(const ds::string& stype)
    {
        for (CoreSystems::iterator sys=systems.begin(); sys!=nullptr; sys++)
        {
            if (sys->GetStrType() == stype)
            {
                return sys.element();
            }
        }
        return nullptr;
    }
    
    bool CoreSystems::AddSystem(kege::CoreSystem* sys)
    {
        if (sys == nullptr) return false;
        if (HasSystem(sys)) return false;
        systems.push_back(sys);
        return true;
    }
    
    bool CoreSystems::HasSystem(kege::CoreSystem* sys)
    {
        for (CoreSystems::iterator s=systems.begin(); s!=nullptr; s++)
        {
            if (s.element() == sys)
            {
                return true;
            }
        }
        return false;
    }
    
    bool CoreSystems::HasSystem(const ds::string& typ)
    {
        for (CoreSystems::iterator sys=systems.begin(); sys!=nullptr; sys++)
        {
            if (sys->GetStrType() == typ)
            {
                return true;
            }
        }
        return false;
    }
    
    void CoreSystems::Update(double time_delta)
    {
        for (CoreSystems::iterator sys=systems.begin(); sys!=nullptr; sys++)
        {
            if ( !sys->IsInit() ) continue;
            sys->Update(time_delta);
        }
    }
    
    void CoreSystems::UnInit()
    {
        for (CoreSystems::iterator sys=systems.begin(); sys!=nullptr; sys++)
        {
            if ( sys->IsInit() )
            {
                KEGE_INFO("UnInit System -> %s", sys->GetStrType().c_str());
                sys->UnInit();
            }
        }
    }
    
    void CoreSystems::Destroy()
    {
        for (CoreSystems::iterator sys=systems.begin(); sys!=nullptr; sys++)
        {
            if ( sys->IsInit() )
            {
                sys->UnInit();
            }
            delete *sys;
        }
        systems.clear();
    }
    
    bool CoreSystems::Init()
    {
        for (CoreSystems::iterator sys=systems.begin(); sys!=nullptr; sys++)
        {
            if ( !sys->IsInit() )
            {
                KEGE_INFO("CoreSystem Init -> %s", sys->GetStrType().c_str());
                if ( !sys->Init() )
                {
                    KEGE_ERROR("System -> %s : Initialization Failed.", sys->GetStrType().c_str());
                    UnInit();
                    return false;
                }
            }
        }
        return true;
    }
    
    void CoreSystems::Clear()
    {
        systems.clear();
    }
    
    CoreSystems::~ CoreSystems()
    {
        Clear();
    }
    
    CoreSystems::CoreSystems()
    {}
}
