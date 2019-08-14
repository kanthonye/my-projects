/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/26/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       TerrainSystem.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "Scene.hpp"
#include "GameEngine.hpp"
#include "TerrainSystem.hpp"
#include "Singleton.hpp"
namespace kege{namespace gfx{
    
//    void TerrainSystem::ReceiveMessage(const kege::Envelope& envelope)
//    {
//        HandleMessage( *envelope.GetMessage() );
//    }
    
    void TerrainSystem::HandleMessage(const kege::Message& message)
    {
    }
    
    void TerrainSystem::Update(double delta)
    {
    }
    
    void TerrainSystem::UnInit()
    {
    }
    
    bool TerrainSystem::Init()
    {
        if ( !_init )
        {
            kege::CoreTaskManager* manager = kege::Singleton::Get<CoreTaskManager>();
            if (manager == nullptr)
            {
                KEGE_ERROR("REQUIRED_CORE_SYSTEM : TerrainSystem reqiure CoreTaskManager");
                return false;
            }
            
            //scene->AddSystem( new gfx::TilingSystem(WORLD_SIZE, TILE_SIZE, TERRAIN_SCALE) );
            terrain = new gfx::Terrain(0,0, this);
            GetScene()->Add( terrain );
            _init = true;
        }
        return _init;
    }
    
    cg::int2 TerrainSystem::WorldToLocalTilecoord(int x, int z)
    {
        cg::int2 t, m(x / columns, z / columns);
        if (0 <= x)
        {
            t.x = x - columns * m.x;
        }
        else
        {
            t.x = (m.x * columns) - x;
        }
        if (0 <= z)
        {
            t.y = z - columns * m.y;
        }
        else
        {
            t.y = m.y * columns - z;
        }
        return t;
    }

    
    TerrainSystem::TerrainSystem(int region_size, int terrain_size, int tile_size, int scale, int min_height, int max_height)
    :   kege::SubSystem("TerrainSystem")
    ,   terrain(nullptr)
    ,   resolution(16)
    ,   region_size(region_size)
    ,   tile_size(tile_size)
    ,   scale(scale)
    ,   columns(terrain_size / tile_size)
    ,   normmap_strength(8)
    ,   max_height( max_height )
    ,   min_height( min_height )
    {
    }
    
    TerrainSystem::~ TerrainSystem()
    {
    }
    
}}
