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
    
    void SkydomeMaterial::ApplyModelMatrix(const cg::mat44& transform) const
    {
        if (_unif_matrix == nullptr) return;
        _unif_matrix->SetMat44f( transform.data );
    }
    
    const gfx::SharedShader& SkydomeMaterial::GetShader()const
    {
        return _shader;
    }
    gfx::SharedShader& SkydomeMaterial::GetShader()
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
            
            kege::image8i image = kege::open_image("seamless-stars.tga");
            if( image.empty() ) return false;
            
            _shader->Enable();
            _unif_matrix = _shader->GetUniform("ModelMatrix");
            _shader->Disable();

            gfx::Texture2D* texture = gfx::Graphics::CreateTexture2D();
            texture->Create(image, false, gfx::REPEAT, gfx::LINEAR_FILTER);
            _texture = texture;
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
        Graphics::DisableBlending();
        _shader->Enable();
        
        if ( _texture != nullptr )
        {
            _texture->SetBindingPoint( 0 );
            _texture->Bind();
        }
    }
    
    SkydomeMaterial::SkydomeMaterial(void)
    :   gfx::Material( kege::ENUM::_SCENE_SKY )
    {
        Init();
    }
    
    SharedShader SkydomeMaterial::_shader;
}}

