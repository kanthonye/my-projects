/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/12/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       SkydomeModel.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef SkydomeModel_hpp
#define SkydomeModel_hpp
#include "Mesh.hpp"
#include "RenderComponent.hpp"
#include "MeshComponent.hpp"
#include "SkydomeMaterial.hpp"
namespace kege {namespace gfx{
    
    class SkydomeModel : public gfx::MeshComponent
    {
    public:
        
        void Draw(gfx::RenderingSystem* renderer)override;
        const cg::vec4& GetSkyColors();
        bool Init(kege::Scene* scene)override;
        
        ~ SkydomeModel();
        SkydomeModel();
        
    private:
        
        cg::vec4 colors[2];
    };
}}
#endif /* SkydomeModel_hpp */
