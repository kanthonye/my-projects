//
//  DecayComponent.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 2/16/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef DecayComponent_hpp
#define DecayComponent_hpp
#include "EntityComponent.hpp"
namespace kege{namespace gfx{
    
    class CompDecay : public gfx::EntityComponent
    {
    public:
        
        void Update(kege::Scene& scene, float delta_ms);
        void Save(kege::XML& xml);
        
        CompDecay(float lifespand, float decay);
        
    private:
        
        float lifespand;
        float decay;
        
    };
}}
#endif /* DecayComponent_hpp */
