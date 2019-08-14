/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GLVBO.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GLVBO_hpp
#define GLVBO_hpp
#include "../../../graphics/framework/VBO.hpp"
namespace kege{namespace gfx{
    
    class GLVBO : public kege::gfx::VBO
    {
    public:
        
        void Create(long size, const void* data, cg::uint usage);
        void UpdateBufferData(long size, const void* data);
        void UnCreate();
        void Unbind();
        void Bind();
        
        GLVBO(long size, const void* data, cg::uint usage);
        ~ GLVBO();
        GLVBO();
        
    private:
        
        cg::uint type;
        cg::uint id;
    };
}}
#endif /* GLVBO_hpp */
