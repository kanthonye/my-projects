//
//  ECM.cpp
//  Particles
//
//  Created by Kenneth A Esdaile on 7/14/20.
//  Copyright © 2020 Kenneth A Esdaile. All rights reserved.
//

namespace kege
{
    /**
     get the owner of the component that correspond to the component id
     @return the integer Entity Id
     */
    template < typename T > 
    int ECM::GetOwner( const CompId& cid )
    {
        return GetAll< T >()->GetOwner( cid );
    }
    
    /**
     get the component id of the component that correspond to the address
     @return the component id
     */
    template < typename T > CompId ECM::GetID( const T* t )
    {
        return GetAll< T >()->IndexOf( t );
    }
    
    /**
     get the component id of the component that correspond to the entity id
     @return the component id
     */
    template < typename T > CompId ECM::GetID( int eid )
    {
        if ( !Valid( eid ) )
        {
            return INVALID_COMPONENT;
        }
        
        int tid = ComponentT< T >::GET_COMP_TYPE();
        return _entities[ eid ]->Get( tid );
    }
    
    /**
     get the "component mamager" / "list of all components" of type T
     */
    template < typename T > ComponentT< T >* ECM::GetAll()
    {
        int index = ComponentT< T >::GET_COMP_TYPE();
        ref< Component >& components = _components[ index ];
        
        /* 
         if the component resource don't exist, create it. 
         */
        if ( components == nullptr ) 
        {
            components = new ComponentT< T >();
        }
        
        return (ComponentT< T >*) components.rawptr();
    }
    
    /**
     get the list of all components of type T
     */
    template < typename T > T* ECM::Get( const CompId& cid )
    {
        return GetAll< T >()->Get( cid );
    }
    
    /**
     get a specific component from the entity eid
     */
    template < typename T > T* ECM::Get( int eid )
    {
        CompId cid = GetID< T >( eid );
        if ( cid == INVALID_COMPONENT ) 
        {
            return nullptr;
        }
        return GetAll< T >()->Get( cid );
    }
    
    /**
     attach a specific component to the entity "eid"
     */
    template < typename T > T* ECM::Add( int eid, const T& t )
    {
        T* c = Add< T >( eid );
        if ( c != nullptr )
        {
            *c = t;
        }
        return c;
    }
    
    /**
     attach a specific component to the entity "eid"
     */
    template < typename T > T* ECM::Add( int eid )
    {
        if ( !Valid( eid ) ) return nullptr;
        
        ComponentT< T >* components = GetAll< T >();
        int type_id = ComponentT< T >::GET_COMP_TYPE();
        CompId cid = _entities[ eid ]->Get( type_id );
        
        if ( cid != INVALID_COMPONENT )
        {
            return components->Get( cid );
        }
        
        cid = components->Attach( eid );
        _entities[ eid ]->Insert( type_id, cid );
        return components->Get( cid );
    }
    
    /**
     dettach a specific component from the entity "eid"
     */
    template < typename T > void ECM::Remove( int eid )
    {
        if ( !Valid( eid ) ) return;
        _entities[ eid ]->Remove( ComponentT< T >::GET_COMP_TYPE() );
        GetAll< T >()->Remove( eid );
    }

    /**
     release all the memory from a specific component manager
     */
    template < typename T > void ECM::Clear()
    {
        int comp_type = ComponentT< T >::GET_COMP_TYPE();
        _components[ comp_type ]->Clear();
        
        for (int i=0; i<_entities.size(); i++)
        {
            if ( _entities[i] != nullptr )
            {
                _entities[i]->Remove( comp_type );
            }
        }
        //_components[ type_id ] = nullptr;
    }
    
}
