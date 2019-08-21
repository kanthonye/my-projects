/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       TextureCube.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef TextureCube_hpp
#define TextureCube_hpp
#include "../../../graphics/core/framework/Texture.hpp"
namespace kege{namespace core{
    
    class TextureCube : public core::Texture
    {
    public:
        
        virtual void Create
        (   cg::uint width
         ,  cg::uint height
         ,  cg::uint internalformat
         ,  cg::uint format
         ,  cg::uint type
         ,  cg::uint min_filter
         ,  cg::uint mag_filter
         ,  cg::uint wrap_x
         ,  cg::uint wrap_y
         ,  cg::uint wrap_z
         ,  bool gen_mipmap
         ,  const void* data[6]  ) = 0;
        
        virtual void UnCreate() = 0;
        virtual void Create() = 0;
        virtual void Unbind() const = 0;
        virtual void Bind() const = 0;
        
        virtual ~ TextureCube(){}
    };
}}
#endif /* TextureCube_hpp */
