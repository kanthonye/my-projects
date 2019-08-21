//
//  Texture.h
//  model_object
//
//  Created by Kenneth Esdaile on 4/20/15.
//  Copyright (c) 2015 kae. All rights reserved.
//

#ifndef __Texture_h__
#define __Texture_h__
#include "../../../graphics/core/framework/GFXEnum.hpp"
#include "../../../graphics/core/image/image.hpp"
#include "../../../graphics/core/cgmath/cgm.hpp"
namespace kege{namespace core{

    class Texture
    {
    public:
        
        virtual void SetBindingPoint(int value) const = 0;
        virtual void UnCreate() = 0;
        virtual void Create() = 0;
        virtual void Unbind() const = 0;
        virtual void Bind() const = 0;
        
        virtual bool Valid()const = 0;
        virtual ~ Texture(){}
    };
}}
namespace kege{namespace shared{
    typedef mem::shared< core::Texture > Texture;
}}
#endif /* defined(__model_object__Texture__) */
