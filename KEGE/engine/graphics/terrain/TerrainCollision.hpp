/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/19/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       TerrainCollision.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef TerrainCollision_hpp
#define TerrainCollision_hpp
#include <stdio.h>
#include "queue.hpp"
#include "dlist.hpp"
#include "Collider.hpp"
#include "CollisionProcess.hpp"
#include "TerrainSystem.hpp"
namespace kege{namespace gfx{
    class CollisionSystem;
    
    class TerrainCollision : public CollisionProcess
    {
    public:
        
        virtual void Update( double delta, gfx::CollisionSystem* system );
        virtual void  UnInit();
        virtual short Init();
        virtual ~ TerrainCollision(){}
        
        Terrain* terrain;
    };
}}
#endif /* TerrainCollision_hpp */
