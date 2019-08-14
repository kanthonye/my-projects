//
//  Light.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/14/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp
#include "cgm.hpp"
namespace kege {namespace gfx{
    
    class DirectionLight
    {
    public:
        
        
        /*
         * direction.xyz : is the direction of the light
         * use for diretional lights and spot lights
         */
        cg::vec3 direction;
        
        /*
         * color.rgb : is the color the light emits.
         * color.a   : is the intensity, the energy that the light emits.
         */
        cg::vec4 color;
        
        float    intensity;
    };
    
    class PointLight
    {
    public:
        /*
         * position.xyz : is the position of the light
         * position.w   : is the radius the light is visible in
         */
        cg::vec4 position;
        
        /*
         * color.rgb : is the color the light emits.
         * color.a   : is the intensity, the energy that the light emits.
         */
        cg::vec4 color;
        
        float    intensity;
        float    radius;
    };
    
    class SpotLight
    {
    public:
        
        /*
         * direction.xyz : is the direction of the light
         * use for diretional lights and spot lights
         * direction.a : is boolean tells shader if light is directional
         */
        cg::vec4 direction;
        /*
         * position.xyz : is the position of the light
         * position.w   : is the radius the light is visible in
         */
        cg::vec4 position;
        
        /*
         * color.rgb : is the color the light emits.
         * color.a   : is the intensity, the energy that the light emits.
         */
        cg::vec4 color;
        
        float    intensity;
        float    radius;
        
        float    exponent;
        float    cosine;
    };
    
    
    class Light
    {
    public:
        
        struct Data
        {
            cg::vec3 color;
            float    intensity;
            cg::vec3 position;
            float    radius;
        } data;
        
    public:
        
        const int GetLightDataSize()const;
        const gfx::Light::Data& GetLightData()const;
        gfx::Light::Data& GetLightData();
        
        void SetPosition(const cg::vec3& position);
        const cg::vec3& GetPosition()const;
        cg::vec3& GetPosition();
        
        void SetColor(const cg::vec3& color);
        const cg::vec3& GetColor()const;
        cg::vec3& GetColor();
        
        void SetIntensity(float intensity);
        float GetIntensity()const;
        
        void SetRadius(float intensity);
        float GetRadius()const;
        
        void SetPointLight // point light
        (   const cg::point3& position
         ,  const cg::point3 &color
         ,  float intensity
         ,  float radius );
        
        Light // point light
        (   const cg::point3& position
         ,  const cg::point3 &color
         ,  float intensity
         ,  float radius );
        
        Light();
    };
}}
#endif /* Light_hpp */
