/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/23/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       MaterialTexture.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef MaterialTexture_hpp
#define MaterialTexture_hpp
#include "Texture2D.hpp"
namespace kege{namespace gfx{
    
    class MaterialTexture
    {
    public:
        
        virtual void Unbind() const = 0;
        virtual void Bind() const = 0;
        virtual void UnInit() = 0;
        virtual void Init() = 0;
        virtual ~ MaterialTexture(){}
        
        
        bool transparency;
        bool has_texture;
        int  blendmode;
    };
    
    typedef kege::shared<gfx::MaterialTexture> SharedMaterialTexture;
}}
#endif /* MaterialTexture_hpp */
