/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       NodeEntity.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#include "../../graphics/scene/Gameobject.hpp"
#include "../../graphics/scene/NodeEntity.hpp"
namespace kege{ namespace gfx{
    
    void gfx::NodeEntity::Submit( gfx::RenderingSystem* renderer )
    {
        gfx::Entity::Submit( renderer );
        
        if (!_visible || !_init || !_loaded )
            return;
        
        for (gfx::Gameobjects::iterator obj=objects.begin(); obj!=nullptr; obj++)
        {
            obj->Submit( renderer );
        }
    }
    
    void gfx::NodeEntity::HandleMessage(const kege::Message& message)
    {
        gfx::Entity::HandleMessage( message );
        
        for (gfx::Gameobjects::iterator obj=objects.begin(); obj!=nullptr; obj++)
        {
            obj->HandleMessage( message );
        }
    }
    
    // GameObjNode
    bool gfx::NodeEntity::Init(kege::Scene* scene)
    {
        if (_parent != nullptr)
        {
            _world = _parent->GetWorld() * _local;
        }
        else _world = _local;

        for (gfx::Gameobjects::iterator obj=objects.begin(); obj!=nullptr; obj++)
        {
            if ( !obj->Init( scene ) )
            {
                Destroy();
                return false;
            };
        }
        return gfx::Gameobject::Init( scene );;
    }
    
    void gfx::NodeEntity::Update(double delta)
    {
        gfx::Entity::Update( delta );
        for (gfx::Gameobjects::iterator obj=objects.begin(); obj!=nullptr; obj++)
        {
            obj->Update( delta );
        }
    }
    
    void gfx::NodeEntity::UnInit()
    {
        for (gfx::Gameobjects::iterator obj=objects.begin(); obj!=nullptr; obj++)
        {
            obj->UnInit();
        }
        gfx::Entity::UnInit();
    }
    
    void gfx::NodeEntity::Destroy()
    {
        gfx::Entity::Destroy();
        RemoveChildren();
    }


    const Gameobject* gfx::NodeEntity::FindChild(const ds::string& name)const
    {
        gfx::Gameobjects::iterator obj;
        for (obj=objects.begin(); obj!=nullptr; obj++)
            if (obj->GetName() == name)
            {
                return obj.element();
            }
        const Gameobject* child = nullptr;
        for (obj=objects.begin(); obj!=nullptr; obj++)
        {
            if (obj->GetType() == Gameobject::NODEENTITY)
            {
                child = ((NodeEntity*)obj.element())->FindChild( name );
            }
            if (child != nullptr)
            {
                return child;
            }
        }
        return nullptr;
    }
    
    Gameobject* gfx::NodeEntity::FindChild(const ds::string& name)
    {
        gfx::Gameobjects::iterator obj;
        for (obj=objects.begin(); obj!=nullptr; obj++)
            if (obj->GetName() == name)
            {
                return obj.element();
            }
        Gameobject* child = nullptr;
        for (obj=objects.begin(); obj!=nullptr; obj++)
        {
            if (obj->GetType() == Gameobject::NODEENTITY)
            {
                child = ((NodeEntity*)obj.element())->FindChild( name );
            }
            if (child != nullptr)
            {
                return child;
            }
        }
        return nullptr;
    }

    
    const Gameobject* gfx::NodeEntity::GetChild(const ds::string& name)const
    {
        if (name.empty() || objects.count() == 0) return nullptr;
        if (name[0] == '/')
        {
            ds::string str = name;
            ds::string obj_name = strtok(str.getdata(), "/");
            const Gameobject* root = GetChild( obj_name );
            while (root && !obj_name.empty())
            {
                if (root->GetType() == Gameobject::NODEENTITY)
                {
                    root = ((NodeEntity*)root)->GetChild( obj_name );
                }
                else
                {
                    return nullptr;
                }
                obj_name = strtok(nullptr, "/\\");
            }
            return root;
        }
        for (gfx::Gameobjects::iterator obj=objects.begin(); obj!=nullptr; obj++)
            if (obj->GetName() == name)
            {
                return obj.element();
            }
        return nullptr;
    }
    
