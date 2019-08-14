/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/4/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ShadowComponent.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "SceneLight.hpp"
#include "RenderingSystem.hpp"
#include "ShadowComponent.hpp"
namespace kege{namespace gfx{
    
    void ShadowComponent::Draw(gfx::RenderingSystem* renderer)
    {
//        SceneLight* light = (SceneLight*) GetParent();
//
//        cg::vec3 forward = light->GetDirection();
//        cg::vec3 right = cg::cross3(cg::vec3::up, forward);
//        cg::vec3 up = cg::cross3(forward, right);
//
//        _view
//        (  right.x, up.x, forward.x, 0.0
//        ,  right.y, up.y, forward.y, 0.0
//        ,  right.z, up.z, forward.z, 0.0
//        ,      0.0,  0.0,       0.0, 1.0  );
//
//        float depth = 10000.0f;
//        float side = 50.0f;
//        _proj = cg::ortho_proj(-side, side, -side, side, -500, depth);
        
//        renderer->SetShadowMatrix(const gfx::Camera &camera)
    }
    
    ShadowComponent::ShadowComponent(const cg::mat44& proj, const cg::mat44& view)
    :   gfx::RenderComponent("")
    ,   _proj(proj)
    ,   _view(view)
    {}
    ShadowComponent::ShadowComponent()
    :   gfx::RenderComponent("")
    ,   _proj(1.0)
    ,   _view(1.0)
    {}
    
}}
