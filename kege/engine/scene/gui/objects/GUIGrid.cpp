/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/30/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIGrid.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "GUIGrid.hpp"
namespace kege{namespace cg{
    
    const GUICol& GUIGrid::operator [](int index)const
    {
        return _rows[ index ];
    }
    GUICol& GUIGrid::operator [](int index)
    {
        return _rows[ index ];
    }
    
    int GUIGrid::onEvent(const cg::GUIEvent& event)
    {
        int s,state = GUIEvent::NOTHING;
        for (int i=0; i<_rows.size(); i++)
        {
            s = _rows[ i ].onEvent( event );
            if (state != GUIEvent::NOTHING)
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
    
    bool GUIGrid::TestMouseOver(double x, double y)
    {
        if ( cg::GUIWidget::TestMouseOverConst(x, y) )
        {
            for (int i=0; i<_rows.size(); i++)
            {
                _rows[ i ].TestMouseOver( x,y );
            }
            return true;
        }
        return false;
    }
    
    void GUIGrid::Render(GUIRenderer* renderer)const
    {
        for (int i=0; i<_rows.size(); i++)
        {
            _rows[ i ].Render( renderer );
        }
    }
    
    void GUIGrid::UpdateTransform()
    {
        GUIWidget::UpdateTransform();
        for (int i=0; i<_rows.size(); i++)
        {
            _rows[ i ].UpdateTransform();
        }
    }
    
    GUIWidget* GUIGrid::Get(double x, double y)
    {
        GUIWidget* w;
        if ( TestMouseOverConst( x,y ) )
        {
            for (int i=0; i<_rows.size(); i++)
            {
                w = _rows[ i ].Get( x,y );
                if ( w != nullptr )
                {
                    return w;
                }
            }
            return this;
        }
        return nullptr;
    }
    
    cg::uint GUIGrid::Init()
    {
        for (int i=0; i<_rows.size(); i++)
        {
            _rows[ i ].Init();
        }
        return true;
    }
    
    void GUIGrid::UnInit()
    {
        for (int i=0; i<_rows.size(); i++)
        {
            _rows[ i ].UnInit();
        }
    }
    
    GUIGrid::GUIGrid( int x, int y, int w, int h, int rows, int cols, const cg::vec4& colr )
    :   cg::GUIControl( GUIType::GRID, "", x,y, w,h, colr )
    {
        int gh = h / rows;
        _rows.resize( rows );
        for (y=0; y<rows; y++)
        {
            _rows[ y ].SetSize(w, gh, cols, colr);
            _rows[ y ].GetLocalPosition().y = (gh+1) * y;
            _rows[ y ].SetParent( this );
            _rows[ y ].SetSystem( _system );
        }
    }
    
    GUIGrid:: ~ GUIGrid()
    {
        _rows.clear();
    }
    GUIGrid::GUIGrid()
    :   cg::GUIControl( GUIType::GRID, "" )
    {
        
    }
    
}}

