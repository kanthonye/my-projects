/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/16/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       VertexLayout.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef VertexLayout_hpp
#define VertexLayout_hpp
#include "cgm.hpp"
#include "array.hpp"
#include "DataBuffer.hpp"
namespace kege{namespace core{
    
    struct VertexElement
    {
        cg::uint index;
        cg::uint size;
        cg::uint offset;
        cg::uint attdiv; /* vertex attribute divisor : use to set the rate at which vertex attributes advance when rendering multiple instances of primitives in a single draw call. If set to zero, the attribute at slot [index] advances once per vertex. If set to non-zero, the attribute advances once per divisor. */
    };
    
    class VertexLayout
    {
    public:
        
        void AddElem(cg::uint tar, cg::uint siz, cg::uint offs, cg::uint attdiv = 0);
        VertexElement& GetElem(cg::uint target);
        
        const VertexElement& operator [](cg::uint i) const;
        VertexElement& operator [](cg::uint i);
        
        cg::uint Count()const;
        
    private:
        
        ds::array< VertexElement > elements;
        static VertexElement dummy;
    };
}}
namespace kege{namespace shared{
    typedef mem::shared< core::VertexLayout > VertexLayout;
}}
#endif /* VertexLayout_hpp */
