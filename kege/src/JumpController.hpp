//
//  JumpController.hpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/20/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef JumpController_hpp
#define JumpController_hpp
#include "JumpComponent.hpp"
#include "InputComponent.hpp"
#include "ComponentInput.hpp"
namespace kege{namespace cmp{
    
    class JumpController : public gfx::Component
    {
    public:
        
        void HandleMessage( const kege::Message& message )override;
        bool Init(kege::Scene* scene)override;
        void UnInit()override;
        void Jump();
        
        JumpController();
        
    private:
        
        cg::real16 jump_power;
    };
}}
#endif /* JumpController_hpp */
