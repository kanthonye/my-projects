//
//  FontSheetMaker.hpp
//  FontTool
//
//  Created by Kenneth Esdaile on 3/1/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef FontSheetMaker_hpp
#define FontSheetMaker_hpp
#include "Window.hpp"
#include "array.hpp"
#include "image.hpp"
#include "lodepng.h"
#include "tga.hpp"
#include "Graphics.hpp"
namespace kege{namespace gfx{
    
    struct Glyph
    {
        short w; // sub-image width
        short h; // sub-image height
        
        cg::vec4 tex;
        
        float o; // offset of sub-image height
        short ascii;
        
        Glyph()
        : w(0)
        , h(0)
        , tex(0.0f)
        , o(0)
        , ascii(0) {}
    };
}}
    
    

namespace kege{namespace gfx{
    class Font;
    typedef mem::shared< gfx::Font > SharedFont;
    
    class Font : public ds::array< Glyph >
    {
    public:
        
        bool Create(short cols, short rows, short min_instensity, ds::string const& filename);
        bool Load(const ds::string& filename);
        
        const shared::Texture& GetTexture()const;
        shared::Texture& GetTexture();
        
        const bool IsLoaded() const;
        void Destroy();
        void Print()const;
        
        ~ Font();
        Font();
        
    private:
        
        bool Load(FILE* file);
        
    protected:
        
        shared::Texture texture;
    };
    
    
    
    
    
    class FontLib
    {
    public:
        static void UnBindFont(int n)
        {
            if (fonts.empty()) return;
            fonts[n].GetTexture()->SetBindingPoint(1);
            fonts[n].GetTexture()->Unbind();
        }
        static bool BindFont(int n)
        {
            if (fonts.empty()) return false;
            fonts[n].GetTexture()->SetBindingPoint(0);
            fonts[n].GetTexture()->Bind();
            return true;
        }
        static Font* GetFont(int n)
        {
            if (fonts.empty() || n >= fonts.size()) return nullptr;
            return &fonts[n];
        }
        static ds::array< Font >& GetFontArrat()
        {
            return fonts;
        }
        static void Destroy()
        {
            fonts.clear();
        }
        FontLib(){}
    private:
        static ds::array< Font > fonts;
    };
}}

#endif /* FontSheetMaker_hpp */
