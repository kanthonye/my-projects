//
//  SkeletalAnimator.hpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/29/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef SkeletalAnimator_hpp
#define SkeletalAnimator_hpp
#include "Component.hpp"
#include "SkeletalAnimation.hpp"
namespace kege{namespace gfx{
    
    class SkeletalAnimator : public gfx::Component
    {
    public:
        
        void Update(kege::Scene& scene, float delta_ms);
        void Add(gfx::SkeletalAnimation* animation);
        void Play(const ds::string& name);
        
        SkeletalAnimator(const shared::Skeleton& skeleton, gfx::SkeletalAnimation* animation);
        ~ SkeletalAnimator();
        SkeletalAnimator();
        
        ds::dlist<gfx::SkeletalAnimation*> animations;
        ds::queue<gfx::SkeletalAnimation*> animque;
        shared::Skeleton skeleton;
    };
}}
#endif /* SkeletalAnimator_hpp */
