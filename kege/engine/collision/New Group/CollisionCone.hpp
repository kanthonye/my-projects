//
//  CollisionCone.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 1/10/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef CollisionCone_hpp
#define CollisionCone_hpp
#include "Mesh.hpp"
#include "CollisionComponent.hpp"
namespace kege{namespace cmp{
    
    class CollisionCone : public cmp::CollisionComponent
    {
    public:
        
        void Render(const gfx::Frustum& frustum, const ds::array<gfx::Light*>& lights);
        bool OnCollisionRay(const cg::point3& p, const cg::vec3& r);
        void ResolveCollision(phx::ContactResolver& data);
        
        void ComputeShape(const gfx::Mesh& mesh);
        
        /*
         SetShape() : set rigid object shape
         */
        void SetShape(const phx::Cone& shape);
        
        /*
         return const rigid object shape
         */
        const phx::Cone& GetShape()const;
        
        /*
         return rigid object shape
         */
        phx::Cone& GetShape();
        
        /*
         */
        void TransformShape();
        
        CollisionCone(const cg::point3& c,const cg::point3& n, float h, float r);
        CollisionCone();
        
    private:
        
        phx::Cone shape;
    };
}}
#endif /* CollisionCone_hpp */
