//
//  UsrCamLookAtComp.hpp
//  dev0
//
//  Created by Kenneth Esdaile on 8/31/17.
//  Copyright © 2017 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef UsrCamZoomComp_hpp
#define UsrCamZoomComp_hpp
#include "Component.hpp"
#include "PhysicsComponent.hpp"
namespace kege{namespace cmp{
    
    class FallowComponent : public gfx::Component
    {
    public:
        
        class ZoomControl : public kege::InputListener
        {
            cmp::FallowComponent* c;
        public:
            bool onWheelMove(const kege::Cursor& cursor)override;
            ZoomControl(cmp::FallowComponent* c) : c(c) {}
        }zoom;
        
        bool Init(kege::Scene* scene);
        void Update(double dt);
        
        gfx::Component* Duplicate();
        
        FallowComponent(gfx::Gameobject* object);
        FallowComponent(const ds::string& name);
        virtual ~ FallowComponent(){}
        
    protected:
        
        phx::PhysicsComponent* physics;
        
        gfx::Gameobject* object;
        
        cg::point3 distance_offset;
        cg::point3 height_offset;
        cg::point3 target;
        cg::point3 last;
        
        cg::point2 sensitivity;
        cg::point2 angle;
        
        bool height_adjust;
    };
    
    
    
    class CameraZoomOut : public gfx::Component
    {
    public:
        
        void HandleMessage( const kege::Message& message );
        bool Init( kege::Scene* scene );
        void UnInit();
        
        CameraZoomOut( phx::PhysicsComponent* physics );
        
    protected:
        
        phx::PhysicsComponent* physics;
        cg::real max_distance;
        cg::real min_distance;
        cg::real sensitivity;
        cg::real distance;
    };
    
    
    class CameraZoomIn : public gfx::Component
    {
    public:
        
        void HandleMessage( const kege::Message& message );
        bool Init( kege::Scene* scene );
        void UnInit();
        
        CameraZoomIn( phx::PhysicsComponent* physics );
        
    protected:
        
        phx::PhysicsComponent* physics;
        cg::real max_distance;
        cg::real min_distance;
        cg::real sensitivity;
        cg::real distance;
    };
}}
#endif /* UserRotationComtroller_hpp */
