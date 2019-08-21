//
//  TerrainTile.cpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/20/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "TerrainTile.hpp"
#include "TerrainSystem.hpp"
#include "Model.hpp"
namespace kege{namespace gfx{

    void gfx::TerrainTile::GetQuadHeigh(float quad[6], double px, double pz) const
    {
//        // convert position px and pz to tilecoord
//        float tx = (px - GetWorld().translation.x) / (float) _system->scale;
//        float tz = (pz - GetWorld().translation.z) / (float) _system->scale;
//        
//        if (tx < 0 || tz < 0 || hmap.width() < tx || hmap.height() < tz)
//        {
//            return;
//        }
//        
//        if (tx >= hmap.width() )
//        {
//            tx = hmap.width() - 2;
//        }
//        if (tz >= hmap.height())
//        {
//            tz = hmap.height() - 2;
//        }
//        
//        int gx = tx; // floor tx
//        int gz = tz; // floor tz
//        
//        quad[0] = tx - gx; // fractional part x, lerp value x
//        quad[1] = tz - gz; // fractional part z, lerp value z
//        
//        quad[2] = *hmap(gx  , gz);
//        quad[3] = *hmap(gx+1, gz);
//        quad[4] = *hmap(gx  , gz+1);
//        quad[5] = *hmap(gx+1, gz+1);
    }
    
    cg::vec4 gfx::TerrainTile::GetHeightNormal(cg::point3 const& position) const
    {
        float quad[6];
        GetQuadHeigh(quad, position.x, position.z);
        
        float rl = cg::lerp(quad[2], quad[3], quad[0]);
        float tb = cg::lerp(quad[4], quad[5], quad[0]);
        float h  = cg::lerp(rl, tb, quad[1]);
        
        cg::vec3 va = cg::normalize3(cg::vec3(0.0f, quad[2] - quad[3], 1.0f));
        cg::vec3 vb = cg::normalize3(cg::vec3(1.0f, quad[4] - quad[5], 0.0f));
        cg::vec3 normal = cg::cross3(va,vb);
        return cg::vec4(normal.x,normal.y,normal.z, h);
    }
    
    cg::vec4 gfx::TerrainTile::GetHeightNormal(double px, double pz) const
    {
        return GetHeight(px, pz);
    }
    
    float gfx::TerrainTile::GetHeight(cg::point3 const& position) const
    {
        return GetHeight(position.x, position.z);
    }
    
    float gfx::TerrainTile::GetHeight(double px, double pz) const
    {
        float quad[6];
        GetQuadHeigh(quad, px, pz);
        
        float rl = cg::lerp(quad[2], quad[3], quad[0]);
        float tb = cg::lerp(quad[4], quad[5], quad[0]);
        float h  = cg::lerp(rl, tb, quad[1]);
        return h;
    }
    
    const kege::image<float>& gfx::TerrainTile::GetHeightmap() const
    {
        return hmap;
    }
    
    kege::image<float>& gfx::TerrainTile::GetHeightmap()
    {
        return hmap;
    }
    
    TerrainTile::TerrainTile(const ds::string& name, const cg::int2& t, TerrainSystem* system)
    :   gfx::Entity( gfx::Gameobject::TERRAIN, name)
    ,   tcoord(t)
    {
        SetRadius( sqrt( 2 * cg::sq(system->GetTileSize() * system->GetScale() * 0.5) ) );
        
        // GetLocal().translation is the topleft corner position of the root node
        GetLocal().translation.x  = tcoord.x * system->GetTileSize();
        GetLocal().translation.z  = tcoord.y * system->GetTileSize();
        GetLocal().translation.y  = 0.0;
    }
    
    TerrainTile:: ~ TerrainTile()
    {}
    
    TerrainTile::TerrainTile()
    :   gfx::Entity( gfx::Gameobject::TERRAIN, "" )
    ,   tcoord(0.0)
    {}
    
}}
