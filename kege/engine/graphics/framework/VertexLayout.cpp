/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/16/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       VertexLayout.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../graphics/framework/VertexLayout.hpp"
namespace kege{namespace gfx{
    
    void VertexLayout::AddElem(cg::uint index, cg::uint siz, cg::uint offs, cg::uint attdiv)
    {
        elements.resize( elements.size()+1 );
        elements[ elements.size()-1 ] = {index, siz, offs, attdiv};
    }
    
    VertexElement& VertexLayout::GetElem(cg::uint index)
    {
        for (int i=0; i<elements.size(); i++)
        {
            if (elements[i].index == index)
            {
                return elements[i];
            }
        }
        return dummy;
    }
    
    const VertexElement& VertexLayout::operator [](cg::uint i) const
    {
        return elements[i];
    }
    
    VertexElement& VertexLayout::operator [](cg::uint i)
    {
        return elements[i];
    }
    
    cg::uint VertexLayout::Count()const
    {
        return (cg::uint) elements.size();
    }
    
    VertexElement VertexLayout::dummy = {0,0,0};
}}
