/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GLTextureCube.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GLTextureCube_hpp
#define GLTextureCube_hpp
#include "../../framework/TextureCube.hpp"
namespace kege{namespace gfx{
    
    class GLTextureCube : public gfx::TextureCube
    {
    public:
        
        void Create
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
         ,  const void* data[6]  ) override;
        
        void SetBindingPoint(int value) const override;
        void UnCreate() override;
        void Create() override;
        void Unbind() const override;
        void Bind() const override;
        ~ GLTextureCube();
        GLTextureCube();
        
    private:
        
        cg::uint type;
        cg::uint id;
    };
}}
#endif /* GLTextureCube_hpp */
