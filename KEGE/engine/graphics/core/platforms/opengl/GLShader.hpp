/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Shader.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GLShader_hpp
#define GLShader_hpp
#include <unordered_map>
#include "string.hpp"
#include "../opengl/GLUBO.hpp"
#include "../opengl/GLUniform.hpp"
#include "../../framework/Shader.hpp"
namespace kege{namespace core{
    
    class GLShader : public core::Shader
    {
    public:
        
        void SetUBO(const char* name, cg::uint size, const void *data)const;
        const UBO* GetUBO(const char* name)const;
        
        void SetMat23f(const char* name, const float* m, int count = 1)const;
        void SetMat32f(const char* name, const float* m, int count = 1)const;
        void SetMat24f(const char* name, const float* m, int count = 1)const;
        void SetMat34f(const char* name, const float* m, int count = 1)const;
        void SetMat42f(const char* name, const float* m, int count = 1)const;
        void SetMat43f(const char* name, const float* m, int count = 1)const;
        
        void SetMat22f(const char* name, const float* m, int count = 1) const;
        void SetMat33f(const char* name, const float* m, int count = 1) const;
        void SetMat44f(const char* name, const float* m, int count = 1) const;
        
        void SetVec2f(const char* name, const float* v, int count = 1) const;
        void SetVec3f(const char* name, const float* v, int count = 1) const;
        void SetVec4f(const char* name, const float* v, int count = 1) const;
        
        void SetDouble(const char* name, double val) const;
        void SetFloat (const char* name, float  val) const;
        void SetInt   (const char* name, int    val) const;
        
        const core::GLUniform& GetUniformLocation(const char* name) const;
        //SharedUniform GetUniform(const ds::string& name);
        int GetAttribute(const ds::string& name);
        
        void FragmentShader(const char* source);
        void GeometryShader(const char* source);
        void TessEvalShader(const char* source);
        void TessContShader(const char* source);
        void VertexShader(const char* source);
        
        void LinkUBO(const ds::string& name)const;
        
        bool Create();
        void UnCreate();
        void Disable()const;
        void Enable()const;
        
        GLShader(bool create);
        ~ GLShader();
        GLShader();
        
    private:
        
        mutable std::unordered_map<unsigned long, core::GLUniform> uniforms;
        static  std::unordered_map<unsigned long, core::GLUBO> ubos;
        cg::uint id;
    };
    
}}
#endif /* GLShader_hpp */
