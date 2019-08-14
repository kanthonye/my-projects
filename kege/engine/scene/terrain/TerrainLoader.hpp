//
//  TerrainLoader.hpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/20/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef TerrainLoader_hpp
#define TerrainLoader_hpp
#include "CoreTask.hpp"
#include "MeshComponent.hpp"
#include "TerrainMaterial.hpp"
#include "TerrainTextures.hpp"
namespace kege{namespace gfx{
    class TerrainTile;
    class Terrain;
    
    class TerrainLoader : public kege::CoreTask
    {
    public:
        
        TerrainLoader(int x, int z, TerrainTile* tile, gfx::Terrain* map)
        :   _tile(tile)
        ,   _map(map)
        ,   _x(x)
        ,   _z(z)
        {}
        
        kege::shared_image GenerateTangentmap();
        kege::shared_image GenerateNormalmap();
        gfx::SharedMesh    GenerateMesh();
        
        gfx::SharedTexture GetTangentTexture();
        gfx::SharedTexture GetNormalTexture();
        
        gfx::SharedMaterial GetMaterial();
        gfx::MeshComponent* GetMeshComponent();
        void Execute() override;
        
    private:
        
        gfx::TerrainTile* _tile;
        gfx::Terrain* _map;
        int _x,_z;
    };
}}
#endif /* TerrainEngine_hpp */
