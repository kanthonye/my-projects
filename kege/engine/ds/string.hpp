/*! @author     Kenneth Anthony Esdaile
 *  @date       created on 11/1/14
 *  @copyright  Copyright (c) 2014 kae. All rights reserved.
 *  @file       string.hpp
 *  @project    data structure containers. */
#ifndef __charstr__
#define __charstr__
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cstring>
#include <stdarg.h>

namespace kege{
    
    typedef const unsigned int cuint;
    typedef const char * ccptr;
    const char endchar = 0;
    
    namespace ds{
        
        /*! string (char string) is a an array data structure of characters for a string of char
         *  which does string minipulation. such as adding, copying, and comparing
         *  string character etc...*/
        class string
        {
        public:
            
            friend string operator + (const char * str, const string & other);
            friend string operator + (const string & a, const char c);
            friend string operator + (const char c, const string & other);
            friend string operator + (const string & left, const string & right);
            
            friend bool operator < (const char * str, const string & other);
            friend bool operator < (const string & other, const char * str);
            friend bool operator > (const char * str, const string & other);
            friend bool operator > (const string & other, const char * str);
            friend bool operator <= (const char * str, const string & other);
            friend bool operator <= (const string & other, const char * str);
            friend bool operator >= (const char * str, const string & other);
            friend bool operator >= (const string & other, const char * str);
            friend bool operator == (const char * str, const string & other);
            friend bool operator == (const string & other, const char * str);
            friend bool operator != (const char * str, const string & other);
            friend bool operator != (const string & other, const char * str);
            friend bool operator < (const string & A, const string & B);
            friend bool operator > (const string & A, const string & B);
            friend bool operator <= (const string & A, const string & B);
            friend bool operator >= (const string & A, const string & B);
            friend bool operator == (const string & A, const string & B);
            friend bool operator != (const string & A, const string & B);
            
            struct hasher
            {
                enum
                {
                    A = 54059, /* a prime */
                    B = 76963, /* another prime */
                    C = 86969, /* yet another prime */
                    FIRSTH  =37 /* also prime */
                };
                
                std::size_t operator()(const kege::ds::string& k) const
                {
                    if( k.empty() ) return 0;
                    
                    const char * s = k.c_str();
                    
                    unsigned h = FIRSTH;
                    while (*s)
                    {
                        h = (h * A) ^ (s[0] * B);
                        s++;
                    }
                    return h;
                }
            };
            
        public:
            
            struct chrstr
            {
                chrstr(char* d, long s):size(s),data(d){}
                chrstr():size(0),data(NULL){}
                long  size;
                char* data;
            };
            
            static ds::string add(const char * p, long psize, const char * q, long qsize);
            static ds::string::chrstr va_list_print(char const* format, va_list& argptr);
            static string strprint(ccptr format, ...);
            
            static std::size_t hash(const char* str);
            std::size_t hash()const;
            
            double to_float()const;
            long to_long()const;
            int to_int()const;
            
            /*
             return true if data is NULL or data[0]='\0'
             */
            bool copy(long offset, const char* str, long size, long start, long end);
            void copy(const char* str, long size);
            
            void overwrtie(long start, long size, const char* str);
            
            void setstring(long strsize, char* str);
            void add(const char* str, long size);
            
            /*
             return true if data is NULL or data[0]='\0'
             */
            const bool cmp(const char* str, long size);
            
            /*
             return true if data is NULL or data[0]='\0'
             */
            const bool empty(void) const;
            
            /*
             set data[0] to '\0' if not NULL
             */
            void clear(void);
            
            /*
             set strsize to size
             */
            void setlength(const long size);
            
            /*
             set strsize to size
             */
            void setsize(const long size);
            
            /*
             resize the string
             */
            void resize(long length);
            
            /*
             return the length of the strsize
             */
            const long length(void) const;
            
            /*
             return pointer to string
             */
            char * getdata(void);
            
            /*
             return pointer to string
             */
            const char * c_str(void) const;
            
            string & sprint(ccptr format, ...);
            
            string tolowercase(void)const;
            string touppercase(void)const;
            string parse_fext()const;
            string parse_name()const;
            string parse_fpath()const;
            string parse_fname()const;
            
            inline char & operator [] (const unsigned long i) const { return str.data[i]; }
            
            void operator += (const string & a);
            void operator += (const char * str);
            void operator += (const char c);
            
            void operator = (const string & other);
            void operator = (const char * cstr);
            
            string operator + (const string & a);
            string operator + (const char * str);
            string operator + (const char chr);
            
            string (char* str, long size, long len);
            string (char const* str, long size);
            string (char* str, long size);
            string (const string & other);
            string (const char * cstr);
            string (string & other);
            string (char* cstr);
            string ();
            
            virtual ~string (void);
            
        private:
            
            chrstr str;
            long size;
        };
        
        typedef string String;
        
