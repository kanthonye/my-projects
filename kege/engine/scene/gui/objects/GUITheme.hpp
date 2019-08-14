/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/11/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUITheme.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUITheme_hpp
#define GUITheme_hpp
#include "../../../graphics/core/Material.hpp"
#include "../../../graphics/core/MaterialTexture.hpp"
#include "../../../graphics/core/MaterialProperty.hpp"
#include "../../../graphics/framework/Shader.hpp"
namespace kege{namespace cg{
    
    class GUITheme : public gfx::Material
    {
    public:
        
        inline void SetProperty(const gfx::SharedMaterialProperty& property) {_property = property;}
        inline void SetTexture(const gfx::SharedMaterialTexture& texture) {_texture = texture;}
        
        const gfx::SharedShader& GetShader()const;
        gfx::SharedShader& GetShader();
        
        void Unbind()const;
        void Bind()const;
        bool Init();
        
        ~ GUITheme();
        GUITheme();
        
        gfx::SharedMaterialProperty _property;
        gfx::SharedMaterialTexture _texture;
        gfx::SharedShader _program;
        gfx::SharedUniform _unif_projection;
    };
}}
#endif /* GUITheme_hpp */
