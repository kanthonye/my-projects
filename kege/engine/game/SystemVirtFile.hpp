//
//  SystemVirtFile.hpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 4/23/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef SystemVirtFile_hpp
#define SystemVirtFile_hpp
#include "VFS.hpp"
#include "CoreSystem.hpp"
namespace kege{
    
    /**
     The @b SystemVirtFile is a @b SubSystem that is of the group @b DATA_STORAGE.
     this kind of system does not require update. It links file path to file names.
     */
    class SystemVirtFile : public kege::CoreSystem
    {
    public:
        
        kege::VFS* GetVFS();
        
        void Update(double time_delta);
        void UnInit();
        bool Init();
        
        SystemVirtFile( kege::GameEngine* engine );
    };
}
#endif /* SystemVirtFile_hpp */
