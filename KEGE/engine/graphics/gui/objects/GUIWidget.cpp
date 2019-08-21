/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/10/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIWidget.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../gui/objects/GUIWidget.hpp"
#include "../../gui/objects/GUIRenderer.hpp"
namespace kege{namespace cg{
    
    bool GUIWidget::ReleaseControl(GUIWidget* contr)
    {
        if (contr == control)
        {
            control = nullptr;
            return true;
        }
        return false;
    }
    void GUIWidget::SetControl(GUIWidget* contr)
    {
        control = contr;
    }
    
    void GUIWidget::HandleMessage( const kege::Message& message )
    {
        if (message.GetType() == kege::MSG::GUI_EVENT)
        {
            onEvent( (const GUIEvent&) message );
        }
    }
    
    GUIWidget* GUIWidget::GetControl()
    {
        return control;
    }
    
    bool GUIWidget::ControlIsActive()
    {
        return control != nullptr;
    }
    
    void GUIWidget::FreeControl()
    {
        control = nullptr;
    }
    
    int GUIWidget::onEvent(const cg::GUIEvent& event)
    {
        return GUIEvent::NOTHING;
    }
    int GUIWidget::onAction(cg::uint event)
    {
        return GUIEvent::NOTHING;
    }
    
    bool GUIWidget::TestMouseOverConst(double x, double y) const
    {
        return
        (_world_position.x <= x) &&
        (_world_position.x + _width  >= x) &&
        (_world_position.y <= y) &&
        (_world_position.y + _height >= y);
    }
    
    bool GUIWidget::TestMouseOver(double x, double y) {return false;}
    
    void GUIWidget::SetParent(cg::GUIWidget* parent) {_parent = parent;}
    const cg::GUIWidget* GUIWidget::GetParent() const {return _parent;}
    cg::GUIWidget* GUIWidget::GetParent() {return _parent;}
    
    cg::GUIWidget* cg::GUIWidget::GetRoot()
    {
        if (GetParent() == nullptr) return this;
        return GetParent()->GetRoot();
    }
    
    void GUIWidget::SetSystem(GUI* system)
    {
        _system = system;
    }
    const GUI* GUIWidget::GetSystem()const
    {
        return _system;
    }
    GUI* GUIWidget::GetSystem()
    {
        return _system;
    }
    
    void GUIWidget::SetName(const ds::string& name)
    {
        _name = name;
    }
    const ds::string& GUIWidget::GetName() const
    {
        return _name;
    }
    ds::string& GUIWidget::GetName()
    {
        return _name;
    }
    
    void GUIWidget::SetColor(const cg::vec4& color)
    {
        _color = color;
    }
    const cg::vec4& GUIWidget::GetColor() const
    {
        return _color;
    }
    cg::vec4& GUIWidget::GetColor()
    {
        return _color;
    }
    
    void GUIWidget::SetTexel(const cg::vec4& texel)
    {
        _texel = texel;
    }
    const cg::vec4& GUIWidget::GetTexel() const
    {
        return _texel;
    }
    cg::vec4& GUIWidget::GetTexel()
    {
        return _texel;
    }
    
    const GUIManager* GUIWidget::GetGUIMgr()const
    {
        return nullptr;
    }
    GUIManager* GUIWidget::GetGUIMgr()
    {
        return nullptr;
    }
    
    void  GUIWidget::SetHeight(short value)
    {
        _height = value;
    }
    short GUIWidget::GetHeight() const
    {
        return _height;
    }
    
    void  GUIWidget::SetWidth(short value)
    {
        _width = value;
    }
    short GUIWidget::GetWidth() const
    {
        return _width;
    }
    
    void GUIWidget::SetVisible(bool value)
    {
        _visible = value;
    }
    bool GUIWidget::IsVisible()const
    {
        return _visible;
    }
    void GUIWidget::SetActive(bool value)
    {
        _active = value;
    }
    bool GUIWidget::IsActive()const
    {
        return _active;
    }
    bool GUIWidget::IsInit() const
    {
        return _init;
    }
    
    void GUIWidget::Render( GUIRenderer* renderer ) const
    {
        if ( _visible )
        {
            renderer->DrawGUI( this );
        }
    }
    void GUIWidget::UpdateTransform()
    {
        if ( _parent != nullptr )
        {
            _world_position = _parent->_world_position + _local_position;
        }
        else
        {
            _world_position = _local_position;
        }
    }
    
    GUIWidget* GUIWidget::Get(double x, double y)
    {
        if ( TestMouseOverConst( x,y) )
        {
            return this;
        }
        return nullptr;
    }
    
    cg::GUIWidget* GUIWidget::GetNext()
    {
        return _next;
    }
    cg::GUIWidget* GUIWidget::GetPrev()
    {
        return _prev;
    }
    
    cg::uint GUIWidget::Init()
    {
        _init = true;
        return _init;
    }
    
