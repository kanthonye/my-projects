/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/17/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Sun.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef SunObject_hpp
#define SunObject_hpp
#include "UBO.hpp"
#include "Entity.hpp"
#include "SkydomeMaterial.hpp"
namespace kege {namespace gfx{
    
    class SunObject : public gfx::Entity
    {
    public:
        
        bool Init(kege::Scene* scene);
        void Update(double delta_ms);
        void UnInit();
        
        ~ SunObject();
        
    private:
        
        kege::shared<gfx::UBO> ubo;
        SharedMaterial material;
        cg::vec4 sun[3];
        cg::vec3 rotation;
    };
}}
#endif /* Sun_hpp */
