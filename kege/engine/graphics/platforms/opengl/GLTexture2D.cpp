/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GLTexture2D.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include <OpenGL/gl3.h>
#include "GLTexture2D.hpp"
#include "Graphics.hpp"
namespace kege{namespace gfx{
    
    void GLTexture2D::Create
    (   cg::uint width
     ,  cg::uint height
     ,  cg::uint internalformat
     ,  cg::uint format
     ,  cg::uint datatype
     ,  cg::uint min_filter
     ,  cg::uint mag_filter
     ,  cg::uint wrap_x
     ,  cg::uint wrap_y
     ,  bool gen_mipmap
     ,  const void* data  )
    {
        CreateGLTexture2D
        (   width
         ,  height
         ,   gfx::Graphics::GetConstant( internalformat )
         ,  gfx::Graphics::GetConstant( format )
         ,  gfx::Graphics::GetConstant( datatype )
         ,  gfx::Graphics::GetConstant( min_filter )
         ,  gfx::Graphics::GetConstant( mag_filter )
         ,  gfx::Graphics::GetConstant( wrap_x )
         ,  gfx::Graphics::GetConstant( wrap_y )
         ,  gen_mipmap
         ,  data  );
    }
    
    void GLTexture2D::Create(const kege::image8i& image, bool gen_mipmap, cg::uint repeat, cg::uint filter)
    {
        Create
        (   image.width()
         ,  image.height()
         ,  GFX::RGB
         ,  GFX::RGB
         ,  GFX::UNSIGNED_BYTE
         ,  filter
         ,  filter
         ,  repeat
         ,  repeat
         ,  gen_mipmap
         ,  image.data()  );
    }
    void GLTexture2D::SetTextureInfo(const TextureInfo2D& info)
    {
        this->info = info;
    }
    const TextureInfo2D& GLTexture2D::GetTextureInfo() const
    {
        return info;
    }
    cg::uint GLGetFormat(const shared_image& image)
    {
        switch ( image->chan() )
        {
            case 1: return GFX::RED; break;
            case 3: return GFX::RGB; break;
            case 4: return GFX::RGBA; break;
        }
        return GL_RED;
    }

    void GLTexture2D::Create()
    {
        Create
        (   info.image->width()
         ,  info.image->height()
         ,  GLGetFormat( info.image )
         ,  GLGetFormat( info.image )
         ,  info.image->type()
         ,  info.min_filter
         ,  info.mag_filter
         ,  info.wrap_x
         ,  info.wrap_y
         ,  info.gen_mipmap
         ,  info.image->data()  );
    }
    
    void GLTexture2D::SetBindingPoint(int value)const
    {
        glActiveTexture( GL_TEXTURE0 + value );
    }
    void GLTexture2D::UnCreate()
    {
        if (id != 0)
        {
            glDeleteTextures(1, &id);
            type = 0;
            id = 0;
        }
    }
    void GLTexture2D::Unbind()const
    {
        if (type == 0) return;
        glBindTexture(type, 0);
    }
    void GLTexture2D::Bind()const
    {
        if (id == 0) return;
        glBindTexture(type, id);
    }
    
    void GLTexture2D::CreateGLTexture2D
    (   cg::uint width
     ,  cg::uint height
     ,  cg::uint internalformat
     ,  cg::uint format
     ,  cg::uint datatype
     ,  cg::uint min_filter
     ,  cg::uint mag_filter
     ,  cg::uint wrap_x
     ,  cg::uint wrap_y
     ,  bool gen_mipmap
     ,  const void* data  )
    {
        type = GL_TEXTURE_2D;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, format, datatype, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_x);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_y);
        if ( gen_mipmap == true )
        {
            glGenerateMipmap(GL_TEXTURE_2D);
            gfx::Graphics::CheckError("glGenerateMipmap");
            if (min_filter == GL_NEAREST)
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
            }
            else
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            }
            gfx::Graphics::CheckError("GL_TEXTURE_MIN_FILTER");
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    GLTexture2D::~ GLTexture2D()
    {
        UnCreate();
    }
    GLTexture2D::GLTexture2D()
    :   type(0)
    ,   id(0)
    {}
}}

