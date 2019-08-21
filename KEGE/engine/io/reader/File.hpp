//
//  File.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 1/28/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef File_hpp
#define File_hpp

#include <stdio.h>
#include "string.hpp"
namespace kege{
    class VFS;
    
    class File
    {
    public:
        
        File GetFileFromPath(const kege::ds::string& fname);
        File& SetFilename(const ds::string& filename);
        const ds::string& GetFilename()const;
        
        char* GetTok(const char* flags);
        char* GetLine();
        int GetChar();
        
        ds::string LoadText();
        
        File(FILE* file, const ds::string& filename);
        File(const ds::string& filename);
        ~ File();
        File();
        
    private:
        
        friend VFS;
        ds::string filename;
        char* buffer;
        FILE* file;
    };
}
#endif /* File_hpp */
