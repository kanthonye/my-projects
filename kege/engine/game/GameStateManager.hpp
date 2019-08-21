/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/12/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GameStateManager.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GameStateManager_hpp
#define GameStateManager_hpp
#include "slist.hpp"
#include "stack.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"
#include "../../engine/game/CoreSystem.hpp"
#include "../../engine/game/GameState.hpp"
namespace kege{
    
    class GameStateManager : public kege::CoreSystem
    {
    public:
        
        kege::GameState* AddState(kege::GameState* state);
        kege::GameState* GetState();
        
        void MouseCursorEvent(const kege::Cursor& cursor);
        void MouseWheelEvent(const kege::Cursor& cursor);
        void MouseButtonEvent(const kege::Key& key);
        void KeyboardEvent(const kege::Key& key);
        
        void SetFirstScene(const ds::string& value);
        bool PushState(const ds::string& value);
        void Push(kege::GameState* scene);
        
        void Update(double gamespeed) override;
        void Render();
        void UnInit() override;
        bool Init() override;
        void Pop();
        
        GameStateManager( kege::GameEngine* engine );
        ~ GameStateManager();
        
    private:
        
        void UpdateState( kege::GameState* state );
        
    private:
        
        ds::stack< kege::GameState* > _stack;
        ds::slist< kege::GameState* > _list;
        ds::string start_state;
        
        kege::MousePointer pointer;
        kege::MouseWheel wheel;
        kege::Mousekeys button;
        kege::Keyboard keyboard;
    };
}
#endif /* GameStateManager_hpp */
