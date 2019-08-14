//
//  Ellipsoid.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/7/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#include "GenMeshEllipsoid.hpp"
namespace kege{namespace gfx{
    
    void GenMeshEllipsoid(gfx::Mesh& mesh, float x_radius, float y_radius, int cols, int rows)
    {
        mesh.SetStrType("ELLIPSOID");
        // make sure the length of the x, y, radius is not zero.
        x_radius = ((x_radius<0.0f) ? 1.0f: x_radius);
        y_radius = ((y_radius<0.0f) ? 1.0f: y_radius);
        // calculate the size of the vertices
        cols = (cols<3) ?3 :cols;
        rows = (rows<2) ?2 :rows;
        
        const float radianX = (6.28318530718/(float)cols); // 360/col
        const float radianY = (3.14159265359/(float)rows); // 180/row
        const float half_pi  =  1.57079632679;
        float cx,cy,sx,sy,x_angle, y_angle;
        int a,b,c,d,x,y;
        const int total_vertices = (rows - 1) * cols + 2;
        const int total_indices  = 6 * cols * (rows - 2) + 3 * cols * 2;
        
        const cg::uint stride = 8;
        
        mesh.SetMaxPoint(cg::point3( x_radius, y_radius, x_radius));
        mesh.SetMinPoint(cg::point3(-x_radius,-y_radius,-x_radius));
        
        gfx::DataBuffer<float>* vertices = &mesh.GetVertexBuffer();
        vertices->setbuffer(stride * total_vertices, stride, 0);
        mesh.GetVertexBuffer().GetVertexLayout().AddElem(VERTEX_POSITION, 3, 0);
        mesh.GetVertexBuffer().GetVertexLayout().AddElem(VERTEX_NORMAL  , 3, 3);
        mesh.GetVertexBuffer().GetVertexLayout().AddElem(VERTEX_TEXCOORD, 2, 6);
        vertices->setcount(0);
        
        gfx::DataBuffer<cg::uint>* indices = &mesh.GetIndexBuffer();
        indices->setbuffer(total_indices, 1, 0);
        indices->setcount(0);
        
        // COMPUTE MESH VERTICES
        {
            // TOP CENTER VERTEX
            vertices->add3(0.0f, y_radius, 0.0f);
            vertices->add3(0.0f, y_radius, 0.0f);
            vertices->add2(0.0f, 0.0f);
            
            // BOTTOM CENTER VERTEX
            vertices->add3(0.0f,-y_radius, 0.0f);
            vertices->add3(0.0f,-y_radius, 0.0f);
            vertices->add2(0.0f, 0.0f);
            
            // THE BODY VERTEX
            for (y=1; y<rows; y++)
            {
                y_angle = half_pi + (radianY * y);
                
                for (x=0; x<cols; x++)
                {
                    x_angle = radianX * x;
                    cx = cos(x_angle);
                    sx = sin(x_angle);
                    cy = cos(y_angle);
                    sy = sin(y_angle);
                    
                    vertices->add3(sx * cy * x_radius, sy * y_radius, cx * cy * x_radius);
                    vertices->add3(sx * cy, sy, cx * cy);
                    vertices->add2(x_angle, y_angle);
                }
            }
        }
        // COMPUTE MESH INDICES
        {
            a=b=c=d=0;
            for (x=0; x<cols; x++)
            {
                if (x >= cols-1)
                    indices->add3(0, x+2, 2);
                else
                    indices->add3(0, x+2, x+3);
                
                for (y=0; y<rows-2; y++)
                {
                    if (x >= cols-1)
                    {
                        a = x + cols * y + 2;
                        b = a - cols + 1;
                        c = a + cols;
                        d = c - cols + 1;
                        indices->add3(a, c, d);
                        indices->add3(d, b, a);
                    }
                    else
                    {
                        a = x + cols * y + 2;
                        b = a + 1;
                        c = a + cols;
                        d = c + 1;
                        indices->add3(a, c, d);
                        indices->add3(d, b, a);
                    }
                }
                
                if (x >= cols-1)
                    indices->add3(1, d, c);
                else
                    indices->add3(1, d, c);
            }
        }
    }
    
    void GenMeshSphere(gfx::Mesh& mesh, float radius, int cols, int rows)
    {
        GenMeshEllipsoid(mesh, radius, radius, cols, rows);
    }
}}
