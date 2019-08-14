//
//  ParticleEmitter.hpp
//  AppDev
//
//  Created by Kenneth Esdaile on 5/16/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef ParticleEmitter_hpp
#define ParticleEmitter_hpp
#include "EntityComponent.hpp"
#include "ForceDriver.hpp"
//#include "TiledTexture2D.hpp"
namespace kege{namespace gfx{
    
    /**
     * ParticleEmitter handles where particles are spawn. Different emitters
     * can spawn particles in different ways. for instance partices can be spawn
     * from a point, on a line, in a circular line, or sphere, cube, cone etc.
     * ParticleEmitter tells the Particle factory where to create a particle.
     */
    class ParticleEmitter : public gfx::EntityComponent
    {
    public:
        
        bool Init(kege::Scene* scene);
        
        void HandleMessage(const kege::Message& message);
        void CreateParticles(cg::ushort total);
        cg::point3 GetSpawnPoint();
        
        void Save(kege::XML& xml);
        ~ ParticleEmitter();
        ParticleEmitter();
    };
}}


namespace kege{namespace gfx{
    
    class CubicEffexParticleFactory : public ParticleEmitter
    {
    public:
        CubicEffexParticleFactory(float width, float height, float depth);
        cg::point3 GetSpawnPoint();
        
        void SetHeight(float len) {height = len;}
        void SetWidth(float len) {width = len;}
        void SetDepth(float len) {depth = len;}
        float GetHeight() {return height;}
        float GetWidth() {return width;}
        float GetDepth() {return depth;}
    private:
        float width, height, depth;
    };
}}

namespace kege{namespace gfx{
    
    class PlaneAreaParticleFactory : public ParticleEmitter
    {
    public:
        PlaneAreaParticleFactory(float width, float height);
        cg::point3 GetSpawnPoint();
        
        void SetHeight(float len) {height = len;}
        void SetWidth(float len) {width = len;}
        float GetHeight() {return height;}
        float GetWidth() {return width;}
    private:
        float width, height;
    };
}}

namespace kege{namespace gfx{
    
    class LinearParticleFactory : public ParticleEmitter
    {
    public:
        LinearParticleFactory(const cg::vec3& ray, float length);
        cg::point3 GetSpawnPoint();
        
        void SetRay(const cg::vec3& r) {ray = r;}
        cg::vec3& GetRay() {return ray;}
        void SetLength(const float l) {length = l;}
        float GetLength() {return length;}
    private:
        cg::vec3 ray;
        float length;
    };
}}

namespace kege{namespace gfx{
    
    class PyrimidParticleFactory : public ParticleEmitter
    {
    public:
        PyrimidParticleFactory(float width, float height, float depth);
        cg::point3 GetSpawnPoint();
        
        void SetHeight(float len) {height = len;}
        void SetWidth(float len) {width = len;}
        void SetDepth(float len) {depth = len;}
        float GetHeight() {return height;}
        float GetWidth() {return width;}
        float GetDepth() {return depth;}
    private:
        float width, height, depth;
    };
}}

namespace kege{namespace gfx{
    
    class TriangularParticleFactory : public ParticleEmitter
    {
    public:
        TriangularParticleFactory(float height, float base);
        cg::point3 GetSpawnPoint();
        
        void SetHeight(float len) {height = len;}
        void SetBase(float h) {base = h;}
        float GetHeight() {return height;}
        float GetBase() {return base;}
    private:
        float height, base;
    };
}}

namespace kege{namespace gfx{
    
    class CircumEffexParticleFactory : public ParticleEmitter
    {
    public:
        CircumEffexParticleFactory(float radius);
        cg::point3 GetSpawnPoint();
        
        void SetRadius(float len) {radius = len;}
        float GetRadius() {return radius;}
    private:
        float radius;
    };
}}

namespace kege{namespace gfx{
    
    class CircAreaEffexParticleFactory : public ParticleEmitter
    {
    public:
        CircAreaEffexParticleFactory(float min_radius, float max_radius);
        cg::point3 GetSpawnPoint();
        
        void SetMinRadius(float len) {min_radius = len;}
        void SetMaxRadius(float len) {max_radius = len;}
        float GetMinRadius() {return min_radius;}
        float GetMaxRadius() {return max_radius;}
    private:
        float min_radius, max_radius;
    };
}}

namespace kege{namespace gfx{
    
    class SphereAreaEffexParticleFactory : public ParticleEmitter
    {
    public:
        SphereAreaEffexParticleFactory(float min_radius, float max_radius);
        cg::point3 GetSpawnPoint();
        
        void SetMinRadius(float len) {min_radius = len;}
        void SetMaxRadius(float len) {max_radius = len;}
        float GetMinRadius() {return min_radius;}
        float GetMaxRadius() {return max_radius;}
    private:
        float min_radius, max_radius;
    };
}}

namespace kege{namespace gfx{
    
    class SphereEffexParticleFactory : public ParticleEmitter
    {
    public:
        SphereEffexParticleFactory(float radius);
        cg::point3 GetSpawnPoint();
        
        void SetRadius(float len) {radius = len;}
        float GetRadius() {return radius;}
    private:
        float radius;
    };
}}

namespace kege{namespace gfx{
    
    class CylindricVolumeFactory : public ParticleEmitter
    {
    public:
        CylindricVolumeFactory(float height, float min_radius, float max_radius);
        cg::point3 GetSpawnPoint();
        
        void SetMinRadius(float len) {min_radius = len;}
        void SetMaxRadius(float len) {max_radius = len;}
        float GetMinRadius() {return min_radius;}
        float GetMaxRadius() {return max_radius;}
        void SetHeight(float len) {height = len;}
        float GetHeight() {return height;}
    private:
        float height, min_radius, max_radius;
    };
}}


namespace kege{namespace gfx{
    
    class CylindricSurfaceFactory : public ParticleEmitter
    {
    public:
        CylindricSurfaceFactory(float height, float radius);
        cg::point3 GetSpawnPoint();
        
        void SetRadius(float len) {radius = len;}
        float GetRadius() {return radius;}
        void SetHeight(float len) {height = len;}
        float GetHeight() {return height;}
    private:
        float height, radius;
    };
}}


namespace kege{namespace gfx{
    
    class ConeVolumeFactory : public ParticleEmitter
    {
    public:
        ConeVolumeFactory(float height, float min_radius, float max_radius);
        cg::point3 GetSpawnPoint();
        
        void SetXRadius(float len) {x_radius = len;}
        void SetZRadius(float len) {z_radius = len;}
        float GetXRadius() {return x_radius;}
        float GetZRadius() {return z_radius;}
        void SetHeight(float len) {height = len;}
        float GetHeight() {return height;}
    private:
        float height, x_radius, z_radius;
    };
}}


#endif /* ParticleEmitter_hpp */
