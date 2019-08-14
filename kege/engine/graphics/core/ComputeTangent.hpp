//
//  ComputeTangent.hpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/19/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef ComputeTangent_hpp
#define ComputeTangent_hpp
#include "cgm.hpp"
#include "array.hpp"
#include "DataBuffer.hpp"
namespace kege{namespace gfx{
    class Mesh;
    
    struct Vertex
    {
        cg::point3 position;
        cg::point2 texcoord;
        cg::vec3   normal;
    };
    
    struct TangentVertex : public gfx::Vertex
    {
        cg::point3 tangent;
    };
    
    struct SkinVertex : public gfx::Vertex
    {
        cg::point4 weights;
        cg::point4 joints;
    };
    
    struct SkinTangentVertex : public gfx::TangentVertex
    {
        cg::point4 weights;
        cg::point4 joints;
    };
    void ComputeTangent(gfx::Mesh& mesh);
    void ComputeTangentNonIndex(gfx::Mesh& mesh);
}}
#endif /* ComputeTangent_hpp */
