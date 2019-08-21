//======================================================================
//  Author  : Kenneth A Esdaile
//  Date    : Created on 5/22/16.
//  Title   : ColladaAnimations.hpp
//  Project : KEGE
//======================================================================
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//======================================================================
#include "Collada.hpp"
#include "ColladaAnimations.hpp"
namespace kege{namespace dae{
    
    kege::XML* ColladaAnimations::GetSamplerOutputSource(kege::XML* animation, kege::XML* sampler)
    {
        kege::XML* input = sampler->GetChildByAttr("semantic", "OUTPUT");
        return GetInputSource(animation, input);
    }
    
    kege::XML* ColladaAnimations::GetSamplerInputSource(kege::XML* animation, kege::XML* sampler)
    {
        kege::XML* input = sampler->GetChildByAttr("semantic", "INPUT");
        return GetInputSource(animation, input);
    }
    
    kege::XML* ColladaAnimations::GetSamplerLerpSource(kege::XML* animation, kege::XML* sampler)
    {
        kege::XML* input = sampler->GetChildByAttr("semantic", "INTERPOLATION");
        return GetInputSource(animation, input);
    }
    
    kege::XML* ColladaAnimations::GetSampler(kege::XML* animation)
    {
        return animation->GetChild("sampler");
    }
    
    float ColladaAnimations::ToKeyframeChannel(gfx::KeyframeChannel* channel, kege::XML* animation)
    {
        if (animation == nullptr) return 0;
        
        kege::XML* sampler = GetSampler(animation);
        if (sampler == nullptr) return 0;
        
        kege::XML* output_source = GetSamplerOutputSource(animation, sampler);
        kege::XML* input_source = GetSamplerInputSource(animation, sampler);
        if (output_source == nullptr) return 0;
        if (input_source == nullptr) return 0;
        
        core::DataBuffer<float> input = ToVertexBuffer(input_source);
        core::DataBuffer<float> output = ToVertexBuffer(output_source);
        
        channel->target = GetChannelTarget(animation);
        channel->keys.resize(input.size());
        
        cg::mat44 *m = (cg::mat44*) output.getdata();
        gfx::Keyframe* frame;
        float length = 0;
        
        for(int i=0; i<input.size(); i++)
        {
            frame = &channel->keys[i];
            frame->time = *input[i];
            frame->transf.rotation = cg::transpose( m[i] );
            frame->transf.translation.x = m[i].m03;
            frame->transf.translation.y = m[i].m13;
            frame->transf.translation.z = m[i].m23;
            if (length < frame->time) length = frame->time;
        }
        return length;
    }
    
    ds::string ColladaAnimations::GetChannelTarget(kege::XML* animation)
    {
        kege::XML* chan = animation->GetChild("channel");
        kege::XML::attrib* target = chan->GetAttr("target");
        return strtok(target->value.getdata(), "/");
    }
    
    gfx::SkeletalAnimation* ColladaAnimations::GetAnimation()
    {
        int n = 0;
        float length;
        int size = (int) animations->Elements().count();
        gfx::SkeletalAnimation* skel_anim = new gfx::SkeletalAnimation(size);
        skel_anim->_length = 0;
        for (kege::XML::iterator i=animations->Begin(); i!=nullptr; i++)
        {
            length = ToKeyframeChannel(&skel_anim->channels[n++], i.element());
            if (skel_anim->_length < length)
            {
                skel_anim->_length = length;
            }
        }
        return skel_anim;
    }
}}


