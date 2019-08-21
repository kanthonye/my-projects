/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/25/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       SkydomeMaterial.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef SkydomeMaterial_hpp
#define SkydomeMaterial_hpp
#include "enumtypes.hpp"
#include "Material.hpp"
namespace kege{namespace gfx{
    
    class SkydomeMaterial : public gfx::Material
    {
    public:
        
        void SetUpperSkyColor( const cg::vec4& value );
        void SetLowerSkyColor( const cg::vec4& value );
        const cg::vec4& GetUpperSkyColors() const;
        const cg::vec4& GetLowerSkyColors() const;
        
        const shared::Shader& GetShader()const;
        shared::Shader& GetShader();
        
        void Unbind()const;
        void Bind()const;
        bool Init();
        
        SkydomeMaterial(void);
        
    private:
        
        static shared::Shader _shader;
        shared::Texture _texture;
        cg::vec4 colors[2];
    };
}}
#endif /* SkydomeMaterial_hpp */
