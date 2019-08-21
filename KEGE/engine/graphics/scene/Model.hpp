/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/3/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Model.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef Model_hpp
#define Model_hpp
#include "Mesh.hpp"
#include "Material.hpp"
#include "Component.hpp"
namespace kege{namespace gfx{
    class AnimModel;
    class Model;
    
    class Model : public gfx::Component
    {
    public:
        
        Model( const ds::string& name, const shared::Mesh& me );
        Model( const shared::Mesh& mesh );
        
        virtual void UnbindMaterial( gfx::RenderingSystem* renderer );
        virtual void BindMaterial( gfx::RenderingSystem* renderer );
        virtual void BeginDraw( gfx::RenderingSystem* renderer );
        virtual void EndDraw( gfx::RenderingSystem* renderer );
        virtual void Draw( gfx::RenderingSystem* renderer );
        
        void Submit( gfx::RenderingSystem* renderer );
        
        void SetMesh( const shared::Mesh& mesh );
        const shared::Mesh& GetMesh() const;
        shared::Mesh& GetMesh();
        
        bool Init( kege::Scene* scene );
        Model( const ds::string& name );
        Model();
        
    protected:
        
        shared::Mesh _mesh;
    };
}}
namespace kege{namespace shared{
    typedef mem::shared< gfx::Model > Model;
}}
#endif /* Model_hpp */
