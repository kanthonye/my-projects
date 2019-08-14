/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/12/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GameState.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GameState_hpp
#define GameState_hpp
#include "../../engine/game/CoreInput.hpp"
#include "../../engine/game/InputDispatcher.hpp"
namespace kege{
    class GameStateManager;
    
    class GameState : public kege::CoreInput
    {
    public:
        
        inline GameStateManager* GetGameStateManager() {return _manager;}
        inline void GetName(const ds::string& value) {_name = value;}
        inline const ds::string& GetName() const {return _name;}
        
        virtual void OnMouseCursorMove(const kege::Cursor& cursor) = 0;
        virtual void OnScrollWheelMove(const kege::Cursor& cursor) = 0;
        virtual void OnMouseButtonPress(const kege::Key& key) = 0;
        virtual void OnKeyboardPress(const kege::Key& key) = 0;
        
        virtual void Update(double time) = 0;
        virtual void Render() = 0;
        virtual void UnInit() = 0;
        virtual short Init() = 0;
        
        GameState(const ds::string& name)
        :   _manager(nullptr)
        ,   _name(name)
        ,   _init( false )
        {}
        
        virtual ~ GameState() {}
        
    protected:
        
        friend GameStateManager;
        GameStateManager* _manager;
        ds::string _name;
        bool _init;
    };
}
#endif /* GameState_hpp */
