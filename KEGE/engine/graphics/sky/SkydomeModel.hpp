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
#include "Model.hpp"
#include "SkydomeMaterial.hpp"
namespace kege {namespace gfx{
    
    class SkydomeModel : public gfx::Model
    {
    public:
        
        void Update(double delta_ms);
        SkydomeModel();
    };
}}
#endif /* SkydomeModel_hpp */
