//
//  ECS.cpp
//  test
//
//  Created by Kenneth A Esdaile on 11/30/20.
//  Copyright © 2020 Kenneth A Esdaile. All rights reserved.
//

#include "ECM.hpp"
namespace kege
{
    void ECM::Entt::Insert( int comp_type, CompId cid )
    {
        components[ comp_type ] = cid;
    }
    
    void ECM::Entt::Remove( int comp_type )
    {
        Components::iterator m = components.find( comp_type );
        if ( m == components.end() ) return;
        components.erase( m );
    }
    
    CompId ECM::Entt::Get( int comp_type )
    {
        Components::iterator m = components.find( comp_type );
        if ( m == components.end() ) return INVALID_COMPONENT;
        return m->second;
    }
    
    void ECM::Entt::RemoveAll( ECM& ecm )
    {
        for (Components::iterator m = components.begin() ; m != components.end() ; m++ )
        {
            ecm._components[ m->first ]->Remove( m->second );
        }
        components.clear();
    }
    
    
    
    void ECM::Send( const Message& msg )
    {
        _messenger.Send( msg );
    }
    
    /**
     get the component list of an entity
     */
    typename ECM::Entt* ECM::operator[]( int eid )
    {
        if ( !Valid( eid ) ) return nullptr;
        return _entities[ eid ].rawptr();
    }
    
    Messenger& ECM::GetMessenger()
    {
        return _messenger;
    }
    
    /**
     check if an entity is valid
     */
    bool ECM::Valid( unsigned int eid )const
    {
        return eid < _entities.size();
    }
    
    /**
     remove an entity
     */
    void ECM::Delete( int eid )
    {
        if (eid < 0 || eid >= _entities.size() )
            return;
        _recycled.push( eid );
        
        _entities[ eid ]->RemoveAll( *this );
        _entity_counter--;
    }
    
    /**
     create an entity
     */
    int ECM::Create()
    {
        int new_entity;
        // use recyclied entity if any exist
        if ( !_recycled.empty() )
        {
            new_entity = _recycled.front();
            _recycled.pop();
            _entity_counter++;
            return new_entity;
        }
        // create new entity if no recyclied entities are empty.
        new_entity = (int) _entities.size();
        ref< ECM::Entt > e = new ECM::Entt;
        _entities.push_back( e );
        //e->components.resize( Component::GET_TOTAL_TYPES() );
        // return new entity id
        _entity_counter++;
        return new_entity;
    }
    
    /**
     un-initialize this system
     */
    void ECM::Uninit()
    {
        _components.clear();
        _entities.clear();
        while (!_recycled.empty()) _recycled.pop();
    }
    
    /**
     initialize this system
     */
    int ECM::Init()
    {
        if ( _components.size() > 0 )
        {
            return true;
        }
        
        int total_componentns = Component::GET_TOTAL_TYPES();
        if ( total_componentns <= 0 )
        {
            return false;
        }
        
        _components.resize( total_componentns );
        return true;
    }
    
    /**
     get the begin iterator for the entity list
     */
    typename ECM::iterator ECM::Begin()
    {
        return _entities.begin();
    }
    
    /**
     get the end iterator for the entity list
     */
    typename ECM::iterator ECM::End()
    {
        return _entities.end();
    }
    
    ECM::~ECM()
    {
        Uninit();
    }
    
    ECM::ECM()
    :   _entity_counter( 0 )
    {}
    
}
