/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/11/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIRenderer.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIRenderer_hpp
#define GUIRenderer_hpp
#include "../../../ds/dynarry.hpp"
#include "../../../graphics/core/Mesh.hpp"
#include "../../gui/objects/GUIText.hpp"
#include "../../gui/objects/GUIWidget.hpp"
#include "../../gui/objects/GUITheme.hpp"
#include "../../gui/objects/Font.hpp"
namespace kege{namespace cg{

    class GUIRenderer
    {
    public:
        
        void SetProjection( const cg::mat44& proj );
        void DrawGUI( const GUIWidget* gui );
        void DrawText( const GUIText* gui );
        
        void UnInit();
        void Init();
        void Unbind();
        bool Bind();
        void Flush();
        
        GUIRenderer();
        
        struct GUIRendrData
        {
            cg::vec4 posi;
            cg::vec4 rect;
            cg::vec4 colr;
            cg::vec4 texl;
            cg::vec4 sdf;
            cg::vec4 sdf_colr;
        };
        ds::dynarry< GUIRendrData > data;
        gfx::SharedVAO _vao;
        GUITheme theme;
        
        cg::ushort max_draw_count;
        cg::ushort draw_count;
        cg::ushort _draw_mode;
        cg::ushort stride;
        double zdepth;
    };
}}
#endif /* GUIRenderer_hpp */
