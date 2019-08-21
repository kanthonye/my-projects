//
//  CollisionPlane.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 1/3/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef CollisionPlane_hpp
#define CollisionPlane_hpp
#include "Mesh.hpp"
#include "CollisionComponent.hpp"
namespace kege{namespace cmp{
    
    class CollisionPlane : public cmp::CollisionComponent
    {
    public:
        
        void Render(const gfx::Frustum& frustum, const ds::array<gfx::Light*>& lights);
        void ResolveCollision(phx::ContactResolver& data);
        
        void ComputeShape(const gfx::Mesh& mesh);
        
        /*
         SetShape() : set rigid object shape
         */
        void SetShape(const phx::Plane& shape);
        
        /*
         return const rigid object shape
         */
        const phx::Plane& GetShape()const;
        
        /*
         return rigid object shape
         */
        phx::Plane& GetShape();
        
        void SetHalfSpace(bool value);
        bool IsHalfSpace()const;
        /*
         */
        void TransformShape();
        
        CollisionPlane(const cg::point3& a, const cg::point3& b, const cg::point3& c, bool halfspace);
        CollisionPlane(const cg::vec3& n, const cg::point3& p, bool halfspace);
        CollisionPlane();
        
    private:
        
        phx::Plane shape;
        bool halfspace;
    };
}}
#endif /* CollisionPlane_hpp */
