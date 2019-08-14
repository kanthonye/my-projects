//
//  GUIRenderer.cpp
//  KEGE_GUI
//
//  Created by Kenneth Esdaile on 2/26/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//
#include "Graphics.hpp"
#include "DebugRenderer.hpp"
namespace kege {namespace gfx{

    void DebugRenderer::DrawBox(const cg::point3& min,const cg::point3& max, const cg::vec3& colr)
    {
        GetInatance().RenderAABB(min, max, colr);
    }
    void DebugRenderer::DrawLine(const cg::point3& p1,const cg::point3& p2, const cg::vec3& colr)
    {
        GetInatance().RenderLine(p1, p2, colr);
    }
    
    void DebugRenderer::DrawBox
    (   const cg::point3& center
     ,  const cg::point3& half
     ,  const cg::vec3& x
     ,  const cg::vec3& y
     ,  const cg::vec3& z
     ,  const cg::vec3& colr )
    {
        GetInatance().RenderOBB(center, half, x, y, z, colr);
    }
    
    void DebugRenderer::DrawBox
    (  const cg::point3& b0
     , const cg::point3& b1
     , const cg::point3& b2
     , const cg::point3& b3
     , const cg::point3& b4
     , const cg::point3& b5
     , const cg::point3& b6
     , const cg::point3& b7
     , const cg::point3& colr )
    {
        GetInatance().RenderBox(b0, b1, b2, b3, b4, b5, b6, b7, colr);
    }
    
    
    DebugRenderer& DebugRenderer::GetInatance()
    {
        static DebugRenderer renderer;
        return renderer;
    }
    
    void DebugRenderer::RenderOBB
    (   const cg::point3& center
     ,  const cg::point3& half
     ,  const cg::vec3& x
     ,  const cg::vec3& y
     ,  const cg::vec3& z
     ,  const cg::vec3& colr  )
    {
        cg::vec3 vertices[8] =
        {     cg::vec3(-half.x, -half.y, -half.z)
            , cg::vec3( half.x, -half.y, -half.z)
            , cg::vec3( half.x,  half.y, -half.z)
            , cg::vec3(-half.x,  half.y, -half.z)
            
            , cg::vec3(-half.x, -half.y,  half.z)
            , cg::vec3( half.x, -half.y,  half.z)
            , cg::vec3( half.x,  half.y,  half.z)
            , cg::vec3(-half.x,  half.y,  half.z)
        };
        
        cg::mat33 m(x,y,z);
        
        vertices[0] = m*vertices[0] + center;
        vertices[1] = m*vertices[1] + center;
        vertices[2] = m*vertices[2] + center;
        vertices[3] = m*vertices[3] + center;
        vertices[4] = m*vertices[4] + center;
        vertices[5] = m*vertices[5] + center;
        vertices[6] = m*vertices[6] + center;
        vertices[7] = m*vertices[7] + center;
        
        RenderBox(vertices[0], vertices[1], vertices[2], vertices[3], vertices[4], vertices[5], vertices[6], vertices[7], colr);
    }
    
    void DebugRenderer::RenderAABB(const cg::point3& min,const cg::point3& max, const cg::vec3& colr)
    {
        RenderBox
        (  cg::point3(min.x, min.y, min.z)
         , cg::point3(max.x, min.y, min.z)
         , cg::point3(max.x, max.y, min.z)
         , cg::point3(min.x, max.y, min.z)
         
         , cg::point3(min.x, min.y, max.z)
         , cg::point3(max.x, min.y, max.z)
         , cg::point3(max.x, max.y, max.z)
         , cg::point3(min.x, max.y, max.z)
         , colr );
    }
    
    void DebugRenderer::RenderLine(const cg::point3& p1,const cg::point3& p2, const cg::vec3& colr)
    {
        if ( VertexCapacityFull() ) return;
        
        BeginVertices();
        AddVertex(p1, colr);
        AddVertex(p2, colr);
        EndVertices();
        AddIncides(0, 1);
    }
    
