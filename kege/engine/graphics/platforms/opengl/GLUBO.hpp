/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GLUBO.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GLUBO_hpp
#define GLUBO_hpp
#include "../../../graphics/framework/UBO.hpp"
namespace kege{namespace gfx{
    
    class GLUBO : public gfx::UBO
    {
    public:
        
        void Create(long size, const void* data, cg::uint usage, const ds::string& name);
        
        
        void UpdateData(cg::uint size, const void *data)const;
        void* BeginBufferReadWrite()const;
        void* BeginBufferWrite()const;
        void* BeginBufferRead()const;
        void EndBufferReadWrite()const;

        void UnCreate();
        void Unbind()const;
        void Bind()const;
        
        GLUBO(long size, const void* data, cg::uint uses, const ds::string& name);
        ~ GLUBO();
        GLUBO();
        
    private:
        
        cg::uint usage;
        cg::uint id;
    };
}}
#endif /* GLUBO_hpp */
