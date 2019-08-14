//
//  Ellipsoid.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/7/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef Tetrahedron_hpp
#define Tetrahedron_hpp
#include "Mesh.hpp"
namespace kege{namespace gfx{
    
    void GenMeshEllipsoid(gfx::Mesh& mesh, float x_radius, float y_radius, int cols, int rows);
    void GenMeshSphere(gfx::Mesh& mesh, float radius, int cols, int rows);
}}
#endif /* Tetrahedron_hpp */
