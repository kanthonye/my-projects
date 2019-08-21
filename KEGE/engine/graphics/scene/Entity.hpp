/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Entity.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef Entity_hpp
#define Entity_hpp
#include "../../graphics/scene/Gameobject.hpp"
#include "../../graphics/scene/Component.hpp"
namespace kege{namespace gfx{
    class Scene;
    class Component;
    
    typedef ds::dlist< gfx::Component* > Components;
    
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
        virtual void Submit( gfx::RenderingSystem* renderer );
        
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
        gfx::Component* Attach(gfx::Component* component);
        
        /*
         get const component by name
         */
        const gfx::Component* GetComponent(const ds::string& name)const;
        gfx::Component* GetComponent(const ds::string& name);
        
        /*
         get const component by name
         */
        const gfx::Component* GetComponent(cg::uint type)const;
        gfx::Component* GetComponent(cg::uint type);
        
        /*
         remove component by name
         */
        gfx::Component* Detach(const ds::string& name);
        void Detach(const gfx::Component& component);
        gfx::Component* Detach(int type);
        
        const EntityComponents& GetComponents()const;
        EntityComponents& GetComponents();
        
        void ClearComponents();
        
        virtual void Destroy();
        
        Entity(const ds::string& name, const Transform& transform, gfx::Component* component);
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
