//======================================================================
//  Author  : Kenneth A Esdaile
//  Date    : Created on 4/14/19.
//  Title   : ColladaCameras.cpp
//  Project : KEGE
//======================================================================
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//======================================================================
#include "ColladaCameras.hpp"
namespace kege{namespace dae{

    cg::mat44 ColladaCameras::InstanceCamera(kege::ds::string const& id)
    {
        kege::XML* perspective = library->GetChildByAttr("id", id);
        perspective = perspective->GetChild("/optics/technique_common/perspective");
        cg::vec4 presp = GetPerspective(perspective);
        // fov, aspect, znear, zfar
        return cg::perspproj(presp.x, presp.y, presp.z, presp.w);
    }
    
    cg::vec4 ColladaCameras::GetPerspective(kege::XML* perspective)
    {
        return cg::vec4
        (   GetFieldOfView(perspective)
         ,  GetAspectRatio(perspective)
         ,  GetZnear(perspective)
         ,  GetZfar(perspective)  );
    }
    
    float ColladaCameras::GetAspectRatio(kege::XML* perspective)
    {
        float value;
        perspective = perspective->GetChild("aspect_ratio");
        StringToFloats(&value, 1, perspective->GetText());
        return value;
    }
    
    float ColladaCameras::GetFieldOfView(kege::XML* perspective)
    {
        float value;
        perspective = perspective->GetChild("xfov");
        StringToFloats(&value, 1, perspective->GetText());
        return value;
    }
    
    float ColladaCameras::GetZnear(kege::XML* perspective)
    {
        float value;
        perspective = perspective->GetChild("znear");
        StringToFloats(&value, 1, perspective->GetText());
        return value;
    }
    
    float ColladaCameras::GetZfar(kege::XML* perspective)
    {
        float value;
        perspective = perspective->GetChild("zfar");
        StringToFloats(&value, 1, perspective->GetText());
        return value;
    }
}}
