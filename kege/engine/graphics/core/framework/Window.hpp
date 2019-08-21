//
//  Window.hpp
//  KEGE_GUI
//
//  Created by Kenneth Esdaile on 3/8/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp
#define  GLFW_INCLUDE_GLCOREARB
#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>
#include "../../../ds/string.hpp"
#include "../../../graphics/core/cgmath/cgm.hpp"
namespace kege{namespace core{

    class Window
    {
    public:
        
        virtual void SetBackgroundColor(const cg::vec4& color) = 0;
        
        virtual void SetTitle(const ds::string& title) = 0;
        virtual const ds::string& GetTitle(void)const = 0;

        virtual int GetHeight(void) const = 0;
        virtual void SetHeight(int size) = 0;

        virtual int GetWidth(void)const = 0;
        virtual void SetWidth(int size) = 0;

        virtual void DisableFullScreenMode(void) = 0;
        virtual void EnableFullScreenMode(void) = 0;

        virtual void EnableVsync(void)const = 0;
        virtual void DisableVsync(void)const = 0;

        virtual void SwapBuffer(void)const = 0;
        virtual void PollEvents(void)const = 0;

        virtual void DisableCursor()const=0;
        virtual void EnableCursor()const=0;

        virtual void HideCursor()const = 0;
        virtual void ShowCursor()const = 0;
        
        virtual void MakeCurrent(void) = 0;
        
        virtual bool IsOpen(void)const = 0;
        virtual void ClearScreen() = 0;
        virtual void CloseWindow() = 0;
        
        virtual ~ Window(){}
    };
}}
namespace kege{namespace shared{
    typedef mem::shared< core::Window > Window;
}}
#endif /* Window_hpp */
