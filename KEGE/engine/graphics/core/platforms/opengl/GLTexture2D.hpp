/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GLTexture2D.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GLTexture_hpp
#define GLTexture_hpp
#include "../../framework/Texture2D.hpp"
namespace kege{namespace core{
    class GLFramebuffer;
    
    class GLTexture2D : public core::Texture2D
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
         ,  bool gen_mipmap
         ,  const void* data  ) override;
        
        void Create
        (  const kege::image8i& image
         , bool gen_mipmap
         , cg::uint repeat
         , cg::uint filter  ) override;
        
        void SetTextureInfo(const TextureInfo2D& info) override;
        const TextureInfo2D& GetTextureInfo() const override;
        void Create() override;
        
        void SetBindingPoint(int value) const override;
        void UnCreate() override;
        void Unbind() const override;
        void Bind() const override;
        
        bool Valid()const override;
        ~ GLTexture2D();
        GLTexture2D();
        
    private:
        
        void CreateGLTexture2D
        (   cg::uint width
         ,  cg::uint height
         ,  cg::uint internalformat
         ,  cg::uint format
         ,  cg::uint type
         ,  cg::uint min_filter
         ,  cg::uint mag_filter
         ,  cg::uint wrap_x
         ,  cg::uint wrap_y
         ,  bool gen_mipmap
         ,  const void* data  );
        
    public:
        
        friend GLFramebuffer;
        TextureInfo2D info;
        cg::uint type;
        cg::uint id;
    };
}}
#endif /* GLTexture_hpp */
