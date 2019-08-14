//
//  LoadGLSL.cpp
//  dev0
//
//  Created by Kenneth Esdaile on 10/14/17.
//  Copyright © 2017 Kenneth Anthony Esdaile. All rights reserved.
//
#include "BufferReader.hpp"
#include "LoadGLSL.hpp"
namespace kege{namespace gfx{
    
    void ParseShaderLayout(ShaderVars* vars, kege::BufferReader& reader)
    {
        char tok[64];
        reader.seek("(");
        reader.skip("(\b \t\n\r");
        if (reader.strcmp("location"))
        {
            reader.skip("location\b \t\n\r");
            if (reader.strcmp("="))
            {
                reader.skip("\b=\" \t\n\r");
                reader.read(tok, 64, ") \"\n"); // tok = layout loacation value
                reader.seek(")");
                reader.skip(")\b \t\n\r");
                
                if (reader.strcmp("in"))
                {
                    ShaderVars::Variable& var = vars->attributes.push_back();
                    var.value = atoi(tok); // store layout loacation
                    
                    reader.skip("in");
                    reader.skip("\b \t\n\r");
                    reader.read(tok, 64, " \"\n");
                    var.type = tok;// TODO: store layout type
                    
                    reader.seek(" ");
                    reader.skip("\b \t\n\r");
                    reader.read(tok, 64, " ;\"\n");
                    var.id = tok;// TODO: store layout id
                }
            }
        }
        else
        {
            reader.seek(")");
            reader.skip("\b )\t\n\r");
            if (reader.strcmp("uniform")) // then its a uniform block
            {
                reader.skip("uniform\b \t\r");
                reader.read(tok, 64, " ;\n");
                ShaderVars::Variable& var = vars->uniform_blocks.push_back();
                var.value = -1;
                var.id = tok;
            }
        }
    }
    
    void ParseShaderUniform(ShaderVars* vars, kege::BufferReader& reader)
    {
        char tok[64];
        reader.skip("uniform");
        reader.skip("\b \t\n\r");
        reader.read(tok, 64, " \n");
        ShaderVars::Variable& var = vars->uniform_variables.push_back();
        var.type = tok;
        
        reader.seek(" ");
        reader.skip("\b \t\n\r");
        reader.read(tok, 64, " ;\n");
        var.id = tok;
        
        var.value = -1;
    }
    
    void ParseShaderStruct(ShaderVars* vars, kege::BufferReader& reader)
    {
        char tok[64];
        reader.skip("struct");
        reader.skip("\b \t\n\r");
        reader.read(tok, 64, " ;\n");
        reader.seek("{");
        reader.skip("\b {\t\n\r");
        
        ShaderVars::ShaderObject& object = vars->objects.push_back();
        object.definition = tok;
        
        while (!reader.strcmp("}"))
        {
            ShaderVars::Variable& var = object.members.push_back();
            
            reader.read(tok, 64, " }\n");
            var.type = tok;
            
            reader.skip("\b \t\n\r");
            reader.read(tok, 64, " ;}\n");
            var.id = tok;
            var.value = -1;
            
            reader.skip("\b \t\n\r");
        }
    }
    
    kege::ds::string makfname(const kege::ds::string& fname, const kege::ds::string& path)
    {   using namespace kege;
        if (path.empty())
        {
            return fname;
        }
        ds::string str = path;
        char *f = &str[str.length()-1];
        char *s = str.getdata();
        char *e = nullptr;
        while (*f!=0) f++;
        f--;
        e=f;
        for (const char* a=fname.c_str(); *a!=0; a++)
        {
            if (a[0] != '.' && a[1] != '.')
            {
                if (f[1] == '/')
                    f+=2;
                *f = 0;
                str.setlength(str.length() - (e-f+1));
                str.overwrtie(str.length(), strlen(a), a);
                return str;
            }
            a+=2;
            
            if (*f == '/') f--;
            while (*f != '/') f--;
            if (f - s != 0) f--;
            else
            {
                return a;
            }
        }
        return path;
    }
    
    void ParseShader(ShaderVars* vars,ds::charlist& charlist, ds::string const& filename)
    {
        kege::BufferReader reader = kege::VFS::GetInstance().OpenFile(filename);
        
        while ( !reader.eof() )
        {
            // (" //#-> ") is the include file tag. must include the connected file
            if ( reader.strcmp("//#->") )
            {
                char newfile_name[128];
                reader.skip("//#->\b \t\n\r");
                reader.read(newfile_name, 128, " \n");
                ds::string include_file = makfname(newfile_name, filename.parse_fpath());
                ParseShader(vars, charlist, include_file);
            }
            else if (vars)
            {
                int count = 0;
                kege::BufferReader r = reader;
                if (reader.strcmp("uniform "))
                {
                    ParseShaderUniform(vars, r);
                    count = int(r - reader);
                }
                else if (reader.strcmp("layout "))
                {
                    ParseShaderLayout(vars, r);
                    count = int(r - reader);
                }
                else if (reader.strcmp("struct "))
                {
                    ParseShaderStruct(vars, r);
                    count = int(r - reader);
                }
                else
                {
                    reader += charlist.append(*reader, "\n");
                    //reader.seek("\n");
                    //reader.skip("\n");
                }
                if (count > 0)
                {
                    charlist.append(*reader, count);
                    reader += count;
                }
            }
            else
            {
                charlist.append(*reader, "\n");
                reader.seek("\n");
                reader.skip("\n");
            }
        }
    }

    
    bool LoadGLSL(ds::string& data, ShaderVars* vars, ds::string const& filename)
    {
        ds::charlist charlist;
        ParseShader(vars, charlist, filename);
        data = charlist.toString();
        return false;
    }
}}



