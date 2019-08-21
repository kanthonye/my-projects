/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/17/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Sun.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#include "GUI.hpp"
#include "myGUI.hpp"
#include "Singleton.hpp"


#include "SunObject.hpp"
#include "Scene.hpp"
#include "Graphics.hpp"
namespace kege {namespace gfx{
    
    bool SunObject::Init(kege::Scene* scene)
    {
        if ( _init ) return _init;
        
        sun[0].xyz = cg::color(255, 250, 245);
        sun[1].xyz = cg::color(255, 245, 200);
        sun[2].xyz = cg::normalize3(cg::vec3(0.0, 0.0, 1.0));
        sun[0].w = 60;
        sun[1].w = 1.0;
        sun[2].w = 0.0;
        
        material = new SkydomeMaterial;
        material->GetShader()->SetUBO("SUN", 3*sizeof(cg::vec4), sun);
        cg::GUIView* view = kege::Singleton::Get< cg::GUI >()->GetView("main");
        view->Add( ColorSlider("sun_dir", 10, 100, 0,0,360, rotation) );
        view->Add( ColorSlider("glow-color", 10, 100, 0,0,1, sun[1].xyz) );
        view->Add( ColorSlider("sun-color", 10, 100, 0,0,1, sun[0].xyz) );
        
        return gfx::Entity::Init(scene);
    }
    
    void SunObject::Update(double delta)
    {
        gfx::Entity::Update( delta );
        
        float cosPitch = cos( cg::deg2rad(rotation.y) );
        float sinPitch = sin( cg::deg2rad(rotation.y) );
        float cosYaw = cos( cg::deg2rad(rotation.x) );
        float sinYaw = sin( cg::deg2rad(rotation.x) );
        sun[2].xyz = cg::vec3( cosPitch * sinYaw, sinPitch, cosPitch * cosYaw );

        if (material != nullptr)
        {
            material->GetShader()->SetUBO("SUN", 3*sizeof(cg::vec4), sun);
        }
    }
    
    void SunObject::UnInit()
    {
        ubo = nullptr;
    }
    SunObject::~ SunObject()
    {
    }
}}
