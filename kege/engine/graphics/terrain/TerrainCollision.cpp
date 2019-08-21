/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/19/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       TerrainCollision.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "Scene.hpp"
#include "TerrainCollision.hpp"
#include "CollisionSystem.hpp"
namespace kege{namespace gfx{

    void TerrainCollision::Update( double delta, gfx::CollisionSystem* system )
    {
        system->GetScene()->GetSystem("TerrainSystem");
    }
    void  TerrainCollision::UnInit()
    {
        
    }
    short TerrainCollision::Init()
    {
        return true;
    }
}}
