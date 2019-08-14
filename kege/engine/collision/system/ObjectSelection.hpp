/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/8/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ObjectSelection.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef ObjectSelection_hpp
#define ObjectSelection_hpp
#include "Camera.hpp"
#include "CollisionProcess.hpp"
#include "../colliders/Collider.hpp"
namespace kege{namespace cg{
    
    class ObjectSelection : public cg::CollisionProcess
    {
    public:
        
        typedef ds::octree<cg::Collider*, ds::dlist<cg::Collider*>> world;
        
        void ResolveCollisions(double delta);
        void DetectCollisions(double delta);
        void TestCollisions(double delta);
        void UnInit();
        short Init();
        
        
        ~ ObjectSelection(){}
        ObjectSelection();
        
    private:
        
        cg::Collider* selection;
        cg::Colliders hitlist;
        
        cg::point3 ray_pos;
        cg::vec3 ray_dir;
        bool castray;
        double dist;
    };
}}
#endif /* ObjectSelection_hpp */
