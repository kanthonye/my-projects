//
//  Graphics.hpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 5/24/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef Graphics_hpp
#define Graphics_hpp
#include "../../resource/VFS.hpp"
#include "../../graphics/core/cgmath/cgm.hpp"
#include "../../graphics/core/mesh/Mesh.hpp"
#include "../../graphics/core/light/Light.hpp"
#include "../../graphics/core/mesh/GenMesh.hpp"
#include "../../graphics/core/mesh/Material.hpp"
#include "../../graphics/core/mesh/Geometry.hpp"
#include "../../graphics/core/mesh/ADSEffect.hpp"
#include "../../graphics/core/framework/GFXEnum.hpp"
#include "../../graphics/core/framework/GraphicsFramework.hpp"
namespace kege{namespace gfx{

    class Graphics
    {
    protected:
        
        typedef void (*FuncPtrParamI4)(int, int, int, int);
        typedef void (*FuncPtrParamI3)(int, int, int);
        typedef void (*FuncPtrParamI2)(int, int);
        typedef void (*FuncPtrParamD2)(double, double);
        typedef void (*FuncPtrParamB1)(bool value);
        
    public:
      
        static core::Window* CreateWindow(int width, int height, const char *title, bool fullscreen);
        
        static core::UBO* CreateUBO(long size, const void* data, cg::uint usage, const ds::string& name);
        static core::VBO* CreateVBO(long size, const void* data, cg::uint usage);
        static core::IBO* CreateIBO(long size, const void* data, cg::uint usage);
        
        static core::VAO* CreateVAO( core::VertexBuffer* vb, core::IndexBuffer* ib );
        
        static core::GraphicsFramework* Framework();
        
        static void SetFramebufferSizeCallback( FuncPtrParamI2 funcptr );
        static void SetWindowSizeCallback( FuncPtrParamI2 funcptr );
        static void SetWindowPositionCallback( FuncPtrParamI2 funcptr );
        static void SetMouseButtonCallback( FuncPtrParamI3 funcptr );
        static void SetMouseCursorCallback( FuncPtrParamD2 funcptr );
        static void SetScrollWheelCallback( FuncPtrParamD2 funcptr );
        static void SetWindowCloseCallback( FuncPtrParamB1 funcptr );
        static void SetKeyboardCallback( FuncPtrParamI4 funcptr );
        
        static core::Shader* CreateShader(const ds::string& filename);
        static core::Shader* CreateShader(core::SHDR& sources);
        static core::Shader* CreateShader();
        
        static core::Framebuffer* CreateFramebuffer();
        static core::TextureCube* CreateTextureCube();
        static core::Texture2D* CreateTexture2D();
        
        
        
        static void SetBackgroundColor(const cg::vec4& color);
        
        static void EnablePointFrame();
        static void EnableWireFrame();
        static void EnableFillFrame();
        static void DisableCulling();
        static void EnableCullingCCW();
        static void EnableCullingCW();
        static void DisableDepthTest();
        static void EnableDepthTest();
        static void DisableBlending();
        static void EnableBlending();
        static void AlphaBlending();
        static void ClearScreen();
        
        static core::VAO* CreateVAO();
        static core::VBO* CreateVBO();
        static core::UBO* CreateUBO();
        static core::IBO* CreateIBO();

        static core::RenderContext* CreateRenderSetting();
        static cg::uint GetConstant(int target);

        static void CheckError( core::source src);

        Graphics( core::GraphicsFramework* g );
        virtual ~ Graphics();
        
    protected:
        
        void operator =(const Graphics& other);
        const Graphics& operator &();
        
        static core::GraphicsFramework* framework;
    };
}}
#endif /* Graphics_hpp */
