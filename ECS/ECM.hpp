//
//  ECM.hpp
//  Particles
//
//  Created by Kenneth A Esdaile on 7/14/20.
//  Copyright © 2020 Kenneth A Esdaile. All rights reserved.
//

#ifndef ECM_hpp
#define ECM_hpp
#include <queue>
#include <vector>
#include <unordered_map>
#include "Object.hpp"
#include "Component.hpp"
#include "Messenger.hpp"
namespace kege
{
    /** ECM (Entity Component Manager)*/
    class ECM : public ObjectType< ECM >
    {
    private:
        
        class Entt : public ObjectType< Entt >
        {
        public:
            
            void Insert( int comp_type, CompId cid );
            void Remove( int comp_type );
            CompId Get( int comp_type );
            void RemoveAll( ECM& ecm );
            
        private:
            
            typedef std::unordered_map< int, CompId > Components;
            Components components;
        };
        
        typedef std::vector< ref< Component > > Components;
        typedef std::vector< ref< ECM::Entt > > Entities;
        friend Entt;
        
    public:
        
        using iterator = typename Entities::iterator;
        
        /**
         get the owner of the component that correspond to the component id
         @return the integer Entity Id
         */
        template < typename T > int GetOwner( const CompId& cid );
        
        /**
         get the component id of the component that correspond to the address
         @return the component id
         */
        template < typename T > CompId GetID( const T* t );
        
        /**
         get the component id of the component that correspond to the entity id
         @return the component id
         */
        template < typename T > CompId GetID( int eid );
        
        /**
         get the "component mamager" / "list of all components" of type T
         */
        template < typename T > ComponentT< T >* GetAll();
        
        /**
         get the list of all components of type T
         */
        template < typename T > T* Get( const CompId& cid );
        
        /**
         get a specific component from the entity eid
         */
        template < typename T > T* Get( int eid );
        
        /**
         attach a specific component to the entity "eid"
         */
        template < typename T > T* Add( int eid, const T& t );
        
        /**
         attach a specific component to the entity "eid"
         */
        template < typename T > T* Add( int eid );
        
        /**
         dettach a specific component from the entity "eid"
         */
        template < typename T > void Remove( int eid );
        
        /**
         release all the memory from a specific component manager
         */
        template < typename T > void Clear();
        
        /**
         send message to objects subcribed to ECM messenger
         */
        void Send( const Message& msg );
        
        /**
         get the component list of an entity
         */
        ECM::Entt* operator[]( int eid );
        
        /**
         get member : messenger
         */
        Messenger& GetMessenger();
        
        /**
         check if an entity is valid
         */
        bool Valid( unsigned int eid )const;
        
        /**
         remove an entity
         */
        virtual void Delete( int eid );
        
        /**
         create an entity
         */
        int Create();
        
        /**
         un-initialize this system
         */
        void Uninit();
        
        /**
         initialize this system
         */
        int Init();
        
        /**
         get the begin iterator for the entity list
         */
        ECM::iterator Begin();
        
        /**
         get the end iterator for the entity list
         */
        ECM::iterator End();
        
        ~ECM();
        
        ECM();
        
    protected:
        
        std::queue< int > _recycled;
        
        Components _components;
        Messenger _messenger;
        Entities _entities;
        int _entity_counter;
        
    };
}
#include "ECM.ipp"
#endif /* ECM_hpp */
