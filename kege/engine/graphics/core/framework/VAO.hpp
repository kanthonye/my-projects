/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       VAO.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef VAO_hpp
#define VAO_hpp
#include "../../../graphics/core/cgmath/cgm.hpp"
#include "../../../graphics/core/framework/GFXEnum.hpp"
#include "../../../graphics/core/framework/VBO.hpp"
#include "../../../graphics/core/framework/IBO.hpp"
#include "../../../graphics/core/framework/VertexBuffer.hpp"
namespace kege{namespace shared{
    typedef mem::shared< core::VBO > VBO;
    typedef mem::shared< core::IBO > IBO;
}}
namespace kege{namespace core{
    
    class VAO
    {
    public:
        
        virtual void DrawIndicesInstanced(cg::uint mode, cg::uint count, const void *indices, cg::uint instancecount)const = 0;
        virtual void DrawArraysInstanced(cg::uint mode, cg::uint first, cg::uint count, cg::uint instancecount)const = 0;
        virtual void DrawIndices(cg::uint mode, cg::uint count, const void *indices)const = 0;
        virtual void DrawArrays(cg::uint mode, cg::uint first, cg::uint count)const = 0;
        
        virtual void AttachVBO(long size, cg::uint stride, const void* data, cg::uint usage, const VertexLayout& layout) = 0;
        virtual void AttachVBO(const VertexBuffer& buffer, const VertexLayout& layout, cg::uint usage) = 0;
        virtual void AttachIBO(long size, const void* data, cg::uint usage) = 0;
        virtual void AttachVBO(const VertexBuffer& buffer, cg::uint usage) = 0;
        virtual void AttachIBO(const IndexBuffer& buffer, cg::uint usage) = 0;
        
        virtual void UnCreate() = 0;
        virtual void Create() = 0;
        virtual void Unbind()const = 0;
        virtual void Bind()const = 0;
        
        const shared::VBO& GetVBO()const {return _vbo;}
        const shared::IBO& GetIBO()const {return _ibo;}
        
        shared::VBO& GetVBO() {return _vbo;}
        shared::IBO& GetIBO() {return _ibo;}
        
        //virtual VBO* GetVBO(int n) = 0;
        
        virtual ~ VAO(){}
        
    protected:
        
        shared::VBO _vbo;
        shared::IBO _ibo;
    };
}}
namespace kege{namespace shared{
    typedef mem::shared< core::VAO > VAO;
}}
#endif /* VAO_hpp */
