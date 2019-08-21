//======================================================================
//  Author  : Kenneth A Esdaile
//  Date    : Created on 4/14/19.
//  Title   : ColladaLights.hpp
//  Project : KEGE
//======================================================================
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//======================================================================
#ifndef ColladaLights_hpp
#define ColladaLights_hpp
#include "Light.hpp"
#include "ColladaLibrary.hpp"
namespace kege{namespace dae{
    
    class ColladaLights : public ColladaLibrary
    {
    public:
        
        gfx::Light InstanceLight(kege::ds::string const& id);
        gfx::Light GetDirectionalLight(kege::XML* light);
        gfx::Light GetAmbientLight(kege::XML* light);
        gfx::Light GetPointLight(kege::XML* light);
        
        float GetConstantAttenuation(kege::XML* a);
        float GetLinearAttenuation(kege::XML* a);
        float GetQuadraticAttenuation(kege::XML* a);
        cg::vec3 GetAttenuation(kege::XML* a);
        cg::vec3 GetColor(kege::XML* a);
        
        ColladaLights(kege::XML* lights)
        :   library(lights)
        {}
        
    private:
        kege::XML* library;
    };
}}
#endif /* ColladaLights */
