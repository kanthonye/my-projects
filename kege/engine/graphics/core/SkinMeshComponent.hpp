/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/24/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       SkinMeshComponent.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef SkinMeshCompnent_hpp
#define SkinMeshCompnent_hpp
#include "Mesh.hpp"
#include "Material.hpp"
#include "Skeleton.hpp"
#include "MeshComponent.hpp"
namespace kege{namespace gfx{
    
    class SkinMeshComponent : public gfx::MeshComponent
    {
    public:
        
        void SetSkeleton(const gfx::Bones& bones)const;
        void Draw(gfx::RenderingSystem* renderer);
        
        SkinMeshComponent
        (   const SharedMesh& mesh
         ,  const SharedMaterial& material
         ,  const SharedSkeleton& skeleton  );
        
    private:
        
        SharedSkeleton _skeleton;
    };
}}
#endif /* SkinMeshCompnent_hpp */
