/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/18/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       World.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "Octree.hpp"
namespace kege{namespace gfx{

    bool  Octree::FullyInside( const cg::vec3& min, const cg::vec3& max )
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
    
    bool Octree::PartlyInside( const cg::vec3& min, const cg::vec3& max )
    {
        if (_x-_w > max.x && _x+_w < min.x ) return false;
        if (_y-_w > max.y && _y+_w < min.y ) return false;
        if (_z-_w > max.z && _z+_w < min.z ) return false;
        return true;
    }
    
    int Octree::GetCoverage( OctreeObject* object )
    {
        int a = cg::magn3sq(object->max - object->min);
        int b = _w*_w*3+1;
        return b / a;
    }
    
    bool Octree::Insert( OctreeObject* object )
    {
        int hw = _w * 0.5;
        int qw = hw * 0.5;
        if ( _y <= object->min.y && _y + _w >= object->max.y )
        {
            if ( _z <= object->min.z && _z + _w >= object->max.z )
            {
                if ( _x >= object->max.x && _x + _w >= object->min.x )
                {
                    // upper_font_left
                    if ( _octant == nullptr ) _octant = new Octant;
                    if ( _octant->upper_front_left == nullptr ) _octant->upper_front_left = new Octree( _x-qw, _y+qw, _z+qw, hw, _minsize );
                    return _octant->upper_front_left->Insert( object );
                }
                else if ( _x <= object->min.x && _x + _w >= object->max.x )
                {
                    // upper_font_right
                    if ( _octant == nullptr ) _octant = new Octant;
                    if ( _octant->upper_front_right == nullptr ) _octant->upper_front_right = new Octree( _x+qw, _y+qw, _z+qw, hw, _minsize );
                    return _octant->upper_front_right->Insert( object );
                }
            }
            else if ( _z >= object->max.z && _z - _w <= object->min.z )
            {
                if ( _x - _w <= object->min.x && _x >= object->max.x )
                {
                    // upper_back_left
                    if ( _octant == nullptr ) _octant = new Octant;
                    if ( _octant->upper_back_left == nullptr ) _octant->upper_back_left = new Octree( _x-qw, _y+qw, _z-qw, hw, _minsize );
                    return _octant->upper_back_left->Insert( object );
                }
                else if ( _x <= object->min.x && _x + _w >= object->max.x )
                {
                    // upper_back_right
                    if ( _octant == nullptr ) _octant = new Octant;
                    if ( _octant->upper_back_right == nullptr ) _octant->upper_back_right = new Octree( _x+qw, _y+qw, _z-qw, hw, _minsize );
                    return _octant->upper_back_right->Insert( object );
                }
            }
        }
        else if ( _y >= object->max.y && _y - _w <= object->min.y )
        {
            if ( _z <= object->min.z && _z + _w >= object->max.z )
            {
                if ( _x - _w <= object->min.x && _x >= object->max.x )
                {
                    // lower_font_left
                    if ( _octant == nullptr ) _octant = new Octant;
                    if ( _octant->lower_front_left == nullptr ) _octant->lower_front_left = new Octree( _x-qw, _y-qw, _z+qw, hw, _minsize );
                    return _octant->lower_front_left->Insert( object );
                }
                else if ( _x <= object->min.x && _x + _w >= object->max.x )
                {
                    // lower_font_right
                    if ( _octant == nullptr ) _octant = new Octant;
                    if ( _octant->lower_front_right == nullptr ) _octant->lower_front_right = new Octree( _x+qw, _y-qw, _z+qw, hw, _minsize );
                    return _octant->lower_front_right->Insert( object );
                }
            }
            else if ( _z >= object->max.z && _z - _w <= object->min.z )
            {
                if ( _x - _w <= object->min.x && _x >= object->max.x )
                {
                    // lower_back_left
                    if ( _octant == nullptr ) _octant = new Octant;
                    if ( _octant->lower_back_left == nullptr ) _octant->lower_back_left = new Octree( _x-qw, _y-qw, _z-qw, hw, _minsize );
                    return _octant->lower_back_left->Insert( object );
                }
                else if ( _x <= object->min.x && _x + _w >= object->max.x )
                {
                    // lower_back_right
                    if ( _octant == nullptr ) _octant = new Octant;
                    if ( _octant->lower_back_right == nullptr ) _octant->lower_back_right = new Octree( _x+qw, _y-qw, _z-qw, hw, _minsize );
                    return _octant->lower_back_right->Insert( object );
                }
            }
        }
        if ( _objects == nullptr ) _objects = new std::vector< OctreeObject* >;
        _objects->push_back( object );
        return true;
    }
    
