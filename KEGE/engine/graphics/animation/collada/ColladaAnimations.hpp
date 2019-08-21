//======================================================================
//  Author  : Kenneth A Esdaile
//  Date    : Created on 5/22/16.
//  Title   : ColladaAnimations.hpp
//  Project : KEGE
//======================================================================
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//======================================================================
#ifndef ColladaAnimations_hpp
#define ColladaAnimations_hpp
#include "ColladaLibrary.hpp"
#include "SkeletalAnimator.hpp"
namespace kege{namespace dae{
    
    class ColladaAnimations : public dae::ColladaLibrary
    {
    public:
        
        kege::XML* GetSamplerOutputSource(kege::XML* animation, kege::XML* sampler);
        kege::XML* GetSamplerInputSource(kege::XML* animation, kege::XML* sampler);
        kege::XML* GetSamplerLerpSource(kege::XML* animation, kege::XML* sampler);
        kege::XML* GetSampler(kege::XML* animation);
        
        ds::string GetChannelTarget(kege::XML* animation);
        
        float ToKeyframeChannel(gfx::KeyframeChannel* channel, kege::XML* animation);
        gfx::SkeletalAnimation* GetAnimation();
        
        ColladaAnimations(kege::XML* a)
        :   animations(a)
        {}
        
    private:
        
        kege::XML* animations;
    };
}}
#endif /* ColladaAnimations */
