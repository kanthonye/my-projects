//
//  GraphicsBuffer.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/18/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#include "GraphicsBuffer.hpp"
namespace kege{ namespace gfx{
    
    void GraphicsBuffer::BeginGeometricPass()const
    {
        fbo->Bind();
    }
    
    void GraphicsBuffer::EndGeometricPass()const
    {
        fbo->Unbind();
    }
    
    void GraphicsBuffer::BeginLightingPass()const
    {
//        for (short i=0; i<fbo.GetTextures().size(); i++) fbo->BindTexture2D(i, i);
    }
    void GraphicsBuffer::EndLightingPass()const
    {
//        for (short i=0; i<fbo.GetTextures().size(); i++) fbo->UnbindTexture2D(i);
    }
    
    void GraphicsBuffer::ClearBuffer()const
    {
//        glClear(clear_buffer_bits);
    }
    
    
    void GraphicsBuffer::Create(short width, short height)
    {
//        fbo.Destroy();
        
//        clear_buffer_bits = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
//        fbo.CreateFBO(width, height, clear_buffer_bits);
//        fbo.GenTextures(5);
//        fbo.AttachTextureBuffer2D(0, GL_COLOR_ATTACHMENT0, GL_RGB32F, GL_RGB, GL_FLOAT, NULL);//position
//        fbo.AttachTextureBuffer2D(1, GL_COLOR_ATTACHMENT1, GL_RGB16F, GL_RGB, GL_FLOAT, NULL);//normal
//        fbo.AttachTextureBuffer2D(2, GL_COLOR_ATTACHMENT2, GL_RGB16F, GL_RGB, GL_FLOAT, NULL);//diffmap
//        fbo.AttachTextureBuffer2D(3, GL_COLOR_ATTACHMENT3, GL_RGB16F, GL_RGB, GL_FLOAT, NULL);//matrmap
//        fbo.AttachTextureBuffer2D(4, GL_DEPTH_ATTACHMENT, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);//depth
        
//        fbo.SetDrawBuffers(4, GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3);
//        if( fbo.CheckFramebufferStatus() )
//        {
//            fbo.Unbind();
//            fbo.GetClearColor() = cg::vec4(0.0,0.0,0.0,1.0);
//        }
    }
}}