    void DebugRenderer::RenderBox
    (  const cg::point3& b0
     , const cg::point3& b1
     , const cg::point3& b2
     , const cg::point3& b3
     , const cg::point3& b4
     , const cg::point3& b5
     , const cg::point3& b6
     , const cg::point3& b7
     , const cg::point3& colr )
    {
        if ( VertexCapacityFull() ) return;
        
        BeginVertices();
        AddVertex(b0, colr);
        AddVertex(b1, colr);
        AddVertex(b2, colr);
        AddVertex(b3, colr);
        AddVertex(b4, colr);
        AddVertex(b5, colr);
        AddVertex(b6, colr);
        AddVertex(b7, colr);
        EndVertices();
        
        AddIncides(0, 1);
        AddIncides(1, 2);
        AddIncides(2, 3);
        AddIncides(3, 0);
        
        AddIncides(4, 5);
        AddIncides(5, 6);
        AddIncides(6, 7);
        AddIncides(7, 4);
        
        AddIncides(0, 4);
        AddIncides(1, 5);
        AddIncides(2, 6);
        AddIncides(3, 7);
    }
    
    void DebugRenderer::AddVertexArray(int size, cg::point3 const* p)
    {
        int i=0;
        while (i<size) AddVertex(p[i++]);
    }
    
    void DebugRenderer::AddVertex(cg::point3 const& p,cg::point3 const& c)
    {
        if ( VertexCapacityFull() ) return;
        points[total_point++] = p;
        points[total_point++] = c;
        vertices++;
    }
    void DebugRenderer::AddVertex(cg::point3 const& p)
    {
        if ( VertexCapacityFull() ) return;
        points[total_point++] = p;
        points[total_point++] = 1.0;
        vertices++;
    }
    
    void DebugRenderer::BeginVertices()
    {
        begin_vertex = vertices;
    }
    void DebugRenderer::EndVertices()
    {
        end_vertex = vertices;
    }
    
    void DebugRenderer::AddIncides(int a, int b)
    {
        if ( IndexCapacityFull() )
            return;
        
        indices[index_counter++] = begin_vertex + a;
        indices[index_counter++] = begin_vertex + b;
    }
    
    void DebugRenderer::Render()
    {
//        if (shader.GetProgram().Handle() == 0) Refresh();
//        if (!vao.IsDrawable() || index_counter==0 || vertices<=1) Refresh();
        
//        EnableDepthTest();
//        DisableCulling();
//        DisableBlending();
        
//        shader.UseShader();
//        vao.Bind();
//        vao.GetEBO().Bind();
//        vao.GetVBO().Bind();
//        {
//            int stride = (int)(sizeof(cg::point3) * 2);
//            vao.GetVBO().SubBufferData(0, stride*vertices, points);
//            vao.GetEBO().SubBufferData(0, sizeof(int)*index_counter, indices);
//            glDrawElements(GL_LINES, index_counter, GL_UNSIGNED_INT, (const void*)0);
//        }
//        vao.GetVBO().Unbind();
//        vao.GetEBO().Unbind();
//        vao.Unbind();
//        shader.UnuseShader();
        Refresh();
    }
    
    void DebugRenderer::Refresh()
    {
        vertices = 0;
        index_counter = 0;
        begin_vertex = 0;
        end_vertex = 0;
        total_point = 0;
    }
    bool DebugRenderer::VertexCapacityFull()
    {
        return (vertices >= MAX_VERTEX_COUNT);
    }
    
    bool DebugRenderer::IndexCapacityFull()
    {
        return (index_counter >= MAX_INDICE_COUNT);
    }
    
    bool DebugRenderer::Init()
    {
        shader = gfx::Graphics::CreateShader("~/shaders/entity/entity-shader.shdr");
        if ( shader != nullptr)
        {
            if ( vao != nullptr ) return true;
            VertexLayout layout;
            layout.AddElem(0, 3, 0);
            vao = Graphics::CreateVAO();
            vao->AttachVBO(MAX_VERTEX_COUNT, 3*sizeof(float), points, gfx::STREAM_DRAW, layout);
            vao->AttachIBO(MAX_INDICE_COUNT, indices, gfx::STREAM_DRAW);
            return true;
        }
        return false;
    }
    
    DebugRenderer::DebugRenderer()
    :   vertices(0)
    ,   index_counter(0)
    ,   begin_vertex(0)
    ,   end_vertex(0)
    ,   total_point(0)
    {
    }
    
    DebugRenderer::~ DebugRenderer()
    {
//        rmesh.Destroy();
    }
}}


