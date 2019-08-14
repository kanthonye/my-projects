//
//  Graphics.cpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 5/24/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "Graphics.hpp"
#include "GLGraphics.hpp"
namespace kege{namespace gfx{
    
    gfx::GraphicsFramework* gfx::Graphics::framework = nullptr;
    
    gfx::GraphicsFramework* Graphics::Framework()
    {
        return framework;
    }
    
    Window* Graphics::CreateWindow(int width, int height, const char *title, bool fullscreen)
    {
        return framework->CreateWindow(width, height, title, fullscreen);
    }
    
    UBO* Graphics::CreateUBO(long size, const void* data, cg::uint usage, const ds::string& name)
    {
        return framework->CreateUBO(size, data, usage, name);
    }
    VBO* Graphics::CreateVBO(long size, const void* data, cg::uint usage)
    {
        return framework->CreateVBO(size, data, usage);
    }
    IBO* Graphics::CreateIBO(long size, const void* data, cg::uint usage)
    {
        return framework->CreateIBO(size, data, usage);
    }
    
    void Graphics::SetFramebufferSizeCallback( FuncPtrParamI2 funcptr )
    {
        framework->SetFramebufferSizeCallback( funcptr );
    }
    void Graphics::SetWindowSizeCallback( FuncPtrParamI2 funcptr )
    {
        framework->SetWindowSizeCallback( funcptr );
    }
    void Graphics::SetWindowPositionCallback( FuncPtrParamI2 funcptr )
    {
        framework->SetWindowPositionCallback( funcptr );
    }
    void Graphics::SetMouseButtonCallback( FuncPtrParamI3 funcptr )
    {
        framework->SetMouseButtonCallback( funcptr );
    }
    void Graphics::SetMouseCursorCallback( FuncPtrParamD2 funcptr )
    {
        framework->SetMouseCursorCallback( funcptr );
    }
    void Graphics::SetScrollWheelCallback( FuncPtrParamD2 funcptr )
    {
        framework->SetScrollWheelCallback( funcptr );
    }
    void Graphics::SetWindowCloseCallback( FuncPtrParamB1 funcptr )
    {
        framework->SetWindowCloseCallback( funcptr );
    }
    void Graphics::SetKeyboardCallback( FuncPtrParamI4 funcptr )
    {
        framework->SetKeyboardCallback( funcptr );
    }
    
    Shader* Graphics::CreateShader(const ds::string& filename)
    {
        return framework->CreateShader( filename );
    }
    
    Shader* Graphics::CreateShader(SHDR& shdr)
    {
        return framework->CreateShader( shdr );
    }
    
    Shader* Graphics::CreateShader()
    {
        return framework->CreateShader();
    }
    
    Framebuffer* Graphics::CreateFramebuffer()
    {
        return framework->CreateFramebuffer();
    }
    
    void Graphics::SetBackgroundColor(const cg::vec4& color)
    {
        framework->SetBackgroundColor( color );
    }
    
    RenderSetting* Graphics::CreateRenderSetting()
    {
        return framework->CreateRenderSetting();
    }
    
    TextureCube* Graphics::CreateTextureCube()
    {
        return framework->CreateTextureCube();
    }
    
    Texture2D* Graphics::CreateTexture2D()
    {
        return framework->CreateTexture2D();
    }
    
    void Graphics::EnablePointFrame()
    {
        framework->EnablePointFrame();
    }
    
    void Graphics::EnableWireFrame()
    {
        framework->EnableWireFrame();
    }
    
    void Graphics::EnableFillFrame()
    {
        framework->EnableFillFrame();
    }
    
    void Graphics::DisableCulling()
    {
        framework->DisableCulling();
    }
    
    void Graphics::EnableCullingCCW()
    {
        framework->EnableCullingCCW();
    }
    
    void Graphics::EnableCullingCW()
    {
        framework->EnableCullingCW();
    }
    
    void Graphics::DisableDepthTest()
    {
        framework->DisableDepthTest();
    }
    void Graphics::EnableDepthTest()
    {
        framework->EnableDepthTest();
    }
    
    void Graphics::DisableBlending()
    {
        framework->DisableBlending();
    }
    
    void Graphics::EnableBlending()
    {
        framework->EnableBlending();
    }
    void Graphics::AlphaBlending()
    {
        framework->AlphaBlending();
    }
    
    void Graphics::ClearScreen(void)
    {
        framework->ClearScreen();
    }
    
    VAO* Graphics::CreateVAO()
    {
        return framework->CreateVAO();
    }
    VBO* Graphics::CreateVBO()
    {
        return framework->CreateVBO();
    }
    UBO* Graphics::CreateUBO()
    {
        return framework->CreateUBO();
    }
    IBO* Graphics::CreateIBO()
    {
        return framework->CreateIBO();
    }
    
    cg::uint gfx::Graphics::GetConstant(int target)
    {
        return framework->GetConstant( target );
    }

    void gfx::Graphics::CheckError(source src)
    {
        framework->CheckError(src);
    }

    gfx::Graphics:: ~ Graphics()
    {
        if (framework != nullptr)
        {
            delete framework;
            framework = nullptr;
        }
    }

    gfx::Graphics::Graphics(GraphicsFramework* g)
    {
        if (g == nullptr)
        {
            framework = new gfx::GLGraphics();
        }
        else
        {
            framework = g;
        }
    }
}}
