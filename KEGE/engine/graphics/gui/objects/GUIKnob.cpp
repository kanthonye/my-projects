/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/30/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIKnob.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "GUIKnob.hpp"
namespace kege{namespace cg{
    
    int GUIKnob::onEvent(const cg::GUIEvent& event)
    {
        if (elem != nullptr)
        {
            return elem->onEvent( event );
        }
        return GUIEvent::NOTHING;
    }
    
    bool GUIKnob::TestMouseOver(double x, double y)
    {
        if ( TestMouseOverConst( x,y ) )
        {
            if (elem != nullptr)
            {
                return elem->TestMouseOver( x,y );
            }
            return true;
        }
        return false;
    }
    
    void GUIKnob::Render(GUIRenderer* renderer) const
    {
        GUIWidget::Render( renderer );
        if (elem != nullptr)
        {
            elem->Render( renderer );
        }
    }
    
    void GUIKnob::SetElem( cg::GUIWidget* elm )
    {
        elem = elm;
    }
    const cg::GUIWidget* GUIKnob::GetElem()const
    {
        return elem;
    }
    cg::GUIWidget* GUIKnob::GetElem()
    {
        return elem;
    }
    
    void GUIKnob::UpdateTransform()
    {
        cg::GUIWidget::UpdateTransform();
        if (elem != nullptr)
        {
            elem->SetParent( this );
            elem->UpdateTransform();
        }
    }
    
    bool GUIKnob::IsOccupied() const
    {
        return occupied;
    }
    bool GUIKnob::FreeElem()
    {
        if (elem != nullptr)
        {
            delete elem;
            elem = nullptr;
            return true;
        }
        return false;
    }
    
    cg::uint GUIKnob::Init()
    {
        if (elem != nullptr)
        {
            elem->Init();
        }
        return GUIWidget::Init();
    }
    void GUIKnob::UnInit()
    {
        if (elem != nullptr)
        {
            elem->UnInit();
        }
        GUIWidget::UnInit();
    }
    
    GUIKnob::GUIKnob( const GUIKnob& knob )
    :   cg::GUIWidget( GUIType::GRID, "" )
    ,   elem( nullptr )
    ,   occupied( false )
    {
        GetLocalPosition() = knob.GetLocalPosition();
        SetName( knob.GetName() );
        SetColor( knob.GetColor() );
        SetElem( knob.elem );
        SetTexel( knob.GetTexel() );
        SetParent( knob._parent );
        SetSystem( knob._system );
        SetWidth( knob.GetWidth() );
        SetHeight( knob.GetHeight() );
    }
    
    GUIKnob::~ GUIKnob()
    {
        FreeElem();
    }
    GUIKnob::GUIKnob()
    :   cg::GUIWidget( GUIType::GRID, "" )
    ,   elem( nullptr )
    ,   occupied( false )
    {
    }
}}