    void Octree::Add( OctreeObject* object )
    {
        if ( _objects == nullptr ) _objects = new std::vector< OctreeObject* >;
        _objects->push_back( object );
    }
    
    void Octree::UpdateObjects()
    {
        if ( _objects != nullptr )
        {
            int k;
            OctreeObject* object;
            for ( std::vector< OctreeObject* >::iterator i=_objects->begin(); i!=_objects->end(); i++ )
            {
                object = (*i);
                /*
                 if the object doesn't Overlaps its current container, then it outside of it.
                 thus it must be re-inserted.
                 */
                if ( !PartlyInside( object->min, object->max ) )
                {
                    if ( _parent != nullptr )
                    {
                        _objects->erase( i );
                        _parent->Insert( object );
                    };
                }
                /*
                 if the object overlaps its parent octree then it is inside of it.
                 if the parent octree has any children, and the object is not stationary,
                 then since the object is a moving object it should be tested to see if any one of
                 the parent octrees child can fully contain the object. if the child octree can fully
                 contain the object, then it should be remove from parent and insert into that child octree.
                 */
                else if ( !_isleaf )
                {
                    for ( k=0; k<8; k++ )
                    {
                        if ( _octant->nodes[ k ] != nullptr )
                        {
                            if ( _octant->nodes[ k ]->FullyInside( object->min, object->max ) )
                            {
                                _objects->erase( i );
                                _octant->nodes[ k ]->Add( object );
                            }
                        }
                    }
                }
            }
            /*
             if the octree contains no object the its object list should be deleted.
             */
            if ( _objects->empty() )
            {
                delete _objects;
                _objects = nullptr;
            }
        }
    }
    
    void Octree::UpdateOctants()
    {
        if ( _octant == nullptr ) return;
        int child_count = 0;
        for (int i=0; i<8; i++)
        {
            if ( _octant->nodes[ i ] != nullptr )
            {
                /*
                 If a child octree contains no object and has no child, then its not being used,
                 so it need to be deleted, otherwise it needs to be updated.
                 */
                if ( _octant->nodes[ i ]->_objects == nullptr && _octant->nodes[ i ]->_isleaf )
                {
                    delete _octant->nodes[ i ];
                    _octant->nodes[ i ] = nullptr;
                    continue;
                }
                _octant->nodes[ i ]->UpdateWorld();
                child_count++;
            }
        }
        _isleaf = (child_count == 0);
    }
    
    void Octree::UpdateWorld()
    {
        UpdateObjects();
        UpdateOctants();
    }
    
    void Octree::Clear()
    {
        if ( _objects != nullptr )
        {
            for ( int i=0; i<_objects->size(); i++ )
            {
                delete _objects->at( i );
            }
            delete _objects;
            _objects = nullptr;
        }
        if ( _octant != nullptr )
        {
            for ( int i=0; i<8; i++ )
            {
                if ( _octant->nodes[ i ] != nullptr )
                {
                    delete _octant->nodes[ i ];
                    _octant->nodes[ i ] = nullptr;
                }
            }
            delete _octant;
            _octant = nullptr;
        }
        _parent = nullptr;
    }
    
    Octree::Octree( int x, int y, int z, int w, float minsize )
    :   _objects( nullptr )
    ,   _octant( nullptr )
    ,   _parent( nullptr )
    ,   _x( x )
    ,   _y( y )
    ,   _z( z )
    ,   _w( w )
    ,   _minsize( minsize )
    ,   _isleaf( false )
    {}
    
    Octree::~ Octree()
    {
        Clear();
    }
    
    Octree::Octree()
    :   _objects( nullptr )
    ,   _octant( nullptr )
    ,   _parent( nullptr )
    ,   _x( 0 )
    ,   _y( 0 )
    ,   _z( 0 )
    ,   _w( 0 )
    ,   _isleaf( false )
    {}
}}
