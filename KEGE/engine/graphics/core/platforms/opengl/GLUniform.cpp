//
//  uniformVariable.cpp
//  dev0
//
//  Created by Kenneth Esdaile on 10/14/17.
//  Copyright © 2017 Kenneth Anthony Esdaile. All rights reserved.
//
#include <OpenGL/gl3.h>
#include "../opengl/GLUniform.hpp"
namespace kege{ namespace core{
    
    void GLUniform::SetMat23f(const float * m, int count)const
    {
        if (location >= 0)
        {
            glUniformMatrix2x3fv(location, count, GL_FALSE, m);
        }
    }
    
    void GLUniform::SetMat32f(const float * m, int count)const
    {
        if (location >= 0)
        {
            glUniformMatrix3x2fv(location, count, GL_FALSE, m);
        }
    }
    
    void GLUniform::SetMat24f(const float * m, int count)const
    {
        if (location >= 0)
        {
            glUniformMatrix2x4fv(location, count, GL_FALSE, m);
        }
    }
    
    void GLUniform::SetMat34f(const float * m, int count)const
    {
        if (location >= 0)
        {
            glUniformMatrix3x4fv(location, count, GL_FALSE, m);
        }
    }
    
    void GLUniform::SetMat42f(const float * m, int count)const
    {
        if (location >= 0)
        {
            glUniformMatrix4x2fv(location, count, GL_FALSE, m);
        }
    }
    
    void GLUniform::SetMat43f(const float * m, int count)const
    {
        if (location >= 0)
        {
            glUniformMatrix4x3fv(location, count, GL_FALSE, m);
        }
    }
    
    void GLUniform::SetMat22f(const float * m, int count) const
    {
        if (location >= 0)
        {
            glUniformMatrix2fv(location, count, GL_FALSE, m);
        }
    }
    
    void GLUniform::SetMat33f(const float * m, int count) const
    {
        if (location >= 0)
        {
            glUniformMatrix3fv(location, count, GL_FALSE, m);
        }
    }
    
    void GLUniform::SetMat44f(const float * m, int count) const
    {
        if (location >= 0)
        {
            glUniformMatrix4fv(location, count, GL_FALSE, m);
        }
    }
    
    void GLUniform::SetVec2f(const float * v, int count) const
    {
        if (location >= 0)
        {
            glUniform2fv(location, count, v);
        }
    }
    
    void GLUniform::SetVec3f(const float * v, int count) const
    {
        if (location >= 0)
        {glUniform3fv(location, count, v);
        }
    }
    
    void GLUniform::SetVec4f(const float * v, int count) const
    {
        if (location >= 0)
        {
            glUniform4fv(location, count, v);
        }
    }
    
    void GLUniform::SetDouble(const double v) const
    {
        if (location >= 0)
        {
            glUniform1d(location, v);
        }
    }
    void GLUniform::SetFloat(const float  v) const
    {
        if (location >= 0)
        {
            glUniform1f(location, v);
        }
    }
    void GLUniform::SetInt(const int    v) const
    {
        if (location >= 0)
        {
            glUniform1i(location, v);
        }
    }
}}
