//
//  Plane.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/7/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef GenMeshGrid_hpp
#define GenMeshGrid_hpp
#include "Mesh.hpp"
namespace kege{namespace gfx{
    
    void GenMeshGrid(gfx::Mesh& mesh, float width, float height, int wdiv, int hdiv);
    void GenMeshPlane(gfx::Mesh& mesh, float width, float height);
}}
#endif /* Plane_hpp */
