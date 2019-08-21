// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//  DST
//  Header.h
//  Created by Kenneth Anthony Esdaile on 6/18/14.
//  Modifiede on 11/15/15
//  Copyright (c) 2014 kae. All rights reserved.
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __DS__ARRAY__
#define __DS__ARRAY__
#ifndef kege_ds
#   define kege_ds ds
#endif
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cstring>
#include <stdarg.h>
namespace kege{namespace kege_ds{
    
    template<class var>  class array
    {
    public:
        
        virtual const var& operator [] (const long index) const;
        virtual var& operator [] (const long index);
        
        virtual const var& at(const long index) const;
        virtual var& at(const long index);
        
        void resize(long size);
        
        bool empty(void) const;
        
        long size(void)const;
        
        void clear(void);
        
        const var* data()const;
        var* data();
        
        array(long size, var* data);
        
        virtual ~ array(void);
        
        array(long isize);
        
        array (void);
        
    protected:
        
        var* _data;
        long _size;
    };
    
    template<class var>  const var& array< var >::operator [] (const long index) const
    {
        return _data[index];
    }
    
    template<class var>  var& array< var >::operator [] (const long index)
    {
        return _data[index];
    }
    
    template<class var>  const var& array< var >::at(const long index) const
    {
        return operator []( index );
    }
    
    template<class var>  var& array< var >::at(const long index)
    {
        return operator []( index );
    }
    
    template<class var>  void array< var >::resize(long size)
    {
        var* arry = new var[size];
        size = (_size < size) ? size : _size;
        
        if (_data != nullptr)
        {
            for (long i=0; i<size; i++) arry[i] = _data[i];
            clear();
        }
        
        _data = arry;
        _size = size;
    }
    
    template <class var>  bool array< var >::empty(void) const
    {
        return _data == nullptr || _size == 0;
    }
    
    template <class var>  long array< var >::size(void)const
    {
        return _size;
    }
    
    template <class var>  void array< var >::clear(void)
    {
        if (_data != nullptr)
        {
            delete [] _data;
            _data = nullptr;
        }
        _size = 0;
    }
    
    template <class var>  const var* array< var >::data()const
    {
        return _data;
    }
    template <class var>  var* array< var >::data()
    {
        return _data;
    }
    
    template <class var>  array< var >::array(long size, var* data)
    :   _data(data)
    ,   _size(size)
    {}
    
    template<class var>  array< var >::array(long size)
    :   _data(new var[size])
    ,   _size(size)
    {
        resize( size );
    }
    
    template<class data>  array< data >::~ array()
    {
        clear();
    }
    
    template<class data>  array< data >::array()
    :   _data(nullptr)
    ,   _size(0)
    {}
}}
#endif
