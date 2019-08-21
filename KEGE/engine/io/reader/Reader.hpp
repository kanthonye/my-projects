//
//  Stream.hpp
//  xmlparser
//
//  Created by Kenneth A Esdaile on 3/17/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef Stream_hpp
#define Stream_hpp
#include <stdio.h>
#include "VFS.hpp"
namespace kege{
    
    class Reader
    {
    public:
        
        /**
         @brief  copy token to target
         @param  flags stops the copying process if any char in flag equal to last target char
         @note   char pointer position will change position
         @return point to current position
         */
        virtual long read(char* target, const long size, const char * flags) = 0;
        
        virtual long read_letters(char* target, const long size) = 0;
        
        virtual long read_digits(char* target, const long size) = 0;
        
        /**
         @brief  copy buffer to target
         @note   char pointer position will not change
         @return total written chars
         */
        virtual long read(char* target, const long size) = 0;
        
        /**
         @brief  check the sequence of char in str is contain with in stream-buffer
         @return true if found, false otherwise
         */
        virtual long find(const char* str,  const char * flags) = 0;
        
        /**
         @brief  seek and move position any of the characters in the string 'flag'
         @return total number of characters skipped
         */
        virtual long seek(const char * flags) = 0;
        
        /**
         @brief  skip and move position any characters not in the string 'flag'
         @return total number of characters skipped
         */
        virtual long skip(const char * flags) = 0;
        
        /**
         @brief  check is the first couple of char match char in 'str'
         @return true if match false otherwise
         */
        virtual bool strcmp(const char * token)const = 0;
        
        /**
         @brief  check the first char is 'c'
         @return true if match false otherwise
         */
        virtual bool chrcmp(const char* str)const = 0;
        
        /**
         @brief  move position to next line
         @return true if match false otherwise
         */
        virtual const char* getln() = 0;
        
        /*
         @brief  increase buffer position by one
         */
        virtual void operator ++(int) = 0;
        
        /*
         @brief  increase buffer position by n
         */
        virtual void operator +=(int n) = 0;
    };
}
#endif /* Stream_hpp */
