//======================================================================
//  Author  : Kenneth A Esdaile
//  Date    : Created on 4/14/19.
//  Title   : ColladaGeometries.hpp
//  Project : KEGE
//======================================================================
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//======================================================================
#ifndef ColladaGeometries_hpp
#define ColladaGeometries_hpp
#include <map>
#include "XML.hpp"
#include "Mesh.hpp"
#include "DataBuffer.hpp"
#include "ColladaLibrary.hpp"
namespace kege{namespace dae{
    
    class ColladaGeometries : public dae::ColladaLibrary
    {
    public:
        
        void GetMeshPolylist(kege::XML::list& polylist, kege::XML* mesh);
        
        kege::XML* GetPolylistInput(kege::XML* polylist, const ds::string& semantic);
        kege::XML* GetMeshSource(kege::XML* mesh, const ds::string& id);
        kege::XML* GetInputSource(kege::XML* mesh, kege::XML* input);
        kege::XML* GetMeshVertices(kege::XML* mesh);
        kege::XML* GetMeshPolylist(kege::XML* mesh);
        kege::XML* GetMesh(const ds::string& id);
    
        void ContructGeometry(gfx::Mesh& mesh, const ds::string& id, gfx::DataBuffer<float>& vw, gfx::DataBuffer<float>& vj);
        void ContructGeometry(gfx::Mesh& mesh, const ds::string& id);
        
        gfx::SharedMesh InstanceGeometry(const ds::string& id);
        
        ColladaGeometries(kege::XML* geometries)
        :   geometries(geometries)
        {}
        
    private:
        
        kege::XML* geometries;
    };
}}
#endif /* ColladaGeometries */

