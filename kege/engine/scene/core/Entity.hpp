/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Entity.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef Entity_hpp
#define Entity_hpp
#include "../../scene/core/Gameobject.hpp"
#include "../../scene/core/EntityComponent.hpp"
namespace kege{namespace gfx{
    class Scene;
    class EntityComponent;
    
    typedef ds::dlist< gfx::EntityComponent* > Components;
    
    class Entity : public Gameobject
    {
    public:
        
        /*
         send message to game components to handle
         */
        virtual void HandleMessage( const kege::Message& message );
        
        /*
         render this object components
         */
        virtual void GetRenderables( kege::SceneFrame& frame );
        
        /*
         initialize this object components
         */
        virtual bool Init( kege::Scene* scene );
        
        /*
         update this objects components
         */
        virtual void Update( double delta );
        
        /*
         clear entities
         */
        virtual void UnInit();
        
        /*
         add component ptr
         */
        gfx::EntityComponent* Attach(gfx::EntityComponent* component);
        
        /*
         get const component by name
         */
        const gfx::EntityComponent* GetComponent(const ds::string& name)const;
        gfx::EntityComponent* GetComponent(const ds::string& name);
        
        /*
         get const component by name
         */
        const gfx::EntityComponent* GetComponent(cg::uint type)const;
        gfx::EntityComponent* GetComponent(cg::uint type);
        
        /*
         remove component by name
         */
        gfx::EntityComponent* Detach(const ds::string& name);
        void Detach(const gfx::EntityComponent& component);
        gfx::EntityComponent* Detach(int type);
        
        const EntityComponents& GetComponents()const;
        EntityComponents& GetComponents();
        
        void ClearComponents();
        
        virtual void Destroy();
        
        Entity(const ds::string& name, const Transform& transform, gfx::EntityComponent* component);
        Entity(const ds::string& name, const Transform& transform);
        Entity(const ds::string& name);
        virtual ~ Entity();
        Entity();
        
    protected:
        
        Entity(Gameobject::Type type, const ds::string& name, const Transform& transform);
        Entity(Gameobject::Type type, const ds::string& name);
        
    protected:
        
        EntityComponents _components;
    };
    
    typedef ds::dlist< Entity* > Entities;
}}
#endif /* Entity_hpp */
