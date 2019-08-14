/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/25/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       CoreSystem.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef CoreSystem_hpp
#define CoreSystem_hpp
#include <stdio.h>
#include "dlist.hpp"
#include "System.hpp"
namespace kege{
    class GameEngine;
    
    class CoreSystem : public kege::System
    {
    public:
        
        kege::GameEngine* GetEngine(){return _engine;}
        virtual void Update(double time_delta) {}
        virtual ~ CoreSystem(){}
        
    protected:
        
        CoreSystem(const ds::string& systyp, kege::GameEngine* engine )
        :   kege::System(systyp)
        ,   _engine( engine )
        {}
        
    protected:
        
        kege::GameEngine* _engine;
        ds::string _group;
        
        friend kege::CoreSystems;
        friend kege::GameEngine;
    };
    
    
}
#endif /* CoreSystem_hpp */
