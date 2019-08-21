//
//  ParticleGenerator.cpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/22/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//
#include "Scene.hpp"
#include "Gameobject.hpp"
#include "CompDecay.hpp"
#include "Rigidbody2D.hpp"
#include "ParticleGenerator.hpp"
namespace kege{namespace gfx{
    
    void ParticleGenerator::SetMassGen(cg::rand1f const& gen)
    {
        mass = gen;
    }
    cg::rand1f const& ParticleGenerator::GetMassGen()const
    {
        return mass;
    }
    cg::rand1f & ParticleGenerator::GetMassGen()
    {
        return mass;
    }
    
    void ParticleGenerator::SetSizeGen(cg::rand1f const& gen)
    {
        size = gen;
    }
    cg::rand1f const& ParticleGenerator::GetSizeGen()const
    {
        return size;
    }
    cg::rand1f & ParticleGenerator::GetSizeGen()
    {
        return size;
    }
    
    void ParticleGenerator::SetLifeGen(cg::rand1f const& gen)
    {
        life = gen;
    }
    cg::rand1f const& ParticleGenerator::GetLifeGen()const
    {
        return life;
    }
    cg::rand1f & ParticleGenerator::GetLifeGen()
    {
        return life;
    }
    
    void ParticleGenerator::SetSaturationGen(cg::rand1f const& gen)
    {
        saturation = gen;
    }
    cg::rand1f const& ParticleGenerator::GetSaturationGen()const
    {
        return saturation;
    }
    cg::rand1f & ParticleGenerator::GetSaturationGen()
    {
        return saturation;
    }
    
    void ParticleGenerator::SetVelocityGen(cg::rand3f const& gen)
    {
        velocity = gen;
    }
    cg::rand3f const& ParticleGenerator::GetVelocityGen()const
    {
        return velocity;
    }
    cg::rand3f & ParticleGenerator::GetVelocityGen()
    {
        return velocity;
    }
    
    void ParticleGenerator::SetSpeedGen(cg::rand1f const& gen)
    {
        speed = gen;
    }
    cg::rand1f const& ParticleGenerator::GetSpeedGen()const
    {
        return speed;
    }
    cg::rand1f & ParticleGenerator::GetSpeedGen()
    {
        return speed;
    }
    
    void ParticleGenerator::SetColorGen(cg::rand4f const& gen)
    {
        color = gen;
    }
    cg::rand4f const& ParticleGenerator::GetColorGen()const
    {
        return color;
    }
    cg::rand4f & ParticleGenerator::GetColorGen()
    {
        return color;
    }
    
    cg::vec3 ParticleGenerator::GenVelocity()const
    {
        return velocity.gen() * speed.gen();
    }
    cg::vec4 ParticleGenerator::GenColor()const
    {
        float saturate = saturation.gen();
        return cg::vec4
        (   color.x.gen() * saturate + (1 - saturate)
         ,  color.y.gen() * saturate + (1 - saturate)
         ,  color.z.gen() * saturate + (1 - saturate)
         ,  color.w.gen() );
    }
    
    void gfx::ParticleGenerator::HandleMessage( const kege::Message& message )
    {
        // ?!!!: update lines
//        if(message.GetDataType() == kege::ENUM::_VEC3)
//        {
//            if(message.GetDetail() == "emit")
//            {
//                Generate( *((cg::vec3*)message.GetMsgData()) );
//                return true;
//            }
//        }
    }
    
    bool gfx::ParticleGenerator::Init(kege::Scene* scene)
    {
        return gfx::Component::Init(scene);
    }
    
