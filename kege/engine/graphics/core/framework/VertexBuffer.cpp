/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/16/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Vertexbuffer.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "VertexBuffer.hpp"
namespace kege{namespace core{
    
    const VertexLayout& VertexBuffer::GetVertexLayout()const
    {
        return vertex_layout;
    }
    VertexLayout& VertexBuffer::GetVertexLayout()
    {
        return vertex_layout;
    }
    
    VertexBuffer::VertexBuffer(long stride, long size, float * data)
    :   core::DataBuffer<cg::real>(stride, size, data)
    {
    }
    
    VertexBuffer::~ VertexBuffer(){}
    VertexBuffer::VertexBuffer(){}
    
}}
