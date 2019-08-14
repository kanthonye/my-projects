/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Entity.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../scene/core/Entity.hpp"
#include "Logger.hpp"
#include "../../scene/core/EntityComponent.hpp"
#include "../../scene/core/Gameobject.hpp"
namespace kege{ namespace gfx{
    
    void Entity::HandleMessage( const kege::Message& message )
    {
        for (gfx::EntityComponents::iterator comp = _components.begin(); comp != nullptr; comp++)
        {
            comp->HandleMessage( message );
        }
    }
    
    void Entity::GetRenderables( kege::SceneFrame& frame )
    {
        for (gfx::EntityComponents::iterator comp = _components.begin(); comp != nullptr; comp++)
        {
            comp->GetRenderables( frame );
        }
    }
    
    bool Entity::Init( kege::Scene* scene )
    {
        Gameobject::Init( scene );
        for (gfx::EntityComponents::iterator comp = _components.begin(); comp != nullptr; comp++)
        {
            if ( !comp->Init( scene ) )
            {
                KEGE_WARN("FAILED_INITIALIZATION : EntityComponent %s", comp->GetName().c_str());
                comp->UnInit();
                delete comp.element();
                _components.erase( comp );
                return false;
            };
        }
        return true;
    }
    
    void Entity::Update(double delta)
    {
        for (gfx::EntityComponents::iterator comp = _components.begin(); comp != nullptr; comp++)
        {
            comp->Update( delta );
        }
        Gameobject::Update( delta );
    }
    
    void Entity::UnInit()
    {
        for (gfx::EntityComponents::iterator comp = _components.begin(); comp != nullptr; comp++)
        {
            comp->UnInit();
        }
        Gameobject::UnInit();
    }
    
    gfx::EntityComponent* Entity::Attach(gfx::EntityComponent* component)
    {
        if (component != nullptr)
        {
            _components.push_back( component );
            component->SetParent( this );
        }
        return component;
    }
    
    const gfx::EntityComponent* Entity::GetComponent(const ds::string& name)const
    {
        for (gfx::EntityComponents::iterator comp = _components.begin(); comp != nullptr; comp++)
        {
            if (comp->GetName() == name)
            {
                return comp.element();
            }
        }
        return nullptr;
    }
    
    gfx::EntityComponent* Entity::GetComponent(const ds::string& name)
    {
        for (gfx::EntityComponents::iterator comp = _components.begin(); comp != nullptr; comp++)
        {
            if (comp->GetName() == name)
            {
                return comp.element();
            }
        }
        return nullptr;
    }
    
    const gfx::EntityComponent* Entity::GetComponent(cg::uint type)const
    {
        for (gfx::Components::iterator comp = _components.begin(); comp != nullptr; comp++)
        {
            if (comp->GetType() == type)
            {
                return comp.element();
            }
        }
        return nullptr;
    }
    gfx::EntityComponent* Entity::GetComponent(cg::uint type)
    {
        for (gfx::EntityComponents::iterator comp = _components.begin(); comp != nullptr; comp++)
        {
            if (comp->GetType() == type)
            {
                return comp.element();
            }
        }
        return nullptr;
    }
    
    gfx::EntityComponent* Entity::Detach(const ds::string& name)
    {
        gfx::EntityComponent* comp;
        for (gfx::EntityComponents::iterator c=_components.begin(); c!=nullptr; c++)
        {
            comp = c.element();
            if (comp->GetName() == name)
            {
                _components.erase( c );
                return comp;;
            }
        }
        return nullptr;
    }
    
    void Entity::Detach(const gfx::EntityComponent& component)
    {
        for (gfx::EntityComponents::iterator comp=_components.begin(); comp!=nullptr; comp++)
        {
            if (comp.element() == &component)
            {
                _components.erase( comp );
                break;
            }
        }
    }
    
    gfx::EntityComponent* Entity::Detach(int type)
    {
        gfx::EntityComponent* comp;
        for (gfx::EntityComponents::iterator c=_components.begin(); c!=nullptr; c++)
        {
            comp = c.element();
            if (comp->GetType() == type)
            {
                _components.erase( c );
                return comp;;
            }
        }
        return nullptr;
    }
    
    const EntityComponents& Entity::GetComponents()const
    {
        return _components;
    }
    
    EntityComponents& Entity::GetComponents()
    {
        return _components;
    }
    
    void Entity::ClearComponents()
    {
        gfx::EntityComponent* component;
        for (gfx::EntityComponents::iterator comp=_components.begin(); comp!=nullptr; comp++)
        {
            component = comp.element();
            component->UnInit();
            delete component;
        }
        _components.clear();
    }
    
    void Entity::Destroy()
    {
        ClearComponents();
        _active = false;
        _name.clear();
    }
    
    Entity::Entity(const ds::string& name, const Transform& transform, gfx::EntityComponent* component)
    :   Gameobject( Gameobject::ENTITY, name, transform )
    {
        Attach( component );
    }
    Entity::Entity(Gameobject::Type type, const ds::string& name, const Transform& transform)
    :   Gameobject( type, name, transform )
    {}
    
    Entity::Entity(Gameobject::Type type, const ds::string& name)
    :   Gameobject( type, name )
    {}
    
    Entity::Entity(const ds::string& name, const Transform& transform)
    :   Gameobject( Gameobject::ENTITY, name, transform )
    {}
    
    Entity::Entity(const ds::string& name)
    :   Gameobject( Gameobject::ENTITY, name )
    {}
    
    Entity::Entity()
    :   Gameobject( Gameobject::ENTITY, "" )
    {}
    
    Entity:: ~ Entity()
    {
        Destroy();
    }
}}

