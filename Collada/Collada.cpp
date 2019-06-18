//======================================================================
//  Author  : Kenneth A Esdaile
//  Date    : Created on 4/14/19.
//  Title   : Collada.cpp
//  Project : KEGE
//======================================================================
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//======================================================================
#include "Collada.hpp"
namespace kege{namespace dae{
    
    gfx::Scenenode* Collada::InstanceCamera(const ds::string& id, kege::XML* instance, kege::XML* node)
    {
        ds::string url = RemoveHashtag(instance->GetAttr("url")->value);
        return new gfx::SceneCamera(id, cameras.InstanceCamera(url), scenes.GetTransform(node));
    }
    
    gfx::Scenenode* Collada::InstanceController(const ds::string& id, kege::XML* instance, kege::XML* node)
    {
        ds::string url = RemoveHashtag(instance->GetAttr("url")->value);
        ds::string sid = RemoveHashtag(instance->GetChild("skeleton")->GetText());
        gfx::Mesh mesh = controllers.InstanceController(url, geometries);
        gfx::Skeleton* skeleton = controllers.BuildSkeleton(instance, scenes);
        gfx::Entity* entity =  new gfx::Entity(id, mesh, scenes.GetTransform(node), skeleton);
        //skeleton->BindSkeletion();
        entity->Attach(new gfx::SkeletalAnimator(skeleton, GetAnimation()));
        return entity;
    }

    gfx::Scenenode* Collada::InstanceGeometry(const ds::string& id, kege::XML* instance, kege::XML* node)
    {
        ds::string url = RemoveHashtag(instance->GetAttr("url")->value);
        return new gfx::Entity(id, geometries.InstanceGeometry(url), scenes.GetTransform(node));
    }

    gfx::Scenenode* Collada::InstanceLight(const ds::string& id, kege::XML* instance, kege::XML* node)
    {
        ds::string url = RemoveHashtag(instance->GetAttr("url")->value);
        return new gfx::SceneLight(id, lights.InstanceLight(url), scenes.GetTransform(node));
    }
    
    gfx::Scenenode* Collada::ConstructScenenode(kege::XML* node)
    {
        kege::XML* instance = node->GetChildLike("instance_");
        kege::XML::attrib* id = node->GetAttr("id");
        
        if (instance != nullptr)
        {
            if (instance->GetName() == "instance_camera")
            {
                return InstanceCamera(id->value, instance, node);
            }
            else if (instance->GetName() == "instance_light")
            {
                return InstanceLight(id->value, instance, node);
            }
            else if (instance->GetName() == "instance_geometry")
            {
                return InstanceGeometry(id->value, instance, node);
            }
            else if (instance->GetName() == "instance_controller")
            {
                return InstanceController(id->value, instance, node);
            }
        }
        return nullptr;
    }
    
    void Collada::GetGeometrySceneObjects(gfx::SceneNodes& nodes)
    {
        kege::XML* scene = collada.GetChild("/COLLADA/library_visual_scenes/visual_scene");
        if (scene == nullptr) return;
        
        kege::XML* instance = nullptr;
        kege::XML::attrib *id = nullptr;
        gfx::Scenenode* obj =  nullptr;
        for (kege::XML::list::iterator i=scene->Begin(); i!=nullptr; i++)
        {
            if (i->GetName() != "node") continue;
            
            id = i->GetAttr("id");
            instance = i->GetChildLike("instance_geometry");
            if (instance != nullptr)
            {
                obj = InstanceGeometry(id->value, instance, i.element());
                if (obj != nullptr) nodes.push_back(obj);
                continue;
            }
            
            instance = i->GetChildLike("instance_controller");
            if (instance != nullptr)
            {
                obj = InstanceController(id->value, instance, i.element());
                if (obj != nullptr) nodes.push_back(obj);
            }
        }
    }
    
    void Collada::GetCameraSceneObjects(gfx::SceneNodes& nodes)
    {
        kege::XML* scene = collada.GetChild("/COLLADA/library_visual_scenes/visual_scene");
        if (scene == nullptr) return;
        
        kege::XML* instance = nullptr;
        kege::XML::attrib *id = nullptr;
        gfx::Scenenode* obj = nullptr;
        for (kege::XML::list::iterator i=scene->Begin(); i!=nullptr; i++)
        {
            if (i->GetName() != "node") continue;
            instance = i->GetChild("instance_camera");
            if (instance != nullptr)
            {
                obj = InstanceCamera(id->value, instance, i.element());
                if (obj != nullptr) nodes.push_back(obj);
            }
        }
    }
    
    void Collada::GetLightSceneObjects(gfx::SceneNodes& nodes)
    {
        kege::XML* scene = collada.GetChild("/COLLADA/library_visual_scenes/visual_scene");
        if (scene == nullptr) return;
        
        kege::XML* instance = nullptr;
        kege::XML::attrib *id = nullptr;
        gfx::Scenenode* obj = nullptr;
        for (kege::XML::list::iterator i=scene->Begin(); i!=nullptr; i++)
        {
            if (i->GetName() != "node") continue;
            instance = i->GetChild("instance_camera");
            if (instance != nullptr)
            {
                obj = InstanceLight(id->value, instance, i.element());
                if (obj != nullptr) nodes.push_back(obj);
            }
        }
    }
    
    void Collada::GetAllSceneObjects(gfx::SceneNodes& nodes)
    {
        kege::XML* visual_scene = collada.GetChild("/COLLADA/library_visual_scenes/visual_scene");
        if (visual_scene == nullptr) return;
        
        for (kege::XML::list::iterator i=visual_scene->Begin(); i!=nullptr; i++)
        {
            if (i->GetName() != "node") continue;
            
            gfx::Scenenode* node = ConstructScenenode(i.element());
            if (node != nullptr) nodes.push_back(node);
        }
    }
    
    gfx::SkeletalAnimation* Collada::GetAnimation()
    {
        return animations.GetAnimation();
    }
    
    bool Collada::IsLoaded()
    {
        return loaded;
    }
    
    Collada::Collada(const ds::string& filename)
    :   loaded(false)
    ,   geometries(nullptr)
    ,   animations(nullptr)
    ,   controllers(nullptr)
    ,   scenes(nullptr)
    ,   lights(nullptr)
    ,   cameras(nullptr)
    {
        loaded = collada.Load(filename);
        if (loaded == false) return;
        geometries = dae::ColladaGeometries(collada.GetChild("/COLLADA/library_geometries"));
        controllers = dae::ColladaControllers(collada.GetChild("/COLLADA/library_controllers"));
        animations = dae::ColladaAnimations(collada.GetChild("/COLLADA/library_animations"));
        scenes = dae::ColladaVisualScenes(collada.GetChild("/COLLADA/library_visual_scenes"));
        lights = dae::ColladaLights(collada.GetChild("/COLLADA/library_lights"));
        cameras = dae::ColladaCameras(collada.GetChild("/COLLADA/library_cameras"));
    }
}}
