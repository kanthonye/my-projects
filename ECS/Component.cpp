//
//  Component.cpp
//  Particles
//
//  Created by Kenneth A Esdaile on 5/11/20.
//  Copyright © 2020 Kenneth A Esdaile. All rights reserved.
//

#include "ECM.hpp"
#include "Component.hpp"
namespace kege
{    
    
    unsigned int Component::_total_types = 0;
    
    int Component::GEN_TYPE(){ return _total_types++; }
    
    typename Component::ConstIterator Component::Begin()const
    {
        return _entities.begin();
    }
    typename Component::ConstIterator Component::End()const
    {
        return _entities.end();
    }
    typename Component::Iterator Component::Begin()
    {
        return _entities.begin();
    }
    typename Component::Iterator Component::End()
    {
        return _entities.end();
    }
    
    CompId Component::Attach( EntityId eid )
    {
        if ( eid < 0 ) return INVALID_COMPONENT;
        
        /*
         if the entity already own a component of this type return its component, if not attach component to entity
         */
        EntityComponentMap::iterator m = _entities.find( eid );
        if ( m != _entities.end() )
        {
            return m->second;
        }
        
        /*
         alloc memory for the entity component
         */
        CompId comp = Cache::Alloc();
        if (Cache::Capacity() != _owners.size())
        {
            _owners.resize( Cache::Capacity() );
        }
        /*
         Set the entity owner of the new component id.
         This is used to tell us which component belong with what entity
         */
        int index = GetIndex( comp );
        _owners[ index ] = eid;
        
        /*
         attach component to entity. keep track of each entity that has this component
         */
        _entities[ eid ] = comp;
        /*
         return the physical component.
         */
        return comp;
    }
    
    bool Component::Remove( EntityId eid )
    {
        EntityComponentMap::iterator m = _entities.find( eid );
        if ( m != _entities.end() )
        {
            Remove( m->second );
            _entities.erase( m );
            return true;
        }
        return false;
    }
    
    void Component::Remove( const CompId& cid )
    {
        int index = GetIndex( cid );
        if (index > 0) 
        {
            _owners[ index ] = -1;
            
            /*
             if this component is attach to an entity detach from the entity.
             */
            Remove( GetOwner( cid ) );
        }
        
        /*
         release the component memory back to the system.
         */
        Cache::Free( cid );
    }
    
    void Component::Clear()
    {
        _entities.clear();
        _owners.clear();
        Cache::Clear();
    }
    
    EntityId Component::GetOwner( const CompId& comp )const
    {
        if ( comp != INVALID_COMPONENT )
        {
            return INVALID_ID;
        }
        return _owners[ GetIndex( comp ) ];
    }
    
    EntityId Component::GetOwner( void* ptr )const
    {
        if ( ptr == nullptr )
        {
            return INVALID_ID;
        }
        return GetOwner( Cache::IndexOf( ptr ) );
    }

    int Component::GetIndex( const CompId& comp )const
    {
        return comp / Cache::SizeOfElem();
    }
    
    Component::Component( int component_size, int total_components )
    :   Cache(component_size, total_components)
    {
        //int poolsize = component_size * total_components;
        _owners.resize( total_components );
        std::fill(_owners.begin(), _owners.end(), -1);
    }
}



