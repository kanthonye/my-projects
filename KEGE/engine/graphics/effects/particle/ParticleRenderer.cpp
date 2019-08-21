//
//  ParticleRenderer.cpp
//  dev0
//
//  Created by Kenneth A Esdaile on 5/30/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#include "ParticleRenderer.hpp"
#define MAX_INSTANCE_COUNT 10000
namespace kege {namespace gfx{

    bool gfx::ParticleRenderer::Draw
    (  const cg::point3& pos
     , float width, float height
     , const cg::vec4& colr
     , const cg::vec4& frame1
     , const cg::vec4& frame2
     , float mix)
    {
        if (elements >= MAX_INSTANCE_COUNT)
        {
            Flush();
        };
        
        graphics[elements].posi.x = pos.x;
        graphics[elements].posi.y = pos.y;
        graphics[elements].posi.z = pos.z;
        graphics[elements].posi.w = mix;
        
        graphics[elements].rect.x = width;
        graphics[elements].rect.y = height;
        
        graphics[elements].colr.r = colr.r;
        graphics[elements].colr.g = colr.g;
        graphics[elements].colr.b = colr.b;
        graphics[elements].colr.a = colr.a;
        
        graphics[elements].img0.r = frame1.x;
        graphics[elements].img0.g = frame1.y;
        graphics[elements].img0.b = frame1.z;
        graphics[elements].img0.a = frame1.w;
        
        graphics[elements].img1.r = frame2.x;
        graphics[elements].img1.g = frame2.y;
        graphics[elements].img1.b = frame2.z;
        graphics[elements].img1.a = frame2.w;
        
        graphics[elements].rect.x = width;
        graphics[elements].rect.y = height;
        
        elements++;
        return true;
    }
    
    void gfx::ParticleRenderer::Flush()
    {
//        if (elements == 0 || shader.GetProgram().Handle() == 0 || !vao.IsDrawable())
//        {
//            elements = 0;
//            return;
//        }
//        Bind();
//        DisableDepthTest();
//        //DisableBlending();
//        EnableBlending();
//        DisableCulling();
//        vao.Bind();
//        {
//            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//            glBlendEquation(GL_FUNC_ADD);
//            vao.GetVBO().SubBufferData(0, stride * elements, graphics.getarray());
//            vao.DrawInstanced(elements);
//        }
//        vao.Unbind();
//        Unbind();
        elements = 0;
    }

    bool gfx::ParticleRenderer::Init()
    {
//        if (LoadShader("~/shaders/particle/particle-shader.shdr"))
//        {
//            graphics.resize(MAX_INSTANCE_COUNT);
//            stride   = sizeof(ParticleElement);
//            elements = 0;
//
//            if ( vao.Create() )
//            {
//                if (vao.GetVBO().Create())
//                {
//                    const cg::uint vec4size = sizeof(cg::vec4);
//                    vao.GetVBO().CreateDynamicBuffer(nullptr, stride*MAX_INSTANCE_COUNT);
//                    for(int i=0; i<5; i++)
//                    {
//                        vao.GetVBO().SetVertexAttrib(i, 4, stride, vec4size * i);
//                        glVertexAttribDivisor(i, 1);
//                    }
//                    vao.GetVBO().Unbind();
//                }
//                vao.DrawTriangleStrips();
//                //vao.SetDrawCount(4);
//                vao.Unbind();
//            }
//            return true;
//        }
        return false;
    }
    
    gfx::ParticleRenderer::ParticleRenderer()
    {}
    
    gfx::ParticleRenderer::~ ParticleRenderer()
    {
        graphics.clear();
        //mesh.Destroy();
    }
}}



