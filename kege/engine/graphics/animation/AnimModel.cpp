/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       AnimModel.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "AnimModel.hpp"
#include "RenderingSystem.hpp"
namespace kege{namespace gfx{
    
  void AnimModel::BindMaterial( gfx::RenderingSystem* renderer )
    {
        _mesh->GetDrawMaterial()->BindMaterial();
        //_mesh->GetDrawMaterial()->ApplyLights( renderer->GetLights(_mesh->GetMinPoint(), _mesh->GetMaxPoint()) );
    }

    void AnimModel::SetSkeleton(const gfx::Bones& bones)const
    {
        const core::UBO* ubo = _mesh->GetDrawMaterial()->GetMaterial()->GetShader()->GetUBO("SKELETON");
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
    
    void AnimModel::Draw( gfx::RenderingSystem* renderer )
    {
        if ( _mesh == nullptr ) return;
        _mesh->Draw( GetParent()->GetWorldMatrix() );
    }
    
    const shared::Skeleton& AnimModel::GetSkeleton() const
    {
        return _skeleton;
    }
    shared::Skeleton& AnimModel::GetSkeleton()
    {
        return _skeleton;
    }
    
    
    AnimModel::AnimModel( const ds::string& name, const shared::Mesh& me, const shared::Skeleton& sk )
    :   gfx::Model( name, me )
    ,   _skeleton( sk )
    {}
    
    AnimModel::AnimModel( const shared::Mesh& me, const shared::Skeleton& sk )
    :   gfx::Model( "no-name", me )
    ,   _skeleton( sk )
    {}
}}

