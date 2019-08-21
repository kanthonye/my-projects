/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/10/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIModButton.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIModButton_hpp
#define GUIModButton_hpp
#include "KeyCode.hpp"
#include "../../gui/modules/GUIModule.hpp"
namespace kege{namespace cg{
    
    class GUIModButton : public cg::GUIModule
    {
    public:
        
        virtual int onButtonRelease( const cg::GUIEventButton& event ) = 0;
        virtual int onButtonPressed( const cg::GUIEventButton& event ) = 0;
        int onEvent( const cg::GUIEvent& event );
        void PressingGUI( GUIWidget* gui );
        void ReleaseGUI( GUIWidget* gui );
        void SelectGUI( GUIWidget* gui );
        
        virtual ~ GUIModButton(){}
        
        GUIModButton()
        :   GUIModule( GUIEvent::MOUSE_BUTTON )
        ,   _pressing( false )
        ,   _selection( false )
        {}
        
    protected:
        
        cg::ushort _pressing;
        bool _selection;
    };
}}


namespace kege{namespace cg{
    
    class GUIModButPress : public cg::GUIModButton
    {
    public:
        int onButtonRelease(const cg::GUIEventButton& event) override;
        int onButtonPressed(const cg::GUIEventButton& event) override;
    };
}}


namespace kege{namespace cg{
    
    class GUIModButClick : public cg::GUIModButton
    {
    public:
        int onButtonRelease(const cg::GUIEventButton& event) override;
        int onButtonPressed(const cg::GUIEventButton& event) override;
    };
}}


namespace kege{namespace cg{
    
    class GUIModButToggle : public cg::GUIModButton
    {
    public:
        int onButtonRelease(const cg::GUIEventButton& event) override;
        int onButtonPressed(const cg::GUIEventButton& event) override;
        
    private:
        bool toggle;
    };
}}


namespace kege{namespace cg{
    
    class GUIModButFocus : public cg::GUIModButton
    {
    public:
        int onButtonRelease(const cg::GUIEventButton& event) override;
        int onButtonPressed(const cg::GUIEventButton& event) override;
    };
}}
namespace kege{namespace cg{
    
    class GUIModDispatcher : public cg::GUIModule
    {
    public:
        int onEvent(const cg::GUIEvent& event);
        GUIModDispatcher( GUIEvent::Type type )
        :   GUIModule( type )
        {}
    };
}}
#endif /* GUIModButtom_hpp */
