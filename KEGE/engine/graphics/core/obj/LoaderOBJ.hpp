
//
//  LibraryMeshs.hpp
//  AppDev
//
//  Created by Kenneth Esdaile on 6/8/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef LibraryMeshs_hpp
#define LibraryMeshs_hpp
#include "Model.hpp"
#include "Texture2D.hpp"
#include "Gameobject.hpp"
#include "BufferReader.hpp"
#include "OBJParser.hpp"
#include "ResourceFramework.hpp"
namespace kege{namespace gfx{
    
    typedef  ds::array< gfx::Mesh > MeshGroup;
    
    class OBJMeshGroupLoader :public kege::ResourceLoader< gfx::MeshGroup >
    {
    public:
        
        mem::shared< MeshGroup > Load( const ds::string& filename );
        OBJMeshGroupLoader();
    };
    
    
    class OBJMeshLoader :public kege::ResourceLoader< gfx::Mesh >
    {
    public:
        
        shared::Mesh Load( const ds::string& filename );
        OBJMeshLoader();
    };
}}
#endif /* LibraryMesh_hpp */
