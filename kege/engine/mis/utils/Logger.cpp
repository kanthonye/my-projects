//
//  LoggingSystem.cpp
//  AppDev
//
//  Created by Kenneth Esdaile on 8/5/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//

#include "Logger.hpp"
#include "charlist.hpp"
namespace kege{
    
    ds::string decode_string(va_list & list, ds::string const& format)
    {
        ds::charlist msg;
        unsigned count=0;
        const char *s = nullptr;
        const char *p = format.c_str();
        char buffer [33];
        
        while(*p!='\0' && count < format.length())
        {
            switch(*p)
            {
                case '%':{
                    count++;
                    switch(*++p)
                    {
                        case 'c':{
                            msg += va_arg(list, int);
                        }break;
                            
                        case 'i':{
                            sprintf(buffer, "%i", va_arg(list, int));
                            msg += buffer;
                        }break;
                            
                        case 'l':{
                            sprintf(buffer, "%li", va_arg(list, long));
                            msg += buffer;
                        }break;
                            
                        case 's':{
                            s = va_arg(list, char *);
                            if (s) msg += s;
                        }break;
                            
                        case 'f':{
                            sprintf(buffer, "%f", va_arg(list, double));
                            msg += buffer;
                        }break;
                            
                        default: msg += *p; break;
                    }break;
                }break;
                    
                default: msg += *p; break;
            }
            count++;
            p++;
        }
        va_end(list);
        return msg.toString();
    }
    
    ds::string GetStrTime()
    {
        time_t t = time(0);   // get time now
        struct tm * now = localtime( & t );
        int year  = now->tm_year + 1900;
        int month = now->tm_mon + 1;
        int day   = now->tm_mday;
        int hour  = now->tm_hour;
        int min   = now->tm_min;

        const char * pm_am;
        if (hour > 12) pm_am = "pm";
        else pm_am = "am";

        hour  = hour - 12;

        if (0 > hour) hour = -hour;
        char buf[64];
        sprintf(buf, "%d:%d:%s %d/%d/%d\n", hour, min, pm_am, year, month, day);
        return ds::string(buf);
    }
    
    void kege::Log::SetFile(ds::string const& filename)
    {
        this->filename = filename;
        SetFile( fopen(filename.c_str(), "w") );
    }
    void kege::Log::SetFile(FILE* file)
    {
        this->file = file;
    }
    
    ds::string const& kege::Log::GetFilename()
    {
        return filename;
    }
    FILE* kege::Log::GetFile()
    {
        return file;
    }
    
    void kege::Log::Msg(char const* format, ...)
    {
        char buffer [512];
        va_list argp;
        va_start(argp, format);
        vsprintf(buffer, format, argp);
        WriteMsg(buffer);
    }
    
    void AddSpacing(int spaces);
    void SubSpacing(int spaces);
    void SetSpacing(int spaces);
    bool FileIsLoaded();
    bool FileIsOpen();
    int  GetSpacing();
    
    

    void kege::Log::WriteMsg(const ds::string& msg)
    {
        if (file != nullptr)
        {
            fwrite(msg.c_str(), msg.length(), sizeof(char), file);
            fwrite("\n", 1, sizeof(char), file);
        }
        else
        {
            printf("[%s] : %s\n", type.c_str(), msg.c_str());
        }
    }
    
    
//    void kege::Log::AddSpacing(int s)
//    {
//        space += s;
//    }
//    void kege::Log::SubSpacing(int s)
//    {
//        space -= s;
//    }
//    void kege::Log::SetSpacing(int s)
//    {
//        space = s;
//    }
//    int kege::Log::GetSpacing()
//    {
//        return space;
//    }
    
    
    kege::Log::Log()
    :   file(nullptr)
    ,   active(false)
    {
    }
    
    kege::Log::Log(ds::string const& fname)
    :   file(nullptr)
    ,   active(false)
    {
        SetFile(filename);
    }
    
    kege::Log::~ Log( void )
    {
        fclose(file);
        file = nullptr;
    }
}


namespace kege{
    
    kege::Log& kege::Logger::operator [](ds::string const& name)
    {
        long key = name.hash();
        kege::Log& log = logs[key];
        if (log.active == false)
        {
            log.active = true;
            log.type = name;
        }
        return log;
    }
    
    Logger::Logger()
    {
    }
    
    Logger::~ Logger()
    {
        logs.clear();
    }
    kege::Logger Logger::log;
}


