//
//  CollisionSphere.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/27/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef CollisionSphere_hpp
#define CollisionSphere_hpp
#include "Mesh.hpp"
#include "geometrics.hpp"
#include "CollisionComponent.hpp"
namespace kege{namespace cmp{
    
    class CollisionSphere : public cmp::CollisionComponent
    {
    public:
        
        void Render(const gfx::Frustum& frustum, const ds::array<gfx::Light*>& lights);
        bool OnCollisionRay(const cg::point3& p, const cg::vec3& r);
        void ResolveCollision(phx::ContactResolver& data);
        
        void ComputeShape(const gfx::Mesh& mesh);
        
        /*
         SetShape() : set rigid object shape
         */
        void SetShape(const phx::Sphere& shape);
        
        /*
         return const rigid object shape
         */
        const phx::Sphere& GetShape()const;
        
        /*
         return rigid object shape
         */
        phx::Sphere& GetShape();
        
        /*
         */
        void TransformShape();
        
        void Save(kege::XML& xml);
        
        CollisionSphere(const cg::point3& c, float radius);
        CollisionSphere();
        
    private:
        
        phx::Sphere shape;
        cg::vec3 last;
    };
}}
#endif /* CollisionSphere_hpp */
