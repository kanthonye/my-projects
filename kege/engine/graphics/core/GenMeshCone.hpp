//
//  Cone.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/11/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef GenMeshCone_hpp
#define GenMeshCone_hpp
#include "Mesh.hpp"
namespace kege{namespace gfx{
    
    void GenMeshCone(gfx::Mesh& mesh, float radius, int min_height, int max_height, int columns);
    void GenMeshCone(gfx::Mesh& mesh, float radius, int height, int columns);
}}
#endif /* Cone_hpp */
