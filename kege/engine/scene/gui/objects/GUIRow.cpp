/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/30/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIRow.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "GUIRow.hpp"
namespace kege{namespace cg{
    
    void GUIRow::SetSize(int w, int h, int divs, const cg::vec4& colr)
    {
        int gh = h / divs;
        SetHeight( h );
        SetWidth( w );
        elems.resize( divs );
        for (int i=0; i<divs; i++)
        {
            elems[ i ].SetParent( this );
            elems[ i ].GetLocalPosition().x = 0.0f;
            elems[ i ].GetLocalPosition().y = (gh+1) * i;
            elems[ i ].SetHeight(gh);
            elems[ i ].SetWidth(w);
            elems[ i ].SetColor( colr );
        }
    }
    
    const GUIKnob& GUIRow::operator [](int index)const
    {
        return elems[ index ];
    }
    GUIKnob& GUIRow::operator [](int index)
    {
        return elems[ index ];
    }
    
    void GUIRow::SetElem(int index, cg::GUIWidget* widget)
    {
        elems[ index ].SetElem( widget );
    }
    const cg::GUIWidget* GUIRow::GetElem(int index) const
    {
        return elems[ index ].GetElem();
    }
    cg::GUIWidget* GUIRow::GetElem(int index)
    {
        return elems[ index ].GetElem();
    }
    
    int GUIRow::onEvent(const cg::GUIEvent& event)
    {
        int s,state = GUIEvent::NOTHING;
        for (int i=0; i<elems.size(); i++)
        {
            s = elems[i].onEvent( event );
            if (state == GUIEvent::NOTHING)
            {
                state = s;
            };
        }
        if (state == GUIEvent::NOTHING)
        {
            return GUIControl::onEvent( event );
        }
        return state;
    }
    bool GUIRow::TestMouseOver(double x, double y)
    {
        if ( cg::GUIWidget::TestMouseOverConst(x, y) )
        {
            for (int i=0; i<elems.size(); i++)
            {
                elems[i].TestMouseOver( x,y );
            }
            return true;
        }
        return false;
    }
    
    void GUIRow::Render( GUIRenderer* renderer )const
    {
        for (int i=0; i<elems.size(); i++)
        {
            elems[i].Render( renderer );
        }
    }
    void GUIRow::UpdateTransform()
    {
        GUIControl::UpdateTransform();
        for (int i=0; i<elems.size(); i++)
        {
            elems[i].UpdateTransform();
        }
    }
    
    GUIWidget* GUIRow::Get(double x, double y)
    {
        if ( TestMouseOverConst( x,y ) )
        {
            for (int i=0; i<elems.size(); i++)
            {
                if ( elems[i].TestMouseOverConst( x,y ) )
                {
                    return &elems[i];
                }
            }
            return this;
        }
        return nullptr;
    }
    
    void GUIRow::Resize(int divs)
    {
        int size = cg::min( divs, (int)elems.size() );
        for (int i=size; i<elems.size(); i++)
        {
            elems[ i ].FreeElem();
        }
        elems.resize( divs );
    }
    
    cg::uint GUIRow::Init()
    {
        for (int i=0; i<elems.size(); i++)
        {
            elems[i].Init();
        }
        return true;
    }
    
    void GUIRow::UnInit()
    {
        for (int i=0; i<elems.size(); i++)
        {
            elems[i].UnInit();
        }
    }
    
    GUIRow::GUIRow(const ds::string& name, int x, int y, int w, int h, int divs, const cg::vec4& colr)
    :   cg::GUIControl( GUIType::ROW, name, x,y, w,h, cg::vec4( 0.0 ) )
    {
        h = h / divs;
        elems.resize( divs );
        for (y=0; y<divs; y++)
        {
            elems[ y ].SetParent( this );
            elems[ y ].GetLocalPosition().x = 0.0f;
            elems[ y ].GetLocalPosition().y = y * h;
            elems[ y ].SetHeight(h - 1);
            elems[ y ].SetWidth(w - 1);
            elems[ y ].SetColor( colr );
        }
    }
    
    GUIRow:: ~ GUIRow()
    {
        for (int i=0; i<elems.size(); i++)
        {
            elems[i].FreeElem();
        }
        elems.clear();
    }
    
    GUIRow::GUIRow()
    :   cg::GUIControl( GUIType::ROW, "" )
    {}
    
}}
