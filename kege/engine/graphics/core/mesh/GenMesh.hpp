/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/20/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GenMesh.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GenMesh_hpp
#define GenMesh_hpp
#include "../../../ds/string.hpp"
#include "../../../graphics/core/mesh/Geometry.hpp"
namespace kege{namespace gfx{
    
    shared::Geometry GenMeshGrid( float width, float height, int wdiv, int hdiv );
    shared::Geometry GenMeshPlane( float width, float height );
}}
namespace kege{namespace gfx{
    
    shared::Geometry GenMeshEllipsoid( float x_radius, float y_radius, int cols, int rows );
    shared::Geometry GenMeshSphere( float radius, int cols, int rows );
}}
namespace kege{namespace gfx{
    
    shared::Geometry GenMesCylinder( float radius, int height, int columns );
}}
namespace kege{namespace gfx{
    
    shared::Geometry GenMeshConeSmooth( float radius, int min_height, int max_height, int columns, int& m );
    shared::Geometry GenMeshConeFlat( float radius, int min_height, int max_height, int columns );
}}
namespace kege{namespace gfx{
    
    shared::Geometry GenMeshBox( const cg::vec3& min, const cg::vec3& max );
    shared::Geometry GenMeshBox( float width, float height, float depth );
    
    /**
     * this particluar function is use to generate a box mesh using a string
     * containing instructions parameters on how to contruct the mesh
     * @code // examples of mesh generation.
     * @code gfx::Mesh mesh("[BOX]( width:1, height:4, depth:4)" );
     * @return the name parsed from the instruction line
     */
    shared::Geometry GenMeshBox( const ds::string& instructions );
}}
#endif /* GenMesh_hpp */
