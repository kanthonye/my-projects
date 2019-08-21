//
//  DataBuffer.hpp
//  dev0
//
//  Created by Kenneth A Esdaile on 6/30/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef DataBuffer_hpp
#define DataBuffer_hpp
#include <string>
#include "../../../graphics/core/cgmath/cgm.hpp"
namespace kege {namespace core{
    
    template <typename tvar>  class DataBuffer
    {   static tvar null_var;
    public:
        
        void read(tvar* ptr, short start, short count, int offset)const;
        
        void copy(const tvar* data, long stride, long count);
        void copy(const DataBuffer<tvar>& bufr);
        
        void setdata(tvar * data, long stride, long count);
        void setmem(int val);
        
        void set4(int i, tvar x, tvar y, tvar z, tvar w);
        void set3(int i, tvar x, tvar y, tvar z);
        void set2(int i, tvar x, tvar y);
        
        void add4(tvar x, tvar y, tvar z, tvar w);
        void add3(tvar x, tvar y, tvar z);
        void add2(tvar x, tvar y);
        
        void add2(const cg::vec2 &v);
        void add3(const cg::vec3 &v);
        void add4(const cg::vec4 &v);
        
        void operator *=(float v);
        
        void add(const tvar* data, long size);
        virtual void add(tvar v);
        
        tvar const* getdata()const;
        tvar * getdata();
        
        tvar get(long i)const;
        tvar& getref(long i);
        
        tvar const* operator [](long i)const;
        tvar * operator [](long i);
        
        void setbuffer(long size, short stride, long count);
        void setsize(long size);
        void resize(long size);
        
        void setstride(short s);
        void setcount(long size);
        short getstride()const;
        long count()const;
        long size()const;
        bool empty()const;
        void clear();
        
        template<class casttype> casttype * GetBuffer()
        {
            return (casttype*) buffer.data;
        }
        
        DataBuffer(long stride, long size, tvar * data);
        virtual ~ DataBuffer();
        DataBuffer();
        
    protected:
        
        virtual void operator +=(tvar a);
        
        struct tvarArray
        {
            tvar * data;
            short stride;
            long count;
            long size;
        } buffer;
    };
    
    template <typename tvar> tvar core::DataBuffer<tvar>::null_var = 0x0;
}}

namespace kege{ namespace core{

    template <typename tvar>
    void DataBuffer<tvar>::read(tvar * ptr, short start, short count, int offset)const
    {
        if (buffer.data == nullptr) return;
        unsigned int read_amount = start + count;
        unsigned int read_count = 0;
        while (start < buffer.size && start < read_amount)
        {
            ptr[read_count++] = buffer.data[start++];
        }
    }
    
    template <typename tvar>
    void core::DataBuffer<tvar>::copy(const tvar* data, long stride, long count)
    {
        clear();
        setsize(stride * count);
        setstride(stride);
        memcpy(buffer.data, data, buffer.size*sizeof(tvar));
        buffer.count = count;
    }
    
    template <typename tvar>
    void core::DataBuffer<tvar>::copy(const core::DataBuffer<tvar>& bufr)
    {
        long bcount = bufr.buffer.size / bufr.buffer.stride;
        if (buffer.data == nullptr)
        {
            copy(bufr.buffer.data, bufr.buffer.stride, bcount);
            return;
        }
        long mcount = buffer.size / buffer.stride;
        
        short bufr_stride = bufr.getstride();
        short min_stride = (buffer.stride < bufr_stride) ? buffer.stride : bufr_stride;
        long  min_count = (mcount < bcount) ? mcount : bcount;
        long  byte_stride = min_stride * sizeof(tvar);
        
        for (long i=0; i<min_count; i++)
        {
            memcpy
            (  &buffer.data[i*buffer.stride]
             , &bufr.buffer.data[i*bufr_stride]
             , byte_stride );
        }
    }
    
    template <typename tvar>
    void core::DataBuffer<tvar>::setdata(tvar * data, long stride, long count)
    {
        if(buffer.data != nullptr)
        {
            delete [] buffer.data;
            buffer.data = data;
        }
        
        buffer.size = stride * count;
        buffer.count = count;
        buffer.stride = stride;
        buffer.data = data;
    }
    
    template <typename tvar>
    void DataBuffer<tvar>::set4(int i, tvar x, tvar y, tvar z, tvar w)
    {
        getref( i ) = x;
        getref(i+1) = y;
        getref(i+2) = z;
        getref(i+4) = w;
    }
    
    template <typename tvar>
    void DataBuffer<tvar>::set3(int i, tvar x, tvar y, tvar z)
    {
        getref( i ) = x;
        getref(i+1) = y;
        getref(i+2) = z;
    }
    
    template <typename tvar>
    void DataBuffer<tvar>::set2(int i, tvar x, tvar y)
    {
        getref( i ) = x;
        getref(i+1) = y;
    }
    
    template <typename tvar>
    void DataBuffer<tvar>::add4(tvar x, tvar y, tvar z, tvar w)
    {
        add(x);
        add(y);
        add(z);
        add(w);
    }
    
    template <typename tvar>
    void DataBuffer<tvar>::add3(tvar x, tvar y, tvar z)
    {
        add(x);
        add(y);
        add(z);
    }
    