        ds::string add(const char * p, long psize, const char * q, long qsize);
    }
    bool cequal(char c, const char * flags);
    long strsize(const char * str, const char * flags);
    long strskip(const char * str, const char * flags);
    
    
    long str_cwspace(const char *& p);
    
    const char * readinput (void);
    
    /**
     @brief copy from one string to another.
     @param str = string length to compute
     @return length of string
     */
    unsigned int str_len(const char * str);
    
    /**
     @brief copy from one string to another.
     @param left = the string being copied to
     @param right = the string being copied from
     @param flags = string of char to check equality, if equal then stop copying
     @return the number of characters copied
     */
    int str_cpyf(char * left, const char *right, const char * flags);
    
    /**
     @brief copy from one string to another.
     @param to = the buffer to store the copied string to
     @param size = the size of the string being copied.
     @param from = the string being copied
     @return the number of characters copied
     */
    long str_cpy (char * to, const long size, const char * from);
    
    /**
     @brief copy from one string to another.
     @param bufr = the buffer to store the copied string to
     @param bsize = the buffer size.
     @param bfrom = starting index to start copying to.
     @param bto = ending index to stop copying to.
     @param cstr = the string being copied.
     @param csize = the size of the string being copied.
     @param cfrom = starting index to start copying from.
     @return the number of characters copied
     */
    long str_cpy(char * bufr,long const bsize,long const bfrom,long const bto, ccptr cstr,long const csize,long const cfrom);
    
    long str_cpy(char * p,long psize, long pstart, ccptr q, long qsize, long qstart, long readsize);
    /**
     @brief compare two strings
     */
    int str_cmp(const char * left,const char * right);
    
    /**
     @brief resize a string
     @param cptr hold the pointer to the resized string
     @param size the size to resize the string to
     @warning the string must be deleted after finish using
     */
    unsigned str_resize (char * cptr, const unsigned size);
    
    /**
     @brief check if a char is equal to a string of characters, return true if any one of the string of characters are equal to c
     @param c the char to compare
     @param flags the string of char to check equality from
     */
    bool str_equal (char c, const char * flags);
    
    /**
     @brief keep counting characters until a flag is cought
     @param line the string of char to compare to the string of flags
     @param flags the string of char to check equality from
     */
    int str_count (const char * line, const char * flags);
    
    long str_copy(char * bufr, int bsize, const char *str, const char * flags);
    
    /**
     @brief search for a string element in a string and return a pointer to the starting index
     @param elem is the string element to find
     @param line is the string buffer to search
     @param flags are the terminating elements
     @return return a char pointer to current index.
     */
    const char * str_nextelem(const char * elem, const char * line, const char * flags);
    
    /**
     @brief search for a string element in a string and return a pointer to the starting index
     @param elem is the string element to find
     @param line is the string buffer to search
     @return return a char pointer to current index.
     */
    const char * str_nextelem(const char * elem, const char * line);
    
    /**
     skip all character other than the ones contained in flags
     @param str the string input.
     @param flags the characters to stop at.
     @return the string position.
     */
    const char * str_next(const char * line, const char * flags);
    char * str_next(char * line, const char * flags);
    
    /**
     skip all current character contain in flags
     @param str the string input.
     @param flags the characters to stop at.
     @return the string position.
     */
    const char * str_skip(const char * str, const char * flags);
    char * str_skip(char * str, const char * flags);
    
    /**
     check if a string contains a particlar character.
     @param str the string to search.
     @param flags the characters to look for.
     */
    bool str_has(const char* str, const char* flag);
    
    /**
     skip a string element separated by space.
     @param str the string input.
     @return the string position.
     */
    const char* str_skipword(const char* str);
    
    
    const char * str_newln(const char * str);
    char * str_newln(char * str);
    
    /**
     @brief break a string up into token
     @param buffer the string to break up
     @param flags how to break up the string
     @return return a string token.
     */
    char * str_tok (char * buffer, const char * flags);
    char * str_tok(char *& bufr, char * buffer, const char * flags);
    
    /**
     @brief same as str_tok() except that the two parameter are constant.
     @param buffer the string to break up
     @param flags how to break up the string
     @return return a string token.
     */
    char * str_word (const char * buffer, const char * flags);
    
    int str_ispath(const char * path);
    
    int str_isfile(const char * path);
    
    char * str_parse_name(char * filename);
    
    char * str_parse_fext(char * path);
    
    char * str_parse_fname(char * filename);
    
    char * str_parse_fpath(char * path);
    
    char * str_parse_fpath(char * buffer, unsigned int bsize, const char * filename);
    
    bool string_contain(char const* word, char const* curr, const char * flags);
    bool string_match(const char * q, const char * p, const char * flags);
    bool string_equal(char const* word, char const* curr);
    
    
    kege::ds::string srinkpath(const kege::ds::string& fname, const kege::ds::string& path);
}
#endif /* defined(__Component_Development__charstr__) */
