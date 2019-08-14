//
//  Texture.h
//  model_object
//
//  Created by Kenneth Esdaile on 4/20/15.
//  Copyright (c) 2015 kae. All rights reserved.
//

#ifndef __Texture_h__
#define __Texture_h__
#include "../../graphics/framework/GFXEnum.hpp"
#include "../../graphics/core/image.hpp"
#include "../../graphics/cgmath/cgm.hpp"
namespace kege{namespace gfx{

    class Texture
    {
    public:
        
        virtual void SetBindingPoint(int value) const = 0;
        virtual void UnCreate() = 0;
        virtual void Create() = 0;
        virtual void Unbind() const = 0;
        virtual void Bind() const = 0;
        virtual ~ Texture(){}
    };

    typedef kege::shared<Texture> SharedTexture;
}}
#endif /* defined(__model_object__Texture__) */
