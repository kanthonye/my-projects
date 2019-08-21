/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/25/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       SkydomeMaterial.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#include "Graphics.hpp"
#include "SkydomeMaterial.hpp"
namespace kege{namespace gfx{
    
    void SkydomeMaterial::SetUpperSkyColor( const cg::vec4& value )
    {
        colors[1] = value;
    }
    void SkydomeMaterial::SetLowerSkyColor( const cg::vec4& value )
    {
        colors[0] = value;
    }
    const cg::vec4& SkydomeMaterial::GetUpperSkyColors() const
    {
        return colors[1];
    }
    const cg::vec4& SkydomeMaterial::GetLowerSkyColors() const
    {
        return colors[0];
    }
    
    const shared::Shader& SkydomeMaterial::GetShader()const
    {
        return _shader;
    }
    shared::Shader& SkydomeMaterial::GetShader()
    {
        return _shader;
    }
    
    bool SkydomeMaterial::Init()
    {
        SetReflectLight( false );
        if ( _shader == nullptr)
        {
            _shader = gfx::Graphics::CreateShader("~/shaders/sky/sky-shader.shdr");
            if ( _shader == nullptr) return false;
            _shader->Disable();
            
            kege::image8i image = kege::open_image("seamless-stars.tga");
            if( !image.empty() )
            {
                core::Texture2D* texture = gfx::Graphics::CreateTexture2D();
                texture->Create(image, false, core::REPEAT, core::LINEAR_FILTER);
                _texture = texture;
            }
            return true;
        }
        return false;
    }
    
    void SkydomeMaterial::Unbind()const
    {
        _shader->Disable();
    }
    
    void SkydomeMaterial::Bind()const
    {
        gfx::Graphics::DisableBlending();
        gfx::Graphics::SetBackgroundColor( colors[1] );
        
        _shader->Enable();
        _shader->SetUBO("SKY", sizeof(cg::vec4)*2, colors);
        
        if ( _texture != nullptr )
        {
            _texture->SetBindingPoint( 0 );
            _texture->Bind();
        }
    }
    
    SkydomeMaterial::SkydomeMaterial(void)
    :   gfx::Material( kege::ENUM::_SCENE_SKY )
    {
        colors[0] = cg::color( 30, 233, 255, 255 ); // sky_color
        colors[1] = cg::color(  0, 100, 255, 255 ); // sea_color
        Init();
    }
    
    shared::Shader SkydomeMaterial::_shader;
}}

