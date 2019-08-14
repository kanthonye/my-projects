/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/11/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       TerrainCollision.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef TerrainCollision_hpp
#define TerrainCollision_hpp
#include "CollisionProcess.hpp"
namespace kege{namespace cg{
    
    class TerrainCollision : public cg::CollisionProcess
    {
    public:
        
        void ResolveCollisions(double delta);
        void DetectCollisions(double delta);
        void TestCollisions(double delta);
        void UnInit();
        short Init();
        
        ~ TerrainCollision();
        TerrainCollision();
    };
}}
#endif /* TerrainCollision_hpp */
