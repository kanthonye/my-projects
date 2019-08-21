/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/30/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUICol.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "GUICol.hpp"
namespace kege{namespace cg{
    
    void GUICol::SetSize(int w, int h, int divs, const cg::vec4& colr)
    {
        int gw = w / divs;
        SetHeight( h );
        SetWidth( w );
        elems.resize( divs );
        for (int i=0; i<divs; i++)
        {
            elems[ i ].SetSystem( GetSystem() );
            elems[ i ].SetParent( this );
            elems[ i ].GetLocalPosition().x = (gw+1) * i;
            elems[ i ].GetLocalPosition().y = 0.0f;
            elems[ i ].SetHeight(h);
            elems[ i ].SetWidth(gw);
            elems[ i ].SetColor( colr );
        }
    }
    
    const GUIKnob& GUICol::operator [](int index)const
    {
        return elems[ index ];
    }
    GUIKnob& GUICol::operator [](int index)
    {
        return elems[ index ];
    }
    
    void GUICol::SetElem(int index, cg::GUIWidget* widget)
    {
        elems[ index ].SetElem( widget );
    }
    const cg::GUIWidget* GUICol::GetElem(int index) const
    {
        return elems[ index ].GetElem();
    }
    cg::GUIWidget* GUICol::GetElem(int index)
    {
        return elems[ index ].GetElem();
    }
    
    int GUICol::onEvent(const cg::GUIEvent& event)
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
    bool GUICol::TestMouseOver(double x, double y)
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
    
    void GUICol::Render( GUIRenderer* renderer )const
    {
        for (int i=0; i<elems.size(); i++)
        {
            elems[i].Render( renderer );
        }
    }
    void GUICol::UpdateTransform()
    {
        GUIControl::UpdateTransform();
        for (int i=0; i<elems.size(); i++)
        {
            elems[i].UpdateTransform();
        }
    }
    GUIWidget* GUICol::Get(double x, double y)
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
    cg::uint GUICol::Init()
    {
        for (int i=0; i<elems.size(); i++)
        {
            elems[i].Init();
        }
        return true;
    }
    
    void GUICol::UnInit()
    {
        for (int i=0; i<elems.size(); i++)
        {
            elems[i].UnInit();
        }
    }
    
    GUICol::GUICol(const ds::string& name, int x, int y, int w, int h, int divs, const cg::vec4& colr)
    :   cg::GUIControl( GUIType::COL, name, x,y, w,h, cg::vec4( 0.0 ) )
    {
        w = w / divs;
        elems.resize( divs );
        for (x=0; x<divs; x++)
        {
            elems[ x ].SetParent( this );
            elems[ x ].GetLocalPosition().x = w * x;
            elems[ x ].GetLocalPosition().y = 0.0f;
            elems[ x ].SetHeight(h - 1);
            elems[ x ].SetWidth(w - 1);
            elems[ x ].SetColor( colr );
        }
    }
    
    GUICol:: ~ GUICol()
    {
        for (int i=0; i<elems.size(); i++)
        {
            elems[i].FreeElem();
        }
        elems.clear();
    }
    
    GUICol::GUICol()
    :   cg::GUIControl( GUIType::COL, "" )
    {}
    
}}
