/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/25/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIPanel.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../gui/objects/GUIPanel.hpp"
#include "../../gui/objects/GUIRenderer.hpp"
namespace kege{namespace cg{
    
    int GUIPanel::onEvent(const cg::GUIEvent &event)
    {
        int state = _manager.onEvent( event );
        if (state == GUIEvent::NOTHING)
        {
            return GUIControl::onEvent( event );
        }
        onAction( state );
        return state;
    }

    bool GUIPanel::TestMouseOver(double x, double y)
    {
        if ( GUIControl::TestMouseOver( x,y) )
        {
            _manager.TestMouseOver( x,y );
            return true;
        }
        return false;
    }
    
    void GUIPanel::Render( GUIRenderer* renderer ) const
    {
        renderer->DrawGUI( this );
        _manager.Render( renderer );
        if ( _color.a <= 0.0)
        {
            return;
        }
    }
    
    GUIWidget* GUIPanel::Get(double x, double y)
    {
        if ( TestMouseOverConst( x,y ) )
        {
            GUIWidget* widget = _manager.Get( x,y );
            if (widget == nullptr)
            {
                return this;
            }
        }
        return nullptr;
    }
    
    GUIWidget* GUIPanel::AddGUI(GUIWidget* object)
    {
        _manager.AddGUI( object );
        object->SetParent( this );
        GUIControl::onEvent( GUIMsgAdd( this, object ) );
        return object;
    }
    
    bool GUIPanel::RemGUI(GUIWidget* object)
    {
        if ( object->GetParent() == this )
        {
            GUIControl::onEvent( GUIMsgRem( this, object ) );
            object->SetParent( nullptr );
            return true;
        }
        return false;
    }
    
    void GUIPanel::SetSystem(cg::GUI* gui)
    {
        _manager.SetSystem( gui );
    }
    
    const GUIManager* GUIPanel::GetGUIMgr()const
    {
        return &_manager;
    }
    
    GUIManager* GUIPanel::GetGUIMgr()
    {
        return &_manager;
    }
    
    cg::uint GUIPanel::Init()
    {
        return _manager.Init();
    }
    
    void GUIPanel::UnInit()
    {
        _manager.UnInit();
    }
    
    void GUIPanel::UpdateTransform()
    {
        GUIWidget::UpdateTransform();
        _manager.UpdateTransform();
    }
    
    GUIPanel::GUIPanel(GUIType type, const ds::string& name, float x, float y, int w, int h, const cg::vec4& colr)
    :   GUIControl( type, name, x, y, w, h, colr )
    {}
    GUIPanel::GUIPanel(GUIType type, const ds::string& name, int w, int h, const cg::vec4& colr)
    :   GUIControl( type, name, w, h, colr )
    {}
    
    GUIPanel::GUIPanel(GUIType type, const ds::string& name, int w, int h)
    :   GUIControl( type, name, w, h )
    {}
    
    GUIPanel::GUIPanel(GUIType type, const ds::string& name)
    :   GUIControl( type, name )
    {}
    
    
    GUIPanel::GUIPanel(const ds::string& name, float x, float y, int w, int h, const cg::vec4& colr)
    :   GUIControl( GUIType::PANEL, name, x, y, w, h, colr )
    {}
    
    GUIPanel::GUIPanel(const ds::string& name, int w, int h, const cg::vec4& colr)
    :   GUIControl( GUIType::PANEL, name, w, h, colr )
    {}
    
    GUIPanel::GUIPanel(const ds::string& name, int w, int h)
    :   GUIControl( GUIType::PANEL, name, w, h )
    {}
    
    GUIPanel::GUIPanel(const ds::string& name)
    :   GUIControl( GUIType::PANEL, name )
    {}
    
    GUIPanel::~ GUIPanel()
    {
        _manager.DestroyGUIs();
    }
}}
