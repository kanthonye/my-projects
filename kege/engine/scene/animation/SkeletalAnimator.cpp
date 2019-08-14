//
//  SkeletalAnimator.cpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/29/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "SkeletalAnimator.hpp"
namespace kege{namespace gfx{
    
    void SkeletalAnimator::Update(kege::Scene& scene, float delta_ms)
    {
        if (animations.count() == 0) {
            return;
        }
        gfx::SkeletalAnimation* animation = animations.front();
        animation->Update(delta_ms);
        
        gfx::Joint* joint;
        for (int i=0; i<animation->channels.size(); i++)
        {
            joint = skeleton->GetJoint(animation->channels[i].target);
            joint->local = animation->channels[i].transf.GetMatrixTR();
        }
    }
    
    void SkeletalAnimator::Add(gfx::SkeletalAnimation* animation)
    {
        animations.push_back(animation);
        animque.push(animation);
    }
    
    SkeletalAnimator::SkeletalAnimator(const gfx::SharedSkeleton& skeleton, gfx::SkeletalAnimation* animation)
    :   gfx::EntityComponent(kege::ENUM::_SKELETAL_ANIMATOR)
    ,   skeleton(skeleton)
    {
        Add(animation);
    }
    
    SkeletalAnimator::~SkeletalAnimator()
    {
        for (ds::dlist<gfx::SkeletalAnimation*>::iterator i=animations.begin(); i!=nullptr; i++)
            delete i.element();
        animations.clear();
    }
    
    SkeletalAnimator::SkeletalAnimator()
    :   gfx::EntityComponent(kege::ENUM::_SKELETAL_ANIMATOR)
    ,   skeleton(nullptr)
    {}
}}
