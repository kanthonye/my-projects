//======================================================================
//  Author  : Kenneth A Esdaile
//  Date    : Created on 4/14/19.
//  Title   : ColladaVisualScenes.hpp
//  Project : KEGE
//======================================================================
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//======================================================================
#ifndef ColladaVisualScenes_hpp
#define ColladaVisualScenes_hpp
#include "XML.hpp"
#include "Skeleton.hpp"
#include "NodeEntity.hpp"
#include "ColladaLibrary.hpp"
namespace kege{namespace dae{
    
    class ColladaVisualScenes : public dae::ColladaLibrary
    {
    public:
        
        kege::XML* GetJointNode(const ds::string& id);
        
        gfx::Skeleton* GetSkeleton(const ds::string& id);
        gfx::Joint* GetHierarchy(kege::XML* joint);
        
        gfx::Transform GetTransform(kege::XML* node);
        cg::vec3 GetTranslation(kege::XML* node);
        cg::quat GetRotation(kege::XML* node);
        cg::vec3 GetScale(kege::XML* node);
        
        kege::XML* GetInstance(kege::XML* node);
        
        ColladaVisualScenes(kege::XML* visual_scenes)
        :   library(visual_scenes)
        {}
        
    private:
        
        kege::XML* library;
    };
}}
#endif /* ColladaVisualScenes */
