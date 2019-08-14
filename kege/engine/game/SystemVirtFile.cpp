//
//  SystemVirtFile.cpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 4/23/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "SystemVirtFile.hpp"
namespace kege{
    
    
    kege::VFS* SystemVirtFile::GetVFS()
    {
        return &kege::VFS::GetInstance();
    }
    
    void SystemVirtFile::Update(double time_delta)
    {}
    
    void SystemVirtFile::UnInit()
    {
        _init = false;
        kege::VFS::GetInstance().Clear();
    }
    bool SystemVirtFile::Init()
    {
        if (_init) return _init;
        
        if (kege::VFS::GetInstance().Load("/Users/kanthonye/Projects/KEGE/dev-kege/dev-kege/kege/assets/virdir/virdir.xml"))
        {
            _init = true;
        }
        return _init;
    }
    SystemVirtFile::SystemVirtFile( kege::GameEngine* engine )
    :   kege::CoreSystem("SystemVirtFile", engine)
    {}
}
