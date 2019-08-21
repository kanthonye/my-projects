/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/10/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GLFramebuffer.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include <OpenGL/gl3.h>
#include "Graphics.hpp"
#include "GLTexture2D.hpp"
#include "GLFramebuffer.hpp"
namespace kege{namespace core{
    
    int GetFormat(cg::uint i);
    void CheckFramebufferStatus();
    
    void GLFramebuffer::BlitFramebuffer(int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, int mask, int filter)
    {
        mask = gfx::Graphics::GetConstant( mask );
        filter = gfx::Graphics::GetConstant( filter );
        glBindFramebuffer(GL_READ_FRAMEBUFFER, id);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1,  dstX0, dstY0, dstX1, dstY1, mask, filter);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    
    void GLFramebuffer::Create(cg::uint width, cg::uint height, const FBOLayout& layout)
    {
        int count = 0;
        int color_attachment = 0;
        ds::array< cg::uint > drawbuffers;
        glBindRenderbuffer(GL_RENDERBUFFER, id);
        
        textures.resize( layout.size() );
        for (int i=0; i<layout.size(); i++)
        {
            GLTexture2D* texture = new GLTexture2D;
            {
                texture->CreateGLTexture2D
                (   width, height
                 ,  layout[ i ].format
                 ,  GetFormat(3)
                 ,  GL_FLOAT
                 ,  GL_LINEAR
                 ,  GL_LINEAR
                 ,  GL_CLAMP_TO_EDGE
                 ,  GL_CLAMP_TO_EDGE
                 ,  false
                 ,  layout[ i ].data  );
            }
            textures[ layout[ i ].index ] = texture;
            
            switch ( layout[ i ].comp_type )
            {
                case core::COLOR_COMPONENT:
                    color_attachment = GL_COLOR_ATTACHMENT0 + count++;
                    glFramebufferTexture2D(GL_FRAMEBUFFER, color_attachment, GL_TEXTURE_2D, texture->id, 0);
                    if ( layout[ i ].draw_buffer == true )
                    {
                        drawbuffers.resize( drawbuffers.size() + 1 );
                        drawbuffers[ drawbuffers.size() - 1 ] = color_attachment;
                    }
                    break;
             
                case core::DEPTH_COMPONENT:
                    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture->id, 0);
                    break;
                    
                default: break;
            }
        }
        glDrawBuffers( (int)drawbuffers.size(), drawbuffers.data() );
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        CheckFramebufferStatus();
    }
    void GLFramebuffer::ClearColor(float r, float g, float b, float a)
    {
        glClearColor( r, g, b, a );
    }
    void GLFramebuffer::ViewPort(int x, int y, int width, int height)
    {
        glViewport( x, y, width, height );
    }
    void GLFramebuffer::UnbindTextureColorComponents()
    {
    }
    void GLFramebuffer::BindTextureColorComponents()
    {
    }
    void GLFramebuffer::UnbindTexture(int i)
    {
    }
    void GLFramebuffer::BindTexture(int i)
    {
    }
    void GLFramebuffer::UnCreate()
    {
    }
    void GLFramebuffer::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    
    void GLFramebuffer::Clear()
    {
        glClear( buffers );
    }
    void GLFramebuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, id);
    }
    
    int GetFormat(cg::uint i)
    {
        switch (i)
        {
            case  3: return GL_RGB;
            case  1: return GL_RED;
            default: break;
        }
        return 1;
    }
    
    void CheckFramebufferStatus()
    {
        switch ( glCheckFramebufferStatus(GL_FRAMEBUFFER) )
        {
            default:
                fprintf(stderr,"\nERROR: UNKNOWN FRAMEBUFFER ERROR.\n");
                break;
                
            case GL_FRAMEBUFFER_UNDEFINED:
                fprintf(stderr,"\nERROR: FRAMEBUFFER UNDEFINED.\n");
                break;
                
            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                fprintf(stderr,"\nERROR: FRAMEBUFFER INCOMPLETE: INCOMPLETE ATTACHMENT.\n");
                break;
                
            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                fprintf(stderr,"\nERROR: FRAMEBUFFER INCOMPLETE: MISSING ATTACHMENT.\n");
                break;
                
            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
                fprintf(stderr,"\nERROR: FRAMEBUFFER INCOMPLETE: INCOMPLETE DRAW BUFFER.\n");
                break;
                
            case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
                fprintf(stderr,"\nERROR: FRAMEBUFFER INCOMPLETE: INCOMPLETE READ BUFFER.\n");
                break;
                
            case GL_FRAMEBUFFER_UNSUPPORTED:
                fprintf(stderr,"\nERROR: UNSUPPORTED FRAMEBUFFER.\n");
                break;
                
            case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
                fprintf(stderr,"\nERROR: FRAMEBUFFER INCOMPLETE: INCOMPLETE MULTISAMPLE.\n");
                break;
                
            case GL_FRAMEBUFFER_COMPLETE:
                break;
        }
    }
    GLFramebuffer::~ GLFramebuffer()
    {
    }
    GLFramebuffer::GLFramebuffer()
    {
    }
}}
