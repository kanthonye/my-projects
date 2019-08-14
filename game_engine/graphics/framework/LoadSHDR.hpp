//
//  LibraryShader.hpp
//  AppDev
//
//  Created by Kenneth Esdaile on 6/14/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef KEGE_LOAD_SHDR
#define KEGE_LOAD_SHDR
#include <map>
#include "VFS.hpp"
namespace kege{namespace gfx{
    
    typedef std::map<int, ds::string> SHDR;
    bool LoadSHDR(SHDR& shaders, ds::string const& filename);
}}
#endif /* LibraryShader_hpp */


