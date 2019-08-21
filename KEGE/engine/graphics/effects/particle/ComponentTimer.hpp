//
//  EmissionTimer.hpp
//  dev0
//
//  Created by Kenneth A Esdaile on 9/12/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef ComponentTimer_hpp
#define ComponentTimer_hpp
#include "Component.hpp"
namespace kege{namespace gfx{
    
    /**
     * EmissionTimer is used to tell ParticleEmitter when to emit a particle.
     */
    class ComponentTimer : public gfx::Component
    {
    public:
        
        void HandleMessage(const kege::Message& message);
        void Update(float delta);
        
        void SetTimelength(unsigned short sec, unsigned short count);
        void SetTimelength(double sec);
        void SetRepeatable(bool rep);
        bool GetRepeatable()const;
        
        void Save(kege::XML& xml);
        
        ComponentTimer(unsigned short sec, unsigned short count);
        ~ ComponentTimer();
        ComponentTimer();
        
    private:
        
        //kege::Message msg;
        double timelength;
        double timespand;
        bool repeatable;
    };
}}
#endif /* EmissionTimer_hpp */
