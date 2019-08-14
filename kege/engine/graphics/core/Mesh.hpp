//
//  Mesh.hpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 5/24/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp
#include "VAO.hpp"
#include "IBO.hpp"
#include "VBO.hpp"
#include "array.hpp"
#include "string.hpp"
#include "enumtypes.hpp"
#include "../framework/VertexBuffer.hpp"
namespace kege{namespace gfx{
    
    class Mesh
    {
    public:
        
        struct Polygon
        {
            cg::uint mode;   // draw mode
            cg::uint start;  // starting vertex index
            cg::uint count;  // total vertex indices to draw index
        };
        
        void AddPolygon(cg::uint mode, cg::uint start, cg::uint count);
        const Mesh::Polygon& GetPolygon(cg::uint i)const;
        cg::uint Polygons() const;
        
        const gfx::VertexBuffer& GetVertexBuffer()const;
        gfx::VertexBuffer& GetVertexBuffer();
        
        const gfx::IndexBuffer& GetIndexBuffer()const;
        gfx::IndexBuffer& GetIndexBuffer();
        
        void SetCenterPoint(const cg::point3& box);
        const cg::point3& GetCenterPoint()const;
        
        void SetMinPoint(const cg::point3& box);
        const cg::point3& GetMinPoint()const;
        
        void SetMaxPoint(const cg::point3& box);
        const cg::point3& GetMaxPoint()const;
        
        void SetStrType(ds::string const& name);
        ds::string const& GetStrType()const;
        ds::string & GetStrType();
        
        bool IsBinded()const;
        void UnInit();
        bool Init();
        
        void Unbind()const;
        void Bind()const;
        void Draw()const;
        
        void Destory();
        virtual ~Mesh();
        Mesh();
        
    private:
        
        ds::array< Polygon > elements;
        gfx::VertexBuffer vertex_buffer;
        gfx::IndexBuffer  index_buffer;
        
        gfx::VAO* vao;
        
        ds::string stype;
        cg::point3 center;
        cg::point3 min;
        cg::point3 max;
        
        bool isbind;
    };
    
    typedef shared<Mesh> SharedMesh;
}}
#endif /* Mesh_hpp */
