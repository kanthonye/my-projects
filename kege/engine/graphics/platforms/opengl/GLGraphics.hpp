/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GLGraphics.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GLGraphics_hpp
#define GLGraphics_hpp
#include "../../../graphics/framework/GraphicsFramework.hpp"
namespace kege{namespace gfx{
    
    class GLGraphics : public GraphicsFramework
    {
    public:
        
        Window* CreateWindow(int width, int height, const char *title, bool fullscreen);
        
        UBO* CreateUBO(long size, const void* data, cg::uint usage, const ds::string& name);
        VBO* CreateVBO(long size, const void* data, cg::uint usage);
        IBO* CreateIBO(long size, const void* data, cg::uint usage);
        
        Shader* CreateShader(const ds::string& filename);
        Shader* CreateShader(SHDR& sources);
        Shader* CreateShader();
        
        Framebuffer* CreateFramebuffer();
        
        RenderSetting* CreateRenderSetting();
        TextureCube* CreateTextureCube();
        Texture2D* CreateTexture2D();
        
        void SetBackgroundColor(const cg::vec4& color)const;
        void EnablePointFrame()const;
        void EnableWireFrame()const;
        void EnableFillFrame()const;
        void DisableCulling()const;
        void EnableCullingCCW()const;
        void EnableCullingCW()const;
        void DisableDepthTest()const;
        void EnableDepthTest()const;
        void DisableBlending()const;
        void EnableBlending()const;
        void AlphaBlending()const;
        void ClearScreen()const;
        
        VAO* CreateVAO();
        VBO* CreateVBO();
        UBO* CreateUBO();
        IBO* CreateIBO();
        
        cg::uint GetConstant(int target);
        static cg::uint GLGetConstant(int target);
        static source EnumToString(int target);
        
        void CheckError(source msg);
        
        ~ GLGraphics();
        GLGraphics();
    };
}}
#endif /* GLGraphics_hpp */
