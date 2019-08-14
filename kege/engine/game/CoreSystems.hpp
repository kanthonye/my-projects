/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/25/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       CoreSystems.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef CoreSystems_hpp
#define CoreSystems_hpp
#include "dlist.hpp"
#include "CoreSystem.hpp"
namespace kege{
    class GameEngine;
    
    class CoreSystems : public kege::Object
    {
    public:
        
        typedef ds::dlist<kege::CoreSystem*>::iterator iterator;
        
        kege::CoreSystem* RemSystem(const ds::string& stype);
        kege::CoreSystem* GetSystem(const ds::string& stype);
        
        void HandleMessage( const kege::Message& message );
        bool AddSystem(kege::CoreSystem* sys);
        bool HasSystem(kege::CoreSystem* sys);
        bool HasSystem(const ds::string& typ);
        void Update(double time_delta);
        void Destroy();
        void UnInit();
        bool Init();
        
        void Clear();
        
        CoreSystems();
        virtual ~ CoreSystems();
        
    private:
        
        ds::dlist<kege::CoreSystem*> systems;
        friend GameEngine;
    };
}
#endif /* CoreSystems_hpp */
