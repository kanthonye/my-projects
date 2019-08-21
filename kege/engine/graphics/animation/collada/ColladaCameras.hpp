//======================================================================
//  Author  : Kenneth A Esdaile
//  Date    : Created on 4/14/19.
//  Title   : ColladaCameras.hpp
//  Project : KEGE
//======================================================================
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//======================================================================
#ifndef ColladaCameras_hpp
#define ColladaCameras_hpp
#include "Camera.hpp"
#include "ColladaLibrary.hpp"
namespace kege{namespace dae{
    
    class ColladaCameras : public ColladaLibrary
    {
    public:
        
        cg::mat44 InstanceCamera(kege::ds::string const& id);
        
        cg::vec4 GetPerspective(kege::XML* perspective);
        float GetAspectRatio(kege::XML* perspective);
        float GetFieldOfView(kege::XML* perspective);
        float GetZnear(kege::XML* perspective);
        float GetZfar(kege::XML* perspective);
        
        ColladaCameras(kege::XML* lights)
        :   library(lights)
        {}
        
    private:
        kege::XML* library;
    };
}}
#endif /* ColladaCameras */
