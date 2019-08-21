//
//  GUIManager.h
//  dev-kege
//
//  Created by Kenneth A Esdaile on 7/19/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef GUILinkedList_h
#define GUILinkedList_h
#include "GUIWidget.hpp"
namespace kege{namespace cg{
    
    class GUIManager
    {
    public:
        
        cg::uint onEventButtonRelease( const cg::GUIEventButton& event );
        cg::uint onEventButtonPressed( const cg::GUIEventButton& event );
        cg::uint HandleEvent( const cg::GUIEvent& event );
        cg::uint onEventReorder( const cg::GUIEvent& event );
        cg::uint onEvent( const cg::GUIEvent& event );
        bool TestMouseOver( double x, double y );
        void onAction( cg::uint event );
        
        void Render( GUIRenderer* renderer )const;
        void UpdateTransform();
        
        GUIWidget* AddGUI( GUIWidget* object );
        void PutFirst( GUIWidget* object );
        void PutLast( GUIWidget* object );
        void RemGUI( GUIWidget* object );
        void Detach( GUIWidget* object );
        void SetMouseOver( bool value );
        
        GUIWidget* Get(double x, double y);
        
        void SetSystem( cg::GUI* gui );
        
        const GUIWidget* GetHead()const;
        const GUIWidget* GetTail()const;
        GUIWidget* GetHead();
        GUIWidget* GetTail();
        
        int GetSize()const;
        void DestroyGUIs();
        cg::uint Init();
        void UnInit();
        
        ~ GUIManager();
        GUIManager();
        
    private:
        
        GUIWidget* _focus;
        GUIWidget* _head;
        GUIWidget* _tail;
        int _size;
    };
}}
#endif /* GUILinkedList_h */
