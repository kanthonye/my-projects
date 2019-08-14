/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GLShaderProgram.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include <OpenGL/gl3.h>
#include "Logger.hpp"
#include "GLShaderProgram.hpp"
#include "GLGraphics.hpp"
namespace kege{namespace gfx{
    
    source GLShaderTargetToString(int target)
    {
        switch (target)
        {
            default: return 0;
                
            case gfx::SHADER_VERTEX:
            case GL_VERTEX_SHADER: return "VERTEX_SHADER";
                
            case gfx::SHADER_FRAGMENT:
            case GL_FRAGMENT_SHADER: return "FRAGMENT_SHADER";
                
            case gfx::SHADER_GEOMETRY:
            case GL_GEOMETRY_SHADER: return "GEOMETRY_SHADER";
                
            case gfx::SHADER_TESS_CTROL:
            case GL_TESS_CONTROL_SHADER: return "TESS_CONTROL_SHADER";
                
            case gfx::SHADER_TESS_EVAL:
            case GL_TESS_EVALUATION_SHADER: return "TESS_EVALUATION_SHADER";
        }
    }
    
    cg::uint GLCompileShader(const ds::string& prog_name, cg::uint  target, source src)
    {
        cg::uint id = glCreateShader( target );
        if (id <= 0)
        {
            //KEGE_ERROR("shader creation error.\n", ShaderTargetToString(target));
            return 0;
        }
        int compiled = 0;
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);
        glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
        if (compiled == GL_FALSE)
        {
            int logsize = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logsize);
            if (logsize>0)
            {
                char error_messgae[logsize+1];
                GLsizei written_char = 0;
                glGetShaderInfoLog(id, logsize, &written_char, error_messgae);
                KEGE_ERROR("%s %s %s\n", prog_name.c_str(), GLShaderTargetToString(target), error_messgae);
            }
            else
            {
                KEGE_ERROR("shader compile error. %s\n", GLShaderTargetToString(target));
            }
            glDeleteShader(id);
            id = 0;
        }
        return id;
    }
    
    void GLShaderProgram::SetUBO(const char* name, cg::uint size, const void *data)const
    {
        unsigned long key = ds::string::hash( name );
        std::unordered_map<unsigned long, gfx::GLUBO>::const_iterator i = ubos.find( key );
        if (i == ubos.end())
        {
            ubos[ key ].Create(size, data, gfx::STREAM_DRAW, name);
            return;
        }
        i->second.UpdateData( size, data );
    }
    const UBO* GLShaderProgram::GetUBO(const char* name)const
    {
        unsigned long key = ds::string::hash( name );
        std::unordered_map<unsigned long, gfx::GLUBO>::const_iterator i = ubos.find( key );
        if (i == ubos.end())
        {
            return nullptr;
        }
        return &i->second;
    }
    void GLShaderProgram::SetMat23f(const char* name, const float* m, int count)const
    {
        GetUniformLocation( name ).SetMat23f( m );
    }
    void GLShaderProgram::SetMat32f(const char* name, const float* m, int count)const
    {
        GetUniformLocation( name ).SetMat32f( m );
    }
    void GLShaderProgram::SetMat24f(const char* name, const float* m, int count)const
    {
        GetUniformLocation( name ).SetMat34f( m );
    }
    void GLShaderProgram::SetMat34f(const char* name, const float* m, int count)const
    {
        GetUniformLocation( name ).SetMat34f( m );
    }
    void GLShaderProgram::SetMat42f(const char* name, const float* m, int count)const
    {
        GetUniformLocation( name ).SetMat42f( m );
    }
    void GLShaderProgram::SetMat43f(const char* name, const float* m, int count)const
    {
        GetUniformLocation( name ).SetMat43f( m );
    }

    void GLShaderProgram::SetMat22f(const char* name, const float* m, int count) const
    {
        GetUniformLocation( name ).SetMat22f( m );
    }
    void GLShaderProgram::SetMat33f(const char* name, const float* m, int count) const
    {
        GetUniformLocation( name ).SetMat33f( m );
    }
    void GLShaderProgram::SetMat44f(const char* name, const float* m, int count) const
    {
        GetUniformLocation( name ).SetMat44f( m );
    }

    void GLShaderProgram::SetVec2f(const char* name, const float* v, int count) const
    {
        GetUniformLocation( name ).SetVec2f( v );
    }
    void GLShaderProgram::SetVec3f(const char* name, const float* v, int count) const
    {
        GetUniformLocation( name ).SetVec3f( v );
    }
    void GLShaderProgram::SetVec4f(const char* name, const float* v, int count) const
    {
        GetUniformLocation( name ).SetVec4f( v );
    }

    void GLShaderProgram::SetDouble(const char* name, double val) const
    {
        GetUniformLocation( name ).SetDouble( val );
    }
    void GLShaderProgram::SetFloat(const char* name, float val) const
    {
        GetUniformLocation( name ).SetFloat( val );
    }
    void GLShaderProgram::SetInt(const char* name, int val) const
    {
        GetUniformLocation( name ).SetInt( val );
    }
    
    int GLShaderProgram::GetAttribute(const ds::string& name)
    {
        return glGetAttribLocation(id, name.c_str());
    }
    
    const gfx::GLUniform& GLShaderProgram::GetUniformLocation(const char* name) const
    {
        unsigned long key = ds::string::hash( name );
        std::unordered_map<unsigned long, gfx::GLUniform>::const_iterator i = uniforms.find( key );
        if (i == uniforms.end())
        {
            gfx::GLUniform& uniform = uniforms[ key ];
            int location = glGetUniformLocation( id, name );
            uniform = location;
            return uniform;
        }
        return i->second;
    }
    
    SharedUniform GLShaderProgram::GetUniform(const ds::string& name)
    {
        int location = glGetUniformLocation(id, name.c_str());
        if (location < 0) return SharedUniform();
        return SharedUniform( new GLUniform( location ) );
    }
    
    void GLShaderProgram::FragmentShader(const char* source)
    {
        cg::uint shader = GLCompileShader(name, GL_FRAGMENT_SHADER, source);
        if (id != 0 && shader)
        {
            glAttachShader(id, shader);
            glDeleteShader(shader);
        }
    }
    void GLShaderProgram::GeometryShader(const char* source)
    {
        cg::uint shader = GLCompileShader(name, GL_GEOMETRY_SHADER, source);
        if (id != 0)
        {
            glAttachShader(id, shader);
            glDeleteShader(shader);
        }
    }
    void GLShaderProgram::TessEvalShader(const char* source)
    {
        cg::uint shader = GLCompileShader(name, GL_TESS_EVALUATION_SHADER, source);
        if (id != 0)
        {
            glAttachShader(id, shader);
            glDeleteShader(shader);
        }
    }
    void GLShaderProgram::TessContShader(const char* source)
    {
        cg::uint shader = GLCompileShader(name, GL_TESS_CONTROL_SHADER, source);
        if (id != 0)
        {
            glAttachShader(id, shader);
            glDeleteShader(shader);
        }
    }
    void GLShaderProgram::VertexShader(const char* source)
    {
        cg::uint shader = GLCompileShader(name, GL_VERTEX_SHADER, source);
        if (id != 0)
        {
            glAttachShader(id, shader);
            glDeleteShader(shader);
        }
    }
    
    void GLShaderProgram::LinkUBO(const ds::string& name)const
    {
        if ( id == 0 ) return;
        cg::uint block_binding = gfx::BindingPoint::Get( name );
        cg::uint block_index = glGetUniformBlockIndex( id, name.c_str() );
        if ( block_index < 0 ) return;
        glUniformBlockBinding( id, block_index, block_binding );
        
        KEGE_INFO("# - [%i] <<- (LinkUBO : %s)", block_binding, name.c_str());
    }
    
    bool GLShaderProgram::Create()
    {
        int error = 0;
        glLinkProgram( id );
        glGetProgramiv( id, GL_LINK_STATUS, &error );
        if (error == GL_FALSE)
        {
            int logsize = 0;
            glGetProgramiv( id, GL_INFO_LOG_LENGTH, &logsize );
            if (logsize>0)
            {
                char error_messgae[logsize+1];
                GLsizei written_char = 0;
                glGetProgramInfoLog(id, logsize, &written_char, error_messgae);
                KEGE_ERROR("%s %s\n", name.c_str(), error_messgae);
            }
            else
            {
                KEGE_ERROR("%s link program error.\n",__FILE__);
            }
            glDeleteProgram( id );
            return false;
        }
        return true;
    }
    void GLShaderProgram::UnCreate()
    {
        if (id != 0)
        {
            glDeleteProgram( id );
            id = 0;
        }
    }
    void GLShaderProgram::Disable()const
    {
        glUseProgram(0);
    }
    void GLShaderProgram::Enable()const
    {
        if (id == 0) return;
        glUseProgram(id);
    }
    GLShaderProgram::GLShaderProgram(bool create)
    :   id(0)
    {
        if ( create )
        {
            id = glCreateProgram();
        }
    }
    GLShaderProgram::~ GLShaderProgram()
    {
        UnCreate();
    }
    GLShaderProgram::GLShaderProgram()
    :   id(0)
    {}
    
    std::unordered_map<unsigned long, gfx::GLUBO> GLShaderProgram::ubos;
}}
