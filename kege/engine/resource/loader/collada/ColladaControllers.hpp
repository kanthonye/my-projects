//======================================================================
//  Author  : Kenneth A Esdaile
//  Date    : Created on 5/22/16.
//  Title   : ColladaControllers.hpp
//  Project : KEGE
//======================================================================
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//======================================================================
#ifndef ColladaControllers_hpp
#define ColladaControllers_hpp
#include "array.hpp"
#include "Mesh.hpp"
#include "ColladaLibrary.hpp"
#include "ColladaVisualScenes.hpp"
namespace kege{namespace dae{
    
    class ColladaControllers : public dae::ColladaLibrary
    {
    public:
        
        void AttachSkeletalBonesToJoints(gfx::Joint* hierarchy, gfx::Skeleton* skeleton, kege::XML* skin);
        void GetVertexWeights(gfx::DataBuffer<float>& vw, gfx::DataBuffer<float>& vj, kege::XML* skin);
        void SetupSkeletalJointmap(gfx::Joint* hierarchy, gfx::Skeleton* skeleton);
        
        gfx::SharedSkeleton BuildSkeleton(kege::XML* instance, dae::ColladaVisualScenes& scenes);
        gfx::SharedMesh InstanceController(const ds::string& id, dae::ColladaGeometries geometries);
        
        gfx::DataBuffer<float> GetInverseBindMatrices(kege::XML* controller);
        gfx::DataBuffer<ds::string> GetJoints(kege::XML* controller);
        cg::mat44 GetBindShapeMatrix(kege::XML* skin);
        
        kege::XML* GetInputSource(kege::XML* mesh, kege::XML* input);
        kege::XML* GetInverseBindMatrixInput(kege::XML* skin);
        kege::XML* GetController(const ds::string& id);
        kege::XML* GetJointInput(kege::XML* skin);
        kege::XML* GetSkin(kege::XML* controller);
        
        kege::XML* GetVertexWeights(kege::XML* skin);
        
        ColladaControllers(kege::XML* controllers)
        :   controllers(controllers)
        {}
        
    private:
        
        kege::XML* controllers;
    };
}}
#endif /* ColladaControllers */
