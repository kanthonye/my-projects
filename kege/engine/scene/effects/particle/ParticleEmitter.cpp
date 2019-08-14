//
//  ParticleEmitter.cpp
//  AppDev
//
//  Created by Kenneth Esdaile on 5/16/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//
#include "Scene.hpp"
#include "Gameobject.hpp"
#include "CompDecay.hpp"
#include "Rigidbody2D.hpp"
#include "ParticleEmitter.hpp"
namespace kege{namespace gfx{
    
    bool gfx::ParticleEmitter::Init(kege::Scene* scene)
    {
        return gfx::EntityComponent::Init(scene);
    }
    
    void gfx::ParticleEmitter::HandleMessage( const kege::Message& message )
    {
//        if(message.GetType() == "TIMED_INTERVAL")
//        {
//            if(message.GetDetail() == "timer")
//            {
//                CreateParticles( *(int*)message.GetContent()->GetData() );
//            }
//        }
    }

    void gfx::ParticleEmitter::CreateParticles(cg::ushort total)
    {
        ;
       
        for (int i=0; i<total; i++)
        {
            cg::point3 position = GetSpawnPoint();
            kege::MsgT<cg::vec3> msg("ParticleEmitter", "emit", "vec3", position);
            GetParent()->HandleMessage(msg);
        }
    }
    
    cg::point3 ParticleEmitter::GetSpawnPoint()
    {
        return GetParent()->GetWorld().translation;
    }
    
    void ParticleEmitter::Save(kege::XML& xml)
    {
        //kege::XML *comp = xml.AddChild(new kege::XML("emitter"));
    }
    
    ParticleEmitter::~ ParticleEmitter()
    {}
    
    ParticleEmitter::ParticleEmitter()
    :   gfx::EntityComponent(kege::ENUM::_PARTICLE_EMITTER)
    {}
}}









namespace kege{namespace gfx{
    
    cg::point3 CubicEffexParticleFactory::GetSpawnPoint()
    {
        cg::point3 center = GetParent()->GetWorld().translation;
        return cg::point3
        ( (cg::randf(center.x-width, center.x+width)  * 0.5f),
         (cg::randf(center.y-height, center.y+height) * 0.5f),
         (cg::randf(center.z-depth , center.z+depth)  * 0.5f) );
    };
    CubicEffexParticleFactory::CubicEffexParticleFactory(float w, float h, float d)
    :   width(w)
    ,   height(h)
    ,   depth(d)
    {
        //        velocity.x = cg::rand1f(0,0);
        //        velocity.y = cg::rand1f(0,0);
        //        velocity.z = cg::rand1f(0,0);
        //        size = cg::rand1f(1,1.5);
    }
}}

namespace kege{namespace gfx{
    
    PlaneAreaParticleFactory::PlaneAreaParticleFactory(float w, float h)
    :   width(w)
    ,   height(h)
    {
    }
    cg::point3 PlaneAreaParticleFactory::GetSpawnPoint()
    {
        return cg::point3(cg::randf(-width, width)* 0.5f, 0.0f, cg::randf(-height, height)*0.5f);
    }
}}

namespace kege{namespace gfx{
    
    LinearParticleFactory::LinearParticleFactory(const cg::vec3& r, float l)
    :   ray(r)
    ,   length(l)
    {
    }
    cg::point3 LinearParticleFactory::GetSpawnPoint()
    {
        return cg::point3::zero + ray * cg::randf(0,length);
    }
}}

namespace kege{namespace gfx{
    
    PyrimidParticleFactory::PyrimidParticleFactory(float w, float h, float d)
    :   width(w)
    ,   height(h)
    ,   depth(d)
    {
    }
    cg::point3 PyrimidParticleFactory::GetSpawnPoint()
    {
        float t = cg::randf(0, 1.0f);
        float h = cg::lerp(-height, height, t);
        
        float w = width*t;
        w = cg::randf(-w, w);
        
        float d = depth*t;
        d = cg::randf(-d, d);
        
        return cg::point3(w, h, d);
    }
}}

namespace kege{namespace gfx{
    
