
//
//  LibraryMeshs.hpp
//  AppDev
//
//  Created by Kenneth Esdaile on 6/8/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef LibraryMeshs_hpp
#define LibraryMeshs_hpp
#include "Mesh.hpp"
#include "Material.hpp"
#include "Texture2D.hpp"
#include "Entity.hpp"
#include "LoaderMTL.hpp"
#include "BufferReader.hpp"
namespace kege{namespace res{
    
    typedef std::pair<ds::string, ds::string> OBJName;
    typedef std::pair<OBJName, gfx::RawMesh*> OBJMesh;
    typedef ds::slist<OBJMesh> OBJMeshLibrary;
    
    class LoaderOBJ :public kege::Loader<gfx::Scenenode>
    {
    public:
        
        struct Polygon
        {
            gfx::DataBuffer<int> v;
            gfx::DataBuffer<int> f;
            ds::string usemtl;
            ds::string name;
            cg::uint drawcount;
        };
        
        struct OBJ
        {
            ds::slist<int> v;
            ds::slist<int> f;
            ds::string usemtl;
            ds::string name;
        };
        
        /**
         parse the entire file data into VertexBuffers, model hold the objects name and indices
         @param model  : hold the object definitions such as obj name, the material to use, and the index buffers
         @param vp     : holds all the vertex position data
         @param vn     : holds all the vertex normal data
         @param vt     : holds all the vertex texcoord data
         @param mtllib : is the name of the material library to load
         @param buffer : holds the text data from the file that the function will parse
         */
        static bool OBJParseDataFrmTextBuffer
        (   ds::slist<OBJ>& model
         ,  ds::slist<cg::point3>& vp
         ,  ds::slist<cg::point3>& vn
         ,  ds::slist<cg::point3>& vt
         ,  ds::string& mtllib
         ,  kege::BufferReader& reader  );
        
        /**
         parse the obj file data to array buffer
         @param objs     : hold the object definitions such as obj name, the material to use, and the index buffers
         @param vp       : holds all the vertex position data
         @param vn       : holds all the vertex normal data
         @param vt       : holds all the vertex texcoord data
         @param mtllib   : is the name of the material library to load
         @param filename : is the name of the file to load
         */
        static bool OBJLoadDataFrmFile
        (   ds::slist<Polygon>& objs
         ,  gfx::DataBuffer<float>& vp
         ,  gfx::DataBuffer<float>& vn
         ,  gfx::DataBuffer<float>& vt
         ,  ds::string& mtllib
         ,  const ds::string& filename  );
        
        /**
         ---- function output ----
         @param mesh : output mesh
         ---- function inputs ----
         @param poly : hold the object definitions such as obj name, the material to use, and the index buffers
         @param vp   : holds all the vertex position data
         @param vn   : holds all the vertex normal data
         @param vt   : holds all the vertex texcoord data
         */
        static cg::mat33 OBJBuildRawMesh
        (   gfx::RawMesh& mesh
         ,  Polygon& poly
         ,  gfx::DataBuffer<float>& vp
         ,  gfx::DataBuffer<float>& vn
         ,  gfx::DataBuffer<float>& vt  );
        
        
        /**
         ---- function output ----
         @param mesh : output mesh
         ---- function inputs ----
         @param filename : is the name of the file to load
         */
        static bool OBJBuildRawMesh(gfx::RawMesh& mesh, const ds::string& filename);
        
        /**
         ---- function output ----
         @param meshlibrary : output meshlibrary
         @param mtllib : output name of material library to load
         ---- function inputs ----
         @param poly : hold the object definitions such as obj name, the material to use, and the index buffers
         @param vp   : holds all the vertex position data
         @param vn   : holds all the vertex normal data
         @param vt   : holds all the vertex texcoord data
         */
        static bool OBJLoadMeshLibrary(OBJMeshLibrary& meshlibrary, ds::string& mtllib, const ds::string& filename);
        static gfx::Gameobject* OBJLoadGameobject(kege::ResourceManager* manager, const ds::string& filename);
        gfx::Scenenode* Load(kege::ResourceManager* manager, const ds::string& filename);
        LoaderOBJ();
    };
}}
#endif /* LibraryModel_hpp */
