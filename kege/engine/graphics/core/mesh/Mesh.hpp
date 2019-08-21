//
//  Mesh.hpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 5/24/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp
#include "array.hpp"
#include "string.hpp"
#include "../../../graphics/core/mesh/Geometry.hpp"
#include "../../../graphics/core/mesh/Geometry.hpp"
#include "../../../graphics/core/mesh/DrawElement.hpp"
#include "../../../graphics/core/framework/VAO.hpp"
namespace kege{namespace gfx{
    
    class Mesh
    {
    public:
        
        void SetMesh( const shared::Geometry& geomtry, const shared::DrawElement& material );

        const shared::DrawElement& GetDrawMaterial()const;
        const shared::Geometry& GetGeomtry()const;
        
        shared::DrawElement& GetDrawMaterial();
        shared::Geometry& GetGeomtry();
        
        void DrawInstanced( cg::uint instances )const;
        void Draw( const cg::mat44& transform )const;
        
        bool IsBinded()const;
        void Unbind()const;
        void Bind()const;
        void UnInit();
        bool Init();
        
        
        void Destory();
        
        Mesh( const shared::Geometry& geomtry, const shared::DrawElement& material );
        virtual ~Mesh();
        Mesh();
        
    private:
        
        shared::DrawElement _draw_element;
        shared::Geometry _geomtry;
        
        bool _isbind;
        bool _init;
    };
}}
namespace kege{namespace shared{
    typedef mem::shared< gfx::Mesh > Mesh;
}}
#endif /* Mesh_hpp */
