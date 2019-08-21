/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/11/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUITheme.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUITheme_hpp
#define GUITheme_hpp
#include "../../../graphics/core/mesh/Material.hpp"
#include "../../../graphics/core/framework/Shader.hpp"
namespace kege{namespace cg{
    
    class GUITheme : public gfx::Material
    {
    public:
        
        const shared::Shader& GetShader()const;
        shared::Shader& GetShader();
        
        void Unbind()const;
        void Bind()const;
        bool Init();
        
        ~ GUITheme();
        GUITheme();
        
        shared::Shader _program;
        shared::Uniform _unif_projection;
    };
}}
#endif /* GUITheme_hpp */
