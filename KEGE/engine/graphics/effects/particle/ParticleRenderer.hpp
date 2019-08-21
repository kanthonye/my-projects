//
//  ParticleRenderer.hpp
//  dev0
//
//  Created by Kenneth A Esdaile on 5/30/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef ParticleRenderer_hpp
#define ParticleRenderer_hpp
#include "Mesh.hpp"
#include "Texture2D.hpp"
namespace kege {namespace gfx{
    
    class ParticleRenderer
    {
    public:
        
        bool Draw(const cg::point3& pos, float w,float h, const cg::vec4& colr, const cg::vec4& img0, const cg::vec4& img1, float mix);
        void Flush();
        
        //ds::dlist<ParticleElement> graphics;
        
        bool Init();
        ~ ParticleRenderer();
        ParticleRenderer();
        
    private:
        
        struct ParticleElement
        {
            cg::vec4 posi;
            cg::vec4 colr;
            cg::vec4 img0;
            cg::vec4 img1;
            cg::vec4 rect;
        };
        
    private:
        
        ds::array<ParticleElement> graphics;
        core::Texture2D* texture;
        unsigned int elements;
        unsigned int stride;
        gfx::Mesh mesh;
        bool init;
    };
}}
#endif /* ParticleRenderer_hpp */
