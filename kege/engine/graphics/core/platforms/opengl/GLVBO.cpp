/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GLVBO.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "GLVBO.hpp"
#include "GLGraphics.hpp"
#include "Graphics.hpp"
#include <OpenGL/gl3.h>
namespace kege{namespace core{
    
    void GLVBO::UpdateBufferData(long size, const void* data)
    {
        glBindBuffer(type, id);
        cg::mat44* bufr = (cg::mat44*)glMapBuffer(type, GL_WRITE_ONLY);
        if (bufr != nullptr)
        {
            memcpy(bufr, data, size);
            glUnmapBuffer(type);
        }
//        glBufferSubData(type, 0, size, data);
//        glBindBuffer(type, 0);
//        gfx::Graphics::CheckError("GLVBO::UpdateBufferData");
    }
    void GLVBO::Create(long size, const void* data, cg::uint usage)
    {
        usage = GLGraphics::GLGetConstant( usage );
        type = GL_ARRAY_BUFFER;
        glGenBuffers(1, &id);
        glBindBuffer(type, id);
        glBufferData(type, size, data, usage);
//        glBindBuffer(type, 0);
    }
    void GLVBO::UnCreate()
    {
        if (id != 0)
        {
            glDeleteBuffers(1, &id);
            type = 0;
            id = 0;
        }
    }
    void GLVBO::Unbind()const
    {
        glBindBuffer(type, 0);
    }
    void GLVBO::Bind()const
    {
        if (id == 0) return;
        glBindBuffer(type, id);
    }
    GLVBO::GLVBO(long size, const void* data, cg::uint usage)
    :   type(0)
    ,   id(0)
    {
        Create(size, data, usage);
    }
    GLVBO::~ GLVBO()
    {
        UnCreate();
    }
    GLVBO::GLVBO()
    :   type(0)
    ,   id(0)
    {}
}}
