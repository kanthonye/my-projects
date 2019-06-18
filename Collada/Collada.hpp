//======================================================================
//  Author  : Kenneth A Esdaile
//  Date    : Created on 4/14/19.
//  Title   : Collada.hpp
//  Project : KEGE
//======================================================================
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//======================================================================
#ifndef collada_scene_hpp
#define collada_scene_hpp
#include <map>
#include "Entity.hpp"
#include "Mesh.hpp"
#include "SceneLight.hpp"
#include "SceneCamera.hpp"
#include "ColladaLights.hpp"
#include "ColladaCameras.hpp"
#include "ColladaGeometries.hpp"
#include "ColladaAnimations.hpp"
#include "ColladaControllers.hpp"
#include "ColladaVisualScenes.hpp"
namespace kege{namespace dae{
    
    class Collada : public dae::ColladaLibrary
    {
    public:
        
        gfx::Scenenode* InstanceController(const ds::string& id, kege::XML* instance, kege::XML* node);
        gfx::Scenenode* InstanceGeometry(const ds::string& id, kege::XML* instance, kege::XML* node);
        gfx::Scenenode* InstanceCamera(const ds::string& id, kege::XML* instance, kege::XML* node);
        gfx::Scenenode* InstanceLight(const ds::string& id, kege::XML* instance, kege::XML* node);
        gfx::Scenenode* ConstructScenenode(kege::XML* node);
        
        void GetGeometrySceneObjects(gfx::SceneNodes& nodes);
        void GetCameraSceneObjects(gfx::SceneNodes& nodes);
        void GetLightSceneObjects(gfx::SceneNodes& nodes);
        void GetAllSceneObjects(gfx::SceneNodes& nodes);
        
        gfx::SkeletalAnimation* GetAnimation();
        bool IsLoaded();
        
        Collada(const ds::string& filename);
        
    private:
        
        dae::ColladaControllers controllers;
        dae::ColladaGeometries geometries;
        dae::ColladaAnimations animations;
        dae::ColladaVisualScenes scenes;
        dae::ColladaCameras cameras;
        dae::ColladaLights lights;
        kege::XML collada;
        bool loaded;
    };
}}

#endif /* collada_scene_hpp */

