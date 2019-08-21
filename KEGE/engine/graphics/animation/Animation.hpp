//
//  Animation2D.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 2/16/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef Animation__hpp
#define Animation__hpp
#include "cgm.hpp"
#include "string.hpp"
namespace kege{ namespace gfx{
    
    class Animation
    {
    public:
        
        inline const ds::string& GetName() const {return name;};
        inline void  SetName(const ds::string& n) {name = n;};
        inline int   GetTotalFrames() const {return total_frame;}
        inline void  SetTotalFrames(int v) {total_frame = v;}
        inline int   GetFirstFrame() const {return first_frame;}
        inline void  SetFirstFrame(int f)  {first_frame = f;}
        inline int   GetLastFrame() const {return last_frame;}
        inline void  SetLastFrame(int v) {last_frame = v;}
        inline int   GetCurrFrame() const {return curr_frame;}
        inline void  SetCurrFrame(int v) {curr_frame = v;}
        inline int   GetNextFrame() const {return next_frame;}
        inline void  SetNextFrame(int v) {next_frame = v;}
        inline float GetFrameTime() const {return frame_time;}
        inline void  SetFrameTime(float v) {frame_time = v;}
        inline float GetAnimLength() const {return anim_length;}
        inline void  SetAnimLength(float v) {anim_length = v;}
        inline float GetAnimTime() const {return anim_time;}
        inline void  SetAnimTime(float v) {anim_time = v;}
        inline bool  GetRepeatable() const {return repeatable;}
        inline void  SetRepeatable(bool v) {repeatable = v;}
        inline bool  GetPlaying() const {return playing;}
        inline void  SetPlaying(bool v) {playing = v;}
        inline int   GetID() const {return id;}
        inline void  SetID(int v) {id = v;}
        
        void Animate(float dt);
        
        Animation(bool rep, int first_frame, int last_frame, float animlen);
        Animation();
        
    private:
        
        ds::string name;
        int   total_frame;
        int   first_frame;
        int   last_frame;
        int   curr_frame;
        int   next_frame;
        int   id;
        
        float frame_time;
        float anim_length;
        float anim_time;
        bool  repeatable;
        bool  playing;
    };
}}
#endif /* Animation2D_hpp */
