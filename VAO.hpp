/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       VAO.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef VAO_hpp
#define VAO_hpp
#include "../../graphics/cgmath/cgm.hpp"
#include "../../graphics/framework/GFXEnum.hpp"
#include "../../graphics/framework/VBO.hpp"
#include "../../graphics/framework/IBO.hpp"
#include "../../graphics/framework/VertexBuffer.hpp"
namespace kege{namespace gfx{
    
    class VAO
    {
    public:
        
        virtual void DrawInstanced(cg::uint mode, cg::uint first, cg::uint count, cg::uint instancecount) = 0;
        virtual void Draw(cg::uint mode, cg::uint first, cg::uint count) = 0;
        
        virtual void AttachVBO(long size, cg::uint stride, const void* data, cg::uint usage, const VertexLayout& layout) = 0;
        virtual void AttachIBO(long size, const void* data, cg::uint usage) = 0;
        virtual void AttachVBO(const VertexBuffer& buffer, cg::uint usage) = 0;
        virtual void AttachIBO(const IndexBuffer& buffer, cg::uint usage) = 0;
        
        virtual void UnCreate() = 0;
        virtual void Create() = 0;
        virtual void Unbind() = 0;
        virtual void Bind() = 0;
        
        
        virtual VBO* GetVBO(int n) = 0;
        
        virtual ~ VAO(){}
    };
    
    typedef kege::shared< VAO > SharedVAO;
}}
#endif /* VAO_hpp */
