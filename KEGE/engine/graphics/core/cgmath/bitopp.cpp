//
//  bitvec.cpp
//  column-major
//
//  Created by Kenneth A Esdaile on 7/13/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#include "../../../graphics/core/cgmath/bitopp.hpp"
namespace kege{namespace cg{
    
    cg::bit8::bit8()
    :   bits(0)
    {
    }
    
    cg::bit8::~bit8()
    {
        bits = 0;
    }
    
    const bool cg::bit8::operator[] ( UI8 index )const
    {
        UI8 bit = index % 8;
        return (bits & (1 << bit)) >> bit;
    }
    
    void cg::bit8::setbit( UI8 index, bool value )
    {
        UI8 bit = index % 8;
        if( value == true )
            bits = (bits | (1 << bit));
        else
            bits = (bits & (~(1 << bit)));
    }
    
    const bool cg::bit8::getbit( UI8 index )const
    {
        UI8 bit = index % 8;
        return (bits & (1 << bit)) >> bit;
    }
    
    void cg::bit8::clearall()
    {
        bits = 0x0;
    }
    
    void cg::bit8::setall()
    {
        bits = 0xFF;
    }
}}



namespace kege{namespace cg{
    
    cg::bit32::bit32(int n)
    :   bits(n)
    {
    }
    
    cg::bit32::bit32()
    :   bits(0)
    {
    }
    
    cg::bit32::~bit32()
    {
        bits = 0;
    }
    
    const bool cg::bit32::operator[] ( UI32 index )const
    {
        int bit = index % 16;
        return (bits & (1 << bit)) >> bit;
    }
    
    void cg::bit32::setbit( UI32 index, bool value )
    {
        int bit = index % 16;
        if( value == true )
            bits = (bits | (1 << bit));
        else
            bits = (bits & (~(1 << bit)));
    }
    
    const bool cg::bit32::getbit( UI32 index )const
    {
        int bit = index % 16;
        return (bits & (1 << bit)) >> bit;
    }
    
    void cg::bit32::clearall()
    {
        bits = 0;
    }
    
    void cg::bit32::setall()
    {
        bits = 0xFFFFFFFF;
    }
}}



namespace kege{namespace cg{
    
    cg::bit64::bit64()
    :   bits(0)
    {
    }
    
    cg::bit64::~bit64()
    {
        bits = 0;
    }
    
    const bool cg::bit64::operator[] ( int index )const
    {
        int bit = index % 32;
        return (bits & (1 << bit)) >> bit;
    }
    
    void cg::bit64::setbit( int index, bool value )
    {
        int bit = index % 32;
        if( value == true )
            bits = (bits | (1 << bit));
        else
            bits = (bits & (~(1 << bit)));
    }
    
    const bool cg::bit64::getbit( int index )const
    {
        int bit = index % 32;
        return (bit & (1 << bit)) >> bit;
    }
    
    void cg::bit64::clearall()
    {
        bits = 0;
    }
    
    void cg::bit64::setall()
    {
        bits = 0x7FFFFFFFFFFFFFFF; // 9223372036854775807 in hex
    }
}}




namespace kege{namespace cg{
    
    void cg::bitvec::resize( int size )
    {
        UL64 * newarry = 0;
        
        if (size%32 == 0) size = size / 32;
        else size = (size / 32) + 1;
        
        newarry = new UL64[size];
        if( newarry == nullptr ) return;
        
        int min;
        
        if( size < arrysize ) min = size;
        else min = arrysize;
        
        for( int i=0; i<min; i++ ) newarry[i] = bitarray[i];
        
        if( bitarray != nullptr ) delete[] bitarray;
        bitarray = newarry;
        arrysize = size;
    }
    
    const bool cg::bitvec::operator[] ( int p_index )const
    {
        int cell = p_index / 32;
        int bit = p_index % 32;
        return (bitarray[cell] & (1 << bit)) >> bit;
    }
    
    void cg::bitvec::set( int p_index, bool p_value )
    {
        int cel = p_index / 32;
        int bit = p_index % 32;
        if( p_value == true )
            bitarray[cel] = (bitarray[cel] | (1 << bit));
        else
            bitarray[cel] = (bitarray[cel] & (~(1 << bit)));
    }
    
    void cg::bitvec::clearall()
    {
        for( int i=0; i<arrysize; i++ ) bitarray[i] = 0;
    }
    
    void cg::bitvec::setall()
    {
        for( int i=0; i<arrysize; i++ ) bitarray[i] = 0xFFFFFFFF;
    }
    
    cg::bitvec::bitvec( int size )
    :   bitarray(nullptr)
    ,   arrysize(0)
    {
        resize( size );
    }
    
    cg::bitvec::~ bitvec()
    {
        if( bitarray != 0 )delete[] bitarray;
        bitarray = 0;
    }
    
    cg::bitvec::bitvec()
    :   bitarray(nullptr)
    ,   arrysize(0)
    {
    }
    
}}

