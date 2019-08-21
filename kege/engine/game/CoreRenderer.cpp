/*!
 *  @author     Kenneth Anthony Esdaile
 *  @date       created on 4/23/19
 *  @copyright  Copyright (c) 2014 kae. All rights reserved.
 *  @file       CoreRenderer.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#include "Singleton.hpp"
#include "GLGraphics.hpp"
#include "GameEngine.hpp"
#include "RenderingSystem.hpp"
#include "CoreRenderer.hpp"
#include "GameStateManager.hpp"
namespace kege{
    
    core::Window* CoreRenderer::GetWindow()
    {
        return _window;
    }
    
    void CoreRenderer::SetWindowTitle(const ds::string& val)
    {
        _title = val;
    }
    void CoreRenderer::WindowBGColor(const cg::vec4& color)
    {
        _color = color;
    }
    void CoreRenderer::SetFBOFlags(cg::uint flags)
    {
        _fbo_flags = flags;
    }
    void CoreRenderer::SetFullscreen(bool val)
    {
        _fullscreen = val;
    }
    void CoreRenderer::SetWindowHeight(int val)
    {
        _height = val;
    }
    void CoreRenderer::SetWindowWidth(int val)
    {
        _width = val;
    }
    
    void CoreRenderer::Update(double time_delta)
    {
    }
    
    void CoreRenderer::ClearBuffer()
    {
        _window->ClearScreen();
    }
    
    void CoreRenderer::SwapBuffer()
    {
        _window->SwapBuffer();
    }
    
    void CoreRenderer::PollEvents()
    {
        _window->PollEvents();
    }
    
    void CoreRenderer::UnInit()
    {
        if (_graphics != nullptr)
        {
            if (_window == nullptr)
            {
                delete _window;
                _window = nullptr;
            }
        }
    }
    
    bool CoreRenderer::Init()
    {
        if (_graphics != nullptr)
        {
            return false;
        }
        _graphics = new gfx::Graphics( new core::GLGraphics() );
        
        _window = gfx::Graphics::CreateWindow(_width, _height, _title.c_str(), _fullscreen);
        _window->ClearScreen();
        
        _init = true;
        return _init;
    }
    
    CoreRenderer::CoreRenderer( kege::GameEngine* engine )
    :   kege::CoreSystem( "CoreRenderer", engine )
    ,   _graphics(nullptr)
    ,   _window(nullptr)
    ,   _height(512)
    ,   _width(1024)
    ,   _title("KEGE")
    ,   _fbo_flags(0)
    ,   _fullscreen(false)
    ,   _color(0.5,0.54,0.56,1.0)
    {
        kege::Singleton::Set< CoreRenderer >( this );
    }
    CoreRenderer::~ CoreRenderer()
    {
        kege::Singleton::Free< CoreRenderer >();
    }
}
