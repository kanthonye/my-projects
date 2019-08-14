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
#include "MeshComponent.hpp"
namespace kege{namespace gfx{

//    gfx::Gameobject* LoaderOBJ::LoadGameobject( const ds::string& filename )
//    {
//        gfx::SharedModel model;
//        const ds::string fname = filename.parse_name();
//        gfx::Entity * entity = new gfx::Entity( fname );
//        if ( _manager != nullptr )
//        {
//            model = _manager->Get< gfx::Model >( fname );
//            if ( model.rawptr() != nullptr )
//            {
//                for (int i=0; i<model->Size(); i++)
//                {
//                    entity->Attach( new gfx::MeshComponent( model->operator[](i)->mesh,model->operator[](i)->material ) );
//                }
//                return entity;
//            }
//        }
//
//        ds::string mtllib;
//        OBJMeshLibrary meshlibrary;
//        if ( !OBJLoadMeshLibrary(meshlibrary, mtllib, filename) )
//        {
//            return nullptr;
//        }
//
//        if ( _manager != nullptr )
//        {
//             model = _manager->Add< gfx::Model >( fname, new gfx::Model );
//        }
//        else
//        {
//            model = gfx::SharedModel( new gfx::Model );
//        }
//
//
//        gfx::Mesh* mesh = nullptr;
//        gfx::SharedMaterial material = new gfx::ObjectMaterial();
//        for (OBJMeshLibrary::iterator m=meshlibrary.begin(); m!=nullptr; m++)
//        {
//            //mtl  = resr_matl->Get(m.element().first.first);
//            //name = m.element().first.second;
//            mesh = m.element().second;
//            model->Attach( new gfx::MeshMaterial( mesh, material ) );
//            entity->Attach( new gfx::MeshComponent( mesh, material) );
//            //resr_mesh->Add(name, mesh);
//        }
//        return nullptr;
//    }
    
    gfx::SharedMesh OBJMeshLoader::Load( const ds::string& filename )
    {
        gfx::Mesh* mesh = new gfx::Mesh;
        if ( !kege::OBJLoadUnifyMesh( *mesh, filename) )
        {
            delete mesh;
            mesh = nullptr;
            return nullptr;
        }
        
        const ds::string fname = filename.parse_name();
        if ( _manager != nullptr )
        {
            return _manager->Add< gfx::Mesh >( fname, mesh );
        }
        return gfx::SharedMesh( mesh );
    }
    
    OBJMeshLoader::OBJMeshLoader()
    :   kege::ResourceLoader< gfx::Mesh >( "obj" )
    {
    }
}}


