//
//  LoaderMTL.cpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 2/18/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//
#include "shared.hpp"
#include "VFS.hpp"
#include "LoaderMTL.hpp"

namespace kege{
    
    const char * LoaderMTL::SetColor(float* a, const char * str, const char * flags)
    {
        char * token = strtok(nullptr, flags);
        if (token != nullptr) a[0] = atof(token);
        
        token = strtok(nullptr, flags);
        if (token != nullptr) a[1] = atof(token);
        
        token = strtok(nullptr, flags);
        if (token != nullptr) a[2] = atof(token);
        
        return str;
    }
    
    gfx::MaterialProperty* LoaderMTL::Load(kege::ResourceManager* manager, const ds::string& filename)
    {
        ds::string buffer = kege::LoadTxtFile(filename);
        if (buffer.empty()) return nullptr;
        
        directory = filename.parse_fpath();
        const char * sp = buffer.getdata();
        
        char name[128];
        
        gfx::MaterialProperty* material = nullptr;
        
        while (*sp != 0)
        {
            if (kege::string_equal(sp, "newmtl"))
            {
                sp = kege::str_skipword(sp);
                kege::str_cpyf(name, sp, " ");
                
                
                material = _manager->Add< gfx::MaterialProperty >( name ).rawptr();
                material->SetEmission(cg::vec4(0.0));
                
                sp = kege::str_newln(sp);
            }
            
            if (*sp == 'K')
            {
                if (sp[1] == 'a')
                {
                    SetColor(material->GetAmbient().rgb, sp, " Ka\n\r\t");
                    material->GetAmbient().a = 1.0;
                }
                if (sp[1] == 'd')
                {
                    SetColor(material->GetDiffuse().rgb, sp, " Ka\n\r\t");
                    material->GetDiffuse().a = 1.0;
                }
                if (sp[1] == 's')
                {
                    SetColor(material->GetSpecular().rgb, sp, " Ka\n\r\t");
                    material->GetSpecular().a = 1.0;
                }
                if (sp[1] == 'e')
                {
                    SetColor(material->GetEmission().rgb, sp, " Ka\n\r\t");
                    material->GetEmission().a = 1.0;
                }
            }
            
            if (*sp == 'N')
            {
                if (sp[1] == 'i')
                {
                    sp = kege::str_skipword(sp);
                }
                else
                {
                }
            }
            
            if (*sp == 'd')
            {
                sp = kege::str_skipword(sp);
            }
            
            if (kege::string_equal(sp, "illum"))
            {
                sp = kege::str_skipword(sp);
            }
            
            if (kege::string_equal(sp, "map"))
            {
                if (sp[4] == 'K')
                {
                    if (sp[5] == 'a')
                    {
                        kege::str_cpyf(name, sp, " ");
                        // ?!!!: material->GetDiffmap().SetFilename(directory + name);
                    }
                    if (sp[5] == 'd')
                    {
                        kege::str_cpyf(name, sp, " ");
                        // ?!!!: material->GetDiffmap().SetFilename(directory + name);
                    }
                    if (sp[5] == 's')
                    {
                        kege::str_cpyf(name, sp, " ");
                        // ?!!!: material->GetMixmap().SetFilename(directory + name);
                    }
                    if (sp[5] == 'e')
                    {
                        kege::str_cpyf(name, sp, " ");
                        // ?!!!: material->GetEmismap().SetFilename(directory + name);
                    }
                }
            }
            
            sp = kege::str_newln(sp);
        }
        return material;
    }
    
    LoaderMTL::LoaderMTL()
    :   kege::ResourceLoader< gfx::MaterialProperty >( "mtl" )
    {}
}
