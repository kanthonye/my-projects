//
//  Cylinder.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/7/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//
#include "../../../graphics/core/Graphics.hpp"
#include "../../../graphics/core/mesh/GenMesh.hpp"
namespace kege{namespace gfx{
    
    shared::Geometry GenMesCylinder( float radius, int height, int columns )
    {
        float vx,vy, nx,ny, rad;
        int count, index, m;
        const int stride = 8;
        float halfHeight = (height/2.0f);
        const float segments = 6.28318530718 / (float)columns;
        columns = (columns<3) ? 3 : columns;
        
        //mesh.SetMaxPoint(cg::point3( radius, radius, halfHeight));
        //mesh.SetMinPoint(cg::point3(-radius,-radius,-halfHeight));
        
        core::VertexBuffer* vertices = new core::VertexBuffer;
        vertices->setbuffer(stride * (columns * 4 + 2), stride, 0);
        
        core::IndexBuffer* indices = new core::IndexBuffer;
        indices->setbuffer(columns * 6 + columns * 3 * 2, 1, 0);
        indices->setcount(0);
        
        {
            // VERTEX ~ TOP CENTER
            vertices->add3(0.0f, 0.0f, halfHeight);
            vertices->add3(0.0f, 0.0f, 1.0);
            vertices->add2(0.0f, 0.0f);

            // VERTEX ~ BOTTOM CENTER
            vertices->add3(0.0f, 0.0f, -halfHeight);
            vertices->add3(0.0f, 0.0f, -halfHeight);
            vertices->add2(1.0f, 1.0f);
            m = 0;
            for (count=2; count<columns+2; count++, m++)
            {
                rad = segments * m;
                nx = cosf(rad);
                ny = sinf(rad);
                vx = nx*radius;
                vy = ny*radius;
                
                // VERTEX ~ TOP CIRCLE
                index = stride * count;
#ifdef KEGE_DEBUG_MODE
                printf("%2i : %2i, ", m,index);
#endif
                vertices->set3(index, vx, vy, halfHeight);
                vertices->set3(index + 3, 0.0f, 0.0f, 1.0);
                vertices->set2(index + 6, nx, ny);
                
                // VERTEX ~ BODY
                index = stride * (count + columns + m);
#ifdef KEGE_DEBUG_MODE
                printf("%2i, ", index);
#endif
                vertices->set3(index, vx, vy, halfHeight);
                vertices->set3(index+3, nx, ny, 0.0f);
                vertices->set2(index+6, nx, ny);

                index = stride * (count + columns + m + 1);
#ifdef KEGE_DEBUG_MODE
                printf("%2i, ", index);
#endif
                vertices->set3(index, vx, vy,-halfHeight);
                vertices->set3(index+3, nx, ny, 0.0f);
                vertices->set2(index+6, 1.0f-nx, 1.0f-ny);

                // VERTEX ~ BOTTOM CIRCLE
                index = stride * ((count + columns) + (columns * 2));
#ifdef KEGE_DEBUG_MODE
                printf("%2i\n", index);
#endif
                vertices->set3(index, vx, vy,-halfHeight);
                vertices->set3(index+3, 0.0f, 0.0f, -1.0);
                vertices->set2(index+6, 1.0f-nx, 1.0f-ny);
            }
#ifdef KEGE_DEBUG_MODE
            index = 0;
            for (count=0; count<vertices->size(); count+=stride)
            {
                printf("%2i : %f %f %f\n", index++, vertices->get(count), vertices->get(count+1), vertices->get(count+2));
            }
#endif
        }
        // INDICES ~ TOP CIRCLE
        {
            m = 0;
            for (count=2; count<columns+2; count++)
            {
                indices->add3(0, count, count+1);
                
                index = columns + count + m++;

                indices->add3(index, index+1, index+3);
                indices->add3(index+3, index+2, index);

                index = columns * 2 + columns + count;

                indices->add3(1, index+1, index);
            }
            m = (columns - 1) * 12 + 2;
            indices->getref(m) = 2;

            m = m + 3;
            indices->getref(m) = columns + 3;

            m = m + 1;
            indices->getref(m) = columns + 3;

            m = m + 1;
            indices->getref(m) = columns + 2;
            
            m = m + 3;
            indices->getref(m) = columns * 2 + columns + 2;
            
#ifdef KEGE_DEBUG_MODE
            m = 0;
            for (count=0; count<indices->size(); count+=3)
            {
                printf("%2i : %2i %2i %2i\n", m++, indices->get(count), indices->get(count+1), indices->get(count+2));
            }
#endif
        }
        core::VertexLayout* layout = &vertices->GetVertexLayout();
        {
            layout->AddElem(core::VERTEX_POSITION, 3,0);
            layout->AddElem(core::VERTEX_NORMAL,   3,3);
            layout->AddElem(core::VERTEX_TEXCOORD, 2,6);
        }
        return new gfx::Geometry( vertices, indices );
    }
}}
