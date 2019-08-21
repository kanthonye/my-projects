//
//  LoaderTXT.cpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 2/19/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//
#include "LoaderTXT.hpp"
namespace kege{
    
    ds::string LoadTxtFile(const ds::string& filename)
    {
        FILE * file = fopen(filename.c_str(), "r");
        if (!file)
        {
            fprintf(stderr,"error: LoadXML(%s) file not found.\n",filename.c_str());
            return ds::string();
        }
        
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        rewind(file);
        
        if (size == 0)
        {
            return ds::string();
        }
        
        char* data = new char[size+1];
        fread(data, size, sizeof(char), file);
        data[size] = '\0';
        
        return ds::string(data, size);
    }
}
