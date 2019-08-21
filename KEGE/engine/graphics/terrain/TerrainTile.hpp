//
//  TerrainTile.hpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/20/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef TerrainTile_hpp
#define TerrainTile_hpp
#include "Mesh.hpp"
#include "image.hpp"
#include "image.hpp"
#include "Entity.hpp"
#include "Graphics.hpp"
namespace kege{namespace gfx{
    class TerrainSystem;
    class Terrain;
    
    class TerrainTile : public gfx::Entity
    {
    public:
        
        void GetQuadHeigh(float quad[6], double px, double pz)const;
        cg::vec4 GetHeightNormal(cg::point3 const& position)const;
        cg::vec4 GetHeightNormal(double px, double pz)const;
        float GetHeight(cg::point3 const& position)const;
        float GetHeight(double px, double pz)const;
        
        const kege::image<float>& GetHeightmap()const;
        kege::image<float>& GetHeightmap();
        
        shared::Texture& GetTangentmap();
        shared::Texture& GetNormalmap();
        
        TerrainTile(const ds::string& name, const cg::var2i& t, TerrainSystem* system);
        virtual ~ TerrainTile();
        TerrainTile();
        
    private:
        
        friend gfx::Terrain;
        
        kege::image< float > hmap;
        cg::int2 tcoord;
    };
}}
#endif /* TerrainTile_hpp */
