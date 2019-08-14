/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/10/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIEvent.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIEvent_hpp
#define GUIEvent_hpp
#include "cgm.hpp"
#include "Message.hpp"
namespace kege{namespace cg{
    class GUIWidget;
    
    
    
//    enum GUIState
//    {
//        NOTHING,
//        RELEASE,
//        PRESSED,
//        PRESSING,
//        GRABBING,
//        SCROLLING,
//    };
    
    class GUIEvent
    {
    public:
        
        enum Type
        {
            NOTHING = -1,
            RELEASE,
            PRESSED,
            PRESSING,
            GRABBING,
            SCROLLING,
            MOUSE_OVER,
            
            MOUSE_BUTTON,
            MOUSE_MOVE,
            MOUSE_GRAB,
            MOUSE_SCROLL,
            MOUSE_RELEASE,
            MOUSE_PRESSED,
            
            KEYBOARD_KEY,
            
            GUI_SELECTED,
            GUI_PRESSING,
            GUI_RELEASE,
            GUI_CHILD,
            GUI_ADD,
            GUI_REM,
            
            VALUE_CHANGE,
            DISABLE,
            ENABLE,
            HIDE,
            SHOW,
            
            ACTION_GUI_SELECTED,
            ACTION_GUI_RELEASE,
            ACTION_VALUE_CHANGE,
            ACTION_SIZE_CHANGE,
            ACTION_PRESSING,
            ACTION_GRABBING,
            ACTION_RELEASE,
            ACTION_MOUSEOVER,
            ACTION_DISABLE,
            ACTION_ENABLE,
            ACTION_SHOW,
            ACTION_HIDE,
        };
        
        inline GUIEvent::Type GetType() const {return _type;}
        virtual ~ GUIEvent(){}
        
        GUIEvent(GUIEvent::Type type) : _type(type) {}
        GUIEvent::Type _type;
    };
    
    typedef kege::shared< GUIEvent > GUISharedEvent;
    
    class GUIEventMouseMove : public GUIEvent
    {
    public:
        
        GUIEventMouseMove(): GUIEvent(MOUSE_MOVE) {}
        double x,y;
    };
    
    class GUIEventGrab : public GUIEvent
    {
    public:
        
        GUIEventGrab(): GUIEvent(MOUSE_GRAB) {}
        double x,y;
    };
    
    class GUIEventScroll : public GUIEvent
    {
    public:
        
        GUIEventScroll(): GUIEvent(MOUSE_SCROLL) {}
        double x,y;
    };
    
    
    class GUIEventButton : public GUIEvent
    {
    public:
        
        GUIEventButton(): GUIEvent(MOUSE_BUTTON) {}
        double x,y;
        cg::ushort key;
        cg::ushort state;
    };
    
    
    class GUIEventKey : public GUIEvent
    {
    public:
        
        GUIEventKey(): GUIEvent(KEYBOARD_KEY) {}
        double x,y;
        cg::ushort key;
        cg::ushort state;
    };
    
    
    class GUIMsgSelection : public cg::GUIEvent
    {
    public:
        GUIMsgSelection( GUIWidget* obj ) : GUIEvent( GUI_SELECTED ), object( obj ) {}
        GUIWidget* object;
    };
    
    class GUIMsgPressing : public cg::GUIEvent
    {
    public:
        GUIMsgPressing( GUIWidget* obj ) : GUIEvent( GUI_PRESSING ), object( obj ) {}
        GUIWidget* object;
    };
    
    class GUIMsgRelease : public cg::GUIEvent
    {
    public:
        GUIMsgRelease( GUIWidget* obj ) : GUIEvent( GUI_RELEASE ), object( obj ) {}
        GUIWidget* object;
    };
    
    class GUIPanel;
    class GUIMsgAdd : public cg::GUIEvent
    {
    public:
        GUIMsgAdd( GUIPanel* pan, GUIWidget* obj ) : cg::GUIEvent( cg::GUIEvent::GUI_ADD ), object( obj ), panel( pan ) {}
        GUIWidget* object;
        GUIPanel* panel;
    };
    
    class GUIMsgRem : public cg::GUIEvent
    {
    public:
        
        GUIMsgRem( GUIPanel* pan, GUIWidget* obj ) : cg::GUIEvent( cg::GUIEvent::GUI_ADD ), object( obj ), panel( pan ) {}
        GUIWidget* object;
        GUIPanel* panel;
    };
    
    
    
    class GUIMsgChild : public cg::GUIEvent
    {
    public:
        
        GUIMsgChild(bool add, GUIWidget* obj )
        :   cg::GUIEvent( cg::GUIEvent::GUI_CHILD )
        ,   widget( obj )
        ,   add( add )
        {}
        
        GUIWidget* widget;
        bool add;
    };
    
  
    const char* GUIEnumToStrong(int n);
    void PrintGUIEvent(int n);
}}
#endif /* GUIEvent_hpp */
