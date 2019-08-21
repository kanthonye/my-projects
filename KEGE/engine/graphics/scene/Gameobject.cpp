/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/12/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Gameobject.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#include "../../graphics/scene/Component.hpp"
#include "../../graphics/scene/Gameobject.hpp"
namespace kege{ namespace gfx{
    
    void gfx::Gameobject::Submit( gfx::RenderingSystem* renderer )
    {
    }
    
    void gfx::Gameobject::HandleMessage(const kege::Message& message)
    {
    }
    
    bool gfx::Gameobject::Init(kege::Scene* scene)
    {
        _scene = scene;
        _loaded = true;
        _visible = true;
        _init = true;
        return _init;
    }
    
    void gfx::Gameobject::Update(double delta)
    {
        if (GetParent() != nullptr)
        {
            _world = GetParent()->GetWorld() * _local;
        } else {
            _world = _local;
        }
    }
    
    void gfx::Gameobject::UnInit()
    {
        _visible = false;
        _init = false;
    }
    
    void gfx::Gameobject::Destroy()
    {
        _active = false;
        _name.clear();
    }
    
    const cg::quat& gfx::Gameobject::GetLocalRotation()const
    {
        return _local.rotation;
    }
    const cg::quat& gfx::Gameobject::GetWorldRotation()const
    {
        return _world.rotation;
    }
    
    const cg::vec3& gfx::Gameobject::GetLocalPosition()const
    {
        return _local.translation;
    }
    const cg::vec3& gfx::Gameobject::GetWorldPosition()const
    {
        return _world.translation;
    }
    
    const cg::vec3& gfx::Gameobject::GetLocalScale()const
    {
        return _local.scale;
    }
    const cg::vec3& gfx::Gameobject::GetWorldScale()const
    {
        return _world.scale;
    }
    
    const gfx::Transform& gfx::Gameobject::GetLocal()const
    {
        return _local;
    }
    const gfx::Transform& gfx::Gameobject::GetWorld()const
    {
        return _world;
    }
    
    cg::mat44 gfx::Gameobject::GetWorldMatrix()const
    {
        return _world.GetMatrix();
    }
    cg::mat44 gfx::Gameobject::GetLocalMatrix()const
    {
        return _local.GetMatrix();
    }
    
    cg::quat& gfx::Gameobject::GetLocalRotation()
    {
        return _local.rotation;
    }
    cg::quat& gfx::Gameobject::GetWorldRotation()
    {
        return _world.rotation;
    }
    
    cg::vec3& gfx::Gameobject::GetLocalPosition()
    {
        return _local.translation;
    }
    cg::vec3& gfx::Gameobject::GetWorldPosition()
    {
        return _world.translation;
    }
    
    cg::vec3& gfx::Gameobject::GetLocalScale()
    {
        return _local.scale;
    }
    cg::vec3& gfx::Gameobject::GetWorldScale()
    {
        return _world.scale;
    }
    
    gfx::Transform& gfx::Gameobject::GetLocal()
    {
        return _local;
    }
    gfx::Transform& gfx::Gameobject::GetWorld()
    {
        return _world;
    }
    
    void gfx::Gameobject::SetParent(Gameobject* parent)
    {
        _parent = parent;
    }
    Gameobject* gfx::Gameobject::GetParent()
    {
        return _parent;
    }
    const kege::Scene* gfx::Gameobject::GetScene()const
    {
        return _scene;
    }
    kege::Scene* gfx::Gameobject::GetScene()
    {
        return _scene;
    }
    
    gfx::Gameobject::Gameobject(Gameobject::Type type, const ds::string& name, gfx::Transform local)
    :   _local( local )
    ,   _name( name )
    ,   _parent( nullptr )
    ,   _scene( nullptr )
    ,   _type( type )
    ,   _visible( false )
    ,   _active( true )
    ,   _loaded( false )
    ,   _init( false )
    {}
    
    gfx::Gameobject::Gameobject(Gameobject::Type type, const ds::string& name)
    :   _name( name )
    ,   _parent( nullptr )
    ,   _scene( nullptr )
    ,   _type( type )
    ,   _visible( false )
    ,   _active( true )
    ,   _loaded( false )
    ,   _init( false )
    {}
    gfx::Gameobject::Gameobject(Gameobject::Type type)
    :   _parent( nullptr )
    ,   _scene( nullptr )
    ,   _type( type )
    ,   _visible( false )
    ,   _active( true )
    ,   _loaded( false )
    ,   _init( false )
    {}
    
    gfx::Gameobject:: ~ Gameobject()
    {
        Destroy();
    }
}}

