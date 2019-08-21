/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GLIBO.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GLIBO_hpp
#define GLIBO_hpp
#include "../../../../graphics/core/framework/IBO.hpp"
namespace kege{namespace core{
    
    class GLIBO : public core::IBO
    {
    public:
        
        void DrawInstanced(cg::uint mode, cg::uint count, const void *indices, cg::uint instancecount);
        void Draw(cg::uint mode, cg::uint count, const void *indices);
        void Create(long size, const void* data, cg::uint usage);
        void UpdateBufferData(long size, const void* data);
        void UnCreate();
        void Unbind()const;
        void Bind()const;
        
        GLIBO(long size, const void* data, cg::uint usage);
        ~ GLIBO();
        GLIBO();
        
    private:
        
        cg::uint type;
        cg::uint id;
    };
}}
#endif /* GLIBO_hpp */
