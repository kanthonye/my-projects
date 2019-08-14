/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/24/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       MeshComponent.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef MeshComponent_hpp
#define MeshComponent_hpp
#include "Mesh.hpp"
#include "Material.hpp"
#include "RenderComponent.hpp"
namespace kege{namespace gfx{
    
    class MeshComponent : public gfx::RenderComponent
    {
    public:
        
        virtual inline void SetMaterial(const SharedMaterial& material) {_material = material;}
        virtual inline const SharedMaterial& GetMaterial() const {return _material;}
        
        virtual inline void SetMesh(const SharedMesh& mesh) {_mesh = mesh;}
        virtual inline const SharedMesh& GetMesh() const {return _mesh;}
        
        virtual void GetRenderables( kege::SceneFrame& frame );
        virtual bool Init(kege::Scene* scene);
        
        virtual void Draw(gfx::RenderingSystem* renderer);
        
        MeshComponent(const SharedMesh& me, const SharedMaterial& ma);
        
    protected:
        
        MeshComponent(const ds::string& name, const SharedMesh& me, const SharedMaterial& ma);
        
        MeshComponent( const ds::string& name )
        :   gfx::RenderComponent( name )
        {}
        
    protected:
        
        SharedMaterial _material;
        SharedMesh _mesh;
    };
}}
#endif /* MeshComponent_hpp */
