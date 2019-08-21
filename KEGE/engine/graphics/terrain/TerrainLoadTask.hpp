/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/18/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       TerrainLoadTask.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef TerrainLoadTask_hpp
#define TerrainLoadTask_hpp
#include "CoreTask.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "TerrainMaterial.hpp"
#include "Graphics.hpp"
#include "Heightmap.hpp"
namespace kege{namespace gfx{
    class TerrainTile;
    class Terrain;
    
    class TerrainLoadTask : public kege::CoreTask
    {
    public:
        
        TerrainLoadTask( int x, int z, TerrainTile* tile, gfx::Heightmap* map )
        :   _tile( tile )
        ,   _map( map )
        ,   _x( x )
        ,   _z( z )
        {}
        
        shared::Geometry GenerateGeometry();
        shared::image GenerateTangentmap();
        shared::image GenerateNormalmap();
        
        shared::Texture GetTangentTexture();
        shared::Texture GetNormalTexture();
        
        shared::Material GetMaterial();
        gfx::Model* GetModel();
        void Execute() override;
        
    private:
        
        gfx::TerrainTile* _tile;
        gfx::Heightmap* _map;
        int _x,_z;
    };
}}
#endif /* TerrainLoadTask_hpp */
