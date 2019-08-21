/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/23/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ADSEffect.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef ADSEffect_hpp
#define ADSEffect_hpp
#include "../../../graphics/core/cgmath/cgm.hpp"
namespace kege{namespace gfx{
    
    class ADSEffect
    {
    public:
        
        virtual void SetSpecular(cg::vec4 const& spec){specular = spec;}
        virtual void SetAmbient(cg::vec4 const& ambi){ambient = ambi;}
        virtual void SetDiffuse(cg::vec4 const& diff){diffuse = diff;}
        
        virtual void SetTxtrScale(float val){txtr_scale = val;}
        virtual void SetShininess(float val){shininess = val;}
        virtual void SetDensity(float val){density = val;}
        virtual void SetAlpha(float val){alpha = val;}
        
        inline cg::vec4 const& GetSpecular()const{return specular;}
        inline cg::vec4 const& GetAmbient()const{return ambient;}
        inline cg::vec4 const& GetDiffuse()const{return diffuse;}
        
        inline cg::vec4& GetSpecular(){return specular;}
        inline cg::vec4& GetAmbient(){return ambient;}
        inline cg::vec4& GetDiffuse(){return diffuse;}
        
        inline float GetTxtrScale()const{return txtr_scale;}
        inline float GetShininess()const{return shininess;}
        inline float GetDensity()const{return density;}
        inline float GetAlpha()const{return alpha;}
        
        virtual ~ ADSEffect(){}
        
    protected:
        
        cg::vec4 specular;
        cg::vec4 ambient;
        cg::vec4 diffuse;
        
        float txtr_scale;
        float shininess;
        float density;
        float alpha;
    };
}}

namespace kege{namespace shared{
    typedef mem::shared< gfx::ADSEffect > ADSEffect;
}}
#endif /* ADSEffect_hpp */
