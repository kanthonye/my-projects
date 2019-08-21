/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GLIBO.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "GLIBO.hpp"
#include <OpenGL/gl3.h>
#include "GLGraphics.hpp"
namespace kege{namespace core{
    
    void GLIBO::DrawInstanced(cg::uint mode, cg::uint count, const void *indices, cg::uint instancecount)
    {
        glDrawElementsInstanced(mode, count, GL_UNSIGNED_INT, indices, instancecount);
    }
    void GLIBO::Draw(cg::uint mode, cg::uint count, const void *indices)
    {
        glDrawElements(mode, count, GL_UNSIGNED_INT, indices);
    }
    
    void GLIBO::UpdateBufferData(long size, const void* data)
    {
        glBindBuffer(type, id);
        glBufferSubData(type, 0, size, data);
        glBindBuffer(type, 0);
    }
//    void GLIBO::UpdateData(cg::uint size, const void *data)const
//    {
//        glBufferData(type, size, data, GL_DYNAMIC_READ);
//    }
//    
//    void* GLIBO::BeginBufferReadWrite()const
//    {
//        glBindBuffer(type, id);
//        return glMapBuffer(type, GL_READ_WRITE);
//    }
//    void* GLIBO::BeginBufferWrite()const
//    {
//        glBindBuffer(type, id);
//        return glMapBuffer(type, GL_WRITE_ONLY);
//    }
//    void* GLIBO::BeginBufferRead()const
//    {
//        glBindBuffer(type, id);
//        return glMapBuffer(type, GL_READ_ONLY);
//    }
//    void GLIBO::EndBufferReadWrite()const
//    {
//        glUnmapBuffer(type);
//    }

    
    void GLIBO::Create(long size, const void* data, cg::uint usage)
    {
        type = GL_ELEMENT_ARRAY_BUFFER;
        glGenBuffers(1, &id);
        glBindBuffer(type, id);
        glBufferData(type, size, data, GLGraphics::GLGetConstant( usage ));
        glBindBuffer(type, 0);
    }
    void GLIBO::UnCreate()
    {
        if (id != 0)
        {
            glDeleteBuffers(1, &id);
            type = 0;
            id = 0;
        }
    }
    void GLIBO::Unbind()const
    {
        glBindBuffer(type, 0);
    }
    void GLIBO::Bind()const
    {
        if (id == 0) return;
        glBindBuffer(type, id);
    }
    GLIBO::GLIBO(long size, const void* data, cg::uint usage)
    :   type(0)
    ,   id(0)
    {
        Create(size, data, usage);
    }
    GLIBO::~ GLIBO()
    {
        UnCreate();
    }
    GLIBO::GLIBO()
    :   type(0)
    ,   id(0)
    {}
}}
