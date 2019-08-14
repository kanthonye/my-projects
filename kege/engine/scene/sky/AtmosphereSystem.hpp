//
//  AtmosphereSystem.hpp
//  Terrain3D
//
//  Created by Kenneth A Esdaile on 10/28/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef AtmosphereSystem_hpp
#define AtmosphereSystem_hpp
#include "UBO.hpp"
#include "Mesh.hpp"
#include "Texture2D.hpp"
#include "SubSystem.hpp"
#include "SkydomeMaterial.hpp"
namespace kege {namespace gfx{
    
    class AtmosphereSystem : public kege::SubSystem
    {
    public:
        
        void Update(double time_delta);
        void UnInit();
        bool Init();
        
        AtmosphereSystem();

    private:
        
        kege::shared<gfx::UBO> _ubo_fog;
        cg::vec4 fog[2];
    };
    
}}
#endif /* AtmosphereSystem_hpp */
