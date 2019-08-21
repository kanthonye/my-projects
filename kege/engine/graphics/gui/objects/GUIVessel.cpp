/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/26/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIVessel.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "GUIVessel.hpp"
#include "../../gui/objects/GUIRenderer.hpp"
namespace kege{namespace cg{
    
    int GUIVessel::onEvent(const cg::GUIEvent &event)
    {
        return _manager.onEvent( event );
    }
    
    bool GUIVessel::TestMouseOver(double x, double y)
    {
        return _manager.TestMouseOver( x,y );
    }
    
    void GUIVessel::Render( GUIRenderer* renderer ) const
    {
        _manager.Render( renderer );
        if ( _color.a <= 0.0)
        {
            return;
        }
        renderer->DrawGUI( this );
    }
    
    GUIWidget* GUIVessel::AddGUI(GUIWidget* object)
    {
        _manager.AddGUI( object );
        object->SetParent( this );
        return object;
    }
    
    bool GUIVessel::RemGUI(GUIWidget* object)
    {
        if ( object->GetParent() == this )
        {
            _manager.RemGUI( object );
            object->SetParent( nullptr );
            return true;
        }
        return false;
    }
    
    GUIWidget* GUIVessel::Get(double x, double y)
    {
        return _manager.Get( x,y );
    }
    
    void GUIVessel::SetSystem(cg::GUI* gui)
    {
        _manager.SetSystem( gui );
    }
    
    const GUIManager* GUIVessel::GetGUIMgr()const
    {
        return &_manager;
    }
    
    GUIManager* GUIVessel::GetGUIMgr()
    {
        return &_manager;
    }
    
    cg::uint GUIVessel::Init()
    {
        GUIWidget::Init();
        return _manager.Init();
    }
    
    void GUIVessel::UnInit()
    {
        _manager.UnInit();
        GUIWidget::UnInit();
    }
    
    void GUIVessel::UpdateTransform()
    {
        GUIWidget::UpdateTransform();
        _manager.UpdateTransform();
    }
    
    GUIVessel::GUIVessel(const ds::string& name, float x, float y, int w, int h, const cg::vec4& colr)
    :   GUIWidget( GUIType::VESSEL, name, x, y, w, h, colr )
    {}
    
    GUIVessel::GUIVessel(const ds::string& name, int w, int h, const cg::vec4& colr)
    :   GUIWidget( GUIType::VESSEL, name, w, h, colr )
    {}
    
    GUIVessel::GUIVessel(const ds::string& name, int w, int h)
    :   GUIWidget( GUIType::VESSEL, name, w, h )
    {}
    
    GUIVessel::GUIVessel(const ds::string& name)
    :   GUIWidget( GUIType::VESSEL, name )
    {}
    
    GUIVessel::~ GUIVessel()
    {
        _manager.DestroyGUIs();
    }
}}
