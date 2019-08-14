/*!
 *  @author     Kenneth Anthony Esdaile
 *  @date       created on 3/1/19
 *  @copyright  Copyright (c) 2014 kae. All rights reserved.
 *  @file       GameEngine.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GameEngine_hpp
#define GameEngine_hpp
#include <unordered_map>
#include "queue.hpp"
#include "Window.hpp"
#include "Message.hpp"
#include "CoreSystems.hpp"
#include "VFS.hpp"
#include "../../engine/game/CoreTaskManager.hpp"
#include "../../engine/game/CoreRenderer.hpp"
#include "../../engine/game/CoreInputSystem.hpp"
#include "../../engine/game/GameStateManager.hpp"
namespace kege{
    class SystemGraphics;
    
    /**
     The @b GameEngine is responsible for update specific sub-systems. The @b GameEngine
     only update systems that are labeled as @b ENGINE_UPDATE.
     */
    class GameEngine : public kege::System
    {
        typedef std::unordered_map<cg::ulong, kege::CoreSystems> CoreSystemsMap;
        static void WindowCloseCallback(bool value);
        
    public:
        
        
        inline GameStateManager& GetGameStateManager() {return _gamestate_manager;}
        inline CoreTaskManager& GetCoreTaskManager() {return _coretask_manager;}
        
        kege::CoreSystems* GetSystemGroup(const ds::string& group);
        kege::CoreSystem* RemSystem(const ds::string& stype);
        kege::CoreSystem* GetSystem(const ds::string& stype);
        
        void MouseCursorEvent(const kege::Cursor& cursor);
        void MouseWheelEvent(const kege::Cursor& cursor);
        void MouseButtonEvent(const kege::Key& key);
        void KeyboardEvent(const kege::Key& key);
        
        void HandleMessage( const kege::Message& message ) override;
        bool AddSystem(kege::CoreSystem* sys);
        
        void SetDesiredFPS(int fps);
        double GetGameTickDelta()const;
        double GetDesiredFPS()const;
        double GetCurrentTime()const;
        double GetTimeDeltaMS()const;
        double GetTimeSpand()const;
        void   Run();
        
        virtual ~ GameEngine();
        
    private:
        // make GameEngine un-assignable
        GameEngine& operator=(const GameEngine& other){ return *this; }
        
        void HandleMessage();
        void UpdateTimer();
        void MainLoop();
        void UnInit() override;
        bool Init() override;
        
    protected:
        
        GameEngine(const ds::string& filepath);
        
    protected:
        
        kege::CoreSystems _systems;
        kege::CoreSystems _empty;
        CoreSystemsMap _sysmap;
        
        CoreTaskManager _coretask_manager;
        GameStateManager _gamestate_manager;
        CoreRenderer _core_renderer;
        CoreInputSystem _core_input;
        kege::VFS vfs;
        
        ds::queue< kege::Message > messages;
        
        double _gametick_delta;
        double _desired_fps;
        double _frame_length;
        double _frame_time;
        double time_delta;
        double time_spand;
        double time_prev;
        bool   _running;
    };
    
    kege::GameEngine* CreateGameInstance(const char * gamepath);
}
#endif /* Game_hpp */
