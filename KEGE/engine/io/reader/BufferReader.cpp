//
//  BufferReader.cpp
//  xmlparser
//
//  Created by Kenneth A Esdaile on 3/17/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "BufferReader.hpp"
namespace kege{
    
    long BufferReader::read(char* target, const long size, const char * flags)
    {
        if (size <= 0) return 0;
        long cnt = 0;
        const char* s, *f;
        for (s=_chrptr; *s!=0 && cnt<size; s++)
        {
            f = flags;
            while (*f != 0 && *f != *s) f++;
            if (*f != 0) break;
            target[cnt++] = *s;
        }
        target[cnt] = 0;
        long written = s - _chrptr;
        _chrptr = s;
        return written;
    }
    
    long BufferReader::read_letters(char* target, const long size)
    {
        if (size <= 0) return 0;
        long cnt = 0;
        const char* s;
        for (s=_chrptr; *s!=0 && cnt<size; s++)
        {
            if ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z'))
            {
                target[cnt++] = *s;
            }
            else break;
        }
        target[cnt] = 0;
        long written = s - _chrptr;
        _chrptr = s;
        return written;
    }
    
    long BufferReader::read_digits(char* target, const long size)
    {
        if (size <= 0) return 0;
        long cnt = 0;
        const char* s;
        for (s=_chrptr; *s!=0 && cnt<size; s++)
        {
            if (*s >= '0' && *s <= '9')
            {
                target[cnt++] = *s;
            }
            else break;
        }
        target[cnt] = 0;
        long written = s - _chrptr;
        _chrptr = s;
        return written;
    }
    
    long BufferReader::read(char* target, const long size)
    {
        if (size <= 0) return 0;
        long cnt = 0;
        const char* s;
        for (s=_chrptr; *s!=0 && cnt<size; s++)
        {
            target[cnt++] = *s;
        }
        target[cnt] = 0;
        long written = s - _chrptr;
        _chrptr = s;
        return written;
    }
    
    long BufferReader::find(const char* str,  const char * flags)
    {
        const char* s, *f;
        const char* a = _chrptr;
        while (*a != 0)
        {
            s = str;
            while ((*s == *a) && (a!=0 && s!=0))
            {
                s++;
                a++;
            }
            if (*s == 0)  return a - _chrptr;
            
            f = flags;
            while (*a!=*f && *f!=0) f++;
            if (*f!=0) return 0;
            
            a++;
        }
        return 0;
    }
    
    long BufferReader::seek(const char * flags)
    {
        const char* f;
        const char* s = _chrptr;
        while (*s != 0)
        {
            f = flags;
            while (*f != 0)
            {
                if (*s == *f )
                {
                    long n = s - _chrptr;
                    _chrptr += n;
                    return n;
                }
                f++;
            }
            s++;
        }
        if (*s == 0)
        {
            return -1;
        }
        return 0;
    }
    
    long BufferReader::skip_letters()
    {
        const char* s = _chrptr;
        while ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z')) s++;
        long n = s - _chrptr;
        _chrptr = s;
        return n;
    }
    
    long BufferReader::skip_digits()
    {
        const char* s = _chrptr;
        while (*s >= '0' && *s <= '9') s++;
        long n = s - _chrptr;
        _chrptr = s;
        return n;
    }
    
    long BufferReader::skip(const char * flags)
    {
        const char* f = flags;
        const char* s = _chrptr;
        
        f = flags;
        while (*f != 0 && *s == *f)
        {
            f++;
            s++;
        }
        if (*f == 0)
        {
            long n = s - _chrptr;
            _chrptr = s;
            return n;
        }
        if (*f == '\b') f++;
        
        const char * rest = f;
        while (*s != 0)
        {
            f = rest;
            while (*f != 0 && *s != *f) f++;
            if (*f == 0) break;
            s++;
        }
        
        long n = s - _chrptr;
        _chrptr = s;
        return n;
    }
    
