//
//  UserRotationComtroller.cpp
//  dev0
//
//  Created by Kenneth Esdaile on 8/31/17.
//  Copyright © 2017 Kenneth Anthony Esdaile. All rights reserved.
//
#include "enumtypes.hpp"
#include "Scene.hpp"
#include "Gameobject.hpp"
#include "RotationComponent.hpp"
namespace kege{namespace cmp{
    
    void RotationComponent::HandleMessage(const kege::Message& message)
    {
        if ( message.GetType() == gfx::Component::ROTATION )
        {
            
        }
    }
    void RotationComponent::Rotate(double x, double y, double z)
    {
        euler.x += x;
        euler.y += y;
        euler.x = cg::cycle(euler.x, -360.0, 360.0);
        euler.y = cg::clamp(euler.y, -90.0, 90.0);
        
        if (isinf(euler.x) || isnan(euler.x))
        {
            KEGE_ERROR("RotationComponent invalide value X\n");
            euler.x = 0;
        }
        if (isinf(euler.y) || isnan(euler.y))
        {
            KEGE_ERROR("RotationComponent invalide value Y\n");
            euler.y = 0;
        }
        body->SetOrientation( cg::axis_angleX(euler.y) * cg::axis_angleY(euler.x) );
        //GetParent()->GetLocal().rotation = cg::axis_angleX(euler.y) * cg::axis_angleY(euler.x);
    }
    
    void cmp::RotationComponent::CycleRotationX(float min, float max)
    {
        if (euler.x > max) euler.x -= max;
        if (euler.x < min) euler.x -= min;
    }
    
    void cmp::RotationComponent::CycleRotationY(float min, float max)
    {
        if (euler.y > max) euler.y -= max;
        if (euler.y < min) euler.y -= min;
    }
    
    void cmp::RotationComponent::CycleRotationZ(float min, float max)
    {
        if (euler.z > max) euler.z -= max;
        if (euler.z < min) euler.z -= min;
    }
    
    void cmp::RotationComponent::ClampRotationX(float min, float max)
    {
        if (euler.x >= max) euler.x = max;
        if (euler.x <= min) euler.x = min;
    }
    
    void cmp::RotationComponent::ClampRotationY(float min, float max)
    {
        if (euler.y >= max) euler.y = max;
        if (euler.y <= min) euler.y = min;
    }
    
    void cmp::RotationComponent::ClampRotationZ(float min, float max)
    {
        if (euler.z >= max) euler.z = max;
        if (euler.z <= min) euler.z = min;
    }

    const cg::vec3& cmp::RotationComponent::GetRotationAngles()const
    {
        return euler;
    }
    cg::vec3& cmp::RotationComponent::GetRotationAngles()
    {
        return euler;
    }

    void cmp::RotationComponent::SetSensitivity(const cg::point2& val)
    {
        sensitivity = val;
    }
    
    const cg::point2& cmp::RotationComponent::GetSensitivity() const
    {
        return sensitivity;
    }
    
    cg::point2 & cmp::RotationComponent::GetSensitivity()
    {
        return sensitivity;
    }
    bool cmp::RotationComponent::Init(kege::Scene* scene)
    {
        body = (phx::PhysicsComponent*) GetComponent( gfx::Component::PHYSICS );
        return gfx::Component::Init(scene);
    }
    gfx::Component* cmp::RotationComponent::Duplicate()
    {
        cmp::RotationComponent* comp = new cmp::RotationComponent;
        comp->sensitivity = sensitivity;
        return comp;
    }
    
    cmp::RotationComponent::RotationComponent(const ds::string& name)
    :   gfx::Component( gfx::Component::ROTATION )
    ,   body(nullptr)
    ,   sensitivity(0.75)
    ,   euler(0.0)
    ,   rotate(false)
    {
    }
    
    cmp::RotationComponent::RotationComponent()
    :   gfx::Component( gfx::Component::ROTATION )
    ,   body(nullptr)
    ,   sensitivity(0.75)
    ,   euler(0.0)
    ,   rotate(false)
    {
    }
}}
