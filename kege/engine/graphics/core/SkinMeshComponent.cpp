/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/24/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       SkinMeshComponent.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#include "Entity.hpp"
#include "RenderingSystem.hpp"
#include "SkinMeshComponent.hpp"
namespace kege{namespace gfx{
    
    void SkinMeshComponent::SetSkeleton(const gfx::Bones& bones)const
    {
        const gfx::UBO* ubo = _material->GetShader()->GetUBO("SKELETON");
        if (ubo == nullptr)
        {
            cg::mat44* m = (cg::mat44*) ubo->BeginBufferRead();
            if (m != nullptr)
            {
                for (int i=0; i<bones.size() && i<128; i++)
                {
                    m[i] = bones[i].inv_bind * bones[i].joint->world;
                }
                ubo->EndBufferReadWrite();
            }
        }
    }
    
    void SkinMeshComponent::Draw(gfx::RenderingSystem* renderer)
    {
        if ( _mesh == nullptr  || _material == nullptr) return;
        
        _material->Bind();
        
        if ( _material->ReflectLight() )
        {
            _material->ApplyLights( renderer->GetLights(_mesh->GetMinPoint(), _mesh->GetMaxPoint()) );
        }
        if (_skeleton != nullptr)
        {
            SetSkeleton( _skeleton->GetBones() );
        }
        _material->ApplyModelMatrix( GetParent()->GetWorldMatrix() );
        _mesh->Bind();
        _mesh->Draw();
        _mesh->Unbind();
        _material->Unbind();
    }
    
    SkinMeshComponent::SkinMeshComponent
    (   const SharedMesh& mesh
     ,  const SharedMaterial& material
     ,  const SharedSkeleton& skeleton  )
    :   gfx::MeshComponent("SkinMeshComponent", mesh, material)
    ,   _skeleton(skeleton)
    {}
    
}}

