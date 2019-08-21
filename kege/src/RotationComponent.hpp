//
//  UserRotationComtroller.hpp
//  dev0
//
//  Created by Kenneth Esdaile on 8/31/17.
//  Copyright © 2017 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef RotationComponent_hpp
#define RotationComponent_hpp
#include "Component.hpp"
#include "PhysicsComponent.hpp"
namespace kege{namespace cmp{
    
    /**
     UsrCamRotContr (User Camera Rotation Controller): this component
     is used to rotate an entity along the x and y axis;
     */
    class RotationComponent : public gfx::Component
    {
    public:
        
        void HandleMessage(const kege::Message& message);
        void SetSensitivity(const cg::point2& val);
        void Rotate(double x, double y, double z);
        
        void CycleRotationX(float min, float max);
        void CycleRotationY(float min, float max);
        void CycleRotationZ(float min, float max);
        void ClampRotationX(float min, float max);
        void ClampRotationY(float min, float max);
        void ClampRotationZ(float min, float max);
        
        const cg::vec3& GetRotationAngles()const;
        cg::vec3& GetRotationAngles();
        
        const cg::point2& GetSensitivity() const;
        cg::point2 & GetSensitivity();
        gfx::Component* Duplicate();
        
        bool Init(kege::Scene* scene);
        
        RotationComponent(const ds::string& name);
        virtual ~ RotationComponent(){}
        RotationComponent();
        
    protected:
        
        phx::PhysicsComponent* body;
        double rx, ry, rz;
        cg::point2 sensitivity;
        cg::vec3 euler;
        bool rotate;
    };
}}
#endif /* UsrCamRotContr_hpp */
