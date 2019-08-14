/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/8/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       DynamicCollisionProcess.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef ObjectCollisions_hpp
#define ObjectCollisions_hpp
#include "CollisionProcess.hpp"
namespace kege{namespace cg{
    
    class ObjectCollisions : public cg::CollisionProcess
    {
    public:
         
        void ResolveCollisions(double delta);
        void DetectCollisions(double delta);
        void TestCollisions(double delta);
        void UnInit();
        short Init();
        
        ~ ObjectCollisions();
        ObjectCollisions();
        
        CollisionContacts contacts;
    };
}}
#endif /* ObjectCollisionProcess_hpp */
