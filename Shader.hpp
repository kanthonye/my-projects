/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Shader.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp
#include "shared.hpp"
#include "string.hpp"
#include "../../graphics/cgmath/cgm.hpp"
#include "../../graphics/framework/Uniform.hpp"
#include "../../graphics/framework/UBO.hpp"
namespace kege{namespace gfx{
    typedef kege::shared<gfx::Uniform> SharedUniform;
    
    class Shader
    {
    public:
        
        virtual void SetUBO(const char* name, cg::uint size, const void *data)const {}
        virtual const UBO* GetUBO(const char* name)const {return nullptr;}
        
        virtual void SetMat23f(const char* name, const float* m, int count = 1)const {}
        virtual void SetMat32f(const char* name, const float* m, int count = 1)const {}
        virtual void SetMat24f(const char* name, const float* m, int count = 1)const {}
        virtual void SetMat34f(const char* name, const float* m, int count = 1)const {}
        virtual void SetMat42f(const char* name, const float* m, int count = 1)const {}
        virtual void SetMat43f(const char* name, const float* m, int count = 1)const {}
        
        virtual void SetMat22f(const char* name, const float* m, int count = 1) const {}
        virtual void SetMat33f(const char* name, const float* m, int count = 1) const {}
        virtual void SetMat44f(const char* name, const float* m, int count = 1) const {}
        
        virtual void SetVec2f(const char* name, const float* v, int count = 1) const {}
        virtual void SetVec3f(const char* name, const float* v, int count = 1) const {}
        virtual void SetVec4f(const char* name, const float* v, int count = 1) const {}
        
        virtual void SetVec4f(const char* name, float x, float y, float z, float w) const {}
        virtual void SetVec3f(const char* name, float x, float y, float z) const {}
        virtual void SetVec2f(const char* name, float x, float y) const {}
        
        virtual void SetDouble(const char* name, double val) const {}
        virtual void SetFloat (const char* name, float  val) const {}
        virtual void SetInt   (const char* name, int    val) const {}
        
        
        virtual SharedUniform GetUniform(const ds::string& name) = 0;
        virtual int  GetAttribute(const ds::string& name) = 0;
        
        virtual void FragmentShader(const char* source) = 0;
        virtual void GeometryShader(const char* source) = 0;
        virtual void TessEvalShader(const char* source) = 0;
        virtual void TessContShader(const char* source) = 0;
        virtual void VertexShader(const char* source) = 0;
        
        virtual bool Create() = 0;
        virtual void UnCreate() = 0;
        virtual void Disable()const = 0;
        virtual void Enable()const = 0;
        
        
        void SetName(ds::string const& name);
        ds::string const& GetName()const;
        ds::string & GetName();

        virtual ~ Shader(){}
        
        ds::string name;
    };
    
    typedef kege::shared<gfx::Shader> SharedShader;
}}
#endif /* ShaderProgram_hpp */