    void ParticleGenerator::Generate(const cg::point3& pos)
    {
        if (GetScene() == nullptr) return;
        // EPG3D - EntityParticleGenerator3D
        //gfx::Entity* particle = _scene->CreateEntity("", model);
//        particle->SetRadius(size.gen());
//        particle->GetLocal().translation = pos;
//        particle->GetLocal().scale = particle->GetRadius();
//        
//        particle->Attach(new gfx::CompDecay(life.gen(), 0.01));
//        
//        phx::Rigidbody2D* body = new phx::Rigidbody2D;
//        body->SetLinearVelocity(GenVelocity());
//        body->SetMass(mass.gen());
//        body->SetPosition(pos);
//        particle->Attach(body);
//        
//        particle->Init(*_scene);
    }
    
    
    void ParticleGenerator::Save(kege::XML& xml)
    {
        kege::XML *a = nullptr, *v = nullptr, *elem = nullptr, *comp = xml.AddChild(new kege::XML("particle_generator"));
        
        elem = comp->AddChild(new kege::XML("saturation"));
        a = elem->AddChild(new kege::XML("rand1f"));
        a->AddAttr(new XML::attrib("min", ds::string::strprint("%f", saturation.min)));
        a->AddAttr(new XML::attrib("max", ds::string::strprint("%f", saturation.max)));
        
        elem = comp->AddChild(new kege::XML("speed"));
        a = elem->AddChild(new kege::XML("rand1f"));
        a->AddAttr(new XML::attrib("min", ds::string::strprint("%f", speed.min)));
        a->AddAttr(new XML::attrib("max", ds::string::strprint("%f", speed.max)));
        
        elem = comp->AddChild(new kege::XML("mass"));
        a = elem->AddChild(new kege::XML("rand1f"));
        a->AddAttr(new XML::attrib("min", ds::string::strprint("%f", mass.min)));
        a->AddAttr(new XML::attrib("max", ds::string::strprint("%f", mass.max)));
        
        elem = comp->AddChild(new kege::XML("size"));
        a = elem->AddChild(new kege::XML("rand1f"));
        a->AddAttr(new XML::attrib("min", ds::string::strprint("%f", size.min)));
        a->AddAttr(new XML::attrib("max", ds::string::strprint("%f", size.max)));
        
        elem = comp->AddChild(new kege::XML("life"));
        a = elem->AddChild(new kege::XML("rand1f"));
        a->AddAttr(new XML::attrib("min", ds::string::strprint("%f", life.min)));
        a->AddAttr(new XML::attrib("max", ds::string::strprint("%f", life.max)));
        
        elem = comp->AddChild(new kege::XML("velocity"));
        {
            v = elem->AddChild(new kege::XML("rand3f"));
            {
                a = v->AddChild(new kege::XML("rand1f"));
                a->AddAttr(new XML::attrib("min", ds::string::strprint("%f", velocity.x.min)));
                a->AddAttr(new XML::attrib("max", ds::string::strprint("%f", velocity.x.max)));
                
                a = v->AddChild(new kege::XML("rand1f"));
                a->AddAttr(new XML::attrib("min", ds::string::strprint("%f", velocity.y.min)));
                a->AddAttr(new XML::attrib("max", ds::string::strprint("%f", velocity.y.max)));
                
                a = v->AddChild(new kege::XML("rand1f"));
                a->AddAttr(new XML::attrib("min", ds::string::strprint("%f", velocity.z.min)));
                a->AddAttr(new XML::attrib("max", ds::string::strprint("%f", velocity.z.max)));
            }
        }
        
        elem = comp->AddChild(new kege::XML("color"));
        {
            v = elem->AddChild(new kege::XML("rand4f"));
            {
                a = v->AddChild(new kege::XML("rand1f"));
                a->AddAttr(new XML::attrib("min", ds::string::strprint("%f", color.x.min)));
                a->AddAttr(new XML::attrib("max", ds::string::strprint("%f", color.x.max)));
                
                a = v->AddChild(new kege::XML("rand1f"));
                a->AddAttr(new XML::attrib("min", ds::string::strprint("%f", color.y.min)));
                a->AddAttr(new XML::attrib("max", ds::string::strprint("%f", color.y.max)));
                
                a = v->AddChild(new kege::XML("rand1f"));
                a->AddAttr(new XML::attrib("min", ds::string::strprint("%f", color.z.min)));
                a->AddAttr(new XML::attrib("max", ds::string::strprint("%f", color.z.max)));
                
                a = v->AddChild(new kege::XML("rand1f"));
                a->AddAttr(new XML::attrib("min", ds::string::strprint("%f", color.w.min)));
                a->AddAttr(new XML::attrib("max", ds::string::strprint("%f", color.w.max)));
            }
        }
    }
    
    ParticleGenerator::ParticleGenerator(const gfx::Mesh& m)
    :   gfx::Component(kege::ENUM::_PARTICLE_GENERATOR)
    ,   mesh()
    ,   saturation(0.0, 1.0)
    ,   velocity(cg::rand1f(-0.5,0.5), cg::rand1f(0.0,0.5), cg::rand1f(-0.5,0.5))
    ,   color(cg::rand1f(0.0,1.0), cg::rand1f(0.0,1.0), cg::rand1f(0.0,1.0), cg::rand1f(0.0,1.0))
    ,   speed(0.5, 2.0)
    ,   mass(1, 3)
    ,   size(0.1, 0.3)
    ,   life(0.1, 0.3)
    {}
    
    ParticleGenerator::~ ParticleGenerator()
    {}
    
    ParticleGenerator::ParticleGenerator()
    :   gfx::Component(kege::ENUM::_PARTICLE_GENERATOR)
    ,   mesh()
    ,   saturation(0.0, 1.0)
    ,   velocity(cg::rand1f(-0.5,0.5), cg::rand1f(0.0,0.5), cg::rand1f(-0.5,0.5))
    ,   color(cg::rand1f(0.0,1.0), cg::rand1f(0.0,1.0), cg::rand1f(0.0,1.0), cg::rand1f(0.0,1.0))
    ,   speed(0.5, 2.0)
    ,   mass(1, 3)
    ,   size(0.1, 0.3)
    ,   life(0.1, 0.3)
    {}
}}
