/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Texture2D.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef Texture2D_hpp
#define Texture2D_hpp
#include "../../../graphics/core/framework/Texture.hpp"
namespace kege{namespace core{
    
    struct TextureInfo2D
    {
        shared::image image;
        cg::uint min_filter;
        cg::uint mag_filter;
        cg::uint wrap_x;
        cg::uint wrap_y;
        bool gen_mipmap;
        
        TextureInfo2D
        (   const shared::image& image
         ,  cg::uint min_filter
         ,  cg::uint mag_filter
         ,  cg::uint wrap_x
         ,  cg::uint wrap_y
         ,  bool gen_mipmap   )
        :   image(image)
        ,   min_filter(min_filter)
        ,   mag_filter(mag_filter)
        ,   wrap_x(wrap_x)
        ,   wrap_y(wrap_y)
        ,   gen_mipmap(gen_mipmap)
        {}
        
        TextureInfo2D
        (   const kege::shared::image& image
         ,  cg::uint repeat
         ,  cg::uint filter
         ,  bool gen_mipmap )
        :   image(image)
        ,   min_filter(filter)
        ,   mag_filter(filter)
        ,   wrap_x(repeat)
        ,   wrap_y(repeat)
        ,   gen_mipmap(gen_mipmap)
        {}
        
        TextureInfo2D()
        :   min_filter(core::LINEAR_FILTER)
        ,   mag_filter(core::LINEAR_FILTER)
        ,   wrap_x(core::REPEAT)
        ,   wrap_y(core::REPEAT)
        ,   gen_mipmap(false)
        {}
    };
    
    
    
    class Texture2D : public kege::core::Texture
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
         ,  bool gen_mipmap
         ,  const void* data  ) = 0;
        
        virtual void Create
        (  const kege::image8i& image
         , bool gen_mipmap
         , cg::uint repeat
         , cg::uint filter  ) = 0;
        
        
        virtual void SetTextureInfo(const TextureInfo2D& info) = 0;
        virtual const TextureInfo2D& GetTextureInfo() const = 0;
        virtual void Create() = 0;
        
        virtual ~ Texture2D(){}
    };
}}
#endif /* Texture2D_hpp */
