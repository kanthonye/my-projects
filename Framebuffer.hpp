//
//  Framebuffer.hpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 5/25/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef Framebuffer_hpp
#define Framebuffer_hpp
#include "array.hpp"
#include "../../graphics/cgmath/cgm.hpp"
namespace kege {namespace gfx{
    class FBOLayout;
    
    class Framebuffer
    {
    public:
        
        virtual void Create(cg::uint width, cg::uint height, const FBOLayout& layout) = 0;
        virtual void ClearColor(float r, float g, float b, float a) = 0;
        virtual void ViewPort(int x, int y, int width, int height) = 0;
        virtual void UnbindTextureColorComponents() = 0;
        virtual void BindTextureColorComponents() = 0;
        
        virtual void UnbindTexture(int i) = 0;
        virtual void BindTexture(int i) = 0;
        virtual void UnCreate() = 0;
        virtual void Unbind() = 0;
        virtual void Clear() = 0;
        virtual void Bind() = 0;
        
        
        virtual ~ Framebuffer(){}
    };
    
    
    struct FBOElement
    {
        void* data;
        int channels;
        int comp_type;
        int format;
        int index;
        bool draw_buffer;
    };
    
    class FBOLayout : public ds::array< FBOElement >
    {
    public:
        void AddRenderTexture2D( int index , int comp_type, int format, int channels, void* data, bool draw_buffer );
        FBOLayout( int n ) : ds::array< FBOElement >( n ) {}
    };
    
    
    typedef kege::shared< Framebuffer > SharedFramebuffer;
}}
#endif /* Framebuffer_hpp */
