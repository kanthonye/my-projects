//
//  LibraryMeshs.cpp
//  AppDev
//
//  Created by Kenneth Esdaile on 6/8/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//
#include "Logger.hpp"
#include "Entity.hpp"
#include "LoaderTXT.hpp"
#include "LoaderOBJ.hpp"
#include "ObjectMaterial.hpp"
#include "Model.hpp"

namespace kege{namespace gfx{

    //shared::Geometry geometry = geometries.ContructGeometry( skin->GetAttr("source")->value, vw, vj );
    //cg::uint draw_count = (cg::uint) geometry->GetIndexBuffer()->size();
    //
    //shared::DrawElement dmatl = new gfx::DrawElement( core::DRAW_TRIANGLES, 0, draw_count, new gfx::ObjectMaterial() );
    //shared::DrawElement mmatl = new gfx::DrawElement( dmatl );
    //return shared::Mesh( new gfx::Mesh( geometry, mmatl ) );
    
    
    
    
    
    
    shared::Mesh OBJMeshLoader::Load( const ds::string& filename )
    {
        gfx::Mesh* mesh = new gfx::Mesh;
//        if ( !kege::OBJLoadUnifyMesh( *mesh, filename) )
//        {
//            delete mesh;
//            mesh = nullptr;
//            return nullptr;
//        }
//        
//        const ds::string fname = filename.parse_name();
//        if ( _manager != nullptr )
//        {
//            return _manager->Add< gfx::Mesh >( fname, mesh );
//        }
        return shared::Mesh( mesh );
    }
    
    OBJMeshLoader::OBJMeshLoader()
    :   kege::ResourceLoader< gfx::Mesh >( "obj" )
    {
    }
}}


