/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       IBO.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef IBO_hpp
#define IBO_hpp
#include "../../graphics/framework/VBO.hpp"
#include "../../graphics/framework/GFXEnum.hpp"
namespace kege{namespace gfx{
    
    class IBO : public VBO
    {
    public:
        
        virtual void DrawInstanced(cg::uint mode, cg::uint count, const void *indices, cg::uint instancecount) = 0;
        virtual void Draw(cg::uint mode, cg::uint count, const void *indices) = 0;
        virtual ~ IBO(){}
    };
}}
#endif /* IBO_hpp */