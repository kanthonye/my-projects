/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/23/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ObjectMaterial.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "Graphics.hpp"
#include "Enumerator.hpp"
#include "ObjectMaterial.hpp"
namespace kege{namespace gfx{
    
    void ObjectMaterial::SetProperty(const SharedMaterialProperty &property)
    {
        _property = property;
    }
    void ObjectMaterial::SetTexture(const SharedMaterialTexture& texture)
    {
        _texture = texture;
    }
    SharedMaterialProperty ObjectMaterial::GetProperty()
    {
        return _property;
    }
    SharedMaterialTexture ObjectMaterial::GetTexture()
    {
        return _texture;
    }
    
    const SharedShader& ObjectMaterial::GetShader()const
    {
        return _shader;
    }
    SharedShader& ObjectMaterial::GetShader()
    {
        return _shader;
    }
    
    void ObjectMaterial::ApplyModelMatrix(const cg::mat44& transform) const
    {
        _shader->SetMat44f( "ModelMatrix", transform.data );
    }
    void ObjectMaterial::SetLightCount(int count) const
    {
        _shader->SetInt( "LightCount", count );
    }
    
    bool ObjectMaterial::Init()
    {
        if ( _shader == nullptr )
        {
            _shader = gfx::Graphics::CreateShader("~/shaders/entity/entity-shader.shdr");
        }
        return _shader != nullptr;
    }
    
    void ObjectMaterial::Unbind()const
    {
        _shader->Disable();
    }
    
    void ObjectMaterial::Bind()const
    {
        _shader->Enable();
        
        if (_property != nullptr)
        {
            _shader->SetVec4f( "Material.diffuse",  _property->GetDiffuse().rgba );
            _shader->SetVec4f( "Material.specular", _property->GetSpecular().rgba );
            _shader->SetVec4f( "Material.ambient",  _property->GetAmbient().rgba );
            _shader->SetVec4f( "Material.emission", _property->GetEmission().rgba );
            _shader->SetFloat( "Material.shininess",_property->GetShininess() );
            _shader->SetFloat( "Material.density",  _property->GetDensity() );
            _shader->SetFloat( "Material.alpha",    _property->GetAlpha() );
        }
        
        if ( _texture != nullptr )
        {
            _texture->Bind();
        }
    }
    
    ObjectMaterial::ObjectMaterial
    (   SharedMaterialProperty property
     ,  SharedMaterialTexture texture  )
    :   gfx::Material( kege::GlobalEnum::Get("ObjectMaterial") )
    ,   _property(property)
    ,   _texture(texture)
    {}
    
    ObjectMaterial::ObjectMaterial(const gfx::ObjectMaterial& material)
    :   gfx::Material( kege::GlobalEnum::Get("ObjectMaterial") )
    ,   _property(material._property)
    ,   _texture(material._texture)
    {
        Init();
    }
    
    ObjectMaterial::ObjectMaterial(void)
    :   gfx::Material( kege::GlobalEnum::Get("ObjectMaterial") )
    {
        Init();
    }
    
    SharedShader ObjectMaterial::_shader = nullptr;
}}

