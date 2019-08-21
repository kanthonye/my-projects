//
//  grad.cpp
//  dev0
//
//  Created by Kenneth A Esdaile on 7/15/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#include "../../../graphics/core/cgmath/grad.hpp"
namespace kege{namespace cg{
    
    void grad::add(cg::real val, cg::ubyte r, cg::ubyte g, cg::ubyte b)
    {
        add(val, cg::color(r,g,b));
    }
    
    void grad::add(cg::real val, const cgmvec3& colr)
    {
        for (std::vector< grad::color >::iterator g=gradients.begin(); g!=gradients.end(); g++)
        {
            if ((*g).value == val)
            {
                (*g).colr = colr;
                return;
            }
        }
        gradients.push_back( grad::color(val, colr) );
    }
    
    cgmvec3 grad::get(cg::real val)const
    {
        if ( gradients.empty() ) return cgmvec3(0.0f);
        
        const grad::color* prev = nullptr;
        const grad::color* curr = &gradients[0];
        for (std::vector< grad::color >::const_iterator g=gradients.begin(); g!=gradients.end(); g++)
        {
            prev = curr;
            curr = &(*g);
            if (curr->value >= val)
            {
                float max = (curr->value - prev->value);
                float pos = (curr->value - val);
                float f = pos / ((max!=0.0f)?max:1.0f);
                return cg::lerp(curr->colr, prev->colr, f);
            }
        }
        return curr->colr;
    }
}}
