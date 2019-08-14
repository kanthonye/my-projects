//
//  FontSheetMaker.cpp
//  FontTool
//
//  Created by Kenneth Esdaile on 3/1/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//

#include <cstring>
#include "Font.hpp"
#include "Graphics.hpp"
namespace kege{namespace gfx{
    
    
    struct GrayScale
    {
        unsigned char * pixels;
        unsigned short width;
        unsigned short height;
        
        unsigned char operator()(int x,int y)const
        {
            if(x>=width || y >= height) return 0;
            return pixels[x+y*width];
        }
        
        GrayScale(ds::string const& filename)
        :   pixels(nullptr)
        ,   width(0)
        ,   height(0)
        {
            kege::image<cg::ubyte> img = kege::open_image(filename);
            if (img.empty())
                return;
            
            // setup image sheet for readying
            height = img.height();
            width = img.width();
            int i,size = width * height;
            short stride = img.bpp() / 8;
            int imgsize = size * stride;
            pixels = new unsigned char[size];
            unsigned short r,g,b,v;
            i = 0;
            for (int j=0; j<imgsize; j+=stride)
            {
                r = *img[j];
                g = *img[j+1];
                b = *img[j+2];
                v = (r + g + b) * 0.3;
                pixels[i++] = v;
            }
            img.clear();
        }
        ~ GrayScale()
        {
            if (pixels != nullptr)
            {
                delete [] pixels;
                pixels = nullptr;
            }
        }
        GrayScale()
        :   pixels(nullptr)
        ,   width(0)
        ,   height(0)
        {}
    };
    
    bool Font::Create(short cols, short rows, short min_instensity, ds::string const& filename)
    {
        kege::image<cg::ubyte> img = kege::open_image(filename);
        if (img.data() == nullptr)
        {
            return false;
        }
        
        int height = img.height();
        int width  = img.width();
        float grid_height = img.height() / rows;
        float grid_width  = img.width()  / cols;
        float grid_h;
        float grid_w;
        
        Font* font = this;
        Glyph* glyph = nullptr;
        font->resize(cols*rows);
        
        cg::var2i max,min;
        int w,h,x,y,i=0;
        
        for (h = height; h>0; h -= grid_height)
        {
            for (w = 0; w < width; w += grid_width)
            {
                max = {0,0};
                min = cg::var2i(width, height);
                
                grid_h = h - grid_height;
                grid_w = w + grid_width;
                for (y = h; y > grid_h; y--)
                {
                    for (x = w; x < grid_w; x++)
                    {
                        if (*img(x,y) >= min_instensity)
                        {
                            max.x = (max.x < x) ? x : max.x;
                            max.y = (max.y < y) ? y : max.y;
                            min.x = (min.x > x) ? x : min.x;
                            min.y = (min.y > y) ? y : min.y;
                        }
                    }
                }
                
                if (min.y >= height) min.y = 0;
                if (min.x >= width)  min.x = 0;
                
                //c = (h + (h-grid_height)) * 0.5;
                
                glyph = &font->at(i);
                glyph->w = (max.x - min.x);
                glyph->h = (max.y - min.y);
                glyph->tex.x = min.x   / double(width);
                glyph->tex.y = min.y   / double(height);
                glyph->tex.z = glyph->w / double(width);
                glyph->tex.w = glyph->h / double(height);
                glyph->o = h - max.y;
                i++;
            }
        }
        
        for (i=0; i<font->size(); i++)
        {
            font->at(i).ascii = i;
        }
        
        ds::string name = filename.parse_name();
        ds::string path = filename.parse_fpath();
        ds::string fname = path + name + ".fnt";
        FILE * file = fopen(fname.c_str(), "wb");
        if (file)
        {
            int count = height * width;
            fwrite(&height, 1, sizeof(short), file);
            fwrite(&width, 1, sizeof(short), file);
            fwrite(img.data(), count, sizeof(unsigned char), file);
            
            count = (int) font->size();
            fwrite(&count, 1, sizeof(int), file);
            fwrite(font->data(), count, sizeof(Glyph), file);
            fclose(file);
        }
        //SaveFontCSV(sheet, grayscale, path + name);
        return true;
    }
    
    bool Font::Load( FILE* file )
    {
        if (file == nullptr)
        {
            return false;
        }
        Font* font = this;
        GrayScale grayscale;
        fread(&grayscale.height, 1, sizeof(short), file);
        fread(&grayscale.width, 1, sizeof(short), file);
        int count = grayscale.height * grayscale.width;
        grayscale.pixels = new unsigned char[count];
        fread(grayscale.pixels, count, sizeof(unsigned char), file);
        
        fread(&count, 1, sizeof(int), file);
        font->resize(count);
        fread(font->data(), count, sizeof(Glyph), file);
        
        fclose(file);
        file = nullptr;
        
        gfx::Texture2D* texture = gfx::Graphics::CreateTexture2D();
        if (texture != nullptr)
        {
            texture->Create
            (  grayscale.width
             , grayscale.height
             , GFX::RED
             , GFX::RED
             , GFX::UNSIGNED_BYTE
             , GFX::LINEAR_FILTER
             , GFX::LINEAR_FILTER
             , GFX::CLAMP_TO_EDGE
             , GFX::CLAMP_TO_EDGE
             , false
             , grayscale.pixels );
            
            font->GetTexture() = texture;
        }
        return true;
    }
    
    bool Font::Load( const ds::string& filename )
    {
        return Load( fopen(filename.c_str(), "r") );
    }
    
    const gfx::SharedTexture& Font::GetTexture()const
    {
        return texture;
    }
    
    gfx::SharedTexture& Font::GetTexture()
    {
        return texture;
    }
    
    const bool Font::IsLoaded() const
    {
        return (size() != 0);
    }
    
    void Font::Print() const
    {
        for (long t=0; t<size(); t++)
        {
            const Glyph* comp = &at( t );
            printf("position( %.3f, %.3f )  width( %.3f )  height( %.3f )  h_offset( %.3f )\n"
                   ,comp->tex.x, comp->tex.y, comp->tex.z, comp->tex.w, comp->o);
        }
    }
    
    void Font::Destroy()
    {
        texture = nullptr;
        clear();
    }
    
    Font::~ Font()
    {
        Destroy();
    }
    
    Font::Font()
    {}
    
    
    
    
    ds::array< Font > FontLib::fonts;
}}

