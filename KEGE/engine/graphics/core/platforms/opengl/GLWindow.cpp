/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GLWindow.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../../../graphics/core/platforms/opengl/GLWindow.hpp"
namespace kege{namespace core{
    
    void GLWindow::SetBackgroundColor(const cg::vec4& color)
    {
        glClearColor(color.x, color.y, color.z, color.w);
    }
    
    void GLWindow::SetTitle(const ds::string& val)
    {
        title = val;
        glfwSetWindowTitle(win, title.c_str());
    }
    const ds::string& GLWindow::GetTitle(void)const
    {
        return title;
    }
    
    void GLWindow::DisableFullScreenMode(void)
    {
        GLFWmonitor * monitor = glfwGetPrimaryMonitor();
        GLFWvidmode const* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(win, nullptr, 0, 0, width, height, mode->refreshRate);
    }
    void GLWindow::EnableFullScreenMode(void)
    {
        GLFWmonitor * monitor = glfwGetPrimaryMonitor();
        GLFWvidmode const* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(win, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    
    void GLWindow::EnableVsync(void)const
    {
        glfwMakeContextCurrent(win);
        glfwSwapInterval(0);
    }
    void GLWindow::DisableVsync(void)const
    {
        glfwMakeContextCurrent(win);
        glfwSwapInterval(1);
    }
    
    void GLWindow::SwapBuffer(void)const
    {
        glfwSwapBuffers(win);
    }
    void GLWindow::PollEvents(void)const
    {
        glfwPollEvents();
    }
    
    
    void GLWindow::DisableCursor() const
    {
        //glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    
    void GLWindow::EnableCursor() const
    {
        glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    
    void GLWindow::HideCursor() const
    {
        glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }
    
    void GLWindow::ShowCursor() const
    {
        glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    
    int GLWindow::GetHeight(void) const
    {
        return height;
    }
    void GLWindow::SetHeight(int h)
    {
        height = h;
        glfwSetWindowSize(win, width, height);
    }
    
    int GLWindow::GetWidth(void)const
    {
        return width;
    }
    void GLWindow::SetWidth(int w)
    {
        width = w;
        glfwSetWindowSize(win, width, height);
    }
    
    void GLWindow::MakeCurrent(void)
    {
        glfwMakeContextCurrent(win);
    }
    
    bool GLWindow::IsOpen(void)const
    {
        if (win == nullptr) return false;
        return !glfwWindowShouldClose(win);
    }
    void  GLWindow::ClearScreen()
    {
        glViewport(0, 0, fbw, fbh);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    }
    void GLWindow::CloseWindow()
    {
        glfwSetWindowShouldClose(win, true);
    }
    
    GLWindow::GLWindow(int width, int height, const char *title, bool fullscreen)
    :   win(nullptr)
    ,   title(title)
    ,   height(height)
    ,   width(width)
    {
        if (fullscreen)
        {
            GLFWmonitor * monitor = glfwGetPrimaryMonitor();
            GLFWvidmode const* mode = glfwGetVideoMode(monitor);
            glfwWindowHint(GLFW_RED_BITS, mode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
            
            win = glfwCreateWindow(mode->width, mode->height, title, monitor, nullptr);
        }
        else
        {
            win = glfwCreateWindow(width, height, title, nullptr, nullptr);
        }
        //flags = GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT;
        glfwGetFramebufferSize(win, &fbw, &fbh);
        //bgcolr = colr;
        MakeCurrent();
    }
    GLWindow::~ GLWindow()
    {
        if (win != nullptr)
        {
            glfwDestroyWindow(win);
            win = nullptr;
        }
    }
    GLWindow::GLWindow()
    :   win(nullptr)
    ,   title()
    ,   height(0)
    ,   width(0)
    {}
    
}}

