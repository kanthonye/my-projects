//
//  SkeletalAnimation.cpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/29/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "SkeletalAnimation.hpp"
namespace kege{namespace gfx{
    
    gfx::KeyframeChannel* SkeletalAnimation::GetChannel(const ds::string& target)
    {
        for (int i=0; i<channels.size(); i++)
        {
            if (target == channels[i].target )
            {
                return &channels[i];
            }
        }
        return nullptr;
    }
    
    void SkeletalAnimation::Update(double time)
    {
        if (channels.empty()) return;
        _time += time * _speed;
        while (_time > _length)
        {
            _time -= _length;
        }
        for (int i=0; i<channels.size(); i++)
        {
            channels[i].Update(_time);
        }
    }
    
    SkeletalAnimation::SkeletalAnimation(int size)
    :   _length(1.0)
    ,   _speed(0.125)
    ,   _time(0.0)
    {
        channels.resize(size);
    }
    
    SkeletalAnimation::SkeletalAnimation()
    :   _length(1.0)
    ,   _speed(0.125)
    ,   _time(0.0)
    {}
}}
