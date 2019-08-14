//
//  CompPhysics2D.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 2/16/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "Entity.hpp"
#include "Rigidbody2D.hpp"
namespace kege{ namespace phx{
    
    
    bool Rigidbody2D::Init(kege::Scene* scene)
    {
        SetPosition(GetParent()->GetLocal().translation);
        return gfx::EntityComponent::Init(scene);
    }
    
    void Rigidbody2D::Update(double dt)
    {
        if (linear_velocity.y != 0.0f)
        {
            grounded = false;
        }
        
        if (driver != nullptr)
        {
            //driver->ApplyForce(rigidbody, dt);
        }
        
        cg::vec3 acceleration = net_force * inv_mass;
        cg::real angular_accel = inertia * inv_mass;
        
        angular_velocity += angular_accel;
        angular_momentum = angular_velocity * mass;
        orientation += angular_velocity * dt;
        
        linear_velocity += acceleration;
        linear_momentum = linear_velocity * mass;
        position += linear_velocity * dt;
        
        ResetNetForce();
        GetParent()->GetLocal().translation = position;
    }
    
    void Rigidbody2D::ApplyForce(const cg::point3& p, const cg::vec3& force)
    {
    }
    
    void Rigidbody2D::ApplyAcceleration(const cg::vec3& acel)
    {
        ApplyForce(mass * acel);
    }
    
    void Rigidbody2D::ApplyForce(const cg::vec3& force)
    {
        net_force += force;
    }
    
    void Rigidbody2D::IncreaseLinearVelocity(const cg::vec3& value)
    {
        linear_velocity += value;
    }
    void Rigidbody2D::IncreasePosition(const cg::point3& value)
    {
        position += value;
    }
    void Rigidbody2D::SetPosition(const cg::point3& value)
    {
        position = value;
    }
    void Rigidbody2D::SetAngularMomentum1(cg::real value)
    {
        angular_momentum = value;
    }
    void Rigidbody2D::SetLinearMomentum(const cg::vec3& value)
    {
        linear_velocity = value;
    }
    void Rigidbody2D::SetAngularVelocity1(cg::real value)
    {
        angular_velocity = value;
    }
    void Rigidbody2D::SetLinearVelocity(const cg::vec3& value)
    {
        linear_velocity = value;
    }
    void Rigidbody2D::SetLinearVelocityX(float value)
    {
        linear_velocity.x = value;
    }
    void Rigidbody2D::SetLinearVelocityY(float value)
    {
        linear_velocity.y = value;
    }
    void Rigidbody2D::SetLinearVelocityZ(float value)
    {
        linear_velocity.z = value;
    }
    void Rigidbody2D::SetNetForce(const cg::vec3& value)
    {
        net_force = value;
    }
    void Rigidbody2D::SetOrientation1(cg::real value)
    {
        orientation = value;
    }
    void Rigidbody2D::SetRestitution(float value)
    {
        restitution = value;
    }
    void Rigidbody2D::SetMass(float value)
    {
        mass = value;
        inv_mass = cg::invrs(mass);
    }
    void Rigidbody2D::ResetNetForce()
    {
        net_force = 0.0;
    }
    
    const cg::point3& Rigidbody2D::GetPosition()const
    {
        return position;
    }
    cg::real Rigidbody2D::GetAngularMomentum1()const
    {
        return angular_momentum;
    }
    const cg::vec3& Rigidbody2D::GetLinearMomentum()const
    {
        return linear_momentum;
    }
    cg::real Rigidbody2D::GetAngularVelocity1()const
    {
        return angular_velocity;
    }
    const cg::vec3& Rigidbody2D::GetLinearVelocity()const
    {
        return linear_velocity;
    }
    const cg::vec3& Rigidbody2D::GetNetForce()const
    {
        return net_force;
    }
    cg::real Rigidbody2D::GetOrientation1()const
    {
        return orientation;
    }
    float Rigidbody2D::GetRestitution()const
    {
        return restitution;
    }
    float Rigidbody2D::GetInvMass()const
    {
        return inv_mass;
    }
    float Rigidbody2D::GetMass()const
    {
        return mass;
    }
    
    cg::point3& Rigidbody2D::GetPosition()
    {
        return position;
    }
    void Rigidbody2D::SetGrounded(bool value)
    {
        grounded = value;
    }
    bool Rigidbody2D::IsGrounded()const
    {
        return grounded;
    }
    void Rigidbody2D::Save(kege::XML& xml)
    {
        kege::XML* comp = xml.AddChild(new kege::XML("physics"));
        comp->AddAttr(new kege::XML::attrib("type","RIGIDBODY_2D"));
    }
    Rigidbody2D::Rigidbody2D(phx::ForceDriver* aggregator)
    :   inertia(1.0)
    ,   orientation()
    ,   position(0.0)
    ,   angular_momentum(0.0)
    ,   linear_momentum(0.0)
    ,   angular_velocity(0.0)
    ,   linear_velocity(0.0)
    ,   net_force(0.0)
    ,   inv_mass(1)
    ,   mass(1)
    ,   grounded(true)
    ,   restitution(0.0)
    {}
    
    Rigidbody2D::~ Rigidbody2D()
    {}
    
    Rigidbody2D::Rigidbody2D()
    :   inertia(1.0)
    ,   orientation()
    ,   position(0.0)
    ,   angular_momentum(0.0)
    ,   linear_momentum(0.0)
    ,   angular_velocity(0.0)
    ,   linear_velocity(0.0)
    ,   net_force(0.0)
    ,   inv_mass(1)
    ,   mass(1)
    ,   grounded(true)
    ,   restitution(0.0)
    {}
    
}}