    Gameobject* gfx::NodeEntity::GetChild(const ds::string& name)
    {
        if (name.empty() || objects.count() == 0) return nullptr;
        if (name[0] == '/')
        {
            ds::string str = name;
            ds::string obj_name = strtok(str.getdata(), "/");
            Gameobject* root = GetChild( obj_name );
            while (root && !obj_name.empty())
            {
                if (root->GetType() == Gameobject::NODEENTITY)
                {
                    root = ((NodeEntity*)root)->GetChild( obj_name );
                }
                else
                {
                    return nullptr;
                }
                obj_name = strtok(nullptr, "/\\");
            }
            return root;
        }
        for (gfx::Gameobjects::iterator obj=objects.begin(); obj!=nullptr; obj++)
            if (obj->GetName() == name)
            {
                return obj.element();
            }
        return nullptr;
    }
    
    Gameobject* gfx::NodeEntity::RemChild(const ds::string& name)
    {
        if (name.empty() || objects.count() == 0) return nullptr;
        if (name[0] == '/')
        {
            ds::string str = name;
            ds::string obj_name = strtok(str.getdata(), "/");
            Gameobject* root = GetChild( obj_name );
            
            while (root && !obj_name.empty())
            {
                if (root->GetType() == Gameobject::NODEENTITY)
                {
                    root = ((NodeEntity*)root)->GetChild( obj_name );
                }
                else
                {
                    return nullptr;
                }
                obj_name = strtok(nullptr, "/\\");
            }
            return root;
        }
        for (gfx::Gameobjects::iterator node=objects.begin(); node!=nullptr; node++)
        {
            if (node.element()->GetName() == name)
            {
                Gameobject* object = node.element();
                object->SetParent( nullptr );
                objects.erase(node);
                return object;
            }
        }
        return nullptr;
    }
    
    bool gfx::NodeEntity::RemChild(Gameobject* object)
    {
        for (gfx::Gameobjects::iterator node=objects.begin(); node!=nullptr; node++)
        {
            if (node.element() == object)
            {
                objects.erase(node);
                return true;
            }
        }
        return false;
    }
    
    Gameobject* NodeEntity::AddChild(Gameobject* object)
    {
        if (object == nullptr) return object;
        
        if ( object->GetParent() != nullptr )
        {
            ((NodeEntity*)object->GetParent())->RemChild( object );
        }
        
        object->SetParent( this );
        objects.push_back( object );
        return object;
    }
   
    bool gfx::NodeEntity::IsEmpty()const
    {
        return objects.empty();
    }
    
    const Gameobjects& gfx::NodeEntity::GetChildren()const
    {
        return objects;
    }
    
    Gameobjects& gfx::NodeEntity::GetChildren()
    {
        return objects;
    }
    
    void gfx::NodeEntity::RemoveChildren()
    {
        Gameobject* gameobject;
        for (gfx::Gameobjects::iterator obj=objects.begin(); obj!=nullptr; obj++)
        {
            gameobject = obj.element();
            gameobject->Destroy();
            delete gameobject;
        }
        objects.clear();
    }
    
    gfx::NodeEntity::NodeEntity(Gameobject::Type type, const ds::string& name)
    :   gfx::Entity(type, name)
    {}
    
    gfx::NodeEntity::NodeEntity(const ds::string& name)
    :   gfx::Entity( gfx::Gameobject::NODEENTITY, name )
    {}
    
    gfx::NodeEntity::NodeEntity()
    :   gfx::Entity( gfx::Gameobject::NODEENTITY, "" )
    {}
    
    
    gfx::NodeEntity:: ~ NodeEntity()
    {
    }
}}
