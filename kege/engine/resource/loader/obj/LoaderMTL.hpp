//
//  LoaderMTL.hpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 2/18/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef LoaderMTL_hpp
#define LoaderMTL_hpp
#include "MaterialProperty.hpp"
#include "Texture2D.hpp"
#include "ResourceManager.hpp"
#include "LoaderTXT.hpp"
#include "ResourceFramework.hpp"
namespace kege{
    
    class LoaderMTL :public kege::ResourceLoader< gfx::MaterialProperty >
    {
    public:
        
        static bool OBJLoadMaterialsLibrary(ds::slist<std::pair<ds::string, gfx::MaterialProperty*>>& material, const ds::string& filename);
        gfx::MaterialProperty* Load(kege::ResourceManager* manager, const ds::string& filename);
        gfx::MaterialProperty* Load(kege::ResourceManager* manager, FILE* file);
        const char * SetColor(float* ka, const char* str, const char* flags);
        LoaderMTL();
        
    private:
        
        ds::string directory;
    };
}

#endif /* LoaderMTL_hpp */
