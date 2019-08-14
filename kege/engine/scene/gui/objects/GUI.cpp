/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/11/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUI.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "Singleton.hpp"
#include "myGUI.hpp"
#include "GUI.hpp"
#include "Scene.hpp"
namespace kege{namespace cg{
    
    void GUI::HandleMessage( const kege::Message& message )
    {
        
    }
    
    bool GUI::OnMouseCursorMove(const kege::Cursor& cursor)
    {
        _cursor  = cursor;
        
        if ( _key.action >= 1 && _key.key == BUTTON_LEFT )
        {
            _grabbing = true;
            GUIEventGrab grab;
            grab.x = _cursor.dx;
            grab.y = _cursor.dy;
            
            state = onEvent( grab );
            return state;
        }

        for (GUIViews::iterator i=_views.begin(); i!=nullptr; i++)
        {
            i->TestMouseOver( cursor.x, cursor.y );
        }
        return false;
    }
    
    void GUI::OnScrollWheelMove(const kege::Cursor& cursor)
    {
        cg::GUIEventScroll scroll;
        scroll.x  = cursor.x;
        scroll.y  = cursor.y;
        onEvent( scroll );
    }
    
    bool GUI::OnMouseButtonPress(const kege::Key& key)
    {
        _key = key;
        
        cg::GUIEventButton button;
        button.x  = _cursor.x;
        button.y  = _cursor.y;
        button.state = key.GetAction();
        button.key = key.GetKey();
        
        _active = Get(button.x, button.y);
        if (_active && button.state >= 1)
        {
            //printf("capture\n");
        }
        else
        {
            //printf("letg o\n");
            _active = nullptr;
        }
        return onEvent( button );
    }
    
    void GUI::OnKeyboardPress(const kege::Key& key)
    {
        cg::GUIEventKey button;
        button.x  = _cursor.x;
        button.y  = _cursor.y;
        button.state = key.GetAction();
        button.key = key.GetKey();
        onEvent( button );
    }

    int GUI::onEvent(const cg::GUIEvent& event)
    {
//        if ( GUIWidget::ControlIsActive() )
//        {
//            state = GUIWidget::GetControl()->onEvent( event );
//            PrintGUIEvent( state );
//            if ( state != GUIEvent::NOTHING && state != GUIEvent::RELEASE )
//            {
//                return true;
//            };
//            //return ( state != GUIEvent::NOTHING && state != GUIEvent::RELEASE );
//        }
        for (GUIViews::iterator i=_views.begin(); i!=nullptr; i++)
        {
            state = i->onEvent( event );
            if ( state != GUIEvent::NOTHING && state != GUIEvent::RELEASE )
            {
                //PrintGUIEvent( state );
                break;
            };
        }
        return GUIWidget::ControlIsActive();
    }
    
    GUIView* GUI::GetView( const ds::string& name )
    {
        for (GUIViews::iterator i=_views.begin(); i!=nullptr; i++)
        {
            if (i->GetName() == name)
            {
                return i.element();;
            }
        }
        return nullptr;
    }
    
    GUIView* GUI::RemView(GUIView* view)
    {
        for (GUIViews::iterator i=_views.begin(); i!=nullptr; i++)
        {
            if (i.element() == view)
            {
                GUIView* view = i.element();
                view->SetGUI( this );
                _views.erase( i );
                return view;;
            }
        }
        return nullptr;
    }
    
    GUIView* GUI::AddView(GUIView* canvas)
    {
        _views.push_back( canvas );
        canvas->SetGUI( this );
        return canvas;
    }
    
    void GUI::SetGrabbing( bool val )
    {
        _grabbing = val;
    }
    GUIWidget* GUI::Get(double x, double y)
    {
        GUIWidget* widget;
        for (GUIViews::iterator i=_views.begin(); i!=nullptr; i++)
        {
            widget = (*i)->Get(x, y);
            if (widget != nullptr)
            {
                return widget;
            }
        }
        return nullptr;
    }
    void GUI::SetFocus(GUIWidget* object)
    {
        _focus = object;
    }
    
