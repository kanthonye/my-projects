/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/25/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       SubSystems.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "Logger.hpp"
#include "SubSystems.hpp"
namespace kege{
    
    void SubSystems::HandleMessage( const kege::Message& message )
    {
        for (SubSystems::iterator sys=systems.begin(); sys!=nullptr; sys++)
        {
            kege::SubSystem* s = sys.element();
            s->HandleMessage( message );
        }
    }
    
    kege::SubSystem* SubSystems::RemSystem(const ds::string& stype)
    {
        for (SubSystems::iterator sys=systems.begin(); sys!=nullptr; sys++)
        {
            if (sys->GetStrType() == stype)
            {
                kege::SubSystem* s = sys.element();
                systems.erase(sys);
                return s;
            }
        }
        return nullptr;
    }
    
    kege::SubSystem* SubSystems::GetSystem(const ds::string& stype)
    {
        for (SubSystems::iterator sys=systems.begin(); sys!=nullptr; sys++)
        {
            if (sys->GetStrType() == stype)
            {
                return sys.element();
            }
        }
        return nullptr;
    }
    
    bool SubSystems::AddSystem(kege::SubSystem* sys)
    {
        if (sys == nullptr) return false;
        if (HasSystem(sys)) return false;
        systems.push_back(sys);
        return true;
    }
    
    bool SubSystems::HasSystem(kege::SubSystem* sys)
    {
        for (SubSystems::iterator s=systems.begin(); s!=nullptr; s++)
        {
            if (s.element() == sys)
            {
                return true;
            }
        }
        return false;
    }
    
    bool SubSystems::HasSystem(const ds::string& typ)
    {
        for (SubSystems::iterator sys=systems.begin(); sys!=nullptr; sys++)
        {
            if (sys->GetStrType() == typ)
            {
                return true;
            }
        }
        return false;
    }
    
    void SubSystems::Update(double time_delta)
    {
        for (SubSystems::iterator sys=systems.begin(); sys!=nullptr; sys++)
        {
            sys->Update(time_delta);
        }
    }
    
    void SubSystems::UnInit()
    {
        for (SubSystems::iterator sys=systems.begin(); sys!=nullptr; sys++)
        {
            if ( sys->IsInit() )
            {
                KEGE_INFO("UnInit SubSystem -> %s", sys->GetStrType().c_str());
                sys->UnInit();
            }
        }
    }
    
    bool SubSystems::Init()
    {
        for (SubSystems::iterator sys=systems.begin(); sys!=nullptr; sys++)
        {
            if ( !sys->IsInit() )
            {
                KEGE_INFO("Init SubSystem ->  %s", sys->GetStrType().c_str());
                if( !sys->Init() )
                {
                    KEGE_ERROR("Failed Initialization : SubSystem -> %s", sys->GetStrType().c_str());
                    return false;
                };
            }
        }
        return true;
    }
    
    void SubSystems::Clear()
    {
        for (SubSystems::iterator sys=systems.begin(); sys!=nullptr; sys++)
        {
            delete sys.element();
        }
        systems.clear();
    }
    
    SubSystems::~ SubSystems()
    {
        Clear();
    }
    
    SubSystems::SubSystems()
    {}
}
