/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       UBO.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef UBO_hpp
#define UBO_hpp
#include "shared.hpp"
#include "string.hpp"
#include "../../graphics/framework/VBO.hpp"
namespace kege{namespace gfx{
    
    class UBO
    {
    public:
        
        virtual void Create(long size, const void* data, cg::uint usage, const ds::string& name) = 0;
        
        virtual void UpdateData(cg::uint size, const void *data)const = 0;
        virtual void* BeginBufferReadWrite()const = 0;
        virtual void* BeginBufferWrite()const = 0;
        virtual void* BeginBufferRead()const = 0;
        virtual void EndBufferReadWrite()const = 0;

        virtual void UnCreate() = 0;
        virtual void Unbind()const = 0;
        virtual void Bind()const = 0;
        
        virtual ~ UBO(){}
    };
    
    typedef kege::shared< gfx::UBO > SharedUBO;
}}
#endif /* UBO_hpp */
