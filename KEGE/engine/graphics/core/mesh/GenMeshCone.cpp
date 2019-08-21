//
//  Cone.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/11/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//
#include "../../../graphics/core/mesh/GenMesh.hpp"
#include "../../../graphics/core/Graphics.hpp"
namespace kege{namespace gfx{
    
    int GenMeshConeSmooth(core::VertexBuffer* vertices, core::IndexBuffer* indices, float radius, int min_height, int max_height, int columns )
    {
        int m = 0;
        //mesh.SetMaxPoint(cg::point3( radius, max_height, radius));
        columns = (columns <= 3) ? 3 : columns;
        vertices->setbuffer(8 * columns + 2, 8, 0);
        indices->setbuffer(columns * 3 * 2, 1, 0);
        indices->setcount(0);
        
        // SET THE BOTTOM CENTER VERTEX OF THE CIRCLE
        vertices->add3(0.0, max_height, 0.0);
        vertices->add3(0.0, 1.0, 0.0);
        vertices->add2(0.0, 0.0);
        
        vertices->add3(0.0, min_height, 0.0);
        vertices->add3(0.0, -1.0, 0.0);
        vertices->add2(0.0, 0.0);
        
        const float segments = 6.28318530718 / (float)columns;
        float nx,ny;
        float rad;
        // CALCULATE THE BOTTOM CORCLE VERTICES WITH RESPECT TO THE CENTER
        for (m=0; m<columns;m++)
        {
            rad = segments * m;
            nx = cosf(rad);
            ny = sinf(rad);
            
            vertices->add3(nx*radius, 0.0, ny*radius);
            vertices->add3(nx, 0.0, ny);
            vertices->add2(nx, ny);
        }
        
        for (m=0; m<columns; m++)
        {
            indices->add3(0, m+3, m+2);
            indices->add3(1, m+2, m+3);
        }
        m = 6 * (columns-1) + 1;
        indices->getref(m)  = 2;
        m = 6 * (columns-1) + 5;
        indices->getref(m)  = 2;
        
        return m;
    }
    
    shared::Geometry GenMeshConeSmooth( float radius, int min_height, int max_height, int columns, int& m )
    {
        core::VertexBuffer* vb = new core::VertexBuffer;
        core::IndexBuffer* ib = new core::IndexBuffer;
        GenMeshConeSmooth( vb, ib, radius, min_height, max_height, columns );
        return new gfx::Geometry( vb, ib );
    }
    
    shared::Geometry GenMeshConeFlat( float radius, int min_height, int max_height, int columns )
    {
        core::VertexBuffer vb;
        core::IndexBuffer ib;
        GenMeshConeSmooth( &vb, &ib, radius, min_height, max_height, columns );
    
        int a,b,c;
        cg::vec3 norm;
        const short vertex_stride = 8;
        core::VertexBuffer* vertices = new core::VertexBuffer;
        vertices->setbuffer(vertex_stride * ib.size(), vertex_stride, 0);
        
        bool flat_base = (min_height != 0);
        bool compute_normal = true;
        for (int m=0; m<ib.size(); m+=3)
        {
            a = ib.get( m ) * vertex_stride;
            b = ib.get(m+1) * vertex_stride;
            c = ib.get(m+2) * vertex_stride;
            
            if (flat_base || compute_normal)
            {
                norm.x = (vb.get(a+3) + vb.get(b+3) + vb.get(c+3)) / 3.0;
                norm.y = (vb.get(a+4) + vb.get(b+4) + vb.get(c+4)) / 3.0;
                norm.z = (vb.get(a+5) + vb.get(b+5) + vb.get(c+6)) / 3.0;
                compute_normal = false;
            }
            else
            {
                norm.x =  0.0;
                norm.y = -1.0;
                norm.z =  0.0f;
                compute_normal = true;
            }
            
            vertices->add3(vb.get(a), vb.get(a+1), vb.get(a+2));
            vertices->add3(norm.x, norm.y, norm.z);
            vertices->add2(vb.get(a+6), vb.get(a+7));
            
            vertices->add3(vb.get(b), vb.get(b+1), vb.get(b+2));
            vertices->add3(norm.x, norm.y, norm.z);
            vertices->add2(vb.get(b+6), vb.get(b+7));
            
            vertices->add3(vb.get(c), vb.get(c+1), vb.get(c+2));
            vertices->add3(norm.x, norm.y, norm.z);
            vertices->add2(vb.get(c+6), vb.get(c+7));
        }
        
        core::VertexLayout* layout = &vertices->GetVertexLayout();
        {
            layout->AddElem(core::VERTEX_POSITION, 3,0);
            layout->AddElem(core::VERTEX_NORMAL,   3,3);
            layout->AddElem(core::VERTEX_TEXCOORD, 2,6);
        }
        return new gfx::Geometry( vertices, nullptr );
    }
}}
