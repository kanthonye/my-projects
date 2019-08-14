//
//  LibraryShader.cpp
//  AppDev
//
//  Created by Kenneth Esdaile on 6/14/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//
#include "Logger.hpp"
#include "enumtypes.hpp"
#include "BufferReader.hpp"
#include "../../graphics/framework/GFXEnum.hpp"
#include "../../graphics/framework/LoadSHDR.hpp"
namespace kege{namespace gfx{
   
    ds::string GetShaderName(BufferReader& reader)
    {
        char name[64];
        reader.read(name, 64, "\b\n\t\r");
        return name;
    }
    
    bool FileIsSHDR(BufferReader& reader)
    {
        reader.skip("\b \n\t\r");
        if (reader != "#DEFINE")
        {
            return false;
        }
        
        reader.skip("#DEFINE\b \n\t\r");
        if (reader != "SHDR")
        {
            return false;
        }
        reader.skip("SHDR\b \n\t\r");
        return true;
    }
    
    std::pair<int,ds::string> GetShaderFile(kege::BufferReader& reader)
    {
        int target = -1;
        reader.skip("@f\b \n\t\r");
        char name[128];
        reader.read(name, 64, "\b \n\t\r");
        if      (strcmp(name,          "VERTEX_SHADER") == 0) target = gfx::SHADER_VERTEX;
        else if (strcmp(name,        "FRAGMENT_SHADER") == 0) target = gfx::SHADER_FRAGMENT;
        else if (strcmp(name,        "GEOMETRY_SHADER") == 0) target = gfx::SHADER_GEOMETRY;
        else if (strcmp(name, "TESS_EVALUATION_SHADER") == 0) target = gfx::SHADER_TESS_EVAL;
        else if (strcmp(name,    "TESS_CONTROL_SHADER") == 0) target = gfx::SHADER_TESS_CTROL;
        else if (strcmp(name,                 "CONFIG") == 0) target = 200;
        
        reader.skip("\b \n\t\r");
        reader.read(name, 128, "\b\n\t\r");
        return std::pair<int,ds::string>(target, name);
    }
    
    bool LoadSHDR(SHDR& shaders, ds::string const& filename)
    {
        BufferReader reader = BufferReader( kege::VFS::GetInstance().OpenFile(filename) );
        if (reader.eof())
        {
            KEGE_ERROR("reading file (%s).", filename.c_str());
            return false;
        }
        if ( !FileIsSHDR(reader) )
        {
            return false;
        }
        
        shaders[ENUM::_STRING] = GetShaderName(reader);
        while (!reader.eof())
        {
            if (reader == "@f")
            {
                std::pair<int,ds::string> file = GetShaderFile(reader);
                shaders[file.first] = file.second;
            }
            else if(reader == "#ENDDEF")
            {
                break;
            }
            else
            {
                if (reader.seek("\n") < 0)
                    break;
                reader.skip("\b \n\t\r");
            }
        }
        return true;
    }
}}



