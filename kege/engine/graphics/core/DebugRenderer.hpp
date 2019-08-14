//
//  GUIRenderer.hpp
//  KEGE_GUI
//
//  Created by Kenneth Esdaile on 2/26/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef DebugRenderer_hpp
#define DebugRenderer_hpp
#include "Renderer.hpp"
namespace kege {namespace gfx{
#define MAX_VERTEX_COUNT 32768
#define MAX_INDICE_COUNT 32768
    class DebugRenderMsg;
    
    class DebugRenderer : public gfx::Renderer
    {
        static DebugRenderer& GetInatance();
    public:
        
        void RenderOBB(const cg::point3& center,const cg::point3& half, const cg::vec3& x, const cg::vec3& y, const cg::vec3& z, const cg::vec3& colr);
        void RenderAABB(const cg::point3& min,const cg::point3& max, const cg::vec3& colr);
        void RenderLine(const cg::point3& p1,const cg::point3& p2, const cg::vec3& colr);
        
        void RenderBox
        (  const cg::point3& b0
         , const cg::point3& b1
         , const cg::point3& b2
         , const cg::point3& b3
         , const cg::point3& b4
         , const cg::point3& b5
         , const cg::point3& b6
         , const cg::point3& b7
         , const cg::point3& colr );
        
        void AddVertexArray(int size, cg::point3 const* p1);
        void AddVertex(cg::point3 const& p,cg::point3 const& c);
        void AddVertex(cg::point3 const& p);
        void AddIncides(int a, int b);
        bool VertexCapacityFull();
        bool IndexCapacityFull();
        void BeginVertices();
        void EndVertices();
        
        void Render();
        bool Init();
        
        void Refresh();
        ~ DebugRenderer();
        DebugRenderer();
    public:
        
        static void DrawBox(const cg::point3& min,const cg::point3& max, const cg::vec3& colr);
        static void DrawLine(const cg::point3& p1,const cg::point3& p2, const cg::vec3& colr);
        
        static void DrawBox
        (   const cg::point3& center
         ,  const cg::point3& half
         ,  const cg::vec3& x
         ,  const cg::vec3& y
         ,  const cg::vec3& z
         ,  const cg::vec3& colr );
        
        static void DrawBox
        (  const cg::point3& b0
         , const cg::point3& b1
         , const cg::point3& b2
         , const cg::point3& b3
         , const cg::point3& b4
         , const cg::point3& b5
         , const cg::point3& b6
         , const cg::point3& b7
         , const cg::point3& colr );
        
    private:
        
        cg::point3 points[MAX_VERTEX_COUNT];
        unsigned indices[MAX_INDICE_COUNT];
        
        int end_vertex;
        int begin_vertex;
        int index_counter;
        int vertices;
        int total_point;
        cg::mat44 model;
        kege::shared< gfx::VAO > vao;
    };
}}

#endif /* Renderer2D_hpp */
