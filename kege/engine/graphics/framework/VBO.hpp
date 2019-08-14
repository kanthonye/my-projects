/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       VBO.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef VBO_hpp
#define VBO_hpp
#include "../../graphics/cgmath/cgm.hpp"
#include "../../graphics/framework/GFXEnum.hpp"
namespace kege{namespace gfx{
    
    class VBO
    {
    public:
        
        virtual void Create(long size, const void* data, cg::uint usage) = 0;
        virtual void UpdateBufferData(long size, const void* data) = 0;
        virtual void UnCreate() = 0;
        virtual void Unbind() = 0;
        virtual void Bind() = 0;
        virtual ~ VBO(){}
    };
}}
#endif /* VBO_hpp */