    TriangularParticleFactory::TriangularParticleFactory(float h, float b)
    :   height(h)
    ,   base(b)
    {
    }
    cg::point3 TriangularParticleFactory::GetSpawnPoint()
    {
        float t = cg::randf(0, 1.0f);
        float h = cg::lerp(-height, height, t);
        
        float b = base*t;
        b = cg::randf(-b, b);
        
        return cg::point3(b, 0.0, h);
    }
}}

namespace kege{namespace gfx{
    
    CircumEffexParticleFactory::CircumEffexParticleFactory(float r)
    :   radius(r)
    {
    }
    cg::point3 CircumEffexParticleFactory::GetSpawnPoint()
    {
        float radian = cg::randf(0, 6.28f);
        return cg::point3(cosf(radian)*radius, 0, sinf(radian)*radius);
    }
}}

namespace kege{namespace gfx{
    
    CircAreaEffexParticleFactory::CircAreaEffexParticleFactory(float minr, float maxr)
    :   min_radius(minr)
    ,   max_radius(maxr)
    {
    }
    cg::point3 CircAreaEffexParticleFactory::GetSpawnPoint()
    {
        float radian = cg::randf(0, 6.28f);
        float radius = cg::randf(min_radius, max_radius);
        return GetParent()->GetWorld().translation + cg::point3(sinf(radian)*radius, 0.0, cosf(radian)*radius);
    }
}}

namespace kege{namespace gfx{
    
    SphereAreaEffexParticleFactory::SphereAreaEffexParticleFactory(float minr, float maxr)
    :   min_radius(minr)
    ,   max_radius(maxr)
    {
    }
    
    cg::point3 SphereAreaEffexParticleFactory::GetSpawnPoint()
    {
        float radianA = cg::randf(0, 6.28f);
        float radianB = cg::randf(0, 6.28f);
        float radius = cg::randf(min_radius, max_radius);
        float y = sinf(radianB)*radius;
        float r = cosf(radianB)*radius;
        float z = sinf(radianA)*r;
        float x = cosf(radianA)*r;
        return cg::point3(x, y, z) + GetParent()->GetWorld().translation;
    }
}}

namespace kege{namespace gfx{
    
    SphereEffexParticleFactory::SphereEffexParticleFactory(float r)
    :   radius(r)
    {
    }
    cg::point3 SphereEffexParticleFactory::GetSpawnPoint()
    {
        float radianA = cg::randf(0, 6.28f);
        float radianB = cg::randf(0, 6.28f);
        float y = sinf(radianB)*radius;
        float r = cosf(radianB)*radius;
        float z = sinf(radianA)*r;
        float x = cosf(radianA)*r;
        
        return cg::point3(x, y, z) + GetParent()->GetWorld().translation;
    }
}}


namespace kege{namespace gfx{
    
    CylindricVolumeFactory::CylindricVolumeFactory(float h, float minr, float maxr)
    :   height(h)
    ,   min_radius(minr)
    ,   max_radius(maxr)
    {
    }
    cg::point3 CylindricVolumeFactory::GetSpawnPoint()
    {
        float h = cg::randf(0, height);
        float radian = cg::randf(0, 6.28f);
        float radius = cg::randf(min_radius, max_radius);
        float z = sinf(radian)*radius;
        float x = cosf(radian)*radius;
        return cg::point3(x, h, z);
    }
}}

namespace kege{namespace gfx{
    
    CylindricSurfaceFactory::CylindricSurfaceFactory(float h, float r)
    :   height(h)
    ,   radius(r)
    {
    }
    cg::point3 CylindricSurfaceFactory::GetSpawnPoint()
    {
        float radian = cg::randf(0, 6.28f);
        float z = sinf(radian)*radius;
        float x = cosf(radian)*radius;
        float y = cg::randf(0, height);
        return cg::point3(x, y, z);
    }
}}

namespace kege{namespace gfx{
    
    ConeVolumeFactory::ConeVolumeFactory(float h, float minr, float maxr)
    :   height(h)
    ,   x_radius(minr)
    ,   z_radius(maxr)
    {
    }
    cg::point3 ConeVolumeFactory::GetSpawnPoint()
    {
        float t = cg::randf(0, 1.0f);
        float h = cg::lerp(-height, height, t);
        
        float radian = cg::randf(0, 6.28f);
        float z = sinf(radian)*t*z_radius;
        float x = cosf(radian)*t*x_radius;
        return cg::point3(x, h, z);
    }
}}
    




