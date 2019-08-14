/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/12/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       CoreInputSystem.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef CoreInputSystem_hpp
#define CoreInputSystem_hpp
#include <mutex>
#include <unordered_map>
#include "stack.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"
#include "../../engine/game/CoreInput.hpp"
#include "../../engine/game/CoreSystem.hpp"
namespace kege{
    class InputCallback;
    
    class CoreInputSystem : public kege::CoreSystem
    {
    public:
        
        void OnKeyboardPress(int key, int scancode, int action, int mods);
        void OnMouseButtonPress(int button, int action, int mods);
        void OnScrollWheelMove(double xoffset, double yoffset);
        void OnMouseCursorMove(double xpos, double ypos);
        //void OnKeyCharCode(int ascii);
        
        void SetCoreInput(kege::CoreInput* coreinput);
        kege::CoreInput* GetCoreInput();
        
        void Update(double time_delta);
        void UnInit();
        bool Init();
        
        ~ CoreInputSystem();
        CoreInputSystem( kege::GameEngine* engine );
        
    private:
        
        kege::InputCallback* callback;
        kege::CoreInput* _coreinput;
        
        kege::MousePointer pointer;
        kege::MouseWheel wheel;
        kege::Keyboard keyboard;
        kege::Mousekeys button;
    };
}
#endif /* CoreInputSystem_hpp */
