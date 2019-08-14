//
//  Graphics.hpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 5/24/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef Graphics_hpp
#define Graphics_hpp
#include "../../graphics/framework/GraphicsFramework.hpp"
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
      
        static gfx::GraphicsFramework* Framework();
        
        static Window* CreateWindow(int width, int height, const char *title, bool fullscreen);
        
        static UBO* CreateUBO(long size, const void* data, cg::uint usage, const ds::string& name);
        static VBO* CreateVBO(long size, const void* data, cg::uint usage);
        static IBO* CreateIBO(long size, const void* data, cg::uint usage);
        
        static void SetFramebufferSizeCallback( FuncPtrParamI2 funcptr );
        static void SetWindowSizeCallback( FuncPtrParamI2 funcptr );
        static void SetWindowPositionCallback( FuncPtrParamI2 funcptr );
        static void SetMouseButtonCallback( FuncPtrParamI3 funcptr );
        static void SetMouseCursorCallback( FuncPtrParamD2 funcptr );
        static void SetScrollWheelCallback( FuncPtrParamD2 funcptr );
        static void SetWindowCloseCallback( FuncPtrParamB1 funcptr );
        static void SetKeyboardCallback( FuncPtrParamI4 funcptr );
        
        static Shader* CreateShader(const ds::string& filename);
        static Shader* CreateShader(SHDR& sources);
        static Shader* CreateShader();
        
        static Framebuffer* CreateFramebuffer();
        
        static TextureCube* CreateTextureCube();
        static Texture2D* CreateTexture2D();
        
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
        
        static VAO* CreateVAO();
        static VBO* CreateVBO();
        static UBO* CreateUBO();
        static IBO* CreateIBO();

        static RenderSetting* CreateRenderSetting();
        static cg::uint GetConstant(int target);

        static void CheckError(source src);

        Graphics(GraphicsFramework* g);
        virtual ~ Graphics();
        
    protected:
        
        void operator =(const Graphics& other);
        const Graphics& operator &();
        
        static gfx::GraphicsFramework* framework;
    };
}}
#endif /* Graphics_hpp */
