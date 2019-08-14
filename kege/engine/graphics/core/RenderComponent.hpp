//
//  RenderComponent.hpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 2/18/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef RenderComponent_hpp
#define RenderComponent_hpp
#include "Mesh.hpp"
#include "Material.hpp"
#include "EntityComponent.hpp"
namespace kege{namespace gfx{
    class RenderingSystem;
    
    class RenderComponent : public gfx::EntityComponent
    {
    public:
        
        virtual void SetMaterial(const SharedMaterial& material) = 0;
        virtual const SharedMaterial& GetMaterial() const = 0;
        
        virtual void SetMesh(const SharedMesh& mesh) = 0;
        virtual const SharedMesh& GetMesh() const = 0;
        
        virtual void Draw(gfx::RenderingSystem* renderer) = 0;
        
        void GetRenderables( kege::SceneFrame& frame ) = 0;;
        bool Init(kege::Scene* scene);
        
        RenderComponent( const ds::string& name )
        :   gfx::EntityComponent( gfx::EntityComponent::RENDERABLE, name )
        {}
    };
    
    typedef ds::dlist< gfx::RenderComponent* > RenderComponents;
}}
#endif /* RenderComponent_hpp */
