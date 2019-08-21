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
    
    core::GraphicsFramework* gfx::Graphics::framework = nullptr;
    
    core::GraphicsFramework* Graphics::Framework()
    {
        return framework;
    }
    
    core::Window* Graphics::CreateWindow(int width, int height, const char *title, bool fullscreen)
    {
        return framework->CreateWindow(width, height, title, fullscreen);
    }
    
    core::UBO* Graphics::CreateUBO(long size, const void* data, cg::uint usage, const ds::string& name)
    {
        return framework->CreateUBO(size, data, usage, name);
    }
    core::VBO* Graphics::CreateVBO(long size, const void* data, cg::uint usage)
    {
        return framework->CreateVBO(size, data, usage);
    }
    core::IBO* Graphics::CreateIBO(long size, const void* data, cg::uint usage)
    {
        return framework->CreateIBO(size, data, usage);
    }
    
    core::VAO* Graphics::CreateVAO( core::VertexBuffer* vb, core::IndexBuffer* ib )
    {
        return framework->CreateVAO( vb, ib );
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
    
    core::Shader* Graphics::CreateShader(const ds::string& filename)
    {
        return framework->CreateShader( filename );
    }
    
    core::Shader* Graphics::CreateShader(core::SHDR& shdr)
    {
        return framework->CreateShader( shdr );
    }
    
    core::Shader* Graphics::CreateShader()
    {
        return framework->CreateShader();
    }
    
    core::Framebuffer* Graphics::CreateFramebuffer()
    {
        return framework->CreateFramebuffer();
    }
    
    void Graphics::SetBackgroundColor(const cg::vec4& color)
    {
        framework->SetBackgroundColor( color );
    }
    
    core::RenderContext* Graphics::CreateRenderSetting()
    {
        return framework->CreateRenderSetting();
    }
    
    core::TextureCube* Graphics::CreateTextureCube()
    {
        return framework->CreateTextureCube();
    }
    
    core::Texture2D* Graphics::CreateTexture2D()
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
    
    core::VAO* Graphics::CreateVAO()
    {
        return framework->CreateVAO();
    }
    core::VBO* Graphics::CreateVBO()
    {
        return framework->CreateVBO();
    }
    core::UBO* Graphics::CreateUBO()
    {
        return framework->CreateUBO();
    }
    core::IBO* Graphics::CreateIBO()
    {
        return framework->CreateIBO();
    }
    
    cg::uint gfx::Graphics::GetConstant(int target)
    {
        return framework->GetConstant( target );
    }

    void gfx::Graphics::CheckError(core::source src)
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

    gfx::Graphics::Graphics( core::GraphicsFramework* g )
    {
        if (g == nullptr)
        {
            framework = new core::GLGraphics();
        }
        else
        {
            framework = g;
        }
    }
}}
