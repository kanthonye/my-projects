/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/14/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Geometry.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef Geometry_hpp
#define Geometry_hpp
#include "../../../graphics/core/framework/VAO.hpp"
#include "../../../graphics/core/mesh/DrawElement.hpp"
#include "../../../graphics/core/framework/VertexBuffer.hpp"
namespace kege{namespace gfx{
    
    class Geometry
    {
    public:
        
        void DrawInstanced( const shared::DrawElement& draw, cg::uint instances )const;
        void Draw( const shared::DrawElement& draw, const cg::mat44& transform )const;
        
        const shared::VertexBuffer& GetVertexBuffer()const;
        const shared::IndexBuffer&  GetIndexBuffer()const;
        
        shared::VertexBuffer& GetVertexBuffer();
        shared::IndexBuffer&  GetIndexBuffer();
        
        void SetCenterPoint(const cg::point3& box);
        const cg::point3& GetCenterPoint()const;
        
        void SetMinPoint(const cg::point3& box);
        const cg::point3& GetMinPoint()const;
        
        void SetMaxPoint(const cg::point3& box);
        const cg::point3& GetMaxPoint()const;
        
        void operator = ( const Geometry& geom );
        
        bool IsBinded()const;
        void Unbind()const;
        void Bind()const;
        void UnInit();
        bool Init();
        
        Geometry( core::VertexBuffer* vb, core::IndexBuffer* ib );
        Geometry( const Geometry& geom );
        ~ Geometry();
        Geometry();
        
    private:
        
        shared::VertexBuffer _vertex_buffer;
        shared::IndexBuffer  _index_buffer;
        shared::VAO _vao;
        
        cg::point3 _center;
        cg::point3 _min;
        cg::point3 _max;
        
        bool _isbind;
        bool _init;
    };
}}
namespace kege{namespace shared{
    typedef mem::shared< gfx::Geometry > Geometry;
}}

namespace kege{namespace gfx{
    
    class DrawTriangles : public gfx::DrawElement
    {
    public:
        DrawTriangles( cg::uint starting_index, cg::uint draw_count, const shared::Material& material )
        :   DrawElement( core::DRAW_TRIANGLES, starting_index, draw_count, material )
        {}
        DrawTriangles( const shared::Geometry& geomtry, const shared::Material& material )
        :   DrawElement( core::DRAW_TRIANGLES, 0, (cg::uint) geomtry->GetIndexBuffer()->size(), material )
        {}
    };
    
    class DrawPoints : public gfx::DrawElement
    {
    public:
        DrawPoints( cg::uint starting_index, cg::uint draw_count, const shared::Material& material )
        :   DrawElement( core::DRAW_POINTS, starting_index, draw_count, material )
        {}
        DrawPoints( const shared::Geometry& geomtry, const shared::Material& material )
        :   DrawElement( core::DRAW_POINTS, 0, (cg::uint) geomtry->GetIndexBuffer()->size(), material )
        {}
    };
}}

#endif /* Geometry_hpp */