    template <typename tvar>
    void DataBuffer<tvar>::add2(tvar x, tvar y)
    {
        add(x);
        add(y);
    }
    
    template <typename tvar>
    void DataBuffer<tvar>::add4(const cg::vec4& a)
    {
        add(a.x);
        add(a.y);
        add(a.z);
        add(a.w);
    }
    
    template <typename tvar>
    void DataBuffer<tvar>::add3(const cg::vec3& a)
    {
        add(a.x);
        add(a.y);
        add(a.z);
    }
    
    template <typename tvar>
    void DataBuffer<tvar>::add2(const cg::vec2& a)
    {
        add(a.x);
        add(a.y);
    }
    
    template <typename tvar>
    void DataBuffer<tvar>::operator *= (float val)
    {
        if (buffer.data)
        {
            for (int i=0; i<count(); i++)
            {
                buffer.data[i] *= val;
            }
        }
    }
    
    
    
    
    template <typename tvar>
    void DataBuffer<tvar>::setmem(int val)
    {
        if (buffer.data == nullptr) return;
        memset(buffer.data, val, buffer.size*sizeof(tvar));
    }
    
    template <typename tvar>
    void core::DataBuffer<tvar>::add(tvar x)
    {
        operator +=(x);
    }
    
    template <typename tvar>
    tvar const* core::DataBuffer<tvar>::getdata()const
    {
        return buffer.data;
    }
    
    template <typename tvar>
    tvar * core::DataBuffer<tvar>::getdata()
    {
        return buffer.data;
    }
    
    template <typename tvar>
    tvar & DataBuffer<tvar>::getref(long i)
    {
        if (i < buffer.size)
        {
            return buffer.data[i];
        }
        return null_var;
    }
    
    template <typename tvar>
    tvar DataBuffer<tvar>::get(long i)const
    {
        if (i < buffer.size)
        {
            return buffer.data[i];
        }
        return 0;
    }
    
    template <typename tvar>
    void core::DataBuffer<tvar>::add(const tvar* data, long size)
    {
        if (buffer.size <= buffer.count) return;
        memcpy(&buffer.data[buffer.count], data, sizeof(tvar)*size);
        buffer.count += size / sizeof(tvar);
    }
    
    template <typename tvar>
    void core::DataBuffer<tvar>::operator +=(tvar a)
    {
        if (buffer.size <= buffer.count) return;
        buffer.data[ buffer.count++ ] = a;
    }
    
    template <typename tvar>
    tvar const* DataBuffer<tvar>::operator [](long i)const
    {
        if (i < buffer.size)
        {
            return &buffer.data[i];
        }
        return nullptr;
    }
    
    template <typename tvar>
    tvar * DataBuffer<tvar>::operator [](long i)
    {
        if (i < buffer.size)
        {
            return &buffer.data[i];
        }
        return nullptr;
    }
    
    template <typename tvar>
    void core::DataBuffer<tvar>::setbuffer(long size, short stride, long count)
    {
        setsize(size);
        setcount(count);
        setstride(stride);
    }
    
    template <typename tvar>
    void core::DataBuffer<tvar>::setcount(long size)
    {
        buffer.count = size;
    }
    
    template <typename tvar>
    void core::DataBuffer<tvar>::setsize(long size)
    {
        if (buffer.data != nullptr)
        {
            delete [] buffer.data;
            buffer.data = nullptr;
        }
        buffer.size = size;
        buffer.data = new tvar[buffer.size];
    }
    
    template <typename tvar>
    void core::DataBuffer<tvar>::resize(long size)
    {
        core::DataBuffer<tvar> vb;
        vb.copy(*this);
        
        setsize(size);
        setmem(0x0);
        
        copy(vb);
    }
    
    template <typename tvar>
    void DataBuffer<tvar>::setstride(short s)
    {
        buffer.stride = s;
    }
    
    template <typename tvar>
    short DataBuffer<tvar>::getstride()const
    {
        return buffer.stride;
    }
    
    template <typename tvar>
    bool core::DataBuffer<tvar>::empty()const
    {
        return count() == 0;
    }
    
    template <typename tvar>
    long core::DataBuffer<tvar>::count()const
    {
        return buffer.count;
    }
    
    template <typename tvar>
    long core::DataBuffer<tvar>::size()const
    {
        return buffer.size;
    }
    
    template <typename tvar>
    void core::DataBuffer<tvar>::clear()
    {
        if (buffer.data != nullptr)
        {
            delete [] buffer.data;
            buffer.data = nullptr;
        }
    }
    
    template <typename tvar>
    DataBuffer<tvar>::DataBuffer(long stride, long size, tvar * data)
    {
        stride = cg::max(1, (int)stride);
        buffer.count = size / stride;
        buffer.stride = stride;
        buffer.size = size;
        buffer.data = data;
    }
    
    template <typename tvar>
    DataBuffer<tvar>::DataBuffer()
    {
        buffer.data = nullptr;
        buffer.stride = 1;
        buffer.count = 0;
        buffer.size = 0;
    }
    
    template <typename tvar>
    DataBuffer<tvar>::~ DataBuffer()
    {
        clear();
        buffer.stride = 1;
        buffer.count = 0;
        buffer.data = 0;
    }
}}
#endif /* DataBuffer_hpp */
