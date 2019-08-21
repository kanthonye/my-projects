//
//  CollisionAABB.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/23/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef CollisionAABB_hpp
#define CollisionAABB_hpp
#include "Mesh.hpp"
#include "CollisionComponent.hpp"
namespace kege{namespace cmp{
    
    class CollisionAABB : public cmp::CollisionComponent
    {
    public:
        
        void Render(const gfx::Frustum& frustum, const ds::array<gfx::Light*>& lights);
        bool OnCollisionRay(const cg::point3& p, const cg::vec3& r);
        void ResolveCollision(phx::ContactResolver& data);
        
        /** Given point p, return the point q on or in AABB b that is closest to p Closest Point on AABB to Point */
        cg::point3 ClosestPointAABB(const cg::point3& p);
        
        void ComputeShape(const gfx::Mesh& mesh);
        
        /*
         SetShape() : set rigid object shape
         */
        void SetShape(const phx::AABB& shape);
        
        /*
         return const rigid object shape
         */
        const phx::AABB& GetShape()const;
        
        /*
         return rigid object shape
         */
        phx::AABB& GetShape();
        
        
        cg::point3 Corner(int n)const;
        
        /*
         */
        void TransformShape();
        
        
        void Save(kege::XML& xml);
        
        CollisionAABB(const cg::point3& c, float w, float h, float d);
        CollisionAABB(const cg::point3& min, const cg::point3& max);
        CollisionAABB();
        
    private:
        
        phx::AABB shape;
        cg::vec3 length;
    };
}}
#endif /* CollisionAABB_hpp */
