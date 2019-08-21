/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/14/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       DrawElement.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef KEGE_DrawElement_hpp
#define KEGE_DrawElement_hpp
#include "../../../graphics/core/framework/VAO.hpp"
#include "../../../graphics/core/mesh/Material.hpp"
namespace kege{namespace gfx{
    
    class DrawElement
    {
    public:
    
        void DrawInstanceIndices( const core::VAO* vao, cg::uint instances )const;
        void DrawInstanceArray( const core::VAO* vao, cg::uint instances )const;
        void DrawIndices( const core::VAO* vao, const cg::mat44& transform )const;
        void DrawArray( const core::VAO* vao, const cg::mat44& transform )const;
        void UnbindMaterial()const;
        void BindMaterial()const;
        
        void ApplyLights( const gfx::ArrayLights& lights )const;
        
        void SetMaterial(const shared::Material& material);
        const shared::Material& GetMaterial()const;
        shared::Material& GetMaterial();
        
        void SetStartingIndex( cg::uint value );
        void SetDrawCount( cg::uint value );
        void SetDrawMode( cg::uint value );
        
        cg::uint GetStartingIndex()const;
        cg::uint GetDrawCount()const;
        cg::uint GetDrawMode()const;
        
        void UnInit();
        bool Init();
        
        DrawElement( cg::uint draw_mode, cg::uint starting_index, cg::uint draw_count, const shared::Material& material );
        DrawElement( );
        
    private:
        
        shared::Material _material;
        cg::uint _starting_index; // starting vertex index
        cg::uint _draw_count;     // total vertex indices to draw index
        cg::uint _draw_mode;      // draw mode
    };
}}
namespace kege{namespace shared{
    typedef mem::shared< gfx::DrawElement > DrawElement;
}}
#endif /* KEGE_DrawElement_hpp */
