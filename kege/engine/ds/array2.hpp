/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/30/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       array2.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef array2_hpp
#define array2_hpp
#include <stdio.h>
#include <cstring>
namespace kege {namespace ds{
    
    template <class var>  class array2
    {
        typedef unsigned int uint;
    public:
        
        void operator  =( const array2< var >& other );
        
        const var& operator ()( int x, int y )const;
        var& operator ()( int x, int y );
        
        const var& operator []( int i )const;
        var& operator []( int i );
        
        void resize( int width, int height );
        
        void set(int col,int row, var d);
        var& at( int x, int y ) const;
        
        
        int  height()const;
        int  width()const;
        bool empty()const;
        void clear();
        
        array2( int width, int height, var* d );
        array2( int width, int height );
        virtual ~ array2();
        array2();
        
    protected:
        
        var* _data;
        uint _height;
        uint _width;
    };
    
    
    template<class var>  void array2< var >::operator =( array2< var > const& other )
    {
        clear();
        long size = _width * _height;
        _data = new var[ size ];
        memcpy( _data, other._data, size * sizeof(var) );
    }
    
    template<class var>  var const& array2< var >::operator()( int x, int y )const
    {
        if (_width <= x || _height <= y ) throw "array2::operator()( int x, int y )const : out of bound index.";
        return _data[ _width * y + x ];
    }
    
    template<class var>  var & array2< var >::operator()( int x, int y )
    {
        if (_width <= x || _height <= y ) throw "array2::operator()( int x, int y )const : out of bound index.";
        return _data[ _width * y + x ];
    }
    
    template<class var>  const var& array2< var >::operator[]( int i ) const
    {
        return _data[i];
    }
    
    template<class var>  var& array2< var >::operator[]( int i )
    {
        return _data[i];
    }
    
    template< typename var >  void array2< var >::resize( int W, int H )
    {
        var* newarry = new var[ W * H ];
        if ( _data != nullptr )
        {
            H = ( _height <= H ) ? _height: H;
            W = ( _width  <= W ) ? _width : W;
            uint i  = 0;
            
            for ( uint w,h=0; h<H; h++ )
            {
                for ( w=0; w<W; w++ )
                {
                    i = W * h + w;
                    newarry[ i ] = _data[ i ];
                }
            }
            
            delete [] _data;
            _data   = newarry;
            _height = H;
            _width  = W;
        }
        else
        {
            _data = newarry;
            _height = H;
            _width  = W;
        }
    }
 
    template< typename var >  bool array2< var >::empty() const
    {
        return _data == nullptr;
    }
    
    template< typename var >  int array2< var >::height() const
    {
        return _height;
    }
    
    template<class var>  int array2< var >::width()const
    {
        return _width;
    }
    
    template< typename var >  void array2< var >::clear(void)
    {
        if ( _data!= nullptr )
        {
            delete [] _data;
            _data = nullptr;
            _height = 0;
            _width = 0;
        }
    }
    
    template<class var>  void array2< var >::set( int x, int y, var d )
    {
        operator()( x, y ) = d;
    }
    
    template<class var>  var& array2< var >::at( int x, int y ) const
    {
        return operator()( x, y );
    }
    
    
    template< typename var >  array2< var >::array2( int width, int height, var* d )
    :   _data( new var[ height * width ] )
    ,   _height( height )
    ,   _width( width )
    {}
    
    template< typename var >  array2< var >::array2( int width, int height )
    :   _data( new var[ height * width ] )
    ,   _height( height )
    ,   _width( width )
    {}
    
    template< typename var >  array2< var >::~array2()
    {
        clear();
    }
    
    template< typename var >  array2< var >::array2()
    :   _data( nullptr )
    ,   _height( 0 )
    ,   _width( 0 )
    {}
}}
#endif /* array2_hpp */
