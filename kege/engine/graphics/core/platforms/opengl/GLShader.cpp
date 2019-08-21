/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GLShader.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include <OpenGL/gl3.h>
#include "Logger.hpp"
#include "GLShader.hpp"
#include "GLGraphics.hpp"
namespace kege{namespace core{
    
    source GLShaderTargetToString(int target)
    {
        switch (target)
        {
            default: return 0;
                
            case core::SHADER_VERTEX:
            case GL_VERTEX_SHADER: return "VERTEX_SHADER";
                
            case core::SHADER_FRAGMENT:
            case GL_FRAGMENT_SHADER: return "FRAGMENT_SHADER";
                
            case core::SHADER_GEOMETRY:
            case GL_GEOMETRY_SHADER: return "GEOMETRY_SHADER";
                
            case core::SHADER_TESS_CTROL:
            case GL_TESS_CONTROL_SHADER: return "TESS_CONTROL_SHADER";
                
            case core::SHADER_TESS_EVAL:
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
    
    void GLShader::SetUBO(const char* name, cg::uint size, const void *data)const
    {
        unsigned long key = ds::string::hash( name );
        std::unordered_map<unsigned long, core::GLUBO>::const_iterator i = ubos.find( key );
        if (i == ubos.end())
        {
            ubos[ key ].Create(size, data, core::STREAM_DRAW, name);
            return;
        }
        i->second.UpdateData( size, data );
    }
    const UBO* GLShader::GetUBO(const char* name)const
    {
        unsigned long key = ds::string::hash( name );
        std::unordered_map<unsigned long, core::GLUBO>::const_iterator i = ubos.find( key );
        if (i == ubos.end())
        {
            return nullptr;
        }
        return &i->second;
    }
    void GLShader::SetMat23f(const char* name, const float* m, int count)const
    {
        GetUniformLocation( name ).SetMat23f( m );
    }
    void GLShader::SetMat32f(const char* name, const float* m, int count)const
    {
        GetUniformLocation( name ).SetMat32f( m );
    }
    void GLShader::SetMat24f(const char* name, const float* m, int count)const
    {
        GetUniformLocation( name ).SetMat34f( m );
    }
    void GLShader::SetMat34f(const char* name, const float* m, int count)const
    {
        GetUniformLocation( name ).SetMat34f( m );
    }
    void GLShader::SetMat42f(const char* name, const float* m, int count)const
    {
        GetUniformLocation( name ).SetMat42f( m );
    }
    void GLShader::SetMat43f(const char* name, const float* m, int count)const
    {
        GetUniformLocation( name ).SetMat43f( m );
    }

    void GLShader::SetMat22f(const char* name, const float* m, int count) const
    {
        GetUniformLocation( name ).SetMat22f( m );
    }
    void GLShader::SetMat33f(const char* name, const float* m, int count) const
    {
        GetUniformLocation( name ).SetMat33f( m );
    }
    void GLShader::SetMat44f(const char* name, const float* m, int count) const
    {
        GetUniformLocation( name ).SetMat44f( m );
    }

    void GLShader::SetVec2f(const char* name, const float* v, int count) const
    {
        GetUniformLocation( name ).SetVec2f( v );
    }
    void GLShader::SetVec3f(const char* name, const float* v, int count) const
    {
        GetUniformLocation( name ).SetVec3f( v );
    }
    void GLShader::SetVec4f(const char* name, const float* v, int count) const
    {
        GetUniformLocation( name ).SetVec4f( v );
    }

    void GLShader::SetDouble(const char* name, double val) const
    {
        GetUniformLocation( name ).SetDouble( val );
    }
    void GLShader::SetFloat(const char* name, float val) const
    {
        GetUniformLocation( name ).SetFloat( val );
    }
    void GLShader::SetInt(const char* name, int val) const
    {
        GetUniformLocation( name ).SetInt( val );
    }
    
    int GLShader::GetAttribute(const ds::string& name)
    {
        return glGetAttribLocation(id, name.c_str());
    }
    
    const core::GLUniform& GLShader::GetUniformLocation(const char* name) const
    {
        unsigned long key = ds::string::hash( name );
        std::unordered_map<unsigned long, core::GLUniform>::const_iterator i = uniforms.find( key );
        if (i == uniforms.end())
        {
            core::GLUniform& uniform = uniforms[ key ];
            int location = glGetUniformLocation( id, name );
            uniform = location;
            return uniform;
        }
        return i->second;
    }
    
//    SharedUniform GLShader::GetUniform(const ds::string& name)
//    {
//        int location = glGetUniformLocation(id, name.c_str());
//        if (location < 0) return SharedUniform();
//        return SharedUniform( new GLUniform( location ) );
//    }
    
    void GLShader::FragmentShader(const char* source)
    {
        cg::uint shader = GLCompileShader(name, GL_FRAGMENT_SHADER, source);
        if (id != 0 && shader)
        {
            glAttachShader(id, shader);
            glDeleteShader(shader);
        }
    }
    void GLShader::GeometryShader(const char* source)
    {
        cg::uint shader = GLCompileShader(name, GL_GEOMETRY_SHADER, source);
        if (id != 0)
        {
            glAttachShader(id, shader);
            glDeleteShader(shader);
        }
    }
    void GLShader::TessEvalShader(const char* source)
    {
        cg::uint shader = GLCompileShader(name, GL_TESS_EVALUATION_SHADER, source);
        if (id != 0)
        {
            glAttachShader(id, shader);
            glDeleteShader(shader);
        }
    }
    void GLShader::TessContShader(const char* source)
    {
        cg::uint shader = GLCompileShader(name, GL_TESS_CONTROL_SHADER, source);
        if (id != 0)
        {
            glAttachShader(id, shader);
            glDeleteShader(shader);
        }
    }
    void GLShader::VertexShader(const char* source)
    {
        cg::uint shader = GLCompileShader(name, GL_VERTEX_SHADER, source);
        if (id != 0)
        {
            glAttachShader(id, shader);
            glDeleteShader(shader);
        }
    }
    
    void GLShader::LinkUBO(const ds::string& name)const
    {
        if ( id == 0 ) return;
        cg::uint block_binding = core::BindingPoint::Get( name );
        cg::uint block_index = glGetUniformBlockIndex( id, name.c_str() );
        if ( block_index < 0 ) return;
        glUniformBlockBinding( id, block_index, block_binding );
        
        KEGE_INFO("# - [%i] <<- (LinkUBO : %s)", block_binding, name.c_str());
    }
    
    bool GLShader::Create()
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
    void GLShader::UnCreate()
    {
        if (id != 0)
        {
            glDeleteProgram( id );
            id = 0;
        }
    }
    void GLShader::Disable()const
    {
        glUseProgram(0);
    }
    void GLShader::Enable()const
    {
        if (id == 0) return;
        glUseProgram(id);
    }
    GLShader::GLShader(bool create)
    :   id(0)
    {
        if ( create )
        {
            id = glCreateProgram();
        }
    }
    GLShader::~ GLShader()
    {
        UnCreate();
    }
    GLShader::GLShader()
    :   id(0)
    {}
    
    std::unordered_map<unsigned long, core::GLUBO> GLShader::ubos;
}}
