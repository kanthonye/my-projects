/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/26/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       PhysicsSystem.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef PhysicsSystem_hpp
#define PhysicsSystem_hpp
#include "SubSystem.hpp"
#include "ForceDriver.hpp"
#include "PhysicsComponent.hpp"
namespace kege {namespace phx{
    
    class PhysicsSystem : public kege::SubSystem
    {
    public:
        
        void AddPhysicsObject(phx::PhysicsComponent* object);
        
        /**
         get ForceDriver for this scene
         */
        inline const phx::ForceDriver& GetForceDriver() const {return force_driver;}
        
        inline phx::ForceDriver& GetForceDriver() {return force_driver;}
        
        void Update(double delta);
        void UnInit();
        bool Init();
        
        ~ PhysicsSystem();
        PhysicsSystem();
        
    private:
        
        ds::dlist<phx::PhysicsComponent*> physics_objetcs;
        phx::ForceDriver force_driver;
        friend phx::PhysicsComponent;
    };
    
}}
#endif /* PhysicsSystem_hpp */
