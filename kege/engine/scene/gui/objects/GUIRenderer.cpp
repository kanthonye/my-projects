/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/11/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIRenderer.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../../graphics/core/Graphics.hpp"
#include "SystemVirtFile.hpp"
#include "Font.hpp"
#include "GUIRenderer.hpp"
namespace kege{namespace cg{
    
    void GUIRenderer::SetProjection( const cg::mat44& proj )
    {
        if (theme._unif_projection != nullptr)
        {
            theme._unif_projection->SetMat44f( proj.data );
        }
    }
    
    void GUIRenderer::DrawGUI( const GUIWidget* gui )
    {
        zdepth += 1.0;
        
        GUIRendrData& m = data[ draw_count++ ];
        m.posi.x = gui->GetWorldPosition().x;
        m.posi.y = gui->GetWorldPosition().y;
        m.posi.z = zdepth;//-draw_count * 0.00005 + 100;
        m.posi.w = 0.0;
        
        m.rect.x = gui->GetWidth();
        m.rect.y = gui->GetHeight();
        m.rect.z = 0.0;
        m.rect.w = 0.0;
        
        m.colr = gui->GetColor();
        m.texl = gui->GetTexel();
        
        if (draw_count >= max_draw_count)
        {
            Flush();
        }
    }
    
    void GUIRenderer::DrawText( const GUIText* gui )
    {
        const gfx::Font* font = gfx::FontLib::GetFont( gui->GetFontID() );
        if (font == nullptr) return;
        gfx::FontLib::BindFont( gui->GetFontID() );
    
        const gfx::Glyph* glyph = &font->at( 'W' );
        const float scale = float(gui->GetFontSize()) / float(glyph->h) * 1.0;
        const short space = glyph->w * scale;
        float o,w,h, advance, len = 0.0f, hgh = 0.0;
        float ls = 0.45; // letter spacing
        cg::vec3 p = gui->GetWorldPosition();
        
        //zdepth = -(gui->GetText()->length() + 1)* 0.00005;
        
        p.y -= 1;
        const char* cstr = gui->GetText()->c_str();
        
        for (; *cstr != 0; cstr++)
        {
            if ( len < gui->GetWidth() )
            {
                glyph = &font->at( *cstr );
            }
            else if ( !gui->GetWrapAround() )
            {
                glyph = &font->at( (int) font->size() - 1 );
            }
            else
            {
                glyph = &font->at( '\n' );
                cstr--;
            }
            
            if (glyph->ascii == ' ')
            {
                advance = space * ls;
            }
            else if (glyph->ascii == '\n')
            {
                advance = 0.0f;
                hgh += space;
                len  = advance;
                p.x  = gui->GetWorldPosition().x;
                p.y  = gui->GetWorldPosition().y + hgh;
                
                //if (hgh >= height) break;
            }
            else
            {
                w = glyph->w * scale;
                h = glyph->h * scale;
                o = glyph->o * scale;
                {
                    GUIRendrData& m = data[ draw_count++ ];
                    zdepth += 0.00005;
                    m.posi.x = p.x;
                    m.posi.y = p.y + o;
                    m.posi.z = zdepth;
                    m.posi.w = 1;
                    
                    m.rect.x = w;
                    m.rect.y = h;
                    m.rect.z = 0.0;
                    m.rect.w = 0.0;
                    
                    m.colr = gui->GetColor();
                    m.texl = glyph->tex;
                    
                    if (draw_count >= max_draw_count)
                    {
                        Flush();
                    }
                }
                advance = w * ls;
                if (len >= gui->GetWidth()) break;
            }
            p.x += advance;
            len += advance;
        }
    }
    
    void GUIRenderer::UnInit()
    {
        _vao = nullptr;
    }
    void GUIRenderer::Init()
    {
        theme.Init();
        _vao = gfx::Graphics::CreateVAO();
        if (_vao != nullptr)
        {
            stride = 24;
            max_draw_count = 2000;
            data.resize( max_draw_count );
            _vao->Bind();
            {
                gfx::VertexLayout layout;
                layout.AddElem(0, 4,  0, 1);
                layout.AddElem(1, 4,  4, 1);
                layout.AddElem(2, 4,  8, 1);
                layout.AddElem(3, 4, 12, 1);
                layout.AddElem(4, 4, 16, 1);
                layout.AddElem(5, 4, 20, 1);
                _vao->AttachVBO(max_draw_count * stride * sizeof(float), stride * sizeof(float), data.data(), gfx::DYNAMIC_DRAW, layout);
                _draw_mode = gfx::Graphics::GetConstant(gfx::DRAW_TRIANGLE_STRIP);
            }
            _vao->Unbind();
        }
        
        ds::string filename = kege::VFS::GetInstance().GetFilename("~/fonts/monaco.fnt");
        gfx::FontLib::GetFontArrat().resize( 10 );
        gfx::FontLib::GetFontArrat()[0].Load( filename );
    }
    void GUIRenderer::Unbind()
    {
        theme.Unbind();
    }
    bool GUIRenderer::Bind()
    {
        if ( theme._program == nullptr)
        {
            return false;
        }
        theme.Bind();
        return true;
    }
    
    void GUIRenderer::Flush()
    {
        if (draw_count > 0)
        {
            _vao->Bind();
            _vao->GetVBO( 0 )->UpdateBufferData( draw_count * stride * sizeof(float), data.data() );
            _vao->DrawInstanced( _draw_mode, 0, 4, draw_count );
            _vao->Unbind();
            draw_count = 0;
        }
        zdepth = 0.0;
    }
    
    GUIRenderer::GUIRenderer()
    :   _vao(nullptr)
    ,   draw_count(0)
    ,   stride(0)
    ,   zdepth( 100.0 )
    {}
    
}}
