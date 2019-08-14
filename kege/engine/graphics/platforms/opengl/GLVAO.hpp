/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GLVAO.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GLVAO_hpp
#define GLVAO_hpp
#include "../../../graphics/framework/VAO.hpp"
namespace kege{namespace gfx{
    
    class GLVAO : public gfx::VAO
    {
    public:
        
        void DrawInstanced(cg::uint mode, cg::uint first, cg::uint count, cg::uint instancecount) override;
        void Draw(cg::uint mode, cg::uint first, cg::uint count) override;
        
        void AttachVBO(long size, cg::uint stride, const void* data, cg::uint usage, const VertexLayout& layout) override;
        void AttachIBO(long size, const void* data, cg::uint usage) override;
        void AttachVBO(const VertexBuffer& buffer, cg::uint usage) override;
        void AttachIBO(const IndexBuffer& buffer, cg::uint usage) override;
        
        VBO* GetVBO(int n) override { return vertex_buffers[n]; }
        
        void UnCreate() override;
        void Create() override;
        void Unbind() override;
        void Bind() override;
        ~ GLVAO();
        GLVAO();
        
    private:
        
        ds::array< VBO* > vertex_buffers;
        IBO* ibo;
        cg::uint id;
    };
}}
#endif /* GLVAO_hpp */
