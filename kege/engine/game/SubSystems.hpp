/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/25/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       SubSystems.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef SubSystems_hpp
#define SubSystems_hpp
#include "dlist.hpp"
#include "SubSystem.hpp"
namespace kege{
    class Scene;
    
    class SubSystems
    {
    public:
        typedef ds::dlist<kege::SubSystem*>::iterator iterator;
        
        kege::SubSystem* RemSystem( const ds::string& stype );
        kege::SubSystem* GetSystem( const ds::string& stype );
        
        void  HandleMessage( const kege::Message& message );
        bool  AddSystem( kege::SubSystem* sys );
        bool  HasSystem( kege::SubSystem* sys );
        bool  HasSystem( const ds::string& typ );
        void  Update( double time_delta );
        void  UnInit();
        bool Init();
        
        void Clear();
        
        ~ SubSystems();
        SubSystems();
        
    private:
        
        ds::dlist<kege::SubSystem*> systems;
        friend Scene;
    };
}
#endif /* SubSystems_hpp */
