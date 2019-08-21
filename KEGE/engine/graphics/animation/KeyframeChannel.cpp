//
//  KeyframeAnimation.cpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/23/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "KeyframeChannel.hpp"
namespace kege{namespace gfx{
    
    cg::uint KeyframeChannel::GetNextKeyIndex(double time)
    {
        for (int i=1; i<keys.size(); i++)
            if (time <= keys[i].time )
                return i;
        return -1;
    }
    
    void KeyframeChannel::SetKeyframeTransform(const Transform& a, const Transform& b, float t)
    {
        transf.translation = cg::lerp(a.translation, b.translation, t);
        transf.rotation = cg::slerp(a.rotation, b.rotation, t);
        transf.scale = cg::lerp(a.scale, b.scale, t);
    }
    
    void KeyframeChannel::Update(double time)
    {
        if (keys.empty()) return;
        cg::uint n = GetNextKeyIndex(time) % keys.size();
        if (n <= 0) return;
        cg::uint m = (n-1);
        double   t = (time - keys[m].time) / (keys[n].time - keys[m].time);
        SetKeyframeTransform(keys[m].transf, keys[n].transf, t);
    }
    
    KeyframeChannel::KeyframeChannel()
    {}
}}
