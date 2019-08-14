//
//  PhysicsComponent.cpp
//  dev0
//
//  Created by Kenneth A Esdaile on 9/16/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//
#include "Entity.hpp"
#include "CollisionComponent.hpp"
#include "PhysicsComponent.hpp"
namespace kege{namespace phx{
    
    bool PhysicsComponent::Init(kege::Scene* scene)
    {
        if ( !_init )
        {
            SetPosition( GetParent()->GetLocal().translation );
            if ( prev == nullptr && next == nullptr )
            {
                if (head == nullptr)
                {
                    tail = head = this;
                }
                else
                {
                    tail->next = this;
                    this->prev = tail;
                    tail = this;
                }
            }
            return gfx::EntityComponent::Init(scene);
        }
        return _init;
    }
    
    void PhysicsComponent::UnInit()
    {
        if ( _init )
        {
            if ( prev != nullptr || next != nullptr )
            {
                if (this == head)
                {
                    head = next;
                    if (nullptr != head) head->prev = nullptr;
                }
                else if (this == tail)
                {
                    tail = prev;
                    if (nullptr != tail) tail->next = nullptr;
                }
                else
                {
                    if (nullptr != prev) prev->next = next;
                    if (nullptr != next) next->prev = prev;
                }
                next = nullptr;
                prev = nullptr;
            }
            gfx::EntityComponent::UnInit();
        }
    }
    
    void PhysicsComponent::Update(double dt)
    {
//        if (GetLinearVelocity().y != 0.0f)
//        {
//            SetGrounded(false);
//        }
//        
//        cg::vec3 acceleration = GetNetForce() * GetInvMass();
//        
//        IncreaseLinearVelocity(acceleration);
//        SetLinearMomentum(linear_velocity * mass);
//        IncreasePosition(linear_velocity * dt);
//        //prev_pos = GetPosition();
//        SetNetForce(0.0);
//        
//        GetParent()->GetLocal().translation = position;
//        cg::quat_to_basis(_right, _up, _forward, GetParent()->GetWorld().rotation);
    }
    
    void PhysicsComponent::ApplyForce(const cg::point3& p, const cg::vec3& force)
    {
    }
    
    void PhysicsComponent::ApplyAcceleration(const cg::vec3& acel)
    {
        ApplyForce(mass * acel);
    }
    
    void PhysicsComponent::ApplyForce(const cg::vec3& force)
    {
        net_force += force;
    }
    
    void PhysicsComponent::IncreaseLinearVelocity(const cg::vec3& value)
    {
        linear_velocity += value;
    }
    void PhysicsComponent::IncreasePosition(const cg::point3& value)
    {
        position += value;
    }
    void PhysicsComponent::SetPosition(const cg::point3& value)
    {
        position = value;
    }
    void PhysicsComponent::SetAngularMomentum(const cg::vec3& value)
    {
        angular_momentum = value;
    }
    void PhysicsComponent::SetLinearMomentum(const cg::vec3& value)
    {
        linear_velocity = value;
    }
    void PhysicsComponent::SetAngularVelocity(const cg::vec3& value)
    {
        angular_velocity = value;
    }
    void PhysicsComponent::SetLinearVelocity(const cg::vec3& value)
    {
        linear_velocity = value;
    }
    void PhysicsComponent::SetLinearVelocityX(float value)
    {
        linear_velocity.x = value;
    }
    void PhysicsComponent::SetLinearVelocityY(float value)
    {
        linear_velocity.y = value;
    }
    void PhysicsComponent::SetLinearVelocityZ(float value)
    {
        linear_velocity.z = value;
    }
    void PhysicsComponent::SetNetForce(const cg::vec3& value)
    {
        net_force = value;
    }
    void PhysicsComponent::SetOrientation(const cg::quat& value)
    {
        rotation = value;
    }
    void PhysicsComponent::SetRestitution(float value)
    {
        restitution = value;
    }
    void PhysicsComponent::SetMass(float value)
    {
        mass = value;
        inv_mass = cg::invrs(mass);
    }
    void PhysicsComponent::ResetNetForce()
    {
        net_force = 0.0;
    }
    
    const cg::mat33& PhysicsComponent::GetInvrsInertia()const
    {
        return invrs_inertia;
    }
    const cg::mat33& PhysicsComponent::GetInerti()const
    {
        return inertia;
    }
    const cg::point3& PhysicsComponent::GetPosition()const
    {
        return position;
    }
    const cg::vec3& PhysicsComponent::GetAngularMomentum()const
    {
        return angular_momentum;
    }
    const cg::vec3& PhysicsComponent::GetLinearMomentum()const
    {
        return linear_momentum;
    }
    const cg::vec3& PhysicsComponent::GetAngularVelocity()const
    {
        return angular_velocity;
    }
    const cg::vec3& PhysicsComponent::GetLinearVelocity()const
    {
        return linear_velocity;
    }
    const cg::vec3& PhysicsComponent::GetNetForce()const
    {
        return net_force;
    }
    const cg::quat& PhysicsComponent::GetOrientation()const
    {
        return rotation;
    }
    float PhysicsComponent::GetRestitution()const
    {
        return restitution;
    }
    float PhysicsComponent::GetInvMass()const
    {
        return inv_mass;
    }
    float PhysicsComponent::GetMass()const
    {
        return mass;
    }
    
//    cg::point3& Rigidbody3D::GetPosition()
//    {
//        return position;
//    }
    void PhysicsComponent::SetGrounded(bool value)
    {
        grounded = value;
    }
    bool PhysicsComponent::IsGrounded()const
    {
        return grounded;
    }
//
//    void Rigidbody3D::GetCollider(cmp::CollisionComponent* value)
//    {
//        collider = value;
//    }
//    const cmp::CollisionComponent* Rigidbody3D::GetCollider()const
//    {
//        return collider;
//    }
//    cmp::CollisionComponent* Rigidbody3D::GetCollider()
//    {
//        return collider;
//    }
//
    void PhysicsComponent::Save(kege::XML& xml)
    {
        kege::XML* comp = xml.AddChild(new kege::XML("physics"));
        comp->AddAttr(new kege::XML::attrib("type","RIGIDBODY"));
    }
    
    PhysicsComponent::PhysicsComponent()
    :   gfx::EntityComponent( gfx::EntityComponent::PHYSICS, "PhysicsComponent" )
    ,   invrs_inertia(1.0)
    ,   inertia(1.0)
    ,   rotation()
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
    ,   _forward(cg::vec3::forward)
    ,   _right(cg::vec3::right)
    ,   _up(cg::vec3::up)
    ,   next(nullptr)
    ,   prev(nullptr)
    {
    }
    
    PhysicsComponent::~ PhysicsComponent()
    {
        EntityComponent::UnInit();
        UnInit();
    }
    
    phx::PhysicsComponent* PhysicsComponent::head = nullptr;
    phx::PhysicsComponent* PhysicsComponent::tail = nullptr;
    cg::mat33 PhysicsComponent::dummy;
    cg::quat PhysicsComponent::dummyq;
}}


