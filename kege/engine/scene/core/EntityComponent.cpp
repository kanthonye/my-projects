/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       EntityComponent.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../scene/core/Entity.hpp"
#include "../../scene/core/EntityComponent.hpp"
namespace kege{namespace gfx{
    
    /*
     queue messages for this object to handle
     */
    void EntityComponent::HandleMessage( const kege::Message& message )
    {
    }
    const gfx::EntityComponent* EntityComponent::GetComponent(cg::uint type)const
    {
        if (_parent == nullptr) return nullptr;
        return _parent->GetComponent( type );
    }
    
    gfx::EntityComponent* EntityComponent::GetComponent(cg::uint type)
    {
        if (_parent == nullptr) return nullptr;
        return _parent->GetComponent( type );
    }
    
    const cg::quat& EntityComponent::GetLocalRotation()const
    {
        return _parent->GetLocalRotation();
    }
    const cg::quat& EntityComponent::GetWorldRotation()const
    {
        return _parent->GetWorldRotation();
    }
    
    const cg::vec3& EntityComponent::GetLocalPosition()const
    {
        return _parent->GetLocalPosition();
    }
    const cg::vec3& EntityComponent::GetWorldPosition()const
    {
        return _parent->GetWorldPosition();
    }
    
    const cg::vec3& EntityComponent::GetLocalScale()const
    {
        return _parent->GetLocalScale();
    }
    const cg::vec3& EntityComponent::GetWorldScale()const
    {
        return _parent->GetWorldScale();
    }
    
    cg::mat44 EntityComponent::GetWorldMatrix()const
    {
        return _parent->GetWorldMatrix();
    }
    cg::mat44 EntityComponent::GetLocalMatrix()const
    {
        return _parent->GetLocalMatrix();
    }
    
    cg::quat& EntityComponent::GetLocalRotation()
    {
        return _parent->GetLocalRotation();
    }
    cg::quat& EntityComponent::GetWorldRotation()
    {
        return _parent->GetWorldRotation();
    }
    
    cg::vec3& EntityComponent::GetLocalPosition()
    {
        return _parent->GetLocalPosition();
    }
    cg::vec3& EntityComponent::GetWorldPosition()
    {
        return _parent->GetWorldPosition();
    }
    
    const kege::Scene* EntityComponent::GetScene()const
    {
        return _parent->GetScene();
    }
    kege::Scene* EntityComponent::GetScene()
    {
        return _parent->GetScene();
    }
    
    
    bool EntityComponent::Init(kege::Scene* scene)
    {
        _init = _parent != nullptr;
        return _init;
    }
    
    void EntityComponent::UnInit()
    {
        _init = false;
    }
    
    void EntityComponent::Destroy()
    {
        UnInit();
        _parent = nullptr;
        _init = false;
    }
    
    EntityComponent:: ~ EntityComponent()
    {
        Destroy();
    }
}}
