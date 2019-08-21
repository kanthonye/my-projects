/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/16/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ContactDetector.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef ContactDetector_hpp
#define ContactDetector_hpp
#include <vector>
#include "../../collision/colliders/Collider.hpp"
#include "../../collision/system/CollisionContact.hpp"
namespace kege{namespace gfx{
    class CollisionBox;
    
    class ContactDetector
    {
        typedef std::vector< CollisionBox* > CollisionObjects;
    private:
        
        void GetPossibleContacts( gfx::CollisionContacts& constacts, CollisionObjects* objects, ContactDetector* children );
        void GetPossibleContacts( gfx::CollisionContacts& constacts, CollisionObjects* objects );
        
    public:
        
        bool Insert( const cg::vec3& min, const cg::vec3& max, gfx::Collider* collider );
        bool TestBoxVsBox( const CollisionBox& m, const CollisionBox& n );
        bool CanFitInside( const cg::vec3& min, const cg::vec3& max );
        void GetPossibleContacts( gfx::CollisionContacts& constacts );
        bool TestOverlap( const CollisionBox& m );
        
        void SubDivide();
        
        ContactDetector( int x, int y, int z, int w );
        ~ ContactDetector();
        ContactDetector();
        
    private:
        
        ContactDetector* _children;
        CollisionObjects* _container;
        int _x, _y, _z, _w;
    };
}}
#endif /* ContactDetector_hpp */
