/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/10/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GLFramebuffer.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GLFramebuffer_hpp
#define GLFramebuffer_hpp
#include "Framebuffer.hpp"
namespace kege{namespace core{
    
    class GLFramebuffer : public Framebuffer
    {
    public:
        
        virtual void BlitFramebuffer(int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, int mask, int filter);
        
        void Create(cg::uint width, cg::uint height, const FBOLayout& layout);
        void ClearColor(float r, float g, float b, float a);
        void ViewPort(int x, int y, int width, int height);
        
        void UnbindTextureColorComponents();
        void BindTextureColorComponents() ;
        void UnbindTexture(int i);
        void BindTexture(int i);
        void UnCreate();
        void Unbind();
        void Clear();
        void Bind();
        
        ~ GLFramebuffer();
        GLFramebuffer();
        
        cg::uint buffers;
        cg::uint id;
        
        
        ds::array< mem::shared< core::Texture > > textures;
    };
}}
#endif /* GLFramebuffer_hpp */
