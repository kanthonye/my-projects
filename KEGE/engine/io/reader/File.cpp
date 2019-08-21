//
//  File.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 1/28/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "File.hpp"
namespace kege{
    
    char* File::GetTok(const char* flags)
    {
        if (file == nullptr) return nullptr;
        int i=0;
        char* p = buffer;
        *p = 32;
        const char* f;
        while (*p!=0 && *p!='\n' && i<256)
        {
            f = flags;
            while (*f!=0 && *f!=*p && i<256)
            {
                *p++ = getc(file);
                i++;
            }
            if (*f==*p && i<256)
            {
                break;
            }
        }
        *p = 0;
        return buffer;
    }
    
    char* File::GetLine()
    {
        if (file == nullptr) return nullptr;
        if (buffer != nullptr)
        {
            
        }
        int i=0;
        char* p = buffer;
        *p = 32;
        while (*p != 0 && *p != '\n' && i<256)
        {
            *p++ = getc(file);
            i++;
        }
        *p = 0;
        return buffer;
    }
    
    int File::GetChar()
    {
        if (file == nullptr) return 0;
        return getc(file);
    }
    
    
    File& File::SetFilename(const ds::string& fname)
    {
        filename = fname;
        return *this;
    }
    
    ds::string File::LoadText()
    {
        if (filename.empty()) return ds::string();
        
        file = fopen(filename.c_str(), "rb");
        if (file == nullptr) return ds::string();
        
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        if (size <= 0) return ds::string();
        rewind(file);
        
        char* data = new char[size + 1];
        fread(data, sizeof(char), size, file);;
        data[size] = 0;
        
        return ds::string(data, size);
    }
    
    const ds::string& File::GetFilename()const
    {
        return filename;
    }
    
    File::File(const ds::string& filename)
    :   file(nullptr)
    {
        SetFilename(filename);
    }
    File::File(FILE* file, const ds::string& filename)
    :   file(file)
    ,   filename(filename)
    {}
    
    File::~ File()
    {
        if (file != nullptr) {
            fclose(file);
            file = nullptr;
        }
    }
    File::File()
    :   file(nullptr)
    {}
}
