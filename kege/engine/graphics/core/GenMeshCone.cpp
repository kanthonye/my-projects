//
//  Cone.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/11/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#include "GenMeshCone.hpp"
namespace kege{namespace gfx{
    
    void GenMeshCone(gfx::Mesh& mesh, float radius, int min_height, int max_height, int columns)
    {
        mesh.SetStrType("CONE");
        columns = (columns <= 3) ? 3 : columns;
        
        mesh.SetMaxPoint(cg::point3( radius, max_height, radius));
        mesh.SetMinPoint(cg::point3(-radius,-min_height,-radius));
        
        gfx::Mesh temp_mesh;
        gfx::VertexBuffer* vb = &temp_mesh.GetVertexBuffer();
        vb->setbuffer(8 * columns + 2, 8, 0);
        
        gfx::DataBuffer<cg::uint>* indices = &temp_mesh.GetIndexBuffer();
        indices->setbuffer(columns * 3 * 2, 1, 0);
        indices->setcount(0);
        
        // SET THE BOTTOM CENTER VERTEX OF THE CIRCLE
        vb->add3(0.0, max_height, 0.0);
        vb->add3(0.0, 1.0, 0.0);
        vb->add2(0.0, 0.0);
        
        vb->add3(0.0, min_height, 0.0);
        vb->add3(0.0, -1.0, 0.0);
        vb->add2(0.0, 0.0);
        
        int m;
        const float segments = 6.28318530718 / (float)columns;
        float nx,ny;
        float rad;
        // CALCULATE THE BOTTOM CORCLE VERTICES WITH RESPECT TO THE CENTER
        for (m=0; m<columns;m++)
        {
            rad = segments * m;
            nx = cosf(rad);
            ny = sinf(rad);
            
            vb->add3(nx*radius, 0.0, ny*radius);
            vb->add3(nx, 0.0, ny);
            vb->add2(nx, ny);
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
        
        //for (m=0; m<indices->size(); m+=3)
        //{
        //    printf("[%i] %i %i %i\n", m, indices->get(m), indices->get(m+1), indices->get(m+2));
        //}
    
        int a,b,c;
        cg::vec3 norm;
        const short vertex_stride = 8;
        gfx::DataBuffer<float>* vertices = &mesh.GetVertexBuffer();
        vertices->setbuffer(vertex_stride * indices->size(), vertex_stride, 0);
        mesh.GetVertexBuffer().GetVertexLayout().AddElem(gfx::VERTEX_POSITION, 3, 0);
        mesh.GetVertexBuffer().GetVertexLayout().AddElem(gfx::VERTEX_NORMAL,   3, 3);
        mesh.GetVertexBuffer().GetVertexLayout().AddElem(gfx::VERTEX_TEXCOORD, 2, 6);
        
        bool flat_base = (min_height != 0);
        bool compute_normal = true;
        for (m=0; m<indices->size(); m+=3)
        {
            a = indices->get( m ) * vertex_stride;
            b = indices->get(m+1) * vertex_stride;
            c = indices->get(m+2) * vertex_stride;
            if (flat_base || compute_normal)
            {
                norm.x = (vb->get(a+3) + vb->get(b+3) + vb->get(c+3)) / 3.0;
                norm.y = (vb->get(a+4) + vb->get(b+4) + vb->get(c+4)) / 3.0;
                norm.z = (vb->get(a+5) + vb->get(b+5) + vb->get(c+6)) / 3.0;
                compute_normal = false;
            }
            else
            {
                norm.x =  0.0;
                norm.y = -1.0;
                norm.z =  0.0f;
                compute_normal = true;
            }
            
            vertices->add3(vb->get(a), vb->get(a+1), vb->get(a+2));
            vertices->add3(norm.x, norm.y, norm.z);
            vertices->add2(vb->get(a+6), vb->get(a+7));
            
            vertices->add3(vb->get(b), vb->get(b+1), vb->get(b+2));
            vertices->add3(norm.x, norm.y, norm.z);
            vertices->add2(vb->get(b+6), vb->get(b+7));
            
            vertices->add3(vb->get(c), vb->get(c+1), vb->get(c+2));
            vertices->add3(norm.x, norm.y, norm.z);
            vertices->add2(vb->get(c+6), vb->get(c+7));
        }
    }
    
    void GenMeshCone(gfx::Mesh& mesh, float radius, int height, int columns)
    {
        gfx::GenMeshCone(mesh, radius, 0, height, columns);
    }
    
//    gfx::Entity* GenPolyEntityCone(gfx::Mesh& mesh, float radius, int min_height, int max_height, int columns)
//    {
//        return nullptr;
//    }
}}
