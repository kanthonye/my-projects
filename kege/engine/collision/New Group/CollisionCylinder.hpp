//
//  CollisionCylinder.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 1/8/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef CollisionCylinder_hpp
#define CollisionCylinder_hpp
#include "Mesh.hpp"
#include "CollisionComponent.hpp"
namespace kege{namespace cmp{
    
    class CollisionCylinder : public cmp::CollisionComponent
    {
    public:
        
        void Render(const gfx::Frustum& frustum, const ds::array<gfx::Light*>& lights);
        void ResolveCollision(phx::ContactResolver& data);
        
        void ComputeShape(const gfx::Mesh& mesh);
        
        /*
         SetShape() : set rigid object shape
         */
        void SetShape(const phx::Cylinder& shape);
        
        /*
         return const rigid object shape
         */
        const phx::Cylinder& GetShape()const;
        
        /*
         return rigid object shape
         */
        phx::Cylinder& GetShape();
        
        void SetHalfSpace(bool value);
        bool IsHalfSpace()const;
        /*
         */
        void TransformShape();
        
        CollisionCylinder(const cg::point3& c, const cg::vec3& d, float r, float h);
        CollisionCylinder(const phx::Cylinder& cylinder);
        CollisionCylinder();
        
    private:
        
        phx::Cylinder shape;
        bool halfspace;
    };
}}
#endif /* CollisionCylinder_hpp */
