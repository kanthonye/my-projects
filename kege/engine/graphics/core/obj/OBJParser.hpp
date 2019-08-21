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
#include "BufferReader.hpp"
#include "../../../ds/listpair.hpp"
#include "../../../graphics/core/mesh/Geometry.hpp"
#include "../../../graphics/core/mesh/DrawElement.hpp"
namespace kege{

    bool OBJLoadGeometies( ds::array< shared::Geometry >& geometries, const ds::string& filename );
}
#endif /* OBJParser_hpp */
