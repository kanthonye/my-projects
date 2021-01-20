//
//  Cache.cpp
//  test
//
//  Created by Kenneth A Esdaile on 11/7/20.
//  Copyright © 2020 Kenneth A Esdaile. All rights reserved.
//

#include "Cache.hpp"
namespace kege
{
    const void* Cache::operator[]( const Cache::Index& index )const
    {
        if ( _memory.size() <= index.id ) return nullptr;
        return &_memory[ index.id ];
    }
    
    void* Cache::operator[]( const Cache::Index& index )
    {
        if ( _memory.size() <= index.id ) return nullptr;
        return &_memory[ index.id ];
    }
    
    Cache::Index Cache::Alloc()
    {
        if ( _trash > 0 ) 
        {
            return _recycle[ _trash-- ];
        }
        
        // compute the component index in memory
        Cache::Index index = (int)(_count * _elem_size);
        
        // if the component index id is larger than memory resize memory
        if ( _capacity <= _count )
        {
            _capacity = (_capacity * 1.5 + 1);
            int memsize = _capacity * _elem_size;
            _memory.resize( memsize );
        }
        
        _count++;
        return index;
    }
    
    void Cache::Free( Cache::Index cid )
    {
        if ( _recycle.size() <= _trash )
        {
            _recycle.push_back( cid );
        }
        else
        {
            _recycle[ _trash ] = cid;
        }
        _trash++;
    }
    
    unsigned int Cache::SizeOfElem()const
    {
        return _elem_size;
    }
    
    unsigned int Cache::MemorySize()const
    {
        return (unsigned int)_memory.size();
    }
    
    unsigned int Cache::Capacity()const
    {
        return _capacity;
    }
    
    void Cache::Clear()
    {
        _recycle.clear();
        _memory.clear();
    }

    Cache::Index Cache::IndexOf( const void* ptr )const
    {
        unsigned int index = ( unsigned int ) ( ((const char*)ptr) - &_memory[0] );
        if ( _memory.size() <= index )
        {
            return Cache::Index();
        }
        return Cache::Index( index );
    }
    
    Cache::Cache(  int elem_size, int capacity )
    :   _elem_size( elem_size )
    ,   _capacity( capacity )
    ,   _count( 0 )
    ,   _trash( 0 )
    {
        int poolsize = _elem_size * _capacity;
        _memory.resize( poolsize );
    }
}
