/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/3/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GraphicsSystem.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GraphicsSystem_hpp
#define GraphicsSystem_hpp
#include "VFS.hpp"
#include "Mesh.hpp"
#include "image.hpp"
#include "Window.hpp"
#include "Graphics.hpp"
#include "Material.hpp"
#include "Skeleton.hpp"
#include "Texture2D.hpp"
#include "TextureCube.hpp"
#include "Shader.hpp"
#include "Gameobject.hpp"
#include "ResourceManager.hpp"
namespace kege{
    
    class GraphicsSystem
    {
    public:
        
        gfx::Gameobject* LoadGameobject(const ds::string& filename);
        kege::shared< gfx::Material > LoadMaterial(const ds::string& filename);
        kege::shared< gfx::Texture > LoadTexture(const ds::string& filename);
        kege::shared< gfx::Shader > LoadShader(const ds::string& filename);
        kege::shared< gfx::Mesh > LoadMesh(const ds::string& filename);
        
        ~ GraphicsSystem();
        GraphicsSystem();
        
    private:
        
        kege::ResourceManager _resmgr;
    };
}
#endif /* GraphicsSystem_hpp */
