/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GraphicsFramework.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GraphicsFramework_hpp
#define GraphicsFramework_hpp
#include "../../graphics/framework/GFXEnum.hpp"
#include "../../graphics/framework/LoadSHDR.hpp"
#include "../../graphics/framework/UBO.hpp"
#include "../../graphics/framework/VBO.hpp"
#include "../../graphics/framework/IBO.hpp"
#include "../../graphics/framework/VAO.hpp"
#include "../../graphics/framework/Window.hpp"
#include "../../graphics/framework/Shader.hpp"
#include "../../graphics/framework/Texture2D.hpp"
#include "../../graphics/framework/TextureCube.hpp"
#include "../../graphics/framework/Framebuffer.hpp"
#include "../../graphics/framework/RenderSetting.hpp"
namespace kege{namespace gfx{
    typedef const char* source;
    
    class GraphicsFramework
    {
    protected:
        
        typedef void (*FuncPtrParamI4)(int, int, int, int);
        typedef void (*FuncPtrParamI3)(int, int, int);
        typedef void (*FuncPtrParamI2)(int, int);
        typedef void (*FuncPtrParamD2)(double, double);
        typedef void (*FuncPtrParamB1)(bool value);
        
    public:
        
        virtual Window* CreateWindow(int width, int height, const char *title, bool fullscreen) = 0;
        
        virtual UBO* CreateUBO(long size, const void* data, cg::uint usage, const ds::string& name) = 0;
        virtual VBO* CreateVBO(long size, const void* data, cg::uint usage) = 0;
        virtual IBO* CreateIBO(long size, const void* data, cg::uint usage) = 0;
        
        static  void OnKeyboardPress(int key, int scancode, int action, int mods);
        static  void OnMouseCursorMove(double xpos, double ypos);
        static  void OnScrollWheelMove(double xoffset, double yoffset);
        static  void OnMouseButtonPress(int button, int action, int mods);
        static  void OnFramebufferSize(int w, int h);
        static  void OnWindowSize(int w, int h);
        static  void OnWindowPosition(int x, int y);
        static  void OnWindowClose(bool value);
        
        void SetFramebufferSizeCallback( FuncPtrParamI2 funcptr );
        void SetWindowSizeCallback( FuncPtrParamI2 funcptr );
        void SetWindowPositionCallback( FuncPtrParamI2 funcptr );
        void SetMouseButtonCallback( FuncPtrParamI3 funcptr );
        void SetKeyboardCallback( FuncPtrParamI4 funcptr );
        void SetMouseCursorCallback( FuncPtrParamD2 funcptr );
        void SetScrollWheelCallback( FuncPtrParamD2 funcptr );
        void SetWindowCloseCallback( FuncPtrParamB1 funcptr );
        
        virtual Shader* CreateShader(const ds::string& filename) = 0;
        virtual Shader* CreateShader(SHDR& sources) = 0;
        virtual Shader* CreateShader() = 0;
        
        virtual Framebuffer* CreateFramebuffer() = 0;
        
        virtual TextureCube* CreateTextureCube() = 0;
        virtual Texture2D* CreateTexture2D() = 0;
        
        virtual void SetBackgroundColor(const cg::vec4& color)const = 0;
        virtual void EnablePointFrame()const = 0;
        virtual void EnableWireFrame()const = 0;
        virtual void EnableFillFrame()const = 0;
        virtual void DisableCulling()const = 0;
        virtual void EnableCullingCCW()const = 0;
        virtual void EnableCullingCW()const = 0;
        virtual void DisableDepthTest()const = 0;
        virtual void EnableDepthTest()const = 0;
        virtual void DisableBlending()const = 0;
        virtual void EnableBlending()const = 0;
        virtual void AlphaBlending()const = 0;
        virtual void ClearScreen()const = 0;
        
        virtual VAO* CreateVAO() = 0;
        virtual VBO* CreateVBO() = 0;
        virtual UBO* CreateUBO() = 0;
        virtual IBO* CreateIBO() = 0;
        
        virtual RenderSetting* CreateRenderSetting() = 0;
        virtual cg::uint GetConstant(int target) = 0;
        
        virtual void CheckError(source msg) = 0;
        
        virtual ~ GraphicsFramework(){}
        
    protected:
        
        static FuncPtrParamI2 callback_framebuffer_size;
        static FuncPtrParamI2 callback_window_position;
        static FuncPtrParamB1 callback_window_close;
        static FuncPtrParamI2 callback_window_size;
        static FuncPtrParamI4 callback_keyboard;
        static FuncPtrParamI3 callback_buttom;
        static FuncPtrParamD2 callback_cursor;
        static FuncPtrParamD2 callback_wheel;
        
    };
    
    struct ShaderVar
    {
        ds::string name;
        int location;
        int index;
    };
}}
#endif /* GraphicsFramework_hpp */
