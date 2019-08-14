//
//  SceneLoader.hpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 2/18/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef SceneLoader_hpp
#define SceneLoader_hpp
#include "xml.hpp"
#include "SceneLight.hpp"
#include "Camera.hpp"
#include "ParticleRenderer.hpp"
#include "CollisionSystem.hpp"
namespace kege{namespace gfx{
    class Scene;
    
//    class LoaderXmlScene :public kege::Loader<gfx::NodeEntity>
//    {
//    public:
//
//        gfx::NodeEntity* Load(kege::ResourceManager* manager, const ds::string& filename);
//        static bool Load(kege::Scene* scene, const ds::string& filename);
//        LoaderXmlScene();
//    };
    
//    void Save(kege::XML& p_xml, gfx::NodeEntity& root);
}}
#endif /* SceneLoader_hpp */
