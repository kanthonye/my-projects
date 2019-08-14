//
//  SkeletalAnimation.hpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/29/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef SkeletalAnimation_hpp
#define SkeletalAnimation_hpp
#include <map>
#include "Skeleton.hpp"
#include "KeyframeChannel.hpp"
namespace kege{namespace gfx{
 
    class SkeletalAnimation
    {
    public:
        
        gfx::KeyframeChannel* GetChannel(const ds::string& target);
        void Update(double time);
        SkeletalAnimation(int size);
        SkeletalAnimation();
        
        ds::array<gfx::KeyframeChannel> channels;
        ds::string name;
        
        float _length;
        float _speed;
        float _time;
    };
}}
#endif /* SkeletalAnimation_hpp */
