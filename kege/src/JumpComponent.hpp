//
//  JumpEntityComponent.hpp
//  dev0
//
//  Created by Kenneth A Esdaile on 9/8/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef JumpComponent_hpp
#define JumpComponent_hpp
#include "PhysicsComponent.hpp"
#include "Component.hpp"
namespace kege{namespace cmp{
    
    class JumpComponent : public gfx::Component
    {
    public:
        
        bool Init(kege::Scene& scene);
        void Save(kege::XML& xml);
        void Jump();
        
        JumpComponent(cg::real16 jump_power, const ds::string& name);
        JumpComponent(cg::real16 jump_power);
        JumpComponent();
        
    protected:
        
        cg::real16 jump_power;
        phx::PhysicsComponent* body;
    };
}}
#endif /* JumpComponent_hpp */
