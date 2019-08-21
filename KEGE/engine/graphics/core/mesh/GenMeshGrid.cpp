//
//  Plane.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/7/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//
#include "../../../graphics/core/Graphics.hpp"
#include "../../../graphics/core/mesh/GenMesh.hpp"
namespace kege{namespace gfx{
    
    
    shared::Geometry GenMeshGrid( int width, int height, int wdiv, int hdiv, int offset_width=0, int offset_height=0 )
    {
        int vsize = (wdiv + 1) * (hdiv + 1);
        int isize = wdiv * hdiv * 6;
        int count = 0;
        
        //mesh.SetCenterPoint(cg::point3( width*0.5, 0.0, height*0.5));
        //mesh.SetMaxPoint(cg::point3( width, 0.0, height));
        //mesh.SetMinPoint(cg::point3(0.0,0.0,0.0));
        
        core::VertexBuffer* vertices = new core::VertexBuffer;
        vertices->setsize(3 * vsize);
        vertices->setstride(3);
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
        
        core::IndexBuffer* indices = new core::IndexBuffer;
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
        core::VertexLayout* layout = &vertices->GetVertexLayout();
        layout->AddElem(core::VERTEX_POSITION, 3,0);
        //layout->AddElem(core::VERTEX_NORMAL,   3,3);
        //layout->AddElem(core::VERTEX_TEXCOORD, 2,6);
        
        return new gfx::Geometry( vertices, indices );
    }
    
    
    shared::Geometry GenMeshGrid( float width, float height, int wdiv, int hdiv )
    {
        int vsize = (wdiv + 1) * (hdiv + 1);
        int isize = wdiv * hdiv * 6;
        int count = 0;
        
        //float uvw = 1.00f / gsize;
        float uvw = 1.00f / wdiv;
        float uvh = 1.00f / hdiv;
        
        
        core::VertexBuffer* vertices = new core::VertexBuffer;
        vertices->setsize(8 * vsize);
        vertices->setstride(8);
        vertices->setcount(0);
        
        //mesh.SetCenterPoint(cg::point3( width*0.5, 0.0, height*0.5));
        //mesh.SetMaxPoint(cg::point3( width, 0.0, height));
        //mesh.SetMinPoint(cg::point3(0.0,0.0,0.0));
        
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
        
        core::IndexBuffer* indices = new core::IndexBuffer;
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
        
        core::VertexLayout* layout = &vertices->GetVertexLayout();
        layout->AddElem(core::VERTEX_POSITION, 3,0);
        layout->AddElem(core::VERTEX_NORMAL,   3,3);
        layout->AddElem(core::VERTEX_TEXCOORD, 2,6);
        
        return new gfx::Geometry( vertices, indices );
    }
    
    shared::Geometry GenMeshPlane( float width, float height )
    {
        return GenMeshGrid( width, height, 1, 1 );
    }
}}
