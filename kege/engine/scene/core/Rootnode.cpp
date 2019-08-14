/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Rootnode.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "Logger.hpp"
#include "../../scene/core/NodeEntity.hpp"
#include "../../scene/core/Rootnode.hpp"
namespace kege{ namespace gfx{
    
    void Rootnode::GetRenderables( kege::SceneFrame& frame )
    {
        for (gfx::Gameobjects::iterator obj=_objects.begin(); obj!=nullptr; obj++)
        {
            obj->GetRenderables( frame );
        }
    }
    
    void Rootnode::HandleMessage(const kege::Message& message)
    {
        for (gfx::Gameobjects::iterator obj=_objects.begin(); obj!=nullptr; obj++)
        {
            obj->HandleMessage( message );
        }
    }
    
    // GameObjNode
    short Rootnode::Init(kege::Scene* scene)
    {
        for (gfx::Gameobjects::iterator obj=_objects.begin(); obj!=nullptr; obj++)
        {
            if ( !obj->Init( scene ) )
            {
                Logger::log["WARNING"].Msg("FAILED_INITIALIZATION Gameobject %s", obj->GetName().c_str());
                delete obj.element();
                _objects.erase(obj);
            };
        }
        return kege::SUCCESSFUL_INITIALIZATION;
    }
    
    void Rootnode::Update(double delta)
    {
        for (gfx::Gameobjects::iterator obj=_objects.begin(); obj!=nullptr; obj++)
        {
            obj->Update( delta );
        }
    }
    
    void Rootnode::UnInit()
    {
        for (gfx::Gameobjects::iterator obj=_objects.begin(); obj!=nullptr; obj++)
        {
            obj->UnInit();
        }
    }
    
    void Rootnode::Destroy()
    {
        Gameobject* gameobject;
        for (gfx::Gameobjects::iterator obj=_objects.begin(); obj!=nullptr; obj++)
        {
            gameobject = obj.element();
            delete gameobject;
        }
        _objects.clear();
    }
    
    
    const Gameobject* Rootnode::FindChild(const ds::string& name)const
    {
        gfx::Gameobjects::iterator obj;
        for (obj=_objects.begin(); obj!=nullptr; obj++)
            if (obj->GetName() == name)
            {
                return obj.element();
            }
        const Gameobject* child = nullptr;
        for (obj=_objects.begin(); obj!=nullptr; obj++)
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
    
    Gameobject* Rootnode::FindChild(const ds::string& name)
    {
        gfx::Gameobjects::iterator obj;
        for (obj=_objects.begin(); obj!=nullptr; obj++)
            if (obj->GetName() == name)
            {
                return obj.element();
            }
        Gameobject* child = nullptr;
        for (obj=_objects.begin(); obj!=nullptr; obj++)
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
    
    
    const Gameobject* Rootnode::GetChild(const ds::string& name)const
    {
        if (name.empty() || IsEmpty()) return nullptr;
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
        for (gfx::Gameobjects::iterator obj=_objects.begin(); obj!=nullptr; obj++)
            if (obj->GetName() == name)
            {
                return obj.element();
            }
        return nullptr;
    }
    
    Gameobject* Rootnode::GetChild(const ds::string& name)
    {
        if (name.empty() || IsEmpty()) return nullptr;
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
        for (gfx::Gameobjects::iterator obj=_objects.begin(); obj!=nullptr; obj++)
            if (obj->GetName() == name)
            {
                return obj.element();
            }
        return nullptr;
    }
    
    Gameobject* Rootnode::RemChild(const ds::string& name)
    {
        if (name.empty() || IsEmpty()) return nullptr;
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
        for (gfx::Gameobjects::iterator node=_objects.begin(); node!=nullptr; node++)
        {
            if (node.element()->GetName() == name)
            {
                Gameobject* object = node.element();
                object->SetParent( nullptr );
                _objects.erase(node);
                return object;
            }
        }
        return nullptr;
    }
    
    bool Rootnode::RemChild(Gameobject* object)
    {
        for (gfx::Gameobjects::iterator node=_objects.begin(); node!=nullptr; node++)
        {
            if (node.element() == object)
            {
                _objects.erase(node);
                return true;
            }
        }
        return false;
    }
    
    void Rootnode::AddChildren(Gameobjects& objects)
    {
        for (gfx::Gameobjects::iterator obj=objects.begin(); obj!=nullptr; obj++)
        {
            AddChild( obj.element() );
        }
    }
    Gameobject* Rootnode::AddChild(Gameobject* object)
    {
        if (object != nullptr)
        {
            _objects.push_back( object );
        }
        return object;
    }
    
    bool Rootnode::IsEmpty()const
    {
        return _objects.empty();
    }
    
    const Gameobjects& Rootnode::GetChildren()const
    {
        return _objects;
    }
    
    Gameobjects& Rootnode::GetChildren()
    {
        return _objects;
    }
    
    Rootnode::Rootnode()
    {}
    
    Rootnode:: ~ Rootnode()
    {
        Destroy();
    }
}}
