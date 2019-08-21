/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/12/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       dynarry.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef dynarry_hpp
#define dynarry_hpp
#include "../ds/array.hpp"
namespace kege{namespace kege_ds{
    
    template<class var>  class dynarry : public kege_ds::array< var >
    {
    public:
        
        inline void setcount(long value);
        inline long count() const;
        void append(var data);
        
        dynarry(long size, var* data);
        
        dynarry(long isize);
        
        dynarry (void);
        
    protected:
        
        long _count;
    };
    
    template <class var>  inline void dynarry< var >::setcount(long value)
    {
        _count = value;
    }
    
    template <class var>  inline long dynarry< var >::count() const
    {
        return _count;
    }
    
    template <class var>  void dynarry< var >::append(var data)
    {
        if ( count() >= array< var >::size() )
        {
            array< var >::resize( count() * 2 + 1 );
        }
        array< var >::at( _count++ ) = data;
    }
    
    template <class var>  dynarry< var >::dynarry(long size, var* data)
    :   kege_ds::array< var >(size, data)
    ,   _count(0)
    {}
    
    template<class var>  dynarry< var >::dynarry(long size)
    :   kege_ds::array< var >( size )
    ,   _count(0)
    {}
    
    template<class data>  dynarry< data >::dynarry()
    :   _count(0)
    {}
}}
#endif /* dynarry_hpp */
