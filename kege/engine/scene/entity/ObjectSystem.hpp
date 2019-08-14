/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/26/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ObjectSystem.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef ObjectSystem_hpp
#define ObjectSystem_hpp
#include "cgm.hpp"
#include "Scene.hpp"
#include "Message.hpp"
#include "SubSystem.hpp"
namespace kege{namespace gfx{
    
    class ObjectSystem : public kege::SubSystem
    {
    public:
        
        void Update(double delta_ms) override;
        void UnInit() override;
        bool Init() override;
        
        ObjectSystem();
    };
}}
#endif /* ObjectSystem_hpp */
