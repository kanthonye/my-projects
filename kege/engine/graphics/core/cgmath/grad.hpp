//
//  grad.hpp
//  dev0
//
//  Created by Kenneth A Esdaile on 7/15/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef grad_hpp
#define grad_hpp
#include "../../../graphics/core/cgmath/vec4.hpp"
#include <vector>
namespace kege{namespace cg{
    
    class grad
    {
    public:
        
        struct color
        {
            color(cg::real v, cg::real r, cg::real g, cg::real b) : value(v), colr(r,g,b) {}
            color(cg::real v, const cgmvec3& c) : value(v), colr(c) {}
            cgmvec3  colr;
            cg::real value;
        };
        
        void add(cg::real val, cg::ubyte r, cg::ubyte g, cg::ubyte b);
        void add(cg::real val, const cgmvec3& color);
        cgmvec3 get(cg::real val)const;
        
    private:
        
        std::vector< cg::grad::color > gradients;
    };
}}
#endif /* grad_hpp */
