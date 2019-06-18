//======================================================================
//  Author  : Kenneth A Esdaile
//  Date    : Created on 4/14/19.
//  Title   : ColladaLibrary.hpp
//  Project : KEGE
//======================================================================
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//======================================================================
#ifndef ColladaLibrary_hpp
#define ColladaLibrary_hpp
#include <stdio.h>
#include <map>
#include "XML.hpp"
#include "RawMesh.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
namespace kege{namespace dae{
    
    class ColladaLibrary
    {
    public:
        
        void ToPolygonBuffers(gfx::IndexBuffer& vcount, gfx::IndexBuffer& v, kege::XML* polylist);
        void StringToFloats(float* arry, const int size, kege::ds::string& text);
        kege::XML* GetInputSource(kege::XML* sources, kege::XML* input);
        char const* RemoveHashtag(kege::ds::string const& a);
        gfx::VertexBuffer ToVertexBuffer(kege::XML* source);
        int GetTotalInputs(kege::XML* polylist);
        int GetInputOffset(kege::XML* input);
        cg::mat44 ToMatrix(kege::ds::string& text);
        cg::quat ToQuat(kege::ds::string& text);
        cg::vec4 ToVec4(kege::ds::string& text);
        cg::vec3 ToVec3(kege::ds::string& text);
        cg::mat33 GetUpAxisMatrix();
        
        gfx::RawMesh* NewRawMesh(const ds::string& id);
        
        virtual ~ ColladaLibrary(){}
    };
}}
#endif /* ColladaLibrary_hpp */