//
//  Uniform.hpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 5/5/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef Uniform_hpp
#define Uniform_hpp
#include "../../graphics/cgmath/cgm.hpp"
namespace kege{namespace gfx{
    
    class Uniform
    {
    public:
        
        virtual void SetMat23f(const float * m, int count = 1)const {}
        virtual void SetMat32f(const float * m, int count = 1)const {}
        virtual void SetMat24f(const float * m, int count = 1)const {}
        virtual void SetMat34f(const float * m, int count = 1)const {}
        virtual void SetMat42f(const float * m, int count = 1)const {}
        virtual void SetMat43f(const float * m, int count = 1)const {}
        
        virtual void SetMat22f(const float * m, int count = 1) const {}
        virtual void SetMat33f(const float * m, int count = 1) const {}
        virtual void SetMat44f(const float * m, int count = 1) const {}
        
        virtual void SetVec2f(const float * v, int count = 1) const {}
        virtual void SetVec3f(const float * v, int count = 1) const {}
        virtual void SetVec4f(const float * v, int count = 1) const {}
        
        
        virtual void SetVec4f(float x, float y, float z, float w) const {}
        virtual void SetVec3f(float x, float y, float z) const {}
        virtual void SetVec2f(float x, float y) const {}
        
        virtual void SetDouble(const double val) const {}
        virtual void SetFloat (const float  val) const {}
        virtual void SetInt   (const int    val) const {}
        
        virtual void SetUBO(cg::uint offset, cg::uint size, const void* data){}
        
        virtual void Enable() const {}
        virtual ~ Uniform(){}
        Uniform(){}
    };
    
    typedef kege::shared<gfx::Uniform> SharedUniform;
}}
#endif /* Uniform_hpp */
