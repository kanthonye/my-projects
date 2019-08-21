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
#define MAX_VERTEX_COUNT 32768
#define MAX_INDICE_COUNT 32768
    class DebugRenderer
    {
    public:
        
        void DrawCube
        (  const cg::point3& b0, const cg::point3& b1, const cg::point3& b2, const cg::point3& b3
         , const cg::point3& b4, const cg::point3& b5, const cg::point3& b6, const cg::point3& b7  );
        
        void DrawQuad( const cg::point3& p0, const cg::point3& p1, const cg::point3& p2, const cg::point3& p3 );
        void DrawTriangle( const cg::point3& p0, const cg::point3& p1, const cg::point3& p2 );
        void DrawLine( const cg::point3& p0, const cg::point3& p1 );
        void DrawPoint( const cg::point3& p0 );
        void SetColor( const cg::vec3& colr );
        
        void DrawCube( const cg::point3& min,const cg::point3& max );
        
        void AddVertexArray(int size, cg::point3 const* p1);
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
        
        static DebugRenderer& GetInatance();
        
    private:
        
        cg::point3 _points[ MAX_VERTEX_COUNT ];
        unsigned _indices[ MAX_INDICE_COUNT ];
        
        shared::Shader _shader;
        shared::VAO _vao;
        cg::mat44 _model;
        cg::vec3 _color;
        
        int _begin_vertex;
        int _end_vertex;
        int _index_counter;
        int _total_point;
        int _vertices;
    };
    
    
    void DebugRenderer::DrawCube
    (  const cg::point3& p0, const cg::point3& p1, const cg::point3& p2, const cg::point3& p3
     , const cg::point3& p4, const cg::point3& p5, const cg::point3& p6, const cg::point3& p7  )
    {
        DrawQuad( p0, p1, p2, p3 );
        DrawQuad( p0, p4, p5, p1 );
        DrawQuad( p1, p5, p6, p2 );
        DrawQuad( p2, p6, p7, p3 );
        DrawQuad( p3, p7, p4, p0 );
        DrawQuad( p4, p5, p6, p7 );
    }
    
    void DebugRenderer::DrawQuad( const cg::point3& p0, const cg::point3& p1, const cg::point3& p2, const cg::point3& p3 )
    {
        DrawTriangle( p0, p1, p2 );
        DrawTriangle( p2, p3, p0 );
    }
    
    void DebugRenderer::DrawTriangle( const cg::point3& p0, const cg::point3& p1, const cg::point3& p2 )
    {
        DrawLine( p0, p1 );
        DrawLine( p1, p2 );
        DrawLine( p2, p0 );
    }
    
    void DebugRenderer::DrawLine( const cg::point3& p0, const cg::point3& p1 )
    {
        BeginVertices();
        {
            DrawPoint( p0 );
            DrawPoint( p1 );
        }
        EndVertices();
        AddIncides( 0, 1 );
    }
    
    void DebugRenderer::DrawPoint( const cg::point3& p0 )
    {
        if ( VertexCapacityFull() ) return;
        _points[ _total_point++ ] = p0;
        _points[ _total_point++ ] = _color;
        _vertices++;
    }
    
    void DebugRenderer::SetColor( const cg::point3& colr )
    {
        _color = colr;
    }
    
    void DebugRenderer::DrawCube( const cg::point3& min,const cg::point3& max )
    {
        DrawCube
        (  cg::point3(min.x, min.y, min.z)
         , cg::point3(max.x, min.y, min.z)
         , cg::point3(max.x, max.y, min.z)
         , cg::point3(min.x, max.y, min.z)
         
         , cg::point3(min.x, min.y, max.z)
         , cg::point3(max.x, min.y, max.z)
         , cg::point3(max.x, max.y, max.z)
         , cg::point3(min.x, max.y, max.z)  );
    }
    
    DebugRenderer& DebugRenderer::GetInatance()
    {
        static DebugRenderer renderer;
        return renderer;
    }

    void DebugRenderer::AddVertexArray( int size, cg::point3 const* p )
    {
        int i=0;
        while (i<size) DrawPoint( p[ i++ ] );
    }
    
    void DebugRenderer::BeginVertices()
    {
        _begin_vertex = _vertices;
    }
    
    void DebugRenderer::EndVertices()
    {
        _end_vertex = _vertices;
    }
    
    void DebugRenderer::AddIncides( int a, int b )
    {
        if ( IndexCapacityFull() )
        {
            Render();
            return;
        }
        _indices[ _index_counter++ ] = _begin_vertex + a;
        _indices[ _index_counter++ ] = _begin_vertex + b;
    }
    
    void DebugRenderer::Render()
    {
        if ( _shader == nullptr ) Refresh();
        if ( _index_counter==0 || _vertices<=1 ) Refresh();
        
        //EnableDepthTest();
        //DisableCulling();
        //DisableBlending();
        
        _vao->Bind();
        _shader->Enable();
        {
            //_vao->GetVBO()->UpdateBufferData( stride*vertices, points );
            //_vao->GetIBO()->UpdateBufferData( sizeof(int)*_index_counter, _indices );
            _vao->DrawIndices( core::DRAW_LINES, 0, _indices );
        }
        _shader->Disable();
        _vao->Unbind();
        Refresh();
    }
    
    void DebugRenderer::Refresh()
    {
        _vertices = 0;
        _index_counter = 0;
        _begin_vertex = 0;
        _end_vertex = 0;
        _total_point = 0;
    }
    
    bool DebugRenderer::VertexCapacityFull()
    {
        return ( _vertices >= MAX_VERTEX_COUNT );
    }
    
    bool DebugRenderer::IndexCapacityFull()
    {
        return ( _index_counter >= MAX_INDICE_COUNT );
    }
    
    bool DebugRenderer::Init()
    {
        if ( _shader == nullptr)
        {
            _shader = gfx::Graphics::CreateShader( "~/shaders/entity/line-shader.shdr" );
            if ( _vao != nullptr )
            {
                _vao = gfx::Graphics::CreateVAO();
                
                core::VertexLayout layout;
                layout.AddElem( 0, 3, 0 );
                layout.AddElem( 1, 3, 3 );
                
                _vao = Graphics::CreateVAO();
                _vao->AttachVBO( MAX_VERTEX_COUNT, 6 * sizeof(float), _points, core::STREAM_DRAW, layout );
                _vao->AttachIBO( MAX_INDICE_COUNT, _indices, core::STREAM_DRAW );
            }
            return true;
        }
        return false;
    }
    
    DebugRenderer::DebugRenderer()
    :   _model( 1.0 )
    ,   _color( 1.0 )
    ,   _begin_vertex( 0 )
    ,   _end_vertex( 0 )
    ,   _index_counter( 0 )
    ,   _total_point( 0 )
    ,   _vertices( 0 )
    {
    }
    
    DebugRenderer::~ DebugRenderer()
    {
    }
}}


