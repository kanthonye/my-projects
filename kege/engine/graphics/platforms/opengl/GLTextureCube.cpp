/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GLTextureCube.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include <OpenGL/gl3.h>
#include "GLTextureCube.hpp"
namespace kege{namespace gfx{
    
    void GLTextureCube::Create
    (   cg::uint width
     ,  cg::uint height
     ,  cg::uint internalformat
     ,  cg::uint format
     ,  cg::uint datatype
     ,  cg::uint min_filter
     ,  cg::uint mag_filter
     ,  cg::uint wrap_x
     ,  cg::uint wrap_y
     ,  cg::uint wrap_z
     ,  bool gen_mipmap
     ,  const void* data[6]  )
    {
        type = GL_TEXTURE_CUBE_MAP;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_CUBE_MAP, id);
        
        for (int i=0; i<6; i++)
        {
            glTexImage2D
            (  GL_TEXTURE_CUBE_MAP_POSITIVE_X + i
             , 0
             , internalformat
             , width
             , height
             , 0
             , format
             , datatype
             , data[i] );
        }
        
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, min_filter);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, mag_filter);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, wrap_x);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, wrap_y);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, wrap_z);
        if (gen_mipmap == false)
        {
            glGenerateMipmap(GL_TEXTURE_2D);
            if (min_filter == GL_NEAREST)
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
            }
            else
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            }
            
            if (mag_filter == GL_NEAREST)
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
            }
            else
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            }
        }
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
    
    void GLTextureCube::SetBindingPoint(int value) const
    {
        glActiveTexture( value );
    }
    void GLTextureCube::UnCreate()
    {
        if (id != 0)
        {
            glDeleteTextures(1, &id);
            type = 0;
            id = 0;
        }
    }
    void GLTextureCube::Create()
    {
        
    }
    void GLTextureCube::Unbind() const
    {
        if (type == 0) return;
        glBindTexture(type, 0);
    }
    void GLTextureCube::Bind() const
    {
        if (id == 0) return;
        glBindTexture(type, id);
    }
    GLTextureCube::~ GLTextureCube()
    {
        UnCreate();
    }
    GLTextureCube::GLTextureCube()
    :   type(0)
    ,   id(0)
    {}
}}

