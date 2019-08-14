/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/12/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       SkydomeModel.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#include "GUI.hpp"
#include "myGUI.hpp"
#include "Scene.hpp"

#include "OBJParser.hpp"
#include "RenderingSystem.hpp"

#include "Graphics.hpp"
#include "SkydomeModel.hpp"
namespace kege {namespace gfx{
    
    void SkydomeModel::Draw(gfx::RenderingSystem* renderer)
    {
        if ( _material == nullptr || _mesh == nullptr )
        {
            return;
        }
        
        gfx::Graphics::SetBackgroundColor( colors[1] );
        float skydome_scale = GetParent()->GetScene()->GetCamera()->GetFarView() * 0.95;
        GetParent()->GetLocal().scale( skydome_scale );
        
        _material->Bind();
        _material->GetShader()->SetUBO("SKY", sizeof(cg::vec4)*2, colors);
        _material->GetShader()->SetMat44f( "ModelMatrix",  GetParent()->GetWorldMatrix().data );
        
        _mesh->Bind();
        _mesh->Draw();
        _mesh->Unbind();
        
        _material->Unbind();
    }
    
    bool SkydomeModel::Init(kege::Scene* scene)
    {
        if ( _init == true ) return _init;
        _mesh->Init();
        _material->Init();
        return gfx::RenderComponent::Init( scene );
    }
    
    SkydomeModel::~ SkydomeModel()
    {
    }
    
    SkydomeModel::SkydomeModel()
    :   gfx::MeshComponent("SkydomeModel")
    {
        colors[0] = cg::color( 30,233,255,255); // sky_color
        colors[1] = cg::vec4(0.000,0.264,0.700, 1); // sea_color
        
        _material = new gfx::SkydomeMaterial;
        _mesh = SharedMesh(new gfx::Mesh);
        kege::OBJLoadUnifyMesh( *_mesh.rawptr(), "skydome-uvsphere.obj" );
        
        
//        if (__set__ == false)
//        {
//            cg::GUIView* view = kege::Singleton::Get< cg::GUI >()->GetView("main");
//            view->Add( ColorSlider("sky_color", 10, 100, 0,0,1, sky_color[1].xyz) );
//            view->Add( ColorSlider("fog_color", 10, 100, 0,0,1, fog[0].xyz) );
//            __set__ = true;
//        }
    }
    
}}
