//======================================================================
//  Author  : Kenneth A Esdaile
//  Date    : Created on 4/14/19.
//  Title   : ColladaLights.cpp
//  Project : KEGE
//======================================================================
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//======================================================================
#include "ColladaLights.hpp"
namespace kege{namespace dae{
    
    gfx::Light ColladaLights::InstanceLight(kege::ds::string const& id)
    {
        kege::XML* light = library->GetChildByAttr("id", id);
        kege::XML* technique = light->GetChild("technique_common");
        
        if (technique == nullptr) throw "[ERROR] nullptr <technique_common>";
        
        kege::XML* details = technique->Elements().front();
        if (details->GetName() == "directional")
        {
            return GetDirectionalLight(details);
        }
        else if (details->GetName() == "ambient")
        {
            return GetAmbientLight(details);
        }
        else if (details->GetName() == "point")
        {
            return GetPointLight(details);
        }
        else throw "[WARNING] <light> not supported";
    }
    gfx::Light  ColladaLights::GetDirectionalLight(kege::XML* details)
    {
        gfx::Light light;
        light.SetColor(GetColor(details));
        return light;
    }
    gfx::Light  ColladaLights::GetAmbientLight(kege::XML* details)
    {
        gfx::Light light;
        light.SetColor(GetColor(details));
        return light;
    }
    gfx::Light ColladaLights::GetPointLight(kege::XML* details)
    {
        gfx::Light light;
        light.SetColor(GetColor(details));
        return light;
    }
    
    float ColladaLights::GetConstantAttenuation(kege::XML* a)
    {
        float val;
        kege::XML* s = a->GetChild("constant_attenuation");
        StringToFloats(&val, 1, s->GetText());
        return val;
    }
    
    float ColladaLights::GetLinearAttenuation(kege::XML* a)
    {
        float val;
        kege::XML* s = a->GetChild("linear_attenuation");
        StringToFloats(&val, 1, s->GetText());
        return val;
    }
    
    float ColladaLights::GetQuadraticAttenuation(kege::XML* a)
    {
        float val;
        kege::XML* s = a->GetChild("quadratic_attenuation");
        StringToFloats(&val, 1, s->GetText());
        return val;
    }
    
    cg::vec3 ColladaLights::GetAttenuation(kege::XML* a)
    {
        return cg::vec3
        (   GetConstantAttenuation(a)
         ,  GetLinearAttenuation(a)
         ,  GetQuadraticAttenuation(a)  );
    }
    
    cg::vec3 ColladaLights::GetColor(kege::XML* a)
    {
        cg::vec3 color;
        kege::XML* s = a->GetChild("color");
        StringToFloats(color.data, 3, s->GetText());
        return color;
    }
    
}}