    const GUIWidget* GUI::GetFocus() const
    {
        return _focus;
    }
    
    GUIWidget* GUI::GetFocus()
    {
        return _focus;
    }
    
    void GUI::Render()
    {
        if ( renderer.Bind() )
        {
            for (GUIViews::iterator i=_views.begin(); i!=nullptr; i++)
            {
                i->Render( &renderer );
            }
            renderer.Flush();
            renderer.Unbind();
        }
    }
    
    void GUI::Update( double delta )
    {
        for (GUIViews::iterator i=_views.begin(); i!=nullptr; i++)
        {
            (*i)->UpdateTransform();
        }
    }
    
    void GUI::UnInit()
    {
        if ( _init == true )
        {
            for (GUIViews::iterator i=_views.begin(); i!=nullptr; i++)
            {
                i->UnInit();
                delete (*i);
            }
            _views.clear();
            renderer.UnInit();
            _init = false;
        }
    }
    
    bool GUI::Init()
    {
        if ( _init == false )
        {
            renderer.Init();
            for (GUIViews::iterator i=_views.begin(); i!=nullptr; i++)
            {
                i->Init();
            }
            
            cg::mat44 proj = cg::orthoproj(-1024, 0, 512, -0, -100.0, 100.0);
            cg::GUIView* canvas = AddView( new cg::GUIView( "main", cg::mat44(1.0), proj ) );
//            canvas->Add( SliderX2("slider2x", 10,5, 100, 15, cg::vec4(1.0), cg::vec4(0.4,0.4,0.4,0.4), 0.0, 0.0, 0.0, 100) );
//            canvas->Add( SliderX("sliderx", 10,20, 100, 10, cg::vec4(1.0), cg::vec4(0.4,0.4,0.4,1), 0.0, 0.0, 100) );
//            canvas->Add( SelectionList("selection", 20, 200, 200, 15, cg::vec4(0.3,0.3,0.3,1), cg::vec4(0.4,0.4,0.4,1)) );
//            canvas->Add( Tab("tab", 230, 200, 200, 15, cg::vec4(0.3,0.3,0.3,1), cg::vec4(0.4,0.4,0.4,1)) );
//            canvas->Add( Droplist("droplist", 440, 200, 200, 200, cg::vec4(0.3,0.3,0.3,1), cg::vec4(0.4,0.4,0.4,1)) );
            
//            canvas->Add( FocusButton("menu-button", 300, 10, 30, 20, cg::vec4(0.3, 0, 0.4, 1.0) ) );
//            canvas->Add( Grid(300,10, 300,200,  3,3, cg::vec4(0.4,0.4,0.4,1)) );
//            canvas->Add( Row(0,10, 33,100, 3, cg::vec4(0.4,0.4,0.4,1)) );
//            canvas->Add( Col(0,10, 100,30, 3, cg::vec4(0.4,0.4,0.4,1)) );
            
//            canvas->Add( new GUIText(20,5, cg::vec4(0,0,0,1), "KEGE") );
            
            
            //canvas->Add( ColorSlider("colr", 10, 100, 150, cg::vec4(0.6,0.6,0.6,1), cg::vec4(0.4,0.4,0.4,1)) );
            
            _init = true;
        }
        return _init;
    }
    
    GUI::~ GUI()
    {
        for (GUIViews::iterator i=_views.begin(); i!=nullptr; i++)
        {
            delete i.element();
        }
        _views.clear();
        kege::Singleton::Free< GUI >();
    }
    
    GUI::GUI()
    :   kege::SubSystem( "GUI" )
    ,   _active( nullptr )
    ,   _focus( nullptr )
    ,   _grabbing( false )
    {
        kege::Singleton::Set< GUI >( this );
    }
}}
