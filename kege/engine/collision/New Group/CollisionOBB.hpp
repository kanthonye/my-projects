//
//  CollisionOBB.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/27/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef CollisionOBB_hpp
#define CollisionOBB_hpp
#include "Mesh.hpp"
#include "CollisionComponent.hpp"
namespace kege{namespace cmp{
    
    class CollisionOBB : public cmp::CollisionComponent
    {
    public:
        
        void Render(const gfx::Frustum& frustum, const ds::array<gfx::Light*>& lights);
        void ResolveCollision(phx::ContactResolver& data);
        
        void ComputeShape(const gfx::Mesh& mesh);
        
        /*
         SetShape() : set rigid object shape
         */
        void SetShape(const phx::OBB& shape);
        
        /*
         return const rigid object shape
         */
        const phx::OBB& GetShape()const;
        
        /*
         return rigid object shape
         */
        phx::OBB& GetShape();
        
        /*
         SetShape() : set rigid object shape
         */
        cg::point3 Corner(int n)const;
        
        /*
         */
        void TransformShape();
        
        void Save(kege::XML& xml);
        
        CollisionOBB(const cg::point3& c, float w, float h, float d, const cg::point3& x, const cg::point3& y, const cg::point3& z);
        CollisionOBB(const cg::point3& c, float w, float h, float d);
        CollisionOBB(const cg::point3& min, const cg::point3& max);
        CollisionOBB();
        
    private:
        
        phx::OBB shape;
    };
}}
#endif /* CollisionOBB_hpp */
