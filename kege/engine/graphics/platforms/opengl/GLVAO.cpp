/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GLVAO.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "GLVAO.hpp"
#include <OpenGL/gl3.h>
#include "Graphics.hpp"
#include "../../../graphics/platforms/opengl/GLVBO.hpp"
#include "../../../graphics/platforms/opengl/GLIBO.hpp"
namespace kege{namespace gfx{

    void GLVAO::DrawInstanced(cg::uint mode, cg::uint first, cg::uint count, cg::uint instancecount)
    {
        if ( ibo != nullptr )
        {
            ibo->DrawInstanced(mode, count, nullptr, instancecount);
        }
        else
        {
            glDrawArraysInstanced(mode, first, count, instancecount);
        }
    }
    void GLVAO::Draw(cg::uint mode, cg::uint first, cg::uint count)
    {
        if ( ibo != nullptr )
        {
            ibo->Draw(mode, count, nullptr);
        }
        else
        {
            glDrawArrays(mode, first, count);
        }
    }
    
    void GLVAO::AttachVBO(long size, cg::uint stride, const void* data, cg::uint usage, const VertexLayout& layout)
    {
        if ( size <= 0 ) return;
        glBindVertexArray(id);
        gfx::Graphics::CheckError("glVertexAttribPointer");
        
        GLVBO* vbo = new GLVBO(size, data, usage);
        for (int i=0; i<layout.Count(); i++)
        {
            const VertexElement& e = layout[i];
            
            glEnableVertexAttribArray( layout[i].index );
            gfx::Graphics::CheckError("glEnableVertexAttribArray");
            
            glVertexAttribPointer
            (  e.index
             , e.size
             , GL_FLOAT
             , GL_FALSE
             , stride
             , (GLvoid*) (sizeof(float) * e.offset)  );
            
            glVertexAttribDivisor(e.index, e.attdiv);
            
            gfx::Graphics::CheckError("glVertexAttribPointer");
        }
        vbo->Unbind();
        
        glBindVertexArray(0);
        vertex_buffers.resize( vertex_buffers.size() + 1 );
        vertex_buffers[ vertex_buffers.size() - 1 ] = vbo;
    }
    
    void GLVAO::AttachIBO(long size, const void* data, cg::uint usage)
    {
        if ( size <= 0 ) return;
        
        glBindVertexArray(id);
        ibo = new GLIBO(size, data, usage);
        glBindVertexArray(0);
    }
    
    void GLVAO::AttachVBO(const VertexBuffer& buffer, cg::uint usage)
    {
        if ( buffer.empty() ) return;
        AttachVBO
        (   buffer.size() * sizeof(float)
         ,  sizeof(float) * buffer.getstride()
         ,  buffer.getdata()
         ,  usage, buffer.GetVertexLayout()  );
    }
    
    void GLVAO::AttachIBO(const IndexBuffer& buffer, cg::uint usage)
    {
        if ( buffer.empty() ) return;
        if (ibo != nullptr) delete ibo;
        
        glBindVertexArray(id);
        ibo = new GLIBO(buffer.size() * sizeof(cg::uint), buffer.getdata(), usage);
        glBindVertexArray(0);
    }
    
    void GLVAO::Create()
    {
        glGenVertexArrays(1, &id);
        glBindVertexArray(id);
    }
    
    void GLVAO::UnCreate()
    {
        for (int i=0; i<vertex_buffers.size(); i++)
        {
            delete vertex_buffers[i];
        }
        vertex_buffers.clear();
        
        if (ibo != nullptr)
        {
            delete ibo;
            ibo = nullptr;
        }
        
        if (id != 0)
        {
            glDeleteVertexArrays(1, &id);
            id = 0;
        }
    }
    void GLVAO::Unbind()
    {
        if ( ibo != nullptr ) ibo->Unbind();
        glBindVertexArray(0);
    }
    void GLVAO::Bind()
    {
        if (id == 0) return;
        glBindVertexArray(id);
        
        if ( ibo == nullptr ) return;
        ibo->Bind();
    }
    GLVAO::~ GLVAO()
    {
        UnCreate();
    }
    GLVAO::GLVAO()
    :   ibo(nullptr)
    ,   id(0)
    {}
}}
