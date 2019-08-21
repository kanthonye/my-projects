//
//  CompPhysics2D.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 2/16/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef Physics2D_hpp
#define Physics2D_hpp
#include "PhysicsComponent.hpp"
namespace kege{ namespace phx{
    
    class Rigidbody2D : public phx::PhysicsComponent
    {
    public:
        
        bool Init(kege::Scene* scene);
        void Update(double dt);
        
        // set rigid body state
        void IncreaseLinearVelocity(const cg::vec3& value);
        void IncreasePosition(const cg::point3& value);
        void SetPosition(const cg::point3& value);
        void SetLinearMomentum(const cg::vec3& value);
        void SetLinearVelocity(const cg::vec3& value);
        void SetLinearVelocityX(float value);
        void SetLinearVelocityY(float value);
        void SetLinearVelocityZ(float value);
        void SetNetForce(const cg::vec3& value);
        void SetAngularMomentum1(float value);
        void SetAngularVelocity1(float value);
        void SetOrientation1(float value);
        void SetRestitution(float value);
        void SetMass(float value);
        void ResetNetForce();
        
        // get rigid body state
        const cg::point3& GetPosition()const;
        const cg::vec3& GetLinearMomentum()const;
        const cg::vec3& GetLinearVelocity()const;
        const cg::vec3& GetNetForce()const;
        cg::real GetAngularMomentum1()const;
        cg::real GetAngularVelocity1()const;
        cg::real GetOrientation1()const;
        float GetRestitution()const;
        float GetInvMass()const;
        float GetMass()const;
        
        cg::point3& GetPosition();
        
        // apply a force to rigid body at a point
        void ApplyForce(const cg::point3& p, const cg::vec3& force);
        void ApplyAcceleration(const cg::vec3& force);
        void ApplyForce(const cg::vec3& force);
        
        void SetGrounded(bool value);
        bool IsGrounded()const;
        
        void Save(kege::XML& xml);
        
        Rigidbody2D(phx::ForceDriver* driver);
        ~ Rigidbody2D();
        Rigidbody2D();
        
    private:
        
        phx::ForceDriver* driver;
        
        cg::vec3 linear_momentum;
        cg::vec3 linear_velocity;
        
        cg::real angular_momentum;
        cg::real angular_velocity;
        
        cg::real orientation;
        cg::vec3 net_force;
        
        cg::point3 position;
        
        float inertia;
        float restitution;
        float inv_mass;
        float mass;
        
        bool grounded;
    };
}}
#endif /* Physics2D_hpp */
