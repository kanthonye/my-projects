/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/23/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       MaterialProperty.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef MaterialProperties_hpp
#define MaterialProperties_hpp
#include "cgm.hpp"
namespace kege{namespace gfx{
    
    class MaterialProperty
    {
    public:
        
        virtual void SetSpecular(cg::vec4 const& spec){specular = spec;}
        virtual void SetEmission(cg::vec4 const& emis){emission = emis;}
        virtual void SetAmbient(cg::vec4 const& ambi){ambient = ambi;}
        virtual void SetDiffuse(cg::vec4 const& diff){diffuse = diff;}
        
        virtual void SetTxtrScale(float val){txtr_scale = val;}
        virtual void SetShininess(float val){shininess = val;}
        virtual void SetDensity(float val){density = val;}
        virtual void SetAlpha(float val){alpha = val;}
        
        inline cg::vec4 const& GetSpecular()const{return specular;}
        inline cg::vec4 const& GetEmission()const{return emission;}
        inline cg::vec4 const& GetAmbient()const{return ambient;}
        inline cg::vec4 const& GetDiffuse()const{return diffuse;}
        
        inline cg::vec4 & GetSpecular(){return specular;}
        inline cg::vec4 & GetEmission(){return emission;}
        inline cg::vec4 & GetAmbient(){return ambient;}
        inline cg::vec4 & GetDiffuse(){return diffuse;}
        
        inline float GetTxtrScale()const{return txtr_scale;}
        inline float GetShininess()const{return shininess;}
        inline float GetDensity()const{return density;}
        inline float GetAlpha()const{return alpha;}
        
        virtual ~ MaterialProperty(){}
        
    protected:
        
        cg::vec4 specular;
        cg::vec4 emission;
        cg::vec4 ambient;
        cg::vec4 diffuse;
        
        float txtr_scale;
        float shininess;
        float density;
        float alpha;
    };
    
    typedef kege::shared<gfx::MaterialProperty> SharedMaterialProperty;
}}
#endif /* MaterialProperties_hpp */
