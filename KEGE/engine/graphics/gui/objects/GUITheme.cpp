/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/11/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUITheme.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "GUITheme.hpp"
#include "../../../graphics/core/Graphics.hpp"
namespace kege{namespace cg{
    
    const shared::Shader& GUITheme::GetShader()const
    {
        return _program;
    }
    shared::Shader& GUITheme::GetShader()
    {
        return _program;
    }
    
    
    bool GUITheme::Init()
    {
        if ( _program == nullptr)
        {
            _program = gfx::Graphics::CreateShader("~/shaders/gui/gui-shader.shdr");
            if ( _program != nullptr)
            {
                _program->Enable();
                //_unif_projection = _program->GetUniform("SineDistOffset");
                //_unif_projection = _program->GetUniform("SineDistColor");
                //_unif_projection = _program->GetUniform("SineDistShadow");
                //_unif_projection = _program->GetUniform("Projection");
                _program->Disable();
                return true;
            }
        }
        return false;
    }
    void GUITheme::Unbind()const
    {
        _program->Disable();
    }
    void GUITheme::Bind()const
    {
        _program->Enable();
    }
    
    GUITheme::~ GUITheme(){}
    GUITheme::GUITheme()
    :   gfx::Material( 0 )
    {}
}}
