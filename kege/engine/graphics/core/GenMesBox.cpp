//
//  Box.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/7/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//
#include <map>
#include "GenMeshBox.hpp"
namespace kege{namespace gfx{
    
    void GenMeshBox(gfx::Mesh& mesh, const cg::vec3& min, const cg::vec3& max)
    {
        mesh.SetStrType("BOX");
        mesh.SetMinPoint(min);
        mesh.SetMaxPoint(max);
        gfx::DataBuffer<float>& vb = mesh.GetVertexBuffer();
        gfx::DataBuffer<cg::uint>& ib = mesh.GetIndexBuffer();
        mesh.GetVertexBuffer().GetVertexLayout().AddElem(VERTEX_POSITION, 3, 0);
        mesh.GetVertexBuffer().GetVertexLayout().AddElem(VERTEX_NORMAL,   3, 3);
        mesh.GetVertexBuffer().GetVertexLayout().AddElem(VERTEX_TEXCOORD, 2, 6);
        
        vb.setsize(8 * 24);
        vb.setstride(8);
        
        ib.setsize(36);
        ib.setstride(1);
        
        // bottom plane
        vb.add3(min.x, min.y, min.z); // 0
        vb.add3(0.0, -1.0, 0.0);
        vb.add2(0.0, 0.0);
        vb.add3(max.x, min.y, min.z); // 1
        vb.add3(0.0, -1.0, 0.0);
        vb.add2(1.0, 0.0);
        vb.add3(max.x, min.y, max.z); // 2
        vb.add3(0.0, -1.0, 0.0);
        vb.add2(1.0, 1.0);
        vb.add3(min.x, min.y, max.z); // 3
        vb.add3(0.0, -1.0, 0.0);
        vb.add2(0.0, 1.0);
        
        ib.add3(0,1,2);
        ib.add3(2,3,0);
        
        // top plane
        
        vb.add3(max.x, max.y, max.z); // 4
        vb.add3(0.0, 1.0, 0.0);
        vb.add2(1.0, 0.0);
        vb.add3(max.x, max.y, min.z); // 5
        vb.add3(0.0, 1.0, 0.0);
        vb.add2(1.0, 1.0);
        vb.add3(min.x, max.y, min.z); // 6
        vb.add3(0.0, 1.0, 0.0);
        vb.add2(0.0, 1.0);
        vb.add3(min.x, max.y, max.z); // 7
        vb.add3(0.0, 1.0, 0.0);
        vb.add2(0.0, 0.0);
        
        ib.add3(4,5,6);
        ib.add3(6,7,4);
        
        // front plane
        
        vb.add3(max.x, max.y, max.z); // 8
        vb.add3(0.0, 0.0, 1.0);
        vb.add2(1.0, 1.0);
        vb.add3(min.x, max.y, max.z); // 9
        vb.add3(0.0, 0.0, 1.0);
        vb.add2(0.0, 1.0);
        vb.add3(min.x, min.y, max.z); // 10
        vb.add3(0.0, 0.0, 1.0);
        vb.add2(0.0, 0.0);
        vb.add3(max.x, min.y, max.z); // 11
        vb.add3(0.0, 0.0, 1.0);
        vb.add2(1.0, 0.0);
        
        ib.add3(8,9,10);
        ib.add3(10,11,8);
        
        // back plane
        
        vb.add3(min.x, min.y, min.z); // 12
        vb.add3(0.0, 0.0, -1.0);
        vb.add2(1.0, 0.0);
        vb.add3(min.x, max.y, min.z); // 13
        vb.add3(0.0, 0.0, -1.0);
        vb.add2(1.0, 1.0);
        vb.add3(max.x, max.y, min.z); // 14
        vb.add3(0.0, 0.0, -1.0);
        vb.add2(0.0, 1.0);
        vb.add3(max.x, min.y, min.z); // 15
        vb.add3(0.0, 0.0, -1.0);
        vb.add2(0.0, 0.0);
        
        ib.add3(12,13,14);
        ib.add3(14,15,12);
        
        // left plane
        
        vb.add3(min.x, min.y, min.z); // 16
        vb.add3(-1.0, 0.0, 0.0);
        vb.add2(1.0, 0.0);
        vb.add3(min.x, min.y, max.z); // 17
        vb.add3(-1.0, 0.0, 0.0);
        vb.add2(1.0, 1.0);
        vb.add3(min.x, max.y, max.z); // 18
        vb.add3(-1.0, 0.0, 0.0);
        vb.add2(0.0, 1.0);
        vb.add3(min.x, max.y, min.z); // 19
        vb.add3(-1.0, 0.0, 0.0);
        vb.add2(0.0, 0.0);
        
        ib.add3(16,17,18);
        ib.add3(18,19,16);
        
        // right plane
        
        vb.add3(max.x, max.y, max.z); // 20
        vb.add3(1.0, 0.0, 0.0);
        vb.add2(0.0, 1.0);
        vb.add3(max.x, min.y, max.z); // 21
        vb.add3(1.0, 0.0, 0.0);
        vb.add2(0.0, 0.0);
        vb.add3(max.x, min.y, min.z); // 22
        vb.add3(1.0, 0.0, 0.0);
        vb.add2(1.0, 0.0);
        vb.add3(max.x, max.y, min.z); // 23
        vb.add3(1.0, 0.0, 0.0);
        vb.add2(1.0, 1.0);
        
        ib.add3(20,21,22);
        ib.add3(22,23,20);
    }
    
    void GenMeshBox(gfx::Mesh& mesh, float width, float height, float depth)
    {
        float w = width  * 0.5;
        float h = height * 0.5;
        float d = depth  * 0.5;
        GenMeshBox(mesh, cg::vec3(-w,-h,-d), cg::vec3(w,h,d));
    }
    
    ds::string GenMeshBox(gfx::Mesh& mesh, const ds::string& instructions)
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
            
            gfx::GenMeshBox(mesh, variables[w], variables[h], variables[d]);
        }
        return name;
    }
}}
