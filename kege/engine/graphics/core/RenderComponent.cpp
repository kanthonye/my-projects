//
//  RenderComponent.cpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 2/18/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//
#include "Scene.hpp"
#include "RenderComponent.hpp"
namespace kege{namespace gfx{
 
    bool RenderComponent::Init(kege::Scene* scene)
    {
        return gfx::EntityComponent::Init(scene);
    }
    
}}
