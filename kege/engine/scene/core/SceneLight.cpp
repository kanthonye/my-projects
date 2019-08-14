//
//  SceneLight.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/15/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//
#include "Scene.hpp"
#include "SceneLight.hpp"
namespace kege {namespace gfx{
    
    void SceneLight::GetRenderables( kege::SceneFrame& frame )
    {
        gfx::Gameobject::GetRenderables(frame);
    }
    
    void SceneLight::Update(double delta_ms)
    {
        gfx::Gameobject::Update(delta_ms);
        light.SetPosition(GetWorld().translation);
    }
    
//    void SceneLight::SaveComponent(kege::XML& xml)
//    {
//        gfx::Gameobject::SaveComponent(xml);
//
//        kege::XML* comp = xml.AddChild(new kege::XML);
//        comp->SetName("light");
//
//        kege::XML* elem = comp->AddChild(new kege::XML);
//        elem->SetName("color");
//        elem->GetText() = ds::string::strprint("%f %f %f", light.GetColor().x, light.GetColor().y, light.GetColor().z);
//
//        elem = comp->AddChild(new kege::XML);
//        elem->SetName("intensity");
//        elem->GetText() = ds::string::strprint("%f", light.GetIntensity());
//
//        elem = comp->AddChild(new kege::XML);
//        elem->SetName("radius");
//        elem->GetText() = ds::string::strprint("%f", light.GetRadius());
//    }
    
    const gfx::Light* SceneLight::GetLight()const
    {
        return &light;
    }
    
    gfx::Light* SceneLight::GetLight()
    {
        return &light;
    }
    
    SceneLight::SceneLight 
    (   const ds::string& name
     ,  const cg::point3& position
     ,  const cg::point3 &color
     ,  float intensity
     ,  float radius )
    :   gfx::Gameobject(gfx::Gameobject::LIGHT, name)
    ,   light(position, color, intensity, radius)
    {
        GetLocal().translation = position;
        SetRadius(radius);
    }
    
    SceneLight::SceneLight(const ds::string& name, const gfx::Light& light, const gfx::Transform& transform)
    :   gfx::Gameobject(gfx::Gameobject::LIGHT, name, transform)
    {
        SetRadius(light.GetRadius());
    }
    
    SceneLight::SceneLight(const ds::string& name)
    :   gfx::Gameobject(gfx::Gameobject::LIGHT, name)
    {
    }
    
    SceneLight::SceneLight()
    :   gfx::Gameobject(gfx::Gameobject::LIGHT)
    {
    }
}}
