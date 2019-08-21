/*! @author     Kenneth Esdaile
 *  @date       created on 4/30/17
 *  @copyright    Copyright © 2017 Kenneth Anthony Esdaile. All rights reserved.
 *  @file       ResourceManager.cpp
 *  @project    entity */
#include "ResourceManager.hpp"
namespace kege{

    void kege::ResourceManager::Terminate()
    {
        CoreResources::Iterator rn;
        kege::itemmap< long, CoreResources>::iterator rm;
        for (rm=_resources.begin(); rm!=_resources.end(); rm++)
        {
            for (rn=rm->second.begin(); rn!=nullptr; rn++)
            {
                delete rn.element().v;
            }
            rm->second.clear();
        }
        _resources.clear();
        
        CoreLoaders::Iterator ln;
        kege::itemmap< long, CoreLoaders>::iterator lm;
        for (lm=_loaders.begin(); lm!=_loaders.end(); lm++)
        {
            for (ln=lm->second.begin(); ln!=nullptr; ln++)
            {
                delete ln.element().v;
            }
            lm->second.clear();
        }
        _loaders.clear();
    }
    
    kege::ResourceManager::~ ResourceManager()
    {
        Terminate();
    }
}


