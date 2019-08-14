//
//  Plane.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/7/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#include "GenMeshGrid.hpp"
namespace kege{namespace gfx{
    
    
    void BuildMeshGrid(gfx::Mesh& mesh, int width, int height, int wdiv, int hdiv, int offset_width=0, int offset_height=0)
    {
        mesh.SetStrType("PLANE");
        int vsize = (wdiv + 1) * (hdiv + 1);
        int isize = wdiv * hdiv * 6;
        int count = 0;
        
        mesh.GetVertexBuffer().GetVertexLayout().AddElem(VERTEX_POSITION, 3, 0);
        mesh.GetVertexBuffer().setsize(3 * vsize);
        mesh.GetVertexBuffer().setstride(3);
        mesh.SetCenterPoint(cg::point3( width*0.5, 0.0, height*0.5));
        mesh.SetMaxPoint(cg::point3( width, 0.0, height));
        mesh.SetMinPoint(cg::point3(0.0,0.0,0.0));
        
        gfx::VertexBuffer* vertices = &mesh.GetVertexBuffer();
        vertices->setcount(0);
        
        int w = width - offset_width;
        int h = height - offset_height;
        for (int x,z=offset_height; z<=h; z++)
        {
            for (x=offset_width; x<=w; x++)
            {
                vertices->add3(x-w,0,z-h);
            }
        }
        
        gfx::IndexBuffer * indices = &mesh.GetIndexBuffer();
        indices->setsize(isize);
        indices->setcount(0);
        
        for (int z = 0; z < hdiv; z++)
        {
            float row = (hdiv + 1) * z;
            for (int x = 0; x < wdiv; x++)
            {
                int a = x + row;
                int b = a + 1;
                int c = a + wdiv + 1;
                int d = c + 1;
                //printf("%i %i %i %i\n",a,b,c,d);
                indices->add3(a,c,d);
                indices->add3(d,b,a);
                count += 6;
            }
        }
    }
    
    
    void GenMeshGrid(gfx::Mesh& mesh, float width, float height, int wdiv, int hdiv)
    {
        mesh.SetStrType("PLANE");
        int vsize = (wdiv + 1) * (hdiv + 1);
        int isize = wdiv * hdiv * 6;
        int count = 0;
        
        //float uvw = 1.00f / gsize;
        float uvw = 1.00f / wdiv;
        float uvh = 1.00f / hdiv;
        
        mesh.GetVertexBuffer().GetVertexLayout().AddElem(VERTEX_POSITION, 3, 0);
        mesh.GetVertexBuffer().GetVertexLayout().AddElem(VERTEX_NORMAL  , 3, 3);
        mesh.GetVertexBuffer().GetVertexLayout().AddElem(VERTEX_TEXCOORD, 2, 6);
        mesh.GetVertexBuffer().setsize(8 * vsize);
        mesh.GetVertexBuffer().setstride(8);
        
        mesh.SetCenterPoint(cg::point3( width*0.5, 0.0, height*0.5));
        mesh.SetMaxPoint(cg::point3( width, 0.0, height));
        mesh.SetMinPoint(cg::point3(0.0,0.0,0.0));
        
        gfx::VertexBuffer* vertices = &mesh.GetVertexBuffer();
        vertices->setcount(0);
        
        float x,z,vz,ty;
        for (z=0; z<=hdiv; z++)
        {
            ty = uvh * float(z);
            vz = uvh * float(z) * height;
            for (x=0; x<=wdiv; x++)
            {
                vertices->add3(uvw * float(x) * width, 0.0f, vz);
                vertices->add3(0.0f, 1.0f, 0.0f);
                vertices->add2(uvw * float(x), ty);
            }
        }
        
        gfx::IndexBuffer * indices = &mesh.GetIndexBuffer();
        indices->setsize(isize);
        indices->setcount(0);
        
        for (int z = 0; z < hdiv; z++)
        {
            float row = (hdiv + 1) * z;
            for (int x = 0; x < wdiv; x++)
            {
                int a = x + row;
                int b = a + 1;
                int c = a + wdiv + 1;
                int d = c + 1;
                //printf("%i %i %i %i\n",a,b,c,d);
                indices->add3(a,c,d);
                indices->add3(d,b,a);
                count += 6;
            }
        }
    }
    
    void GenMeshPlane(gfx::Mesh& mesh, float width, float height)
    {
        GenMeshGrid(mesh, width, height, 1, 1);
    }
}}