    bool BufferReader::strcmp(const char * t) const
    {
        const char* s = _chrptr;
        while (*s != 0 && *t != 0) if (*s++ != *t++) return false;
        t--;
        s--;
        if ( *s == *t ) return true;
        return false;
    }
    
    bool BufferReader::chrcmp(const char * t) const
    {
        while (*t != 0)
        {
            if (*_chrptr == *t++) return true;
        }
        return false;
    }
    
    const char* BufferReader::getln()
    {
        const char* ln = _chrptr;
        seek("\n");
        if (*_chrptr == '\n') _chrptr++;
        return ln;
    }
    
    void BufferReader::operator ++(int)
    {
        if (_chrptr == nullptr) return;
        if (*_chrptr == 0) return;
        _chrptr++;
    }
    
    void BufferReader::operator +=(int n)
    {
        if (_chrptr == nullptr) return;
        if (*_chrptr == 0) return;
        _chrptr += n;
    }
    
    bool BufferReader::eof()const
    {
        if (_chrptr == nullptr) return true;
        if (*_chrptr == 0) return true;
        return false;
    }
    
    bool BufferReader::open(const ds::string& filename)
    {
        FILE * file = fopen(filename.c_str(), "r");
        if (!file)
        {
            fprintf(stderr,"error: LoadXML(%s) file not found.\n",filename.c_str());
            return false;
        }
        return load(file);
    }
    
    bool BufferReader::load(FILE * file)
    {
        if (!file)
        {
            return false;
        }
        
        fseek(file, 0, SEEK_END);
        size_t filesize = ftell(file);
        rewind(file);
        
        if (filesize == 0) return false;
        _buffer = new char[filesize];
        fread(_buffer, filesize, sizeof(char), file);
        fclose(file);
        _buffer[filesize] = '\0';
        _chrptr = _buffer;
        return true;
    }
    
    BufferReader::BufferReader(const ds::string& filename)
    {
        open(filename);
    }
    
    BufferReader::~ BufferReader()
    {
        if (_buffer != nullptr)
        {
            delete [] _buffer;
            _buffer = nullptr;
        }
        _chrptr = nullptr;
    }
    BufferReader::BufferReader(const kege::VFS::File& f)
    :   _chrptr(nullptr)
    ,   _buffer(nullptr)
    ,   _refcnt(0)
    {
        load(f.file);
    }
    
    BufferReader::BufferReader(const BufferReader& br)
    :   _chrptr(br._chrptr)
    ,   _buffer(nullptr)
    ,   _refcnt(0)
    {}
    
