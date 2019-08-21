//
//  Animator2D.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 2/16/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "Animator2D.hpp"
namespace kege{ namespace gfx{
    
    
    void Animator2D::Play(const ds::string& name)
    {
        for (ds::dlist<gfx::Animation*>::iterator a=animations.begin(); a!=nullptr; a++)
        {
            if (a->GetName() == name)
            {
                Play(a.element());
                break;
            }
        }
    }
    void Animator2D::Play(int id)
    {
        for (ds::dlist<gfx::Animation*>::iterator a=animations.begin(); a!=nullptr; a++)
        {
            if (a->GetID() == id)
            {
                Play(a.element());
                break;
            }
        }
    }
    
    void Animator2D::Stop(const ds::string& name)
    {
        for (ds::dlist<gfx::Animation*>::iterator a=animations.begin(); a!=nullptr; a++)
        {
            if (a->GetName() == name)
            {
                a->SetPlaying(false);
                playlist.erase(a);
                break;
            }
        }
    }
    void Animator2D::Stop(int id)
    {
        for (ds::dlist<gfx::Animation*>::iterator a=playlist.begin(); a!=nullptr; a++)
        {
            if (a->GetID() == id)
            {
                a->SetPlaying(false);
                playlist.erase(a);
                break;
            }
        }
    }
    
    void Animator2D::Add(gfx::Animation* anim)
    {
        animations.push_back(anim);
    }
    
    void Animator2D::Play(gfx::Animation* anim)
    {
        if (anim->GetPlaying()) return;
        playlist.push_back(anim);
        anim->SetPlaying(true);
    }
    
    void Animator2D::Animate(float time)
    {
        int f;
        double u = 0;
        for (ds::dlist<gfx::Animation*>::iterator a=playlist.begin(); a!=nullptr; a++)
        {
            if (a->GetAnimLength() <= a->GetAnimTime())
            {
                if (!a->GetRepeatable())
                {
                    a->SetPlaying(false);
                    playlist.erase(a);
                    continue;
                }
                else
                {
                    a->SetAnimTime(a->GetAnimTime() - a->GetAnimLength());
                }
            }
            
            a->SetAnimTime(a->GetAnimTime() + time);
            u = a->GetAnimTime() / a->GetAnimLength();
            u = a->GetTotalFrames() * u;
            
            f = u;
            f = f % a->GetTotalFrames();
            
            a->SetCurrFrame(f);
            a->SetNextFrame((1 + f) % a->GetTotalFrames());
            a->SetFrameTime(u - double(f));
        }
    }
}}
