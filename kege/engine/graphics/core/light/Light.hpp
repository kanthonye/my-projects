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
#include "array.hpp"
#include "Component.hpp"
namespace kege {namespace gfx{
    
    class DirectionLight
    {
    public:
        
        cg::vec4 color;      //  'xyz' store the color. 'w' store the intensity
        cg::vec3 direction;
    };
    
    class PointLight
    {
    public:
        
        cg::vec4 position;   //  'xyz' store the position. 'w' store the radius
        cg::vec4 color;      //  'xyz' store the color.    'w' store the intensity
    };
    
    class SpotLight
    {
    public:
        
        cg::vec4 position;   //  'xyz' store the position.  'w' store the radius
        cg::vec4 color;      //  'xyz' store the color.     'w' store the intensity
        cg::vec4 direction;  //  'xyz' store the direction. 'w' store the ambience
        float    exponent;
        float    cosine;
    };
    
    
    class Light : public gfx::Component
    {
    public:
        class Data
        {
        public:
            
            cg::vec3 position;   //  'xyz' store the position.  'w' store the radius
            cg::vec3 color;      //  'xyz' store the color.     'w' store the intensity
            float    intensity;
            float    radius;
        };
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
        
        Data data;
    };
    
    typedef ds::array< gfx::Light::Data > ArrayLights;
}}
#endif /* Light_hpp */
