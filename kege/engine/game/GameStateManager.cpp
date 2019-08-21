/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/12/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GameStateManager.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "Singleton.hpp"
#include "GameEngine.hpp"
#include "CoreInputSystem.hpp"
#include "GameStateManager.hpp"
namespace kege{
    
    kege::GameState* GameStateManager::AddState(kege::GameState* state)
    {
        // check is scene is already in list. list must contain only unique elements
        ds::slist<kege::GameState*>::iterator s;
        for (s=_list.begin(); s!=nullptr; s++)
        {
            if (s.element() == state)
                return state;
        }
        _list.push_back( state );
        state->_manager = this;
        return state;
    }
    
    kege::GameState* GameStateManager::GetState()
    {
        if (_stack.empty()) return nullptr;
        return _stack.top();
    }
    
    void GameStateManager::MouseCursorEvent(const kege::Cursor& cursor)
    {
        if ( _stack.empty() ) return;
        _stack.top()->OnMouseCursorMove( cursor );
    }
    void GameStateManager::MouseWheelEvent(const kege::Cursor& cursor)
    {
        if ( _stack.empty() ) return;
        _stack.top()->OnScrollWheelMove( cursor );
    }
    void GameStateManager::MouseButtonEvent(const kege::Key& key)
    {
        if ( _stack.empty() ) return;
        _stack.top()->OnMouseButtonPress( key );
    }
    void GameStateManager::KeyboardEvent(const kege::Key& key)
    {
        if ( _stack.empty() ) return;
        _stack.top()->OnKeyboardPress( key );
    }
    
    
    void GameStateManager::SetFirstScene(const ds::string& value)
    {
        start_state = value;
    }
    
    bool GameStateManager::PushState(const ds::string& value)
    {
        ds::slist<kege::GameState*>::iterator state;
        for (state=_list.begin(); state!=nullptr; state++)
        {
            if (state->GetName() == value)
            {
                Push( state.element() );
                return true;
            }
        }
        return false;
    }
    
    void GameStateManager::Push(kege::GameState* state)
    {
        if (state == nullptr) return;
        if ( !_stack.empty() )
        {
            if (_stack.top() == state)
            {
                return;
            }
            _stack.top()->UnInit();
        }
        else
        {
            _stack.push( state );
        }
        
        if ( state->Init() == kege::SUCCESSFUL_INITIALIZATION )
        {
            _stack.push( state );
        };
    }
    
    void GameStateManager::UpdateState( kege::GameState* state )
    {
        state->Update( _engine->GetGameTickDelta() );
    }
    
    void GameStateManager::Update(double delta)
    {
        if ( _stack.empty() )
        {
            PushState(start_state);
            if (_stack.empty()) return;
        }
        
        kege::GameState* state = _stack.top();
        UpdateState( state );
    }
    
    void GameStateManager::Render()
    {
        if ( _stack.empty() )
        {
            PushState( start_state );
            if (_stack.empty()) return;
            _stack.top()->Init();
        }
        _stack.top()->Render();
    }
    
    void GameStateManager::UnInit()
    {
        if ( _init )
        {
            ds::slist<kege::GameState*>::iterator state;
            for (state=_list.begin(); state!=nullptr; state++)
            {
                state->UnInit();
            }
            _stack.clear();
            kege::System::UnInit();
        }
    }
    bool GameStateManager::Init()
    {
        //PushState( start_state );
//        if ( _stack.empty() )
//        {
//            return kege::FAILED_INITIALIZATION;
//        }
        _init = true;
        return _init;
    }
    
    void GameStateManager::Pop()
    {
        if (_stack.empty()) return;
        
        _stack.top()->UnInit();
        _stack.pop();
    }
    
    GameStateManager::~ GameStateManager()
    {
        ds::slist<kege::GameState*>::iterator state;
        for (state=_list.begin(); state!=nullptr; state++)
        {
            delete state.element();
        }
        _list.clear();
        _stack.clear();
        kege::Singleton::Free< GameStateManager >();
    }
    
    GameStateManager::GameStateManager( kege::GameEngine* engine )
    :   kege::CoreSystem( "GameStateManager", engine )
    {
        kege::Singleton::Set< GameStateManager >( this );
    }
}
