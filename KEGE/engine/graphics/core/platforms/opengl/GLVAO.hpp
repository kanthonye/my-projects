/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GLVAO.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GLVAO_hpp
#define GLVAO_hpp
#include "../../../../graphics/core/framework/VAO.hpp"
namespace kege{namespace core{
    
    class GLVAO : public core::VAO
    {
    public:
        
        void DrawIndicesInstanced(cg::uint mode, cg::uint count, const void *indices, cg::uint instancecount)const override;
        void DrawArraysInstanced(cg::uint mode, cg::uint first, cg::uint count, cg::uint instancecount)const override;
        void DrawIndices(cg::uint mode, cg::uint count, const void *indices)const override;
        void DrawArrays(cg::uint mode, cg::uint first, cg::uint count)const override;
        
        void AttachVBO(long size, cg::uint stride, const void* data, cg::uint usage, const VertexLayout& layout) override;
        void AttachVBO( const VertexBuffer& buffer, const VertexLayout& layout, cg::uint usag ) override;
        void AttachIBO(long size, const void* data, cg::uint usage) override;
        void AttachVBO(const VertexBuffer& buffer, cg::uint usage) override;
        void AttachIBO(const IndexBuffer& buffer, cg::uint usage) override;
        
        //VBO* GetVBO(int n) override { return vertex_buffers[n]; }
        
        void UnCreate() override;
        void Create() override;
        void Unbind()const override;
        void Bind()const override;
        ~ GLVAO();
        GLVAO();
        
    private:
        
        cg::uint id;
    };
}}
#endif /* GLVAO_hpp */
