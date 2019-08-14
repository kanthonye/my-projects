/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/24/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       MeshComponent.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "Entity.hpp"
#include "RenderingSystem.hpp"
#include "MeshComponent.hpp"
namespace kege{namespace gfx{

    void MeshComponent::Draw(gfx::RenderingSystem* renderer)
    {
        if ( _material != nullptr && _mesh != nullptr )
        {
            if ( _material->ReflectLight() )
            {
                const gfx::ArrayLights& lights = renderer->GetLights(_mesh->GetMinPoint(), _mesh->GetMaxPoint());
                _material->ApplyLights( lights );
            }
            
            _material->Bind();
            _material->ApplyModelMatrix( GetParent()->GetWorldMatrix() );
            
            _mesh->Bind();
            _mesh->Draw();
            _mesh->Unbind();
            
            _material->Unbind();
        }
    }
    
    void MeshComponent::GetRenderables( kege::SceneFrame& frame )
    {
        frame.renderables[ _material->GetType() ].push_back( this );
    }
    
    bool MeshComponent::Init(kege::Scene* scene)
    {
        if (_mesh != nullptr)
        {
            _material->Init();
            _mesh->Init();
        }
        return gfx::EntityComponent::Init(scene);
    }
    
    MeshComponent::MeshComponent(const ds::string& name, const SharedMesh& me, const SharedMaterial& ma)
    :   gfx::RenderComponent(name)
    ,   _mesh(me)
    ,   _material(ma)
    {}
    MeshComponent::MeshComponent( const SharedMesh& mesh, const SharedMaterial& material )
    :   gfx::RenderComponent("MeshComponent")
    ,   _mesh(mesh)
    ,   _material(material)
    {}
    
}}
