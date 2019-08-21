//
//  LoadGLSL.hpp
//  dev0
//
//  Created by Kenneth Esdaile on 10/14/17.
//  Copyright © 2017 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef LoadGLSL_hpp
#define LoadGLSL_hpp
#include <stdio.h>
#include <iostream>
#include "string.hpp"
#include "charlist.hpp"
#include "dlist.hpp"
#include "BufferReader.hpp"
#include "VFS.hpp"
namespace kege{namespace core{

    class ShaderVars
    {
    public:
        
        struct Variable
        {
            ds::string type;
            ds::string id;
            int value;
        };
        typedef ds::dlist<Variable> ShaderVarList;
        
        struct ShaderObject
        {
            ds::string definition;
            ShaderVarList members;
        };
        typedef ds::dlist<ShaderObject> ShaderObjects;
        
        ShaderVarList uniform_variables;
        ShaderVarList uniform_blocks;
        ShaderVarList attributes;
        ShaderObjects objects;
        bool subroutine;
        int target;
    };
    
    bool LoadGLSL(ds::string& data, ShaderVars* vars, ds::string const& filename);
}}
#endif /* LoadGLSL_hpp */
