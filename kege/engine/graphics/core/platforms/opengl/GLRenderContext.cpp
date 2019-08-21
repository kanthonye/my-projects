/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GLRenderContext.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include <OpenGL/gl3.h>
#include "GLRenderContext.hpp"
namespace kege{namespace core{
    
    void GLRenderContext::EnablePointFrame()const
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
    
    void GLRenderContext::EnableWireFrame()const
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    
    void GLRenderContext::EnableFillFrame()const
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    
    void GLRenderContext::DisableCulling()const
    {
        glDisable(GL_CULL_FACE);
    }
    
    void GLRenderContext::EnableCullingCCW()const
    {
        glEnable(GL_CULL_FACE);
        glFrontFace (GL_CCW);
        glCullFace (GL_FRONT);
    }
    
    void GLRenderContext::EnableCullingCW()const
    {
        glEnable(GL_CULL_FACE);
        glFrontFace (GL_CW);
        glCullFace (GL_FRONT);
    }
    
    void GLRenderContext::DisableDepthTest()const
    {
        glDisable(GL_DEPTH_TEST);
    }
    void GLRenderContext::EnableDepthTest()const
    {
        glEnable(GL_DEPTH_TEST);
    }
    
    void GLRenderContext::DisableBlending()const
    {
        glDisable(GL_BLEND);
    }
    
    void GLRenderContext::EnableBlending()const
    {
        glEnable(GL_BLEND);
    }
    void GLRenderContext::AlphaBlending()const
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);
    }
    
    void GLRenderContext::ClearScreen(float x, float y, float z, float w)const
    {
//        glViewport(0, 0, gfx::Window::framebuffer_width, gfx::Window::framebuffer_height);
        glClearColor(x, y, z, w);
//        glClear( flags );
    }
}}


