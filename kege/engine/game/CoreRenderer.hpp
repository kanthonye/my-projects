/*!
 *  @author     Kenneth Anthony Esdaile
 *  @date       created on 4/23/19
 *  @copyright  Copyright (c) 2014 kae. All rights reserved.
 *  @file       SystemGraphics.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef SystemGraphics_hpp
#define SystemGraphics_hpp
#include "../game/System.hpp"
#include "../graphics/core/Graphics.hpp"
#include "Shader.hpp"
#include "CoreSystem.hpp"
namespace kege{
    
    /**
     The @b SystemGraphics is a @b SubSystem that is responsible for updating
     sub-systems within the @b GameEngine that are labeled as @b GRAPHICS_UPDATE.
     @b SystemGraphics is also responsible for initializing the graphics and
     creating the render window. @b SystemGraphics is of the group @b ENGINE_UPDATE,
     thus it is the @b GameEngine responsible to update it.
     */
    class CoreRenderer : public kege::CoreSystem
    {
    public:
        
        core::Window* CreateWindow();
        core::Window* GetWindow();
        
        void SetWindowTitle(const ds::string& val);
        void WindowBGColor(const cg::vec4& color);
        void SetFBOFlags(cg::uint flags);
        void SetFullscreen(bool val);
        void SetWindowHeight(int val);
        void SetWindowWidth(int val);
        
        void Update(double time_delta);
        void ClearBuffer();
        void SwapBuffer();
        void PollEvents();
        void UnInit();
        bool Init();
        
        CoreRenderer( kege::GameEngine* engine );
        ~ CoreRenderer();
        
    private:
        
        gfx::Graphics* _graphics;
        core::Window* _window;
        ds::string _title;
        cg::vec4 _color;
        cg::uint _fbo_flags;
        bool _fullscreen;
        int _height;
        int _width;
    };
}
#endif /* SystemGraphics_hpp */
