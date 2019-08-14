/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/3/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GraphicsSystem.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "GraphicsSystem.hpp"
namespace kege{

    gfx::Gameobject* GraphicsSystem::LoadGameobject(const ds::string& filename)
    {
        
        return nullptr;
    }
    
    kege::shared< gfx::Shader > GraphicsSystem::LoadShader(const ds::string& filename)
    {
        ds::string fname = filename.parse_fname();
        kege::shared< gfx::Shader > shader = _resmgr.Get< gfx::Shader >( fname );
        if ( shader == nullptr )
        {
            return gfx::Graphics::CreateShader(filename);
        }
        return shader;
    }
    kege::shared< gfx::Material > GraphicsSystem::LoadMaterial(const ds::string& filename)
    {
        return nullptr;
    }
    
    kege::shared< gfx::Texture > GraphicsSystem::LoadTexture(const ds::string& filename)
    {
        return _resmgr.Load< gfx::Texture >( filename );
    }
    
    kege::shared< gfx::Mesh > GraphicsSystem::LoadMesh(const ds::string& filename)
    {
        ds::string fname = filename.parse_fname();
        kege::shared< gfx::Mesh > mesh = _resmgr.Get< gfx::Mesh >( fname );
        if ( mesh == nullptr )
        {
            _resmgr.Load< gfx::Mesh >( filename );
        }
        return mesh;
    }
    
    GraphicsSystem::~ GraphicsSystem()
    {
    }
    GraphicsSystem::GraphicsSystem()
    {
    }
}
