/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GraphicsFramework.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../../graphics/core/framework/GraphicsFramework.hpp"
namespace kege{namespace core{
    
    GraphicsFramework::FuncPtrParamI2 GraphicsFramework::callback_framebuffer_size = nullptr;
    GraphicsFramework::FuncPtrParamI2 GraphicsFramework::callback_window_position = nullptr;
    GraphicsFramework::FuncPtrParamB1 GraphicsFramework::callback_window_close = nullptr;
    GraphicsFramework::FuncPtrParamI2 GraphicsFramework::callback_window_size = nullptr;
    GraphicsFramework::FuncPtrParamI4 GraphicsFramework::callback_keyboard = nullptr;
    GraphicsFramework::FuncPtrParamI3 GraphicsFramework::callback_buttom = nullptr;
    GraphicsFramework::FuncPtrParamD2 GraphicsFramework::callback_cursor = nullptr;
    GraphicsFramework::FuncPtrParamD2 GraphicsFramework::callback_wheel = nullptr;
    
    void GraphicsFramework::OnKeyboardPress(int key, int scancode, int action, int mods)
    {
        if (callback_keyboard != nullptr) callback_keyboard(key, scancode, action, mods);
    }
    void GraphicsFramework::OnMouseCursorMove(double xpos, double ypos)
    {
        if (callback_cursor != nullptr) callback_cursor(xpos, ypos);
    }
    void GraphicsFramework::OnScrollWheelMove(double xoffset, double yoffset)
    {
        if (callback_wheel != nullptr) callback_wheel(xoffset, yoffset);
    }
    void GraphicsFramework::OnFramebufferSize(int w, int h)
    {
        if (callback_framebuffer_size != nullptr) callback_framebuffer_size(w, h);
    }
    void GraphicsFramework::OnWindowPosition(int x, int y)
    {
        if (callback_window_position != nullptr) callback_window_position(x, y);
    }
    void GraphicsFramework::OnWindowSize(int w, int h)
    {
        if (callback_window_size != nullptr) callback_window_size(w, h);
    }
    void GraphicsFramework::OnMouseButtonPress(int button, int action, int mods)
    {
        if (callback_buttom != nullptr) callback_buttom(button, action, mods);
    }
    void GraphicsFramework::OnWindowClose(bool value)
    {
        if (callback_window_close != nullptr) callback_window_close(value);
    }
    
    void GraphicsFramework::SetFramebufferSizeCallback( FuncPtrParamI2 funcptr )
    {
        callback_framebuffer_size = funcptr;
    }
    void GraphicsFramework::SetWindowPositionCallback( FuncPtrParamI2 funcptr )
    {
        callback_window_position = funcptr;
    }
    void GraphicsFramework::SetKeyboardCallback( FuncPtrParamI4 funcptr )
    {
        callback_keyboard = funcptr;
    }
    void GraphicsFramework::SetMouseButtonCallback( FuncPtrParamI3 funcptr )
    {
        callback_buttom = funcptr;
    }
    void GraphicsFramework::SetWindowSizeCallback( FuncPtrParamI2 funcptr )
    {
        callback_window_size = funcptr;
    }
    void GraphicsFramework::SetMouseCursorCallback(FuncPtrParamD2 funcptr )
    {
        callback_cursor = funcptr;
    }
    void GraphicsFramework::SetScrollWheelCallback(FuncPtrParamD2 funcptr )
    {
        callback_wheel = funcptr;
    }
    void GraphicsFramework::SetWindowCloseCallback(FuncPtrParamB1 funcptr )
    {
        callback_window_close = funcptr;
    }
    
}}
