/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/25/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Scene.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../scene/core/Scene.hpp"
namespace kege{
    
    void Scene::OnMouseCursorMove( const kege::Cursor& cursor )
    {
        if ( _gui != nullptr )
        {
            _gui->OnMouseCursorMove( cursor );
        }
        if ( !_guiHasControl )
        {
            _interface.OnMouseCursor( cursor );
        }
    }
    void Scene::OnScrollWheelMove( const kege::Cursor& cursor )
    {
        if ( _gui != nullptr )
        {
            _gui->OnScrollWheelMove( cursor );
        }
    }
    void Scene::OnMouseButtonPress( const kege::Key& key )
    {
        if ( _gui != nullptr )
        {
            bool v = _gui->OnMouseButtonPress( key );
            if ( v )
            {
                //printf("_guiHasControl %i\n", v);
                _guiHasControl = true;
            }
        }
        if (key.action == 0)
        {
            _guiHasControl = false;
        }
        if ( !_guiHasControl )
        {
            _interface.OnKey( key );
        }
    }
    void Scene::OnKeyboardPress( const kege::Key& key )
    {
        if ( _gui != nullptr )
        {
            _gui->OnKeyboardPress( key );
        }
        if ( !_guiHasControl )
        {
            _interface.OnKey( key );
        }
    }
    
    void Scene::RemvMsgHandler( cg::uint msgtyp, kege::Object* object )
    {
        _interface.RemvMsgHandler( msgtyp, object );
    }
    
    void Scene::AddMsgHandler(cg::uint msgtyp, kege::Object* object)
    {
        _interface.AddMsgHandler( msgtyp, object );
    }
    
    void Scene::HandleMessage( const kege::Message& message )
    {
        _interface.HandleMessage( message );
    }
    
    kege::SubSystem* Scene::RemSystem( const ds::string& stype )
    {
        return _systems.RemSystem( stype );
    }
    
    kege::SubSystem* Scene::GetSystem( const ds::string& stype )
    {
        return _systems.GetSystem( stype );
    }
    
    bool Scene::AddSystem( kege::SubSystem* sys )
    {
        short status = _systems.AddSystem( sys );
        if (status == kege::SUCCESSFUL_INITIALIZATION)
        {
            sys->_scene = this;
        }
        return status;
    }
    
    kege::Interface& Scene::GetInterface()
    {
        return _interface;
    }
    
    void Scene::Update( double delta )
    {
        _systems.Update( delta );
        _rootnode.Update( delta );
    }
    
    void Scene::Render()
    {
        kege::SubSystem* system = GetSystem( "RenderingSystem" );
        if (system != nullptr)
        {
            system->Render();
        }
    }
    
    gfx::Gameobject* Scene::Add( gfx::Gameobject* object )
    {
        _rootnode.AddChild( object );
        return object;
    }
    
    void Scene::Add( gfx::Gameobjects& objects )
    {
        _rootnode.AddChildren( objects );
    }
    
    const gfx::NodeEntity* Scene::GetPlayer()const
    {
        return _player;
    }
    gfx::NodeEntity* Scene::GetPlayer()
    {
        return _player;
    }
    void Scene::SetCamera( gfx::Camera* camera )
    {
        _camera = camera;
    }
    const gfx::Camera* Scene::GetCamera()const
    {
        return _camera;
    }
    gfx::Camera* Scene::GetCamera()
    {
        return _camera;
    }
    
    const gfx::Rootnode& Scene::GetRootNode()const
    {
        return _rootnode;
    }
    gfx::Rootnode& Scene::GetRootNode()
    {
        return _rootnode;
    }
    void Scene::UnInit()
    {
        _rootnode.UnInit();
        _systems.UnInit();
    }
    
    short Scene::Init()
    {
        if (_systems.Init() == kege::SUCCESSFUL_INITIALIZATION)
        {
            _gui = (cg::GUI*) GetSystem("GUI");
            _rootnode.Init( this );
            return kege::SUCCESSFUL_INITIALIZATION;
        }
        return kege::FAILED_INITIALIZATION;
    }
    
    Scene:: ~ Scene()
    {
        _systems.UnInit();
        _systems.Clear();
    }
    Scene::Scene( const ds::string& name )
    :   kege::GameState( name )
    ,   _game_state( nullptr )
    ,   _camera( nullptr )
    ,   _player( nullptr )
    ,   _gui(nullptr)
    ,   _guiHasControl( false )
    {
        _camera = new gfx::Camera("main-camera", 1024.0 / 512.0, 45.0, 0.1, 4000);
        Add( _camera );
        
//        _player = new gfx::NodeEntity( "player" );
//        Add( _player );
    }
}
