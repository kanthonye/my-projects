/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Component.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../graphics/scene/Entity.hpp"
#include "../../graphics/scene/Component.hpp"
namespace kege{namespace gfx{
    
    /*
     queue messages for this object to handle
     */
    void Component::HandleMessage( const kege::Message& message )
    {
    }
    const gfx::Component* Component::GetComponent(cg::uint type)const
    {
        if (_parent == nullptr) return nullptr;
        return _parent->GetComponent( type );
    }
    
    gfx::Component* Component::GetComponent(cg::uint type)
    {
        if (_parent == nullptr) return nullptr;
        return _parent->GetComponent( type );
    }
    
    const cg::quat& Component::GetLocalRotation()const
    {
        return _parent->GetLocalRotation();
    }
    const cg::quat& Component::GetWorldRotation()const
    {
        return _parent->GetWorldRotation();
    }
    
    const cg::vec3& Component::GetLocalPosition()const
    {
        return _parent->GetLocalPosition();
    }
    const cg::vec3& Component::GetWorldPosition()const
    {
        return _parent->GetWorldPosition();
    }
    
    const cg::vec3& Component::GetLocalScale()const
    {
        return _parent->GetLocalScale();
    }
    const cg::vec3& Component::GetWorldScale()const
    {
        return _parent->GetWorldScale();
    }
    
    cg::mat44 Component::GetWorldMatrix()const
    {
        return _parent->GetWorldMatrix();
    }
    cg::mat44 Component::GetLocalMatrix()const
    {
        return _parent->GetLocalMatrix();
    }
    
    cg::quat& Component::GetLocalRotation()
    {
        return _parent->GetLocalRotation();
    }
    cg::quat& Component::GetWorldRotation()
    {
        return _parent->GetWorldRotation();
    }
    
    cg::vec3& Component::GetLocalPosition()
    {
        return _parent->GetLocalPosition();
    }
    cg::vec3& Component::GetWorldPosition()
    {
        return _parent->GetWorldPosition();
    }
    
    const kege::Scene* Component::GetScene()const
    {
        return _parent->GetScene();
    }
    kege::Scene* Component::GetScene()
    {
        return _parent->GetScene();
    }
    
    
    bool Component::Init(kege::Scene* scene)
    {
        _init = _parent != nullptr;
        return _init;
    }
    
    void Component::UnInit()
    {
        _init = false;
    }
    
    void Component::Destroy()
    {
        UnInit();
        _parent = nullptr;
        _init = false;
    }
    
    Component:: ~ Component()
    {
        Destroy();
    }
}}
