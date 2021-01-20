//
//  Cache.hpp
//  test
//
//  Created by Kenneth A Esdaile on 11/7/20.
//  Copyright © 2020 Kenneth A Esdaile. All rights reserved.
//

#ifndef Cache_hpp
#define Cache_hpp
#include <vector>
#include "Object.hpp"
namespace kege
{    
    class Cache : public ObjectType< Cache >
    {
    public:
        
        class Index
        {
        public:
            
            inline friend bool operator ==(const Cache::Index& a, const Cache::Index& b) { return a.id == b.id; }
            inline friend bool operator !=(const Cache::Index& a, const Cache::Index& b) { return a.id != b.id; }
            inline int operator /(int n)const{ return (id / n); }
            inline int operator *(int n)const{ return (id * n); }
            inline int operator -(int n)const{ return (id - n); }
            inline int operator +(int n)const{ return (id + n); }
            inline int operator *()const{return id;}
            
            Index(const Index& I): id(I.id) {}
            Index():id(-1){}
            
        private:
            
            Index(int i): id(i) {}
            friend Cache;
            int id;
        };
        
    public:
        
        typedef std::vector< Cache::Index > Recycler;
        typedef std::vector< char > Memory;
        
        /* 
         return a point to the given index. null is returned if index is out of bound 
         */
        const void* operator[]( const Cache::Index& comp )const;
        
        /* 
         return a point to the given index. null is returned if index is out of bound
         */
        void* operator[]( const Cache::Index& comp );
        
        /* 
         IndexOf() return the index of the pointer
         */
        Cache::Index IndexOf( const void* ptr )const;
        
        /* 
         Alloc() create memory to store data and return the index of the data
         */
        Cache::Index Alloc();
        
        /* 
         Free() deletes the memory at the given index
         */
        void Free( Cache::Index comp );
        
        unsigned int SizeOfElem()const;
        
        /* 
         Size() return the cache memory size
         */
        unsigned int MemorySize()const;
        
        /* 
         Size() return the cache memory size
         */
        unsigned int Capacity()const;
        
        /* 
         Clear() release the entire memory held by this object
         */
        void Clear();
        
        virtual ~ Cache(){}
        
    protected:
        
        Cache( int elem_size, int capacity );
        
    protected:
        
        /* 
         _recycler will be use to recycle deleted memory 
         */
        Recycler _recycle;
        
        /* 
         _memory hold the data
         */
        Memory _memory;
        
        int _capacity;
        int _count;
        
        /* 
         _elem_size hold the size of a single element in memory 
         */
        int _elem_size;
        
        /* 
         _cache_type hold the type id of this object 
         */
        int _cache_type;
        
        /* 
         _trash hold the number of deleted elements 
         */
        int _trash;
    };
}

namespace kege
{    
    template< typename T > class CacheType : public Cache
    {
    public:
        
        const T* Get( Cache::Index comp_id )const
        {
            return (T*) operator[]( comp_id );
        }
        
        T* Get( Cache::Index comp_id )
        {
            return (T*) operator[]( comp_id );
        }
        
        CacheType( int size )
        :   Cache( sizeof( T ), size )
        {}
        
        CacheType()
        :   Cache( sizeof( T ), 1 )
        {}
        
        ~ CacheType()
        {
            for (int i=0; i<_memory.size(); i+=_elem_size)
            {
                ((T*) (&_memory[ i ]))->~T();
            }
        }
        
    private:
        
        static int _CACHE_TYPE;
    };
    
    template< typename T > int CacheType< T >::_CACHE_TYPE = CacheType< T >::GenType();
}
#endif /* Cache_hpp */
