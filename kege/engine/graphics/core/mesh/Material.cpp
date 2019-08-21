/*! @author     Kenneth Anthony Esdaile
 *  @date       created on 10/24/15
 *  @copyright  Copyright (c) 2016 kae. All rights reserved.
 *  @file       Material.cpp
 *  @project    kege engine. */
#include "../../../graphics/core/mesh/Material.hpp"
namespace kege{namespace gfx{

    void Material::ApplyLights(const gfx::ArrayLights& lights)const
    {
        if ( !lights.empty() )
        {
            const core::UBO* ubo = GetShader()->GetUBO("SKELETON");
            if (ubo == nullptr)
            {
                gfx::Light::Data* m = (gfx::Light::Data*) ubo->BeginBufferWrite();
                if (m != nullptr)
                {
                    memcpy( m, lights.data(), sizeof(gfx::Light::Data)*4 );
                    ubo->EndBufferReadWrite();
                }
            }
            GetShader()->SetInt("LightCount", (int) lights.size() );
        }
    }
    
    void Material::SetReflectLight(bool value)
    {
        _reflect_light = value;
    }
    bool Material::ReflectLight()const
    {
        return _reflect_light;
    }
    
    Material::Material(cg::uint type)
    :   _type( type )
    ,   _reflect_light(true)
    {
    }
    
    Material::~ Material()
    {}
}}
