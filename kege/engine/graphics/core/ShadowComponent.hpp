/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/4/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ShadowComponent.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef ShadowComponent_hpp
#define ShadowComponent_hpp
#include "cgm.hpp"
#include "RenderComponent.hpp"
namespace kege{namespace gfx{
    
    class ShadowComponent : public gfx::RenderComponent
    {
    public:
        
        void Draw(gfx::RenderingSystem* renderer);
        
        //bool Init(kege::Scene* scene);
        
        ShadowComponent(const cg::mat44& proj, const cg::mat44& view);
        ShadowComponent();
        
    private:
        
        cg::mat44 _view;
        cg::mat44 _proj;
    };
}}
#endif /* ShadowComponent_hpp */
