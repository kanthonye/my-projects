/*!
 *  @author     Kenneth Anthony Esdaile
 *  @date       created on 3/1/19
 *  @copyright  Copyright (c) 2014 kae. All rights reserved.
 *  @file       GameEngine.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#include "VFS.hpp"
#include "Singleton.hpp"
#include "../../engine/game/CoreTaskManager.hpp"
#include "../../engine/game/SystemVirtFile.hpp"
#include "../../engine/game/GameEngine.hpp"
namespace kege{
    
    void GameEngine::WindowCloseCallback(bool value)
    {
        Singleton::Get< kege::GameEngine >()->HandleMessage( WindowClosed() );
    }
    
    kege::CoreSystems* GameEngine::GetSystemGroup(const ds::string& group)
    {
        CoreSystemsMap::iterator m = _sysmap.find( group.hash() );
        if (m == _sysmap.end())
        {
            return &_empty;
        }
        return &m->second;
    }
    
    kege::CoreSystem* GameEngine::RemSystem(const ds::string& systyp)
    {
        return _systems.RemSystem(systyp);
    }
    
    kege::CoreSystem* GameEngine::GetSystem(const ds::string& systyp)
    {
        return _systems.GetSystem(systyp);
    }
    
    void GameEngine::HandleMessage( const kege::Message& message )
    {
        messages.push( message );
    }
    
    bool GameEngine::AddSystem(kege::CoreSystem* sys)
    {
        if (sys != nullptr)
        {
            _sysmap[ sys->_group.hash() ].AddSystem( sys );
            _systems.AddSystem( sys );
            sys->_engine = this;
            return true;
        }
        return false;
    }
    
    void GameEngine::HandleMessage()
    {
        while ( !messages.empty() )
        {
            kege::Message msg = messages.top();
            messages.pop();
            
            if ( msg.GetType() == kege::MSG::WINDOW_CLOSED || msg.GetType() == kege::MSG::TERMINATE )
            {
                _running = false;
            }
        }
    }
    
    void GameEngine::MouseCursorEvent(const kege::Cursor& cursor)
    {
        _gamestate_manager.MouseCursorEvent( cursor );
    }
    void GameEngine::MouseWheelEvent(const kege::Cursor& cursor)
    {
        _gamestate_manager.MouseWheelEvent( cursor );
    }
    void GameEngine::MouseButtonEvent(const kege::Key& key)
    {
        _gamestate_manager.MouseButtonEvent( key );
    }
    void GameEngine::KeyboardEvent(const kege::Key& key)
    {
        _gamestate_manager.KeyboardEvent( key );
    }

    void GameEngine::UpdateTimer()
    {
        double current = GetCurrentTime();
        if (time_prev == 0.0) time_prev = current;
        time_delta   = current - time_prev;
        time_prev    = current;
        
        _frame_time += time_delta * 0.001f;
        _frame_time  = cg::min(_frame_length*5, _frame_time);
    }
    
    void GameEngine::MainLoop()
    {
        if ( !_init ) return;
        
        time_prev = GetCurrentTime();
        bool update_graphics = false;
        while ( _running )
        {
            UpdateTimer();
            if ( messages.empty() )
            {
                while(_frame_time >= _frame_length)
                {
                    _core_input.Update( time_delta );
                    _gamestate_manager.Update( time_delta );
                    _frame_time -= _frame_length;
                    update_graphics = true;
                }
                
                if (update_graphics)
                {
                    _core_renderer.ClearBuffer();
                    _gamestate_manager.Render();
                    _core_renderer.SwapBuffer();
                }
                _core_renderer.PollEvents();
            }
            else
            {
                HandleMessage();
            }
        }
    }

    void GameEngine::UnInit()
    {
        _coretask_manager.UnInit();
        _gamestate_manager.UnInit();
        _core_input.UnInit();
        _core_renderer.UnInit();
        
        if ( _init )
        {
            _systems.UnInit();
            _sysmap.clear();
            kege::System::UnInit();
        }
    }
    
    bool GameEngine::Init()
    {
        if ( !vfs.GetInstance().Load("/Users/kanthonye/Projects/KEGE/dev-kege/dev-kege/kege/assets/virdir/virdir.xml") )
        {
            KEGE_ERROR("unable to locate VFS directory.");
            return false;
        }
        
        if ( !_init )
        {
            _core_renderer.Init();
            _core_input.Init();
            _coretask_manager.Init();
            _gamestate_manager.Init();
            _running = true;
            _init = true;
        }
        return _init;
    }
    
    double GameEngine::GetGameTickDelta()const
    {
        return _gametick_delta;
    }
    
    double GameEngine::GetDesiredFPS()const
    {
        return _desired_fps;
    }
    
    void GameEngine::SetDesiredFPS(int fps)
    {
        _desired_fps = cg::max(1, fps);
        _frame_length = 1.0f / _desired_fps;
    }
    
    double GameEngine::GetCurrentTime()const
    {
        return std::chrono::duration_cast< std::chrono::milliseconds >
        ( std::chrono::system_clock::now().time_since_epoch() ).count();
    }
    
    double GameEngine::GetTimeDeltaMS()const
    {
        return time_delta;
    }
    
    double GameEngine::GetTimeSpand()const
    {
        return time_spand;
    }
    
    void  GameEngine::Run()
    {
        Init();
        MainLoop();
        UnInit();
    }
    
    GameEngine:: ~ GameEngine()
    {
        _systems.Destroy();
        Singleton::Free<kege::GameEngine>();
    }
    
    GameEngine::GameEngine(const ds::string& virfile)
    :   kege::System("GameEngine")
    ,   _coretask_manager( this )
    ,   _gamestate_manager( this )
    ,   _core_renderer( this )
    ,   _core_input( this )
    ,   _gametick_delta( 0.25 )
    ,   _desired_fps(60)
    ,   _frame_length(1)
    ,   _frame_time(0.0)
    ,   time_delta(0.0)
    ,   time_prev(0.0)
    ,   _running(false)
    {
        gfx::Graphics::SetWindowCloseCallback( kege::GameEngine::WindowCloseCallback );
        Singleton::Set<kege::GameEngine>( this );
        SetDesiredFPS(60);
        
//        AddSystem(new kege::CoreTaskManager);
//        AddSystem(new kege::SystemVirtFile);
//        AddSystem(new kege::CoreRenderer);
//        AddSystem(new kege::CoreInputSystem);
//        AddSystem(new kege::GameStateManager);
    }
}