    void GUIWidget::UnInit()
    {
        _init = false;
    }
    
    void GUIWidget::SetMouseOver( bool val ) {}
    bool GUIWidget::GetMouseOver() const {return false;}
    
    GUIWidget::GUIWidget(const ds::string& name, float x, float y, int w, int h, const cg::vec4& colr)
    :   _system( nullptr )
    ,   _parent( nullptr )
    ,   _next( nullptr )
    ,   _prev( nullptr )
    ,   _world_position( 0.0 )
    ,   _local_position(x, y, 0.0f)
    ,   _name( name )
    ,   _type( GUIType::WIDGET )
    ,   _color( colr )
    ,   _height( h )
    ,   _width( w )
    ,   _visible( true )
    ,   _active( true )
    ,   _init( false )
    {}
    
    GUIWidget::GUIWidget(const ds::string& name, int w, int h, const cg::vec4& colr)
    :   _system( nullptr )
    ,   _parent( nullptr )
    ,   _local_position( 0.0 )
    ,   _world_position( 0.0 )
    ,   _name( name )
    ,   _next( nullptr )
    ,   _prev( nullptr )
    ,   _type( GUIType::WIDGET )
    ,   _color( colr )
    ,   _height( h )
    ,   _width( w )
    ,   _visible( true )
    ,   _active( true )
    ,   _init( false )
    {}
    
    GUIWidget::GUIWidget(const ds::string& name, int w, int h)
    :   _system( nullptr )
    ,   _parent( nullptr )
    ,   _local_position( 0.0 )
    ,   _world_position( 0.0 )
    ,   _name( name )
    ,   _next( nullptr )
    ,   _prev( nullptr )
    ,   _type( GUIType::WIDGET )
    ,   _height( h )
    ,   _width( w )
    ,   _color( 1.0 )
    ,   _visible( true )
    ,   _active( true )
    ,   _init( false )
    {}
    
    GUIWidget::GUIWidget(const ds::string& name)
    :   _system( nullptr )
    ,   _parent( nullptr )
    ,   _local_position( 0.0 )
    ,   _world_position( 0.0 )
    ,   _name( name )
    ,   _next( nullptr )
    ,   _prev( nullptr )
    ,   _type( GUIType::WIDGET )
    ,   _height( 10 )
    ,   _width( 10 )
    ,   _color( 1.0 )
    ,   _visible( true )
    ,   _active( true )
    ,   _init( false )
    {}
    
    GUIWidget::GUIWidget(GUIType type, const ds::string& name, float x, float y, int w, int h, const cg::vec4& colr)
    :   _system( nullptr )
    ,   _parent( nullptr )
    ,   _next( nullptr )
    ,   _prev( nullptr )
    ,   _world_position( 0.0 )
    ,   _local_position(x, y, 0.0f)
    ,   _name( name )
    ,   _type( type )
    ,   _color( colr )
    ,   _height( h )
    ,   _width( w )
    ,   _visible( true )
    ,   _active( true )
    ,   _init( false )
    {}
    
    GUIWidget::GUIWidget(GUIType type, const ds::string& name, int w, int h, const cg::vec4& colr)
    :   _system( nullptr )
    ,   _parent( nullptr )
    ,   _local_position( 0.0 )
    ,   _world_position( 0.0 )
    ,   _name( name )
    ,   _next( nullptr )
    ,   _prev( nullptr )
    ,   _type( type )
    ,   _color( colr )
    ,   _height( h )
    ,   _width( w )
    ,   _visible( true )
    ,   _active( true )
    ,   _init( false )
    {}
    
    GUIWidget::GUIWidget(GUIType type, const ds::string& name, int w, int h)
    :   _system( nullptr )
    ,   _parent( nullptr )
    ,   _local_position( 0.0 )
    ,   _world_position( 0.0 )
    ,   _name( name )
    ,   _next( nullptr )
    ,   _prev( nullptr )
    ,   _type( type )
    ,   _height( h )
    ,   _width( w )
    ,   _color( 1.0 )
    ,   _visible( true )
    ,   _active( true )
    ,   _init( false )
    {}
    
    GUIWidget::GUIWidget(GUIType type, const ds::string& name)
    :   _system( nullptr )
    ,   _parent( nullptr )
    ,   _local_position( 0.0 )
    ,   _world_position( 0.0 )
    ,   _next( nullptr )
    ,   _prev( nullptr )
    ,   _name( name )
    ,   _type( type )
    ,   _height( 0 )
    ,   _width( 0 )
    ,   _color( 1.0 )
    ,   _visible( true )
    ,   _active( true )
    ,   _init( false )
    {}
    
    GUIWidget::~ GUIWidget()
    {
        _system = nullptr;
        _parent = nullptr;
        _next = nullptr;
        _prev = nullptr;
    }
    
    
    GUIWidget* GUIWidget::control = nullptr;
    bool GUIWidget::take_control = false;
}}

