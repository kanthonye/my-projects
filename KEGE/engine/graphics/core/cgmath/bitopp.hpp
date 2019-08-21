//
//  bitvec.hpp
//  column-major
//
//  Created by Kenneth A Esdaile on 7/13/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef bitvec_hpp
#define bitvec_hpp
#include "../../../graphics/core/cgmath/coremath.hpp"
namespace kege{namespace cg{
    
    class bit8
    {
        typedef unsigned char UI8;
    protected:
        UI8 bits;
    public:
        bit8();
        
        ~bit8();
        
        const bool operator[] ( UI8 index )const;
        
        void setbit( UI8 index, bool value );
        
        const bool getbit( UI8 index )const;
        
        void clearall();
        
        void setall();
    };
}}

namespace kege{namespace cg{
    
    class bit32
    {
        typedef unsigned int UI32;
    protected:
        UI32 bits;
    public:
        
        bit32(int n);
        ~bit32();
        bit32();
        
        const bool operator[] ( UI32 index )const;
        
        void setbit( UI32 index, bool value );
        
        const bool getbit( UI32 index )const;
        
        void clearall();
        
        void setall();
        
        UI32 getval()const{return bits;}
    };
}}

namespace kege{namespace cg{
    
    class bit64
    {
        typedef unsigned long int UL64;
    protected:
        UL64 bits;
    public:
        bit64();
        
        ~bit64();
        
        const bool operator[] ( int index )const;
        
        void setbit( int index, bool value );
        
        const bool getbit( int index )const;
        
        void clearall();
        
        void setall();
    };
}}

namespace kege{namespace cg{
    
    class bitvec
    {
        typedef unsigned long int UL64;
    protected:
        UL64 * bitarray;
        int    arrysize;
    public:
        
        void resize( int size );
        
        const bool operator[] ( int p_index )const;
        
        void set( int p_index, bool p_value );
        
        void clearall();
        
        void setall();
        
        bitvec( int size );
        ~ bitvec();
        bitvec();
    };
}}
#endif /* bitvec_hpp */
