//
//  ParticleGenerator.hpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/22/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef ParticleGenerator_hpp
#define ParticleGenerator_hpp
#include "Mesh.hpp"
#include "Component.hpp"
#include "ForceDriver.hpp"
namespace kege{namespace gfx{
    
    /**
     * ParticleEmitter handles where particles are spawn. Different emitters
     * can spawn particles in different ways. for instance partices can be spawn
     * from a point, on a line, in a circular line, or sphere, cube, cone etc.
     * ParticleEmitter tells the Particle factory where to create a particle.
     */
    class ParticleGenerator : public gfx::Component
    {
    public:
        
        void SetSaturationGen(cg::rand1f const& gen);
        cg::rand1f const& GetSaturationGen()const;
        cg::rand1f & GetSaturationGen();
        
        void SetVelocityGen(cg::rand3f const& gen);
        cg::rand3f  const& GetVelocityGen()const;
        cg::rand3f  & GetVelocityGen();
        
        void SetSpeedGen(cg::rand1f const& gen);
        cg::rand1f const& GetSpeedGen()const;
        cg::rand1f & GetSpeedGen();
        
        void SetColorGen(cg::rand4f const& gen);
        cg::rand4f  const& GetColorGen()const;
        cg::rand4f  & GetColorGen();
        
        void SetMassGen(cg::rand1f const& gen);
        cg::rand1f const& GetMassGen()const;
        cg::rand1f & GetMassGen();
        
        void SetSizeGen(cg::rand1f const& gen);
        cg::rand1f const& GetSizeGen()const;
        cg::rand1f & GetSizeGen();
        
        void SetLifeGen(cg::rand1f const& gen);
        cg::rand1f const& GetLifeGen()const;
        cg::rand1f & GetLifeGen();
        
        cg::vec3 GenVelocity()const;
        cg::vec4 GenColor()const;
        
        void HandleMessage( const kege::Message& message );
        void Generate(const cg::point3& pos);
        
        bool Init(kege::Scene* scene);
        
        void Save(kege::XML& xml);
        
        ParticleGenerator(const gfx::Mesh& m);
        ~ ParticleGenerator();
        ParticleGenerator();
        
    private:
        
        phx::ForceDriver driver;
        gfx::Mesh mesh;
        
        cg::rand1f saturation;
        cg::rand3f velocity;
        cg::rand4f color;
        cg::rand1f speed;
        cg::rand1f mass;
        cg::rand1f size;
        cg::rand1f life;
        float decay;
    };
}}

#endif /* ParticleGenerator_hpp */
