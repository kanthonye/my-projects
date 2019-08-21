/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/16/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       CollisionDetector.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef CollisionDetector_hpp
#define CollisionDetector_hpp
#include <vector>
#include "../../collision/colliders/Collider.hpp"
#include "../../collision/system/CollisionContact.hpp"
namespace kege{namespace gfx{

    class CollisionDetector
    {
    public:
        
        CollisionDetector( int x, int y, int z, int w );
        ~ CollisionDetector();
        CollisionDetector();
    };
}}
#endif /* CollisionDector_hpp */
