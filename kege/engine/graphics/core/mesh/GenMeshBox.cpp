//
//  Box.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/7/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//
#include "../../../graphics/core/Graphics.hpp"
#include "../../../graphics/core/mesh/GenMesh.hpp"
namespace kege{namespace gfx{
    
    shared::Geometry GenMeshBox( const cg::vec3& min, const cg::vec3& max )
    {
        core::IndexBuffer* indices = new core::IndexBuffer;
        core::VertexBuffer* vertices = new core::VertexBuffer;
        
        //mesh.SetMinPoint(min);
        //mesh.SetMaxPoint(max);
        
        vertices->setsize(8 * 24);
        vertices->setstride(8);
        
        indices->setsize(36);
        indices->setstride(1);
        
        // bottom plane
        vertices->add3(min.x, min.y, min.z); // 0
        vertices->add3(0.0, -1.0, 0.0);
        vertices->add2(0.0, 0.0);
        vertices->add3(max.x, min.y, min.z); // 1
        vertices->add3(0.0, -1.0, 0.0);
        vertices->add2(1.0, 0.0);
        vertices->add3(max.x, min.y, max.z); // 2
        vertices->add3(0.0, -1.0, 0.0);
        vertices->add2(1.0, 1.0);
        vertices->add3(min.x, min.y, max.z); // 3
        vertices->add3(0.0, -1.0, 0.0);
        vertices->add2(0.0, 1.0);
        
        indices->add3(0,1,2);
        indices->add3(2,3,0);
        
        // top plane
        
        vertices->add3(max.x, max.y, max.z); // 4
        vertices->add3(0.0, 1.0, 0.0);
        vertices->add2(1.0, 0.0);
        vertices->add3(max.x, max.y, min.z); // 5
        vertices->add3(0.0, 1.0, 0.0);
        vertices->add2(1.0, 1.0);
        vertices->add3(min.x, max.y, min.z); // 6
        vertices->add3(0.0, 1.0, 0.0);
        vertices->add2(0.0, 1.0);
        vertices->add3(min.x, max.y, max.z); // 7
        vertices->add3(0.0, 1.0, 0.0);
        vertices->add2(0.0, 0.0);
        
        indices->add3(4,5,6);
        indices->add3(6,7,4);
        
        // front plane
        
        vertices->add3(max.x, max.y, max.z); // 8
        vertices->add3(0.0, 0.0, 1.0);
        vertices->add2(1.0, 1.0);
        vertices->add3(min.x, max.y, max.z); // 9
        vertices->add3(0.0, 0.0, 1.0);
        vertices->add2(0.0, 1.0);
        vertices->add3(min.x, min.y, max.z); // 10
        vertices->add3(0.0, 0.0, 1.0);
        vertices->add2(0.0, 0.0);
        vertices->add3(max.x, min.y, max.z); // 11
        vertices->add3(0.0, 0.0, 1.0);
        vertices->add2(1.0, 0.0);
        
        indices->add3(8,9,10);
        indices->add3(10,11,8);
        
        // back plane
        
        vertices->add3(min.x, min.y, min.z); // 12
        vertices->add3(0.0, 0.0, -1.0);
        vertices->add2(1.0, 0.0);
        vertices->add3(min.x, max.y, min.z); // 13
        vertices->add3(0.0, 0.0, -1.0);
        vertices->add2(1.0, 1.0);
        vertices->add3(max.x, max.y, min.z); // 14
        vertices->add3(0.0, 0.0, -1.0);
        vertices->add2(0.0, 1.0);
        vertices->add3(max.x, min.y, min.z); // 15
        vertices->add3(0.0, 0.0, -1.0);
        vertices->add2(0.0, 0.0);
        
        indices->add3(12,13,14);
        indices->add3(14,15,12);
        
        // left plane
        
        vertices->add3(min.x, min.y, min.z); // 16
        vertices->add3(-1.0, 0.0, 0.0);
        vertices->add2(1.0, 0.0);
        vertices->add3(min.x, min.y, max.z); // 17
        vertices->add3(-1.0, 0.0, 0.0);
        vertices->add2(1.0, 1.0);
        vertices->add3(min.x, max.y, max.z); // 18
        vertices->add3(-1.0, 0.0, 0.0);
        vertices->add2(0.0, 1.0);
        vertices->add3(min.x, max.y, min.z); // 19
        vertices->add3(-1.0, 0.0, 0.0);
        vertices->add2(0.0, 0.0);
        
        indices->add3(16,17,18);
        indices->add3(18,19,16);
        
        // right plane
        
        vertices->add3(max.x, max.y, max.z); // 20
        vertices->add3(1.0, 0.0, 0.0);
        vertices->add2(0.0, 1.0);
        vertices->add3(max.x, min.y, max.z); // 21
        vertices->add3(1.0, 0.0, 0.0);
        vertices->add2(0.0, 0.0);
        vertices->add3(max.x, min.y, min.z); // 22
        vertices->add3(1.0, 0.0, 0.0);
        vertices->add2(1.0, 0.0);
        vertices->add3(max.x, max.y, min.z); // 23
        vertices->add3(1.0, 0.0, 0.0);
        vertices->add2(1.0, 1.0);
        
        indices->add3(20,21,22);
        indices->add3(22,23,20);
        
        core::VertexLayout* layout = &vertices->GetVertexLayout();
        layout->AddElem(core::VERTEX_POSITION, 3,0);
        layout->AddElem(core::VERTEX_NORMAL,   3,3);
        layout->AddElem(core::VERTEX_TEXCOORD, 2,6);
        
        return new gfx::Geometry( vertices, indices );
    }
    
    shared::Geometry GenMeshBox( float width, float height, float depth )
    {
        float w = width  * 0.5;
        float h = height * 0.5;
        float d = depth  * 0.5;
        return GenMeshBox( cg::vec3(-w,-h,-d), cg::vec3(w,h,d) );
    }
    
    shared::Geometry GenMeshBox( const ds::string& instructions )
    {
        std::map<long, float> variables;
        ds::string name, v;
        long h = ds::string("height").hash();
        long w = ds::string("width").hash();
        long d = ds::string("depth").hash();
        variables[w] = 0;
        variables[h] = 0;
        variables[d] = 0;
        
        char value[64];
        const char* command = instructions.c_str();
        command = kege::str_next(command, "<");
        command = kege::str_skip(command, " <\n\t\r");
        if (kege::string_contain("BOX", command, ")"))
        {
            command = kege::str_next(command, "[");
            command = kege::str_skip(command, " ['\n\t\r");
            
            str_cpyf(value, command, ", ']\n");
            name = value;
            
            command = kege::str_next(command, "(");
            command = kege::str_skip(command, " (\n\t\r");
            
            while (*command != 0)
            {
                str_cpyf(value, command, ":, \n");
                v = value;
                
                command = kege::str_next(command, ":");
                command = kege::str_skip(command, " :\n\t\r");
                
                str_cpyf(value, command, ", \n");
                variables[v.hash()] = atof(value);
                
                command = kege::str_next(command, ",");
                command = kege::str_skip(command, " ,\n\t\r");
            }
        }
        return gfx::GenMeshBox( variables[w], variables[h], variables[d] );
    }
}}
