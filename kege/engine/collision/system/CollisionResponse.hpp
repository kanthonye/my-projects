/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/8/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       CollisionResponse.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef CollisionResponse_hpp
#define CollisionResponse_hpp
#include "cgm.hpp"
#include "dlist.hpp"
#include "CollisionContact.hpp"
namespace kege{namespace gfx{
    
    class CollisionResponse
    {
    public:
        virtual void Execute(const gfx::CollisionContact& contact) = 0;
        virtual ~ CollisionResponse(){}
    };
    
    
    class MultiCollisionResponse : public CollisionResponse
    {
    public:
        void Execute(const gfx::CollisionContact& contact);
        ~ MultiCollisionResponse();
    };
}}
#endif /* CollisionResponse_hpp */
