/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GLWindow.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GLWindow_hpp
#define GLWindow_hpp
#include "glfw3.h"
#include "../../framework/Window.hpp"
namespace kege{namespace gfx{
    class GLGraphics;
    
    class GLWindow : public gfx::Window
    {
    public:
        
        void SetBackgroundColor(const cg::vec4& color);
        
        void SetTitle(const ds::string& title);
        const ds::string& GetTitle(void)const;
        
        void DisableFullScreenMode(void);
        void EnableFullScreenMode(void);
        
        void EnableVsync(void)const;
        void DisableVsync(void)const;
        
        void SwapBuffer(void)const;
        void PollEvents(void)const;
        
        void DisableCursor()const;
        void EnableCursor()const;
        
        void HideCursor()const;
        void ShowCursor()const;
        
        int GetHeight(void) const;
        void SetHeight(int size);
        
        int GetWidth(void)const;
        void SetWidth(int size);
        
        void MakeCurrent(void);
        
        bool IsOpen(void)const;
        void ClearScreen();
        void CloseWindow();
        
        GLWindow(int width, int height, const char *title, bool fullscreen);
        ~ GLWindow();
        GLWindow();
        
    private:
        
        friend GLGraphics;
        GLFWwindow * win;
        ds::string title;
        cg::uint height;
        cg::uint width;
        int fbh;
        int fbw;
        bool close;
    };
}}
#endif /* GLWindow_hpp */
