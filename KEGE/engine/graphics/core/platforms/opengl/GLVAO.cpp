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
#include "../../../../graphics/core/platforms/opengl/GLVBO.hpp"
#include "../../../../graphics/core/platforms/opengl/GLIBO.hpp"
namespace kege{namespace core{


    void GLVAO::DrawIndicesInstanced(cg::uint mode, cg::uint count, const void *indices, cg::uint instancecount)const
    {
        glDrawElementsInstanced(mode, count, GL_UNSIGNED_INT, indices, instancecount);
    }
    void GLVAO::DrawIndices(cg::uint mode, cg::uint count, const void *indices)const
    {
        glDrawElements(mode, count, GL_UNSIGNED_INT, indices);
    }
    void GLVAO::DrawArraysInstanced(cg::uint mode, cg::uint first, cg::uint count, cg::uint instancecount)const
    {
        glDrawArraysInstanced(mode, first, count, instancecount);
    }
    void GLVAO::DrawArrays(cg::uint mode, cg::uint first, cg::uint count)const
    {
        glDrawArrays(mode, first, count);
    }

    void GLVAO::AttachVBO(long size, cg::uint stride, const void* data, cg::uint usage, const VertexLayout& layout)
    {
        if ( size <= 0 ) return;
        glBindVertexArray(id);
        gfx::Graphics::CheckError("glVertexAttribPointer");
        
        _vbo = new GLVBO(size, data, usage);
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
        _vbo->Unbind();
        
        glBindVertexArray(0);
//        vertex_buffers.resize( vertex_buffers.size() + 1 );
//        vertex_buffers[ vertex_buffers.size() - 1 ] = _vbo;
    }
    
    void GLVAO::AttachVBO( const VertexBuffer& buffer, const VertexLayout& layout, cg::uint usage )
    {
        AttachVBO
        (   buffer.size() * sizeof( float )
         ,  buffer.getstride() * sizeof( float )
         ,  buffer.getdata()
         ,  usage, layout  );
    }
    void GLVAO::AttachIBO(long size, const void* data, cg::uint usage)
    {
        if ( size <= 0 ) return;
        
        glBindVertexArray(id);
        _ibo = new GLIBO(size, data, usage);
        glBindVertexArray(0);
    }
    
    void GLVAO::AttachVBO(const VertexBuffer& buffer, cg::uint usage)
    {
        if ( buffer.size() == 0 ) return;
        
        AttachVBO
        (   buffer.size() * sizeof(float)
         ,  buffer.getstride() * sizeof( float )
         ,  buffer.getdata()
         ,  usage, buffer.GetVertexLayout()  );
    }
    
    void GLVAO::AttachIBO(const IndexBuffer& buffer, cg::uint usage)
    {
        if ( buffer.size() == 0 ) return;
        
        glBindVertexArray(id);
        _ibo = new GLIBO(buffer.size() * sizeof(cg::uint), buffer.getdata(), usage);
        glBindVertexArray(0);
    }
    
    void GLVAO::Create()
    {
        glGenVertexArrays(1, &id);
        glBindVertexArray(id);
    }
    
    void GLVAO::UnCreate()
    {
//        for (int i=0; i<vertex_buffers.size(); i++)
//        {
//            delete vertex_buffers[i];
//        }
//        vertex_buffers.clear();
//
//        if (ibo != nullptr)
//        {
//            delete ibo;
//            ibo = nullptr;
//        }
        
        if (id != 0)
        {
            glDeleteVertexArrays(1, &id);
            id = 0;
        }
    }
    void GLVAO::Unbind()const
    {
        if ( _ibo != nullptr ) _ibo->Unbind();
        glBindVertexArray(0);
    }
    void GLVAO::Bind()const
    {
        if (id == 0) return;
        glBindVertexArray(id);
        
        if ( _ibo == nullptr ) return;
        _ibo->Bind();
    }
    GLVAO::~ GLVAO()
    {
        UnCreate();
    }
    GLVAO::GLVAO()
    :   id(0)
    {}
}}
