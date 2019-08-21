/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/16/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Vertexbuffer.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef VertexBuffer_hpp
#define VertexBuffer_hpp
#include "../../../graphics/core/framework/DataBuffer.hpp"
#include "../../../graphics/core/framework/VertexLayout.hpp"
namespace kege{namespace core{
    
    class VertexBuffer : public core::DataBuffer< cg::real >
    {
    public:
        
        const VertexLayout& GetVertexLayout()const;
        VertexLayout& GetVertexLayout();
        
        VertexBuffer(long stride, long size, float * data);
        ~ VertexBuffer();
        VertexBuffer();
        
    private:
        
        VertexLayout vertex_layout;
    };
    
    typedef core::DataBuffer<cg::uint> IndexBuffer;
}}
namespace kege{namespace shared{
    typedef mem::shared< core::VertexBuffer > VertexBuffer;
    typedef mem::shared< core::IndexBuffer > IndexBuffer;
}}
#endif /* Vertexbuffer_hpp */