    BufferReader::BufferReader()
    :   _chrptr(nullptr)
    ,   _buffer(nullptr)
    ,   _refcnt(0)
    {}
//    long BufferReader::read(char* target, const long size, const char * flags)
//    {
//        long cnt = 0;
//        const char* s, *f;
//        for (s=_stream; *s!=0 && cnt<size; s++)
//        {
//            f = flags;
//            while (*f != 0 && *f != *s) f++;
//            if (*f != 0) break;
//            target[cnt++] = *s;
//        }
//        target[cnt] = 0;
//        long written = s - _stream;
//        _stream += written;
//        return written;
//    }
//
//    long BufferReader::copy(char* target, const long size)
//    {
//        long cnt = 0;
//        const char* s;
//        for (s=_stream; *s!=0 && cnt<size; s++)
//        {
//            target[cnt++] = *s;
//        }
//        return s - _stream;
//    }
//
//    /**
//     @brief  check the sequence of char in str is contain with in stream-buffer
//     @return true if found, false otherwise
//     */
//    long BufferReader::find(const char* str,  const char * flags)
//    {
//        const char* s, *f;
//        const char* a=_stream;
//        while (*a != 0)
//        {
//            s = str;
//            if (*s == *a)
//            {
//                do
//                {
//                    f = flags;
//                    while (*s != *f && *f != 0) f++;
//                    if (f != 0) return 0;
//                    s++;
//                    a++;
//                }while (*s == *a && *s!=0 && *a!=0);
//                if (s == 0)
//                {
//                    return a - _stream;
//                }
//            }
//            else
//            {
//                a++;
//            }
//        }
//        return 0;
//    }
//
//    /**
//     @brief  seek any of the characters in the string 'flag'
//     @return total number of characters skipped
//     */
//    long BufferReader::count(const char * flags)
//    {
//        const char* f;
//        const char* s = _stream;
//        while (*s != 0)
//        {
//            f = flags;
//            while (*s != *f && *s != 0 && *f != 0) f++;
//            if (*f != 0) break;
//            s++;
//        }
//        return s - _stream;
//    }
//
//    /**
//     @brief  seek and move position any of the characters in the string 'flag'
//     @return total number of characters skipped
//     */
//    long BufferReader::seek(const char * flags)
//    {
//        const char* f;
//        const char* s = _stream;
//        while (*s != 0)
//        {
//            f = flags;
//            while (*f != 0)
//            {
//                if (*s == *f )
//                {
//                    long n = s - _stream;
//                    _stream += n;
//                    return n;
//                }
//                f++;
//            }
//            s++;
//        }
//        return 0;
//    }
//
//    /**
//     @brief  skip and move position any characters not in the string 'flag'
//     @return total number of characters skipped
//     */
//    long BufferReader::skip(const char * flags)
//    {
//        const char* f = flags;
//        const char* s = _stream;
//
//        while (*s != 0)
//        {
//            f = flags;
//            while (*f != 0 && *s != *f) f++;
//            if (*f == 0) break;
//            s++;
//        }
//
//        long n = s - _stream;
//        _stream += n;
//        return n;
//    }
//
//    /**
//     @brief  check is the first couple of char match char in 'str'
//     @return true if match false otherwise
//     */
//    bool BufferReader::equal(const char * t)
//    {
//        const char* s = _stream;
//        while (*s != 0 && *t != 0) if (*s++ != *t++) return false;
//        return true;
//    }
//
//    /**
//     @brief  check is the first couple of char match char in 'str'
//     @return true if match false otherwise
//     */
//    bool BufferReader::cequal(const char * t)
//    {
//        while (*t != 0)
//        {
//            if (*_stream == *t++) return true;
//        }
//        return false;
//    }
//
//    /**
//     @brief  move position to next line
//     @return true if match false otherwise
//     */
//    const char* BufferReader::getln()
//    {
//        const char* ln = _stream;
//        seek("\n");
//        if (*_stream == '\n') _stream++;
//        return ln;
//    }
//
//    void BufferReader::operator ++(int)
//    {
//        if (_stream == nullptr) return;
//        if (*_stream == 0) return;
//        _stream++;
//    }
//
//    void BufferReader::operator +=(int n)
//    {
//        if (_stream == nullptr) return;
//        if (*_stream == 0) return;
//        _stream += n;
//    }
//
//    bool BufferReader::LoadText(const ds::string& filename)
//    {
//        FILE * file = fopen(filename.c_str(), "r");
//        if (!file)
//        {
//            fprintf(stderr,"error: LoadXML(%s) file not found.\n",filename.c_str());
//            return false;
//        }
//
//        fseek(file, 0, SEEK_END);
//        size_t filesize = ftell(file);
//        rewind(file);
//
//        if (filesize == 0) return false;
//        _buffer.setsize(filesize);
//
//        fread(_buffer.getdata(), filesize, sizeof(char), file);
//        _buffer[filesize] = '\0';
//
//        SetBufferStream(_buffer);
//        return true;
//    }
//
//    void BufferReader::SetBufferStream(const ds::string& bufr)
//    {
//        _stream = bufr.c_str();
//    }
//
//    BufferReader::BufferReader(const BufferReader& stream)
//    :   _stream(stream._stream)
//    {}
//
//    BufferReader::BufferReader()
//    :   _stream(nullptr)
//    {}
}
