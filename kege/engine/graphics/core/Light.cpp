//
//  Light.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/14/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#include "Light.hpp"
namespace kege {namespace gfx{
    
    
    const int Light::GetLightDataSize()const
    {
        return sizeof(Data);
    }
    const gfx::Light::Data& Light::GetLightData()const
    {
        return data;
    }
    
    gfx::Light::Data& Light::GetLightData()
    {
        return data;
    }
    
    void Light::SetPosition(const cg::vec3& position)
    {
        data.position = position;
    }
    const cg::vec3& Light::GetPosition()const
    {
        return data.position;
    }
    cg::vec3& Light::GetPosition()
    {
        return data.position;
    }
    
    void Light::SetColor(const cg::vec3& color)
    {
        data.color = color;
    }
    const cg::vec3& Light::GetColor()const
    {
        return data.color;
    }
    cg::vec3& Light::GetColor()
    {
        return data.color;
    }
    
    void Light::SetIntensity(float intensity)
    {
        data.intensity = intensity;
    }
    float Light::GetIntensity()const
    {
        return data.intensity;
    }
    
    void Light::SetRadius(float radius)
    {
        data.radius = radius;
    }
    float Light::GetRadius()const
    {
        return data.radius;
    }
    
    void Light::SetPointLight // point light
    (   const cg::point3& position
     ,  const cg::point3 &color
     ,  float intensity
     ,  float radius )
    {
        SetPosition(position);
        SetColor(color);
        SetIntensity(intensity);
        SetRadius(radius);
    }
    
    Light::Light // point light
    (   const cg::point3& position
     ,  const cg::point3 &color
     ,  float intensity
     ,  float radius )
    {
        SetPointLight(position, color, intensity, radius);
    }
    
    Light::Light()
    {
        SetPointLight(0.0f, 1.0, 1.0, 10.0);
    }
}}
