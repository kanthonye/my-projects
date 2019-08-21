//
//  UniformVariable.hpp
//  dev0
//
//  Created by Kenneth Esdaile on 10/14/17.
//  Copyright © 2017 Kenneth Anthony Esdaile. All rights reserved.
//
#ifndef UniformVariable_hpp
#define UniformVariable_hpp
#include <map>
#include "string.hpp"
#include "Enumerator.hpp"
#include "../../framework/Uniform.hpp"
namespace kege{namespace core{

    class GLUniform : public core::Uniform
    {
    public:
        
        void SetMat23f(const float * m, int count = 1) const;
        void SetMat32f(const float * m, int count = 1) const;
        void SetMat24f(const float * m, int count = 1) const;
        void SetMat34f(const float * m, int count = 1) const;
        void SetMat42f(const float * m, int count = 1) const;
        void SetMat43f(const float * m, int count = 1) const;
        void SetMat22f(const float * m, int count = 1) const;
        void SetMat33f(const float * m, int count = 1) const;
        void SetMat44f(const float * m, int count = 1) const;
        void SetVec2f(const float * v, int count = 1) const;
        void SetVec3f(const float * v, int count = 1) const;
        void SetVec4f(const float * v, int count = 1) const;
        void SetDouble(const double v) const;
        void SetFloat (const float  v) const;
        void SetInt   (const int    v) const;
        
        inline void SetLocation(int uniform)
        {
            location = uniform;
        }
        
        inline int GetLocation()const
        {
            return location;
        }
        
        void operator = (cg::uint u)
        {
            location = u;
        }
        
        GLUniform(cg::uint u)
        :   location(u)
        {}
        
        GLUniform()
        :   location(-1)
        {}
        
    protected:
        
        int location;
    };
}}

namespace kege{namespace core{
    
    class BindingPoint
    {
    private:
        static Enumerator& Instance()
        {
            static Enumerator instance;
            return instance;
        }
    public:
        static unsigned int Get(const ds::string& name)
        {
            return Instance().GetEnum( name );
        }
    };
}}
#endif /* uniformVariable_hpp */

