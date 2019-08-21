//
//  KeyframeAnimation.hpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/23/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef KeyframeChannel_hpp
#define KeyframeChannel_hpp
#include "string.hpp"
#include "array.hpp"
#include "dlist.hpp"
#include "queue.hpp"
#include "Transform.hpp"
#include "Animation.hpp"
namespace kege{namespace gfx{
   
    struct Keyframe
    {
        gfx::Transform transf;
        float time;
    };
    
    class KeyframeChannel
    {
    public:

        void SetKeyframeTransform(const Transform& a, const Transform& b, float t);
        cg::uint GetNextKeyIndex(double time);
        void Update(double time);
        
        ~KeyframeChannel(){}
        KeyframeChannel();
        
        ds::array< gfx::Keyframe > keys;
        gfx::Transform transf;
        ds::string target;
    };
}}
#endif /* KeyframeAnimation_hpp */
