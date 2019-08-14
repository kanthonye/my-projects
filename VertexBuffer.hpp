/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/16/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Vertexbuffer.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef VertexBuffer_hpp
#define VertexBuffer_hpp
#include "DataBuffer.hpp"
#include "VertexLayout.hpp"
namespace kege{namespace gfx{
    
    class VertexBuffer : public DataBuffer<cg::real>
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
}}
#endif /* Vertexbuffer_hpp */
