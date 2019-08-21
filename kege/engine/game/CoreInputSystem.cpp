/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/12/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       CoreInputSystem.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../engine/graphics/core/Graphics.hpp"
#include "../../engine/game/CoreInputSystem.hpp"
#include "../../engine/game/GameEngine.hpp"
namespace kege{
    
    class InputCallback
    {
    private:
        
        static void OnKeyboardPress(int key, int scancode, int action, int mods)
        {
            if (callback != nullptr) callback->OnKeyboardPress(key, scancode, action, mods);
        }
        static void OnMouseCursorMove(double xpos, double ypos)
        {
            if (callback != nullptr) callback->OnMouseCursorMove(xpos, ypos);
        }
        static void OnScrollWheelMove(double xoffset, double yoffset)
        {
            if (callback != nullptr) callback->OnScrollWheelMove(xoffset, yoffset);
        }
        static void OnMouseButtonPress(int button, int action, int mods)
        {
            if (callback != nullptr) callback->OnMouseButtonPress(button, action, mods);
        }
        
    public:
        
        InputCallback(kege::CoreInputSystem* cb)
        {
            callback = cb;
            if (callback != nullptr)
            {
                gfx::Graphics::SetMouseButtonCallback( OnMouseButtonPress );
                gfx::Graphics::SetMouseCursorCallback( OnMouseCursorMove );
                gfx::Graphics::SetScrollWheelCallback( OnScrollWheelMove );
                gfx::Graphics::SetKeyboardCallback( OnKeyboardPress );
            }
        }
        
    private:
        
        static kege::CoreInputSystem* callback;
    };
    kege::CoreInputSystem* InputCallback::callback = nullptr;
    
    
    
    
    void CoreInputSystem::OnKeyboardPress(int key, int scancode, int action, int mods)
    {
        keyboard.SetKey(key, scancode, action, mods);
    }
    
    void CoreInputSystem::OnMouseButtonPress(int key, int action, int mods)
    {
        button.SetKey(key, 0, action, mods);
    }
    
    void CoreInputSystem::OnScrollWheelMove(double x, double y)
    {
        wheel.SetPosition(x, y);
    }
    
    void CoreInputSystem::OnMouseCursorMove(double x, double y)
    {
        pointer.SetPosition(x, y);
    }
    
    void CoreInputSystem::SetCoreInput(kege::CoreInput* coreinput)
    {
        _coreinput = coreinput;
    }
    
    kege::CoreInput* CoreInputSystem::GetCoreInput()
    {
        return _coreinput;
    }
    
    void CoreInputSystem::Update(double time_delta)
    {
        if (_engine != nullptr)
        {
            keyboard.UpdateInputContext( _engine );
            button.UpdateInputContext( _engine );
            pointer.UpdateInputContext( _engine );
            wheel.UpdateInputContext( _engine );
        }
    }
    
    void CoreInputSystem::UnInit()
    {
        if (callback != nullptr)
        {
            delete callback;
            callback = nullptr;
        }
        _init = false;
    }
    
    bool CoreInputSystem::Init()
    {
        if ( !_init )
        {
            callback = new InputCallback( this );
            _init = true;
        }
        return _init;
    }
    
    CoreInputSystem::~ CoreInputSystem()
    {
        UnInit();
    }
    
    CoreInputSystem::CoreInputSystem( kege::GameEngine* engine )
    :   kege::CoreSystem( "CoreInputSystem", engine )
    ,   _coreinput(nullptr)
    ,   callback(nullptr)
    {}
}


