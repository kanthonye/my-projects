/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GLUBO.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "GLUBO.hpp"
#include "GLUniform.hpp"
#include <OpenGL/gl3.h>
#include "GLGraphics.hpp"
namespace kege{namespace core{
    
    void GLUBO::UpdateData(cg::uint size, const void *data)const
    {
        if (id == 0) return;
        glBindBuffer(GL_UNIFORM_BUFFER, id);
        glBufferData(GL_UNIFORM_BUFFER, size, data, usage);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
    
    void* GLUBO::BeginBufferReadWrite()const
    {
        glBindBuffer(GL_UNIFORM_BUFFER, id);
        return glMapBuffer(GL_UNIFORM_BUFFER, GL_READ_WRITE);
    }
    void* GLUBO::BeginBufferWrite()const
    {
        glBindBuffer(GL_UNIFORM_BUFFER, id);
        return glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
    }
    void* GLUBO::BeginBufferRead()const
    {
        glBindBuffer(GL_UNIFORM_BUFFER, id);
        return glMapBuffer(GL_UNIFORM_BUFFER, GL_READ_ONLY);
    }
    void GLUBO::EndBufferReadWrite()const
    {
        glUnmapBuffer(GL_UNIFORM_BUFFER);
    }
    
    void GLUBO::Create(long size, const void* data, cg::uint uses, const ds::string& name)
    {
        cg::uint block_binding = core::BindingPoint::Get(name);
        usage = GLGraphics::GLGetConstant( uses );
        
        glGenBuffers(1, &id);
        glBindBuffer(GL_UNIFORM_BUFFER, id);
        glBufferData(GL_UNIFORM_BUFFER, size, data, usage);
        glBindBufferBase(GL_UNIFORM_BUFFER, block_binding, id);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
    
    void GLUBO::UnCreate()
    {
        if (id != 0)
        {
            glDeleteBuffers(1, &id);
            id = 0;
        }
    }
    void GLUBO::Unbind()const
    {
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
    void GLUBO::Bind()const
    {
        if (id == 0) return;
        glBindBuffer(GL_UNIFORM_BUFFER, id);
    }
    GLUBO::GLUBO(long size, const void* data, cg::uint usage, const ds::string& name)
    :   usage(usage)
    ,   id(0)
    {
        Create(size, data, usage, name);
    }
    GLUBO::~ GLUBO()
    {
        UnCreate();
    }
    GLUBO::GLUBO()
    :   usage(0)
    ,   id(0)
    {}
}}
