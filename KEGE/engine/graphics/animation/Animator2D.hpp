//
//  Animator2D.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 2/16/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef Animator2D_hpp
#define Animator2D_hpp
#include "dlist.hpp"
#include "Animation.hpp"
namespace kege{ namespace gfx{
    
    class Animator2D
    {
    public:
        
        void Play(const ds::string& name);
        void Play(int id);
        
        void Stop(const ds::string& name);
        void Stop(int id);
        
        void Add(gfx::Animation* anim);
        
        void Animate(float time);
        
    private:
        
        void Play(gfx::Animation* anim);
        
    private:
        
        ds::dlist<gfx::Animation*> animations;
        ds::dlist<gfx::Animation*> playlist;
    };
}}
#endif /* Animator2D_hpp */
