/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/25/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Scene.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef CoreScene_hpp
#define CoreScene_hpp
#include <map>
#include "dlist.hpp"
#include "GUI.hpp"
#include "Camera.hpp"
#include "SubSystems.hpp"
#include "Interface.hpp"
#include "../../game/CoreInput.hpp"
#include "../../game/GameState.hpp"
#include "../../game/GameState.hpp"
#include "../../scene/core/Rootnode.hpp"
#include "../../scene/core/SceneFrame.hpp"
namespace kege{
    
    class Scene : public kege::GameState
    {
    public:
        
        virtual void OnMouseCursorMove(const kege::Cursor& cursor);
        virtual void OnScrollWheelMove(const kege::Cursor& cursor);
        virtual void OnMouseButtonPress(const kege::Key& key);
        virtual void OnKeyboardPress(const kege::Key& key);
        
        void RemvMsgHandler(cg::uint msgtyp, kege::Object* object);
        void AddMsgHandler(cg::uint msgtyp, kege::Object* object);
        void HandleMessage(const kege::Message& message);
        
        kege::SubSystem* RemSystem(const ds::string& stype);
        kege::SubSystem* GetSystem(const ds::string& stype);
        bool AddSystem(kege::SubSystem* sys);
        
        
        kege::Interface& GetInterface();
        
        /*
         get and set the name of this scene
         */
        inline void SetName(const ds::string& val) {_name = val;}
        inline const ds::string& GetName() const {return _name;}
        
        
        gfx::Gameobject* Add(gfx::Gameobject* object);
        void Add(gfx::Gameobjects& object);
        
        /**
         get root node
         */
        const gfx::Rootnode& GetRootNode()const;
        gfx::Rootnode& GetRootNode();
        
        /**
         get Player
         */
        virtual const gfx::NodeEntity* GetPlayer()const;
        virtual gfx::NodeEntity* GetPlayer();
        
        /**
         set Camera for this scene
         */
        virtual void SetCamera(gfx::Camera* camera);
        virtual const gfx::Camera* GetCamera()const;
        virtual gfx::Camera* GetCamera();
        
        /*
         update this scene
         */
        virtual void Update(double delta_ms);
        
        /*
         update this scene
         */
        virtual void Render();
        
        /*
         uninitialize this scene
         */
        virtual void UnInit();
        
        /*
         initialize this scene
         */
        virtual short Init();
        
        
        cg::GUI* GetGUI() {return _gui;}
        
        Scene(const ds::string& name);
        virtual ~ Scene();
        
    protected:
        
        std::map<long, ds::dlist<kege::Object*>> _message_handlers;
        short keybinds[ 512 ];
        
        kege::Interface _interface;
        kege::SubSystems _systems;
        gfx::Rootnode _rootnode;
        
        kege::GameState* _game_state;
        gfx::NodeEntity* _player;
        gfx::Camera* _camera;
        cg::GUI* _gui;
        
        bool _guiHasControl;
    };
}
#endif /* CoreScene_hpp */
