/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/3/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Model.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "Model.hpp"
#include "RenderingSystem.hpp"
namespace kege{namespace gfx{
    
    void Model::Submit( gfx::RenderingSystem* renderer )
    {
        renderer->Submit( GetMesh(), GetParent()->GetWorldMatrix() );
    }
    
    void Model::UnbindMaterial( gfx::RenderingSystem* renderer )
    {
        _mesh->GetDrawMaterial()->UnbindMaterial();
    }
    
    void Model::BindMaterial( gfx::RenderingSystem* renderer )
    {
        _mesh->GetDrawMaterial()->BindMaterial();
        //_mesh->GetDrawMaterial()->ApplyLights( renderer->GetLights(_mesh->GetMinPoint(), _mesh->GetMaxPoint()) );
    }
    
    void Model::BeginDraw( gfx::RenderingSystem* renderer )
    {
        if ( _mesh == nullptr ) return;
        _mesh->Bind();
    }
  
    void Model::EndDraw( gfx::RenderingSystem* renderer )
    {
        if ( _mesh == nullptr ) return;
        _mesh->GetDrawMaterial()->UnbindMaterial();
        _mesh->Unbind();
    }
    
    void Model::Draw( gfx::RenderingSystem* renderer )
    {
        if ( _mesh == nullptr ) return;
        _mesh->Draw( GetParent()->GetWorldMatrix() );
    }
    
    void Model::SetMesh( const shared::Mesh& mesh )
    {
        _mesh = mesh;
    }
    const shared::Mesh& Model::GetMesh() const
    {
        return _mesh;
    }
    
    shared::Mesh& Model::GetMesh()
    {
        return _mesh;
    }
    
    bool Model::Init( kege::Scene* scene )
    {
        if ( _init == true ) return _init;
        _mesh->Init();
        return gfx::Component::Init( scene );
    }
    
    Model::Model( const ds::string& name, const shared::Mesh& me )
    :   gfx::Component( gfx::Component::MODEL, name )
    ,   _mesh( me )
    {}
    
    Model::Model( const shared::Mesh& mesh )
    :   gfx::Component( gfx::Component::MODEL, "no-name" )
    ,   _mesh( mesh )
    {}
    
    Model::Model( const ds::string& name )
    :   gfx::Component( gfx::Component::MODEL, name )
    {}
}}

