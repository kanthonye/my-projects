/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/26/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ObjectSystem.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "Mesh.hpp"
#include "Material.hpp"
#include "ObjectMaterial.hpp"
#include "RotationComponent.hpp"
#include "MotionComponent.hpp"
#include "RotationController.hpp"
#include "MotionController.hpp"
#include "MeshComponent.hpp"
#include "Gameobject.hpp"
#include "GenMeshBox.hpp"
#include "PhysicsComponent.hpp"
#include "SceneLight.hpp"
#include "Collada.hpp"

#include "ObjectSystem.hpp"
namespace kege{namespace gfx{
    
    void ObjectSystem::Update(double delta_ms)
    {
    }
    
    void ObjectSystem::UnInit()
    {
        _init = true;
    }
    bool ObjectSystem::Init()
    {
        if ( _init ) return _init;
        
        gfx::SharedMaterialProperty material_property = new MaterialProperty;
        material_property->SetAmbient(cg::vec4(0,0,0,1));
        material_property->SetDiffuse(cg::vec4(0.8, 0.8, 0.8, 1));
        material_property->SetSpecular(cg::vec4(1,1,1,1));
        material_property->SetEmission(cg::vec4(0,0,0,1));
        material_property->SetShininess(0.2);
        material_property->SetDensity(30);
        material_property->SetAlpha(1.0);
        
        gfx::SharedMaterial mtl = new gfx::ObjectMaterial();
        mtl->SetProperty( material_property );
        
        gfx::SharedMesh box = new Mesh;
        gfx::GenMeshBox(*box.rawptr(), cg::vec3(-1.0), cg::vec3(1.0));
        box->Init();

        gfx::Entity* gameobject = new gfx::Entity("comp");
        gameobject->Attach( new gfx::MeshComponent(gfx::SharedMesh(box), mtl) );
        GetScene()->Add(gameobject);
        
        
//        gfx::Gameobject* light1 = GetScene()->Add(new gfx::SceneLight("light-0", cg::point3(-10,20,-5), cg::point3(1), 1.0, 30));
//        light1->GetLocal().scale(0.25, 0.25, 0.25);
        
//        gfx::Gameobject* light2 = GetScene()->Add(new gfx::SceneLight("light-1", cg::point3(0,10,10), cg::point3(1), 1.0, 34));
//        light2->GetLocal().scale(0.25, 0.25, 0.25);
        
//        gfx::Gameobject* light3 = GetScene()->Add(new gfx::SceneLight("light-2", cg::point3(10,20,-20), cg::point3(1), 1.0, 30));
//        light3->GetLocal().scale(0.25, 0.25, 0.25);
        
//        dae::Collada collada("/Users/kanthonye/Projects/boneman_running.dae");
//        if (collada.IsLoaded())
//        {
//            gfx::Gameobjects nodes;
//            collada.GetGeometrySceneObjects(nodes);
//            GetScene()->Add( nodes );
//        }
        _init = true;
        return _init;
    }
    
    ObjectSystem::ObjectSystem()
    :   kege::SubSystem("ObjectSystem")
    {}
}}
