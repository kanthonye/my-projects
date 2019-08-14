//
//  Mesh.cpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 5/24/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "../core/Mesh.hpp"
#include "../core/Graphics.hpp"
namespace kege{namespace gfx{
    
    void gfx::Mesh::AddPolygon(cg::uint mode, cg::uint start, cg::uint count)
    {
        mode = gfx::Graphics::GetConstant( mode );
        elements.resize( elements.size() + 1 );
        elements[ elements.size() - 1 ] = {mode, start, count};
    }
    
    const gfx::Mesh::Polygon& gfx::Mesh::GetPolygon(cg::uint i)const
    {
        return elements[i];
    }
    
    cg::uint gfx::Mesh::Polygons()const
    {
        return (cg::uint) elements.size();
    }
        
    const gfx::VertexBuffer& gfx::Mesh::GetVertexBuffer()const
    {
        return vertex_buffer;
    }
    
    gfx::VertexBuffer& gfx::Mesh::GetVertexBuffer()
    {
        return vertex_buffer;
    }
    
    const gfx::IndexBuffer& gfx::Mesh::GetIndexBuffer()const
    {
        return index_buffer;
    }
    
    gfx::IndexBuffer& gfx::Mesh::GetIndexBuffer()
    {
        return index_buffer;
    }
    
    void gfx::Mesh::SetCenterPoint(const cg::point3& val)
    {
        center = val;
    }
    
    const cg::point3& gfx::Mesh::GetCenterPoint()const
    {
        return center;
    }
    
    void gfx::Mesh::SetMinPoint(const cg::point3& m)
    {
        min = m;
    }
    
    const cg::point3& gfx::Mesh::GetMinPoint()const
    {
        return min;
    }
    
    void gfx::Mesh::SetMaxPoint(const cg::point3& m)
    {
        max = m;
    }
    
    const cg::point3& gfx::Mesh::GetMaxPoint()const
    {
        return max;
    }
    
    void gfx::Mesh::SetStrType(ds::string const& name)
    {
        stype = name;
    }
    ds::string const& gfx::Mesh::GetStrType()const
    {
        return stype;
    }
    ds::string & gfx::Mesh::GetStrType()
    {
        return stype;
    }
    
    bool Mesh::IsBinded()const
    {
        return isbind;
    }
    
    void Mesh::UnInit()
    {
        if (vao != nullptr)
        {
            delete vao;
            vao = nullptr;
        }
    }
    
    bool Mesh::Init()
    {
        if ( vao != nullptr ) return true;
        if ( vertex_buffer.empty() ) return false;
        
        vao = Graphics::CreateVAO();
        if ( vertex_buffer.size() != 0 ) vao->AttachVBO( vertex_buffer, gfx::STATIC_DRAW );
        if ( index_buffer.size()  != 0 ) vao->AttachIBO( index_buffer, gfx::STATIC_DRAW );
        vao->Unbind();
        
        if ( elements.size() == 0 )
        {
            if ( !index_buffer.empty() )
            {
                cg::uint draw_count = (cg::uint) index_buffer.size();
                AddPolygon(gfx::DRAW_TRIANGLES, 0, draw_count);
            }
            else
            {
                cg::uint draw_count = (cg::uint) vertex_buffer.size() / vertex_buffer.getstride();
                draw_count = (cg::uint) vertex_buffer.size() / 3;
                AddPolygon(gfx::DRAW_TRIANGLES, 0, draw_count);
            }
        }
        return true;
    }
    
    void Mesh::Destory()
    {
        UnInit();
        vertex_buffer.clear();
        index_buffer.clear();
    }
    
    void Mesh::Unbind() const
    {
        if ( vao == nullptr ) return;
        const_cast<bool&>(isbind) = true;
        vao->Unbind();
    }
    void Mesh::Bind() const
    {
        if ( vao == nullptr ) return;
        const_cast<bool&>(isbind) = true;
        vao->Bind();
    }
    void Mesh::Draw()const
    {
        if ( !IsBinded() ) return;
        
        for (int i=0; i<elements.size(); i++)
        {
            vao->Draw(elements[i].mode, elements[i].start, elements[i].count);
        }
    }
    Mesh:: ~Mesh()
    {
        Destory();
    }
    
    Mesh::Mesh()
    :   isbind(false)
    ,   vao(nullptr)
    {}
}}
