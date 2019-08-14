//
//  LoggingSystem.hpp
//  AppDev
//
//  Created by Kenneth Esdaile on 8/5/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef __LOG__
#define __LOG__
#ifndef SafeDelete
#define SafeDelete(p){ if(p){delete p; p=nullptr;} }
#endif
#ifndef SafeDeleteArray
#define SafeDeleteArray(p){ if(p){delete []p; p=nullptr;} }
#endif
#include <map>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include "string.hpp"
#include "slist.hpp"
namespace kege{
    class Logger;

    class Log
    {
        void WriteMsg(const ds::string& type);
        
    public:
        
        void SetFile(ds::string const& filename);
        void SetFile(FILE* file);
        
        ds::string const& GetFilename();
        FILE* GetFile();
        
        void Msg(char const* format, ...);
        
        
        Log(ds::string const& filename);
        ~ Log();
        Log();
        
    private:
        
        friend Logger;
        ds::string filename;
        ds::string type;
        FILE * file;
        bool active;
    };
    
    class Logger
    {
    public:
        
        kege::Log& operator [](ds::string const& name);
        static kege::Logger log;
        
        ~ Logger();
        Logger();
        
    private:
        
        std::map<long, kege::Log> logs;
    };
#define kegeLOG kege::Logger::log
#define KEGE_ERROR kege::Logger::log["ERROR"].Msg
#define KEGE_INFO kege::Logger::log["INFO"].Msg
#define KEGE_WARN kege::Logger::log["WARNING"].Msg
}
#endif /* __LOG__ */
