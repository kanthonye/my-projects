//
//  PhysicsEntityComponent.hpp
//  dev0
//
//  Created by Kenneth A Esdaile on 9/16/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//
#ifndef PhysicsComponent_hpp
#define PhysicsComponent_hpp
#include "EntityComponent.hpp"
#include "ForceDriver.hpp"
#include "../collision/colliders/Collider.hpp"
namespace kege{namespace phx{
    class PhysicsSystem;
    
    class PhysicsComponent : public gfx::EntityComponent
    {
    public:
        
        bool Init(kege::Scene* scene);
        void UnInit();
        /*
         update this object components and child objects
         */
        virtual void Update(double delta_ms);
        
        // set rigid body state
        void IncreaseLinearVelocity(const cg::vec3& value);
        void IncreasePosition(const cg::point3& value);
        void SetPosition(const cg::point3& value);
        void SetAngularMomentum(const cg::vec3& value);
        void SetLinearMomentum(const cg::vec3& value);
        void SetAngularVelocity(const cg::vec3& value);
        void SetLinearVelocity(const cg::vec3& value);
        void SetLinearVelocityX(float value);
        void SetLinearVelocityY(float value);
        void SetLinearVelocityZ(float value);
        void SetNetForce(const cg::vec3& value);
        void SetOrientation(const cg::quat& value);
        void SetRestitution(float value);
        void SetMass(float value);
        void ResetNetForce();
        
        // get rigid body state
        const cg::mat33& GetInvrsInertia()const;
        const cg::mat33& GetInerti()const;
        const cg::point3& GetPosition()const;
        const cg::vec3& GetAngularMomentum()const;
        const cg::vec3& GetLinearMomentum()const;
        const cg::vec3& GetAngularVelocity()const;
        const cg::vec3& GetLinearVelocity()const;
        const cg::vec3& GetNetForce()const;
        const cg::quat& GetOrientation()const;
        float GetRestitution()const;
        float GetInvMass()const;
        float GetMass()const;
        
        const cg::vec3& GetForward() const {return _forward;}
        const cg::vec3& GetRight() const {return _right;}
        const cg::vec3& GetUp() const {return _up;}
        
        // apply a force to rigid body at a point
        void ApplyForce(const cg::point3& p, const cg::vec3& force);
        void ApplyAcceleration(const cg::vec3& force);
        void ApplyForce(const cg::vec3& force);
        
        void SetGrounded(bool value);
        bool IsGrounded()const;
        
        void Save(kege::XML& xml);
        
        ~ PhysicsComponent();
        PhysicsComponent();
        
    private:
        
        cg::point3 position;
        
        cg::mat33 invrs_inertia;
        cg::mat33 inertia;
        cg::quat rotation;
        cg::vec3 angular_momentum;
        cg::vec3 linear_momentum;
        cg::vec3 angular_velocity;
        cg::vec3 linear_velocity;
        cg::vec3 net_force;
        cg::vec3 _forward;
        cg::vec3 _right;
        cg::vec3 _up;
        float restitution;
        float inv_mass;
        float mass;
        
        bool grounded;
        
        static cg::mat33 dummy;
        static cg::quat dummyq;
        
    private:
        
        friend phx::PhysicsSystem;
        static PhysicsComponent* head;
        static PhysicsComponent* tail;
        PhysicsComponent* next;
        PhysicsComponent* prev;
        cg::Collider* _collider;
    };
}}
#endif /* PhysicsComponent_hpp */

