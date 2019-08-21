/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/25/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIView.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "GUI.hpp"
#include "GUIView.hpp"
namespace kege{namespace cg{

    int GUIView::onEvent(const cg::GUIEvent& event)
    {
        return _manager.onEventReorder( event );
    }

    int GUIView::TestMouseOver(double x, double y)
    {
        return _manager.TestMouseOver( x,y );
    }

    void GUIView::Render(GUIRenderer* renderer) const
    {
        renderer->SetProjection( _proj );
        _manager.Render( renderer );
    }
    
    void GUIView::UpdateTransform()
    {
        _manager.UpdateTransform();
    }
    
    GUIWidget* GUIView::Add( GUIWidget* widget )
    {
        if (widget != nullptr)
        {
            widget->SetSystem( _gui );
        }
        return _manager.AddGUI( widget );
    }

    cg::uint GUIView::Init()
    {
        return _manager.Init();
    }
    
    void GUIView::UnInit()
    {
        _manager.UnInit();
    }
    
    GUIWidget* GUIView::Get(double x, double y)
    {
        return _manager.Get( x, y );
    }
    
    void GUIView::SetFocus(GUIWidget* object)
    {
        _focus = object;
    }
    const GUIWidget* GUIView::GetFocus() const
    {
        return _focus;
    }
    GUIWidget* GUIView::GetFocus()
    {
        return _focus;
    }
    
    const ds::string& GUIView::GetName()
    {
        return _name;
    }
    
    void GUIView::SetGUI(GUI* gui)
    {
        _gui = gui;
    }
    const GUI* GUIView::GetGUI() const
    {
        return _gui;
    }
    GUI* GUIView::GetGUI()
    {
        return _gui;
    }
    
    GUIView::GUIView(const ds::string& name, const cg::mat44& view, const cg::mat44& proj)
    :   _proj( proj )
    ,   _view( 1.0 )
    ,   _name( name )
    ,   _gui( nullptr )
    ,   _focus( nullptr )
    {
    }
    
    GUIView::GUIView(const cg::mat44& view, const cg::mat44& proj)
    :   _proj( proj )
    ,   _view( 1.0 )
    ,   _gui( nullptr )
    ,   _focus( nullptr )
    {
    }
    
    GUIView::~ GUIView()
    {
        _manager.DestroyGUIs();
    }
}}
