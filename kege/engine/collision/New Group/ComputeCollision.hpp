//
//  ComputeCollision.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 1/13/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef ComputeCollision_hpp
#define ComputeCollision_hpp
#include "CollisionComponent.hpp"
namespace kege{namespace phx{
    class CollisionDetector;
    
    bool ComputeCollision(phx::CollisionResolver& resolver, cmp::CollisionSphere   &a, cmp::CollisionAABB     &b);
    bool ComputeCollision(phx::CollisionResolver& resolver, cmp::CollisionSphere   &a, cmp::CollisionSphere   &b);
    bool ComputeCollision(phx::CollisionResolver& resolver, cmp::CollisionSphere   &a, cmp::CollisionPlane    &b);
    bool ComputeCollision(phx::CollisionResolver& resolver, cmp::CollisionSphere   &a, cmp::CollisionCylinder &b);
    bool ComputeCollision(phx::CollisionResolver& resolver, cmp::CollisionSphere   &a, cmp::CollisionOBB      &b);
    bool ComputeCollision(phx::CollisionResolver& resolver, cmp::CollisionSphere   &a, cmp::CollisionCone     &b);
    bool ComputeCollision(phx::CollisionResolver& resolver, cmp::CollisionAABB     &a, cmp::CollisionAABB     &b);
    bool ComputeCollision(phx::CollisionResolver& resolver, cmp::CollisionAABB     &a, cmp::CollisionPlane    &b);
    bool ComputeCollision(phx::CollisionResolver& resolver, cmp::CollisionAABB     &a, cmp::CollisionCone     &b);
    bool ComputeCollision(phx::CollisionResolver& resolver, cmp::CollisionOBB      &a, cmp::CollisionPlane    &b);
    bool ComputeCollision(phx::CollisionResolver& resolver, cmp::CollisionOBB      &a, cmp::CollisionOBB      &b);
    bool ComputeCollision(phx::CollisionResolver& resolver, cmp::CollisionCylinder &a, cmp::CollisionCylinder &b);
    bool ComputeCollision(phx::CollisionResolver& resolver, cmp::CollisionCylinder &a, cmp::CollisionPlane    &b);
}}
#endif /* ComputeCollision_hpp */
