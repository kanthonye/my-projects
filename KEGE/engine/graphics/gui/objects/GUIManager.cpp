//
//  GUIManager.c
//  dev-kege
//
//  Created by Kenneth A Esdaile on 7/19/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "GUIManager.hpp"
namespace kege{namespace cg{
    
    cg::uint GUIManager::onEventButtonRelease( const cg::GUIEventButton& event )
    {
        int s,state = GUIEvent::NOTHING;
        GUIWidget* gui = GetHead();
        while (gui != nullptr)
        {
            s = gui->onEvent( event );
            if (s != GUIEvent::NOTHING)
            {
                state = s;
            };
            gui = gui->GetNext();
        }
        return state;
    }
    
    cg::uint GUIManager::onEventButtonPressed( const cg::GUIEventButton& event )
    {
        int s,state = GUIEvent::NOTHING;
        GUIWidget* gui = GetHead();
        while (gui != nullptr)
        {
            s = gui->onEvent( event );
            if (s != GUIEvent::NOTHING)
            {
                state = s;
            };
            gui = gui->GetNext();
        }
        return state;
    }

    cg::uint GUIManager::HandleEvent( const cg::GUIEvent& event )
    {
        int state = GUIEvent::NOTHING;
        GUIWidget* gui = GetHead();
        while (gui != nullptr)
        {
            state = gui->onEvent( event );
            if (state != GUIEvent::NOTHING)
            {
                return state;
            };
            gui = gui->GetNext();
        }
        return state;
    }
    
    cg::uint GUIManager::onEventReorder( const cg::GUIEvent& event )
    {
        if ( event.GetType() == GUIEvent::MOUSE_BUTTON )
        {
            int s,state = GUIEvent::NOTHING;
            GUIWidget* gui = GetHead();
            while (gui != nullptr)
            {
                s = gui->onEvent( event );
                if (s != GUIEvent::NOTHING)
                {
                    if (state == GUIEvent::NOTHING && gui != GetHead())
                    {
                        GUIWidget* next = gui->GetNext();
                        RemGUI( gui );
                        PutFirst( gui );
                        gui = next;
                        continue;
                    }
                    state = s;
                };
                gui = gui->GetNext();
            }
            return state;
        }
        
        return HandleEvent( event );
    }
    
    cg::uint GUIManager::onEvent( const cg::GUIEvent& event )
    {
        if ( _focus != nullptr )
        {
            int state = _focus->onEvent( event );
            if ( state == GUIEvent::RELEASE || state == GUIEvent::NOTHING )
            {
                _focus = nullptr;
            }
            return state;
        }
        
        if ( event.GetType() == GUIEvent::MOUSE_BUTTON )
        {
            const cg::GUIEventButton& button = (const cg::GUIEventButton&)event;
            if (button.state == 0)
            {
                return onEventButtonRelease( button );
            }
            return onEventButtonPressed( button );
        }
        
        return HandleEvent( event );
    }
    
    void GUIManager::onAction( cg::uint event )
    {
        GUIWidget* next = _head;
        while (next != nullptr)
        {
            next->onAction( event );
            next = next->_next;
        }
    }
    
    bool GUIManager::TestMouseOver( double x, double y )
    {
        if ( _focus != nullptr ) return true;
        
        bool mouse_hit = false;
        GUIWidget* next = _head;
        while (next != nullptr)
        {
            if ( next->TestMouseOver( x, y ) )
            {
                mouse_hit = true;
            };
            next = next->_next;
        }
        return mouse_hit;
    }
    
    void GUIManager::Render( GUIRenderer* renderer ) const
    {
        GUIWidget* next = _tail;
        while (next != nullptr)
        {
            if ( !next->IsVisible() )
            {
                next = next->_prev;
                continue;
            }
            next->Render( renderer );
            next = next->_prev;
        }
    }
    
    void GUIManager::UpdateTransform()
    {
        GUIWidget* gui = _head;
        while (gui != nullptr)
        {
            if ( !gui->IsActive() )
            {
                GUIWidget* a = gui;
                gui = gui->_next;
                
                RemGUI( a );
                a->UnInit();
                delete a;
                a = nullptr;
                
                continue;
            }
            gui->UpdateTransform();
            gui = gui->_next;
        }
    }
    
    void GUIManager::SetSystem( cg::GUI* gui )
    {
        GUIWidget* next = _head;
        while (next != nullptr)
        {
            next->SetSystem( gui );
            next = next->_next;
        }
    }
    void GUIManager::PutFirst( GUIWidget* object )
    {
        if (_head == nullptr)
        {
            _tail = _head = object;
        }
        else
        {
            object->_next = _head;
            _head->_prev = object;
            _head = object;
        }
        _size++;
    }
    
    GUIWidget* GUIManager::AddGUI( GUIWidget* object )
    {
        if (_head == nullptr)
        {
            _tail = _head = object;
        }
        else
        {
            object->_prev = _tail;
            _tail->_next = object;
            _tail = object;
        }
        _size++;
        return object;
    }
    
    void GUIManager::RemGUI( GUIWidget* object )
    {
        if (object == _head)
        {
            _head = _head->_next;
            if (_head == nullptr) _tail = nullptr;
            else _head->_prev = nullptr;
        }
        else if (object == _tail)
        {
            _tail = _tail->_prev;
            if (_tail == nullptr) _head = nullptr;
            else _tail->_next = nullptr;
        }
        else
        {
            object->_next->_prev = object->_prev;
            object->_prev->_next = object->_next;
        }
        object->_next = nullptr;
        object->_prev = nullptr;
        _size--;
    }
    
    void GUIManager::SetMouseOver( bool value )
    {
        GUIWidget* next = _head;
        while (next != nullptr)
        {
            next->SetMouseOver( value );
            next = next->_next;
        }
    }
    
    GUIWidget* GUIManager::Get(double x, double y)
    {
        GUIWidget* a;
        GUIWidget* widget = _head;
        while (widget != nullptr)
        {
            a = widget->Get(x, y);
            if ( a != nullptr )
            {
                return a;
            }
            widget = widget->_next;
        }
        return nullptr;
    }
    
    const GUIWidget* GUIManager::GetHead()const
    {
        return _head;
    }
    const GUIWidget* GUIManager::GetTail()const
    {
        return _tail;
    }
    
    GUIWidget* GUIManager::GetHead()
    {
        return _head;
    }
    GUIWidget* GUIManager::GetTail()
    {
        return _tail;
    }
    int GUIManager::GetSize()const
    {
        return _size;
    }
    void GUIManager::DestroyGUIs()
    {
        GUIWidget* object;
        while (_head != nullptr)
        {
            object = _head;
            _head = _head->_next;
            delete object;
            object = nullptr;
            _size--;
        }
        _tail = _head = nullptr;
    }
    
    cg::uint GUIManager::Init()
    {
        cg::uint handled = 0;
        GUIWidget* gui = _head;
        while (gui != nullptr)
        {
            handled = gui->Init();
            gui = gui->_next;
        }
        return handled;
    }
    void GUIManager::UnInit()
    {
        GUIWidget* gui = _head;
        while (gui != nullptr)
        {
            gui->UnInit();
            gui = gui->_next;
        }
    }
    GUIManager::~ GUIManager()
    {
        DestroyGUIs();
    }
    
    GUIManager::GUIManager()
    :   _head( nullptr )
    ,   _tail( nullptr )
    ,   _focus( nullptr )
    ,   _size( 0 )
    {}
}}
