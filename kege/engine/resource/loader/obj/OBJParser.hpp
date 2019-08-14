/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/3/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       OBJParser.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef OBJParser_hpp
#define OBJParser_hpp
#include "Model.hpp"
#include "Texture2D.hpp"
#include "Gameobject.hpp"
#include "LoaderMTL.hpp"
#include "BufferReader.hpp"
namespace kege{
    
    bool OBJLoadLibrary( ds::array< gfx::Mesh* >& lib, const ds::string& filename );
    bool OBJLoadUnifyMesh( gfx::Mesh& mesh, const ds::string& filename );
}
#endif /* OBJParser_hpp */
