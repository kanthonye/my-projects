//
//  Box.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/7/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef GenMeshBox_hpp
#define GenMeshBox_hpp
#include "Mesh.hpp"
namespace kege{namespace gfx{
   
    void GenMeshBox(gfx::Mesh& mesh, const cg::vec3& min, const cg::vec3& max);
    void GenMeshBox(gfx::Mesh& mesh, float width, float height, float depth);
    
    /**
     * this particluar function is use to generate a box mesh using a string
     * containing instructions parameters on how to contruct the mesh
     * @code // examples of mesh generation.
     * @code gfx::Mesh mesh("[BOX]( width:1, height:4, depth:4)" );
     * @return the name parsed from the instruction line
     */
    ds::string GenMeshBox(gfx::Mesh& mesh, const ds::string& instructions);
}}
#endif /* Box_hpp */
