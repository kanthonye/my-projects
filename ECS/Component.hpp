//
//  Component.hpp
//  Particles
//
//  Created by Kenneth A Esdaile on 5/11/20.
//  Copyright © 2020 Kenneth A Esdaile. All rights reserved.
//

#ifndef Component_hpp
#define Component_hpp
#include <map>
#include <vector>
#include <unordered_map>
#include "Cache.hpp"
namespace kege{
    
    typedef int EntityId;
    static const EntityId INVALID_ID = -1;
    
    typedef Cache::Index CompId;
    static const CompId INVALID_COMPONENT;

    /**
     A Component contain nothing but data. Components are the building blocks of entities. 
     This object store and managers the data for each component.
     */
    class Component : public Cache
    {
    public:
        
        typedef std::unordered_map< EntityId, Cache::Index > EntityComponentMap;
        typedef EntityComponentMap::const_iterator ConstIterator;
        typedef EntityComponentMap::iterator Iterator;
        
        typedef std::vector< EntityId > ComponentOwners;
        typedef std::vector< char > ComponentMemory;
        
        EntityId GetOwner( const CompId& comp )const;
        EntityId GetOwner( void* ptr )const;
        
        CompId Attach( EntityId entity );
        bool Remove( EntityId entity );
        void Remove( const CompId& comp );
        void Clear();
        
        ConstIterator Begin()const;
        ConstIterator End()const;
        Iterator Begin();
        Iterator End();
        
        static unsigned int GET_TOTAL_TYPES(){ return _total_types; }
        virtual int GetType() const { return -1; }
        
        virtual ~ Component(){}
        
    protected:
        
        Component( int component_size, int total_components );
        int GetIndex( const CompId& comp )const;
        static int GEN_TYPE();
        
    protected:
        
        EntityComponentMap _entities;
        ComponentOwners _owners;
        
    private:
        
        static unsigned int _total_types;
    };
}


namespace kege{
    
    template< typename T > class ComponentT : public Component
    {
    public:
        
        static int GET_COMP_TYPE() { return _component_type; }
        virtual int GetType() const { return _component_type; }
        
        const T* Get( const CompId& cid )const
        {
            return (T*) Cache::operator[]( cid );
        }
        
        T* Get( const CompId& cid )
        {
            return (T*) Cache::operator[]( cid );
        }
        
        ComponentT( int quantity = 1 )
        :   Component( sizeof( T ), quantity )
        {
        }
        
        ~ ComponentT()
        {
            for (int i=0; i<Cache::_memory.size(); i+=Cache::_elem_size)
            {
                /*
                 call the deconstructor of the component object
                 */
                ((T*) (&Cache::_memory[ i ]))->~T();
            }
            Component::_owners.clear();
        }
        
    private:
        
        static int _component_type;
    };
    
    template< typename T > int ComponentT< T >::_component_type = ComponentT< T >::GEN_TYPE();
}
#endif /* Component_hpp */
