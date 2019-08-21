/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/16/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ContactDetector.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../collision/system/ContactDetector.hpp"
namespace kege{ namespace gfx{
    
    class CollisionBox
    {
    public:
        CollisionBox( const cg::vec3& min, const cg::vec3& max, gfx::Collider* collider )
        :   max( max )
        ,   min( min )
        ,   collider( collider )
        {}
        
        cg::vec3 max;
        cg::vec3 min;
        shared::Collider collider;
    };
    
    void ContactDetector::GetPossibleContacts( gfx::CollisionContacts& constacts, CollisionObjects* objects, ContactDetector* children )
    {
        CollisionObjects::iterator n, m = objects->begin();
        while ( m != objects->end() )
        {
            CollisionBox* box = (*m);
            m++;
            
            for (int i=0; i<8; i++)
            {
                // if the box intersects any child node, then we need to check its objects
                // anainst the boxes in the CollisionObjects list
                if ( children[ i ].TestOverlap( *box ) )
                {
                    // test the box against all objects in the child object list
                    if ( children[ i ]._container != nullptr )
                    {
                        n = children[ i ]._container->begin();
                        while ( n != children[ i ]._container->end() )
                        {
                            if ( TestBoxVsBox( (**m), *box ) )
                            {
                                gfx::CollisionContact& contact = constacts.push_back();
                                contact.collider1 = box->collider.rawptr();
                                contact.collider2 = (*m)->collider.rawptr();
                            }
                            n++;
                        }
                    }
                    // the objects in the list will possibly be colliding with object
                    // lower in the octree, since larger objects are in the upper tree nodes.
                    // So we must test each children childrens against the boxes in objects
                    if ( children[ i ]._children != nullptr )
                    {
                        children[ i ].GetPossibleContacts( constacts, objects, children[ i ]._children );
                    }
                }
            }
        }
    }
    void ContactDetector::GetPossibleContacts( gfx::CollisionContacts& constacts, CollisionObjects* objects )
    {
        CollisionObjects::iterator n,m=objects->begin();
        while ( m!=objects->end() )
        {
            n=m;
            n++;
            while ( n!=objects->end() )
            {
                if ( TestBoxVsBox( (**m), (**n) ) )
                {
                    gfx::CollisionContact& contact = constacts.push_back();
                    contact.collider1 = (*m)->collider.rawptr();
                    contact.collider2 = (*n)->collider.rawptr();
                }
                n++;
            }
            m++;
        }
    }
    
    void ContactDetector::GetPossibleContacts( gfx::CollisionContacts& constacts )
    {
        if ( _container != nullptr )
        {
            GetPossibleContacts( constacts, _container );
            if ( _children != nullptr )
            {
                GetPossibleContacts( constacts, _container, _children );
            }
        }
        
        if ( _children != nullptr )
        {
            for ( int i=0; i<8; i++ )
            {
                _children[ i ].GetPossibleContacts( constacts );
            }
        }
    }
    
    bool ContactDetector::Insert( const cg::vec3& min, const cg::vec3& max, gfx::Collider* collider )
    {
        if ( CanFitInside( min, max ) )
        {
            double j = cg::magn3sq(max - min);
            double k = cg::sq( _w*_sqrt_2_ );
            bool too_small = (j/k) <= 1.0;
            
            if ( _children == nullptr && !too_small )
            {
                SubDivide();
            }
            if ( _children != nullptr )
            {
                for (int i=0; i<8; i++)
                {
                    if ( _children[i].Insert( min, max, collider ) )
                    {
                        break;
                    }
                }
            }
            else
            {
                if ( _container == nullptr )
                {
                    _container = new CollisionObjects;
                }
                _container->push_back( new CollisionBox( min, max, collider ) );
            }
            return true;
        }
        return false;
    }
    
    bool ContactDetector::CanFitInside( const cg::vec3& min, const cg::vec3& max )
    {
        if (   (_x-_w <= min.x && _x+_w >= max.x )
            && (_y-_w <= min.y && _y+_w >= max.y )
            && (_z-_w <= min.z && _z+_w >= max.z )   )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    bool ContactDetector::TestBoxVsBox( const CollisionBox& m, const CollisionBox& n )
    {
        if ( m.min.x > n.max.x || m.max.x < n.min.x ) return false;
        if ( m.min.y > n.max.y || m.max.y < n.min.y ) return false;
        if ( m.min.z > n.max.y || m.max.z < n.min.z ) return false;
        return true;
    }
    
    bool ContactDetector::TestOverlap( const CollisionBox& m )
    {
        if (_x-_w > m.max.x && _x+_w < m.min.x ) return false;
        if (_y-_w > m.max.y && _y+_w < m.min.y ) return false;
        if (_z-_w > m.max.z && _z+_w < m.min.z ) return false;
        return true;
    }
    
    void  ContactDetector::SubDivide()
    {
        int hw = _w*0.5;
        int i=0 ,px ,pz, py;
        _children = new ContactDetector[8];
        for ( py=-hw; py<_w; py+=_w )
        {
            for ( pz=-_w; pz<_w; pz+=_w )
            {
                for ( px=-_w; px<_w; px+=_w )
                {
                    _children[ i ]._x = _x+px;
                    _children[ i ]._y = _y+py;
                    _children[ i ]._z = _z+pz;
                    _children[ i ]._w = hw;
                }
            }
        }
    }
    ContactDetector::ContactDetector( int x, int y, int z, int w )
    :   _children( nullptr )
    ,   _container( nullptr )
    ,   _x( x )
    ,   _y( y )
    ,   _z( z )
    ,   _w( w )
    {
        
    }
    ContactDetector::~ ContactDetector()
    {
        if ( _children != nullptr )
        {
            delete [] _children;
            _children = nullptr;
        }
        _container->clear();
        _container = nullptr;
    }
    ContactDetector::ContactDetector()
    :   _children( nullptr )
    ,   _container( nullptr )
    ,   _x( 0 )
    ,   _y( 0 )
    ,   _z( 0 )
    ,   _w( 0 )
    {}
}}
