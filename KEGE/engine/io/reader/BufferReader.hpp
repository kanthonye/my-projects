//
//  BufferReader.hpp
//  xmlparser
//
//  Created by Kenneth A Esdaile on 3/17/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef BufferReader_hpp
#define BufferReader_hpp
#include "string.hpp"
#include "Reader.hpp"
namespace kege{
    
    class BufferReader : public kege::Reader
    {
    public:
        
        /**
         @brief  write buffer data to target char array
         @param  target is the char array you want data written to.
         @param  size is the array size of target char array.
         @param  flags are character that will stop the writing process.
         @return the number of characters written
         */
        long read(char* target, const long size, const char * flags);
        
        /**
         @brief  write letter character to target char array
         @param  target is the char array you want data written to.
         @param  size is the array size of target char array, and the number of character to read.
         @return the number of characters written
         */
        long read_letters(char* target, const long size);
        
        /**
         @brief  write numerical character to target char array
         @param  target is the char array you want data written to.
         @param  size is the array size of target char array, and the number of character to read.
         @return the number of characters written
         */
        long read_digits(char* target, const long size);
        
        /**
         @brief  write buffer data to target char array
         @param  target is the char array you want data written to.
         @param  size is the array size of target char array, and the number of character to read.
         @return the number of characters written
         */
        long read(char* target, const long size);
        
        /**
         * @brief  search string buffer for the first string that matched all the chars in str,
         *         stop search if any chars in char array flag is encountered
         * @return position where the string is found
         */
        long find(const char* str,  const char * flags);
        
        /**
         @brief  skip the preceding chars until any chars in the char array flags is found
         @return total character skipped;
         */
        long seek(const char * flags);
        
        /**
         @brief  skip the preceding chars that equal any chars in the char array flags
         @return total character skipped;
         */
        long skip(const char * flags);
        
        /**
         @brief  compare the preceding char to any of the char in the char array str
         @return true if any char is equal, false otherwise
         */
        bool chrcmp(const char* str) const;
        
        /**
         @brief  compare the preceding chars to the chars in the char array str
         @return true if all chars match, false otherwise
         */
        bool strcmp(const char* str) const;
        
        /**
         * @brief  skip all letter chars
         * @return total character skipped
         */
        long skip_letters();
        
        /**
         * @brief  skip all digit chars
         * @return total character skipped
         */
        long skip_digits();
        
        /**
         * @brief  get a line of chars
         * @return char pointer
         */
        const char* getln();
        
        /**
         * @brief  end of file (eof) : check if char buffer is empty, or end of buffer
         * @return true if eob or null
         */
        bool eof()const;
        
        /**
         * @brief  move forward n places
         */
        inline void operator +=(long n)
        {
            if (_chrptr == nullptr) return;
            _chrptr += n;
        }
        
        /**
         * @brief  move backward n places
         */
        inline void operator -=(long n)
        {
            if (_chrptr == nullptr) return;
            _chrptr -= n;
        }
        
        /**
         * @brief  move forward 1 place
         */
        void operator +=(int n);
        
        /**
         * @brief  move backward 1 place
         */
        void operator ++(int);
        
        /**
         @brief  check if the preceding char is a letter char
         @return true preceding char is letter, false otherwise
         */
        inline long char_letter() const
        {
            return (*_chrptr >= 'a' && *_chrptr <= 'z') || (*_chrptr >= 'A' && *_chrptr <= 'Z');
        }
        
        /**
         @brief  check if the preceding char is a digit char
         @return true preceding char is digit, false otherwise
         */
        inline long char_digit() const
        {
            return *_chrptr >= '0' && *_chrptr <= '9';
        }
        
        /**
         @brief  set beffer reader eqial to another buffer reader
         */
        inline void operator =(const BufferReader& br)
        {
            _chrptr = br._chrptr;
        }
        
        /**
         @brief  set beffer reader eqial to char array
         */
        inline void operator =(const char* cstr)
        {
            _chrptr = cstr;
        }
        
        /**
         @brief  check equality against preceding char
         @return true char match found, false otherwise
         */
        inline bool operator ==(const char* cstr) const
        {
            if (_chrptr == nullptr) return false;
            return strcmp(cstr);
        }
        
        /**
         @brief  check equality against preceding char
         @return true char match not found, false otherwise
         */
        inline bool operator !=(const char* cstr) const
        {
            if (_chrptr == nullptr) return false;
            return !strcmp(cstr);
        }
        
        /**
         @brief  check equality against preceding char
         @return true char match found, false otherwise
         */
        inline bool operator ==(int c) const
        {
            return *_chrptr == c;
        }
        
        /**
         @brief  check equality against preceding char
         @return true char match not found, false otherwise
         */
        inline bool operator !=(int c) const
        {
            return *_chrptr != c;
        }
        
        /**
         @brief  boolean less-than or equal comparison test against preceding char
         @return true if preceding char is less-than or equal param c, false otherwise
         */
        inline bool operator <=(int c) const
        {
            return *_chrptr <= c;
        }
        
        /**
         @brief  boolean greater-than or equal comparison test against preceding char
         @return true if preceding char is greater-than or equal param c, false otherwise
         */
        inline bool operator >=(int c) const
        {
            return *_chrptr >= c;
        }
        
        /**
         @brief  boolean less-than comparison test against preceding char
         @return true if preceding char is less-than param c, false otherwise
         */
        inline bool operator <(int c) const
        {
            return *_chrptr < c;
        }
        
        /**
         @brief  boolean greater-than comparison test against preceding char
         @return true if preceding char is greater-than param c, false otherwise
         */
        inline bool operator >(int c){return *_chrptr > c;}
        
        /**
         @return preceding char ascii value
         */
        inline int ascii(){return *_chrptr;}
        
        /**
         @return buffer char pointer
         */
        inline const char* operator *() const
        {
            return _chrptr;
        }
        
        /**
         @return buffer char pointer
         */
        inline long operator -(const BufferReader& br) const
        {
            return _chrptr - br._chrptr;
        }
        
        bool open(const ds::string& filename);
        bool load(FILE * file);
        
        BufferReader(const ds::string& filename);
        BufferReader(const kege::VFS::File& f);
        BufferReader(const BufferReader& br);
        ~ BufferReader();
        BufferReader();
        
        
    private:
        
        const char* _chrptr;
        char* _buffer;
        int _refcnt;
    };
}
#endif /* BufferStream_hpp */
