/*! @author     Kenneth Anthony Esdaile
 *  @date       created on 6/20/14
 *  @copyright  Copyright (c) 2014 kae. All rights reserved.
 *  @file       charlist.h
 *  @project    data structure containers. */
//       ___           ___           ___
//      /__/|         /  /\         /  /\
//     |  |:|        /  /::\       /  /:/_
//     |  |:|       /  /:/\:\     /  /:/ /\
//   __|  |:|      /  /:/~/::\   /  /:/ /:/_
//  /__/\_|:|____ /__/:/ /:/\:\ /__/:/ /:/ /\
//  \  \:\/:::::/ \  \:\/:/__\/ \  \:\/:/ /:/
//   \  \::/~~~~   \  \::/       \  \::/ /:/
//    \  \:\        \  \:\        \  \:\/:/
//     \  \:\        \  \:\        \  \::/
//      \__\/         \__\/         \__\/
#ifndef DST_CHARSTR_H
#define DST_CHARSTR_H
#include <stdlib.h>
#include "string.hpp"
#ifndef kae_ds
#define kae_ds ds
#endif
namespace kege{namespace kae_ds{
    /*! @author Kenneth A Esdaile
     *  @date January 6, 2015
     *  @copyright Copyright (c) 2015 kae. All rights reserved.
     *
     *  charlist (list string) is a linked list data structure for characters
     *  which does string minipulation. such as adding, copying, and comparing
     *  string character, this data structure is implemented for fast removal 
     *  and adding of character...*/
    class charlist
    {
    public:
        struct Slot
        {
            char data;
            Slot * next;
            Slot * prev;
            ~Slot(){}
        };
    private:
        Slot * head;
        Slot * tail;
        Slot * position;
        Slot * lastpos;
        unsigned long size;
        
    public:
        
         charlist            ( void );
         charlist            ( const char c );
         charlist            ( const char * str );
        
         charlist            ( const charlist & other );
         charlist            ( const charlist * other );
        ~charlist            ( void );
        
        ds::string toString      ( void ) const;
        char* toCstr      (char * buffer, unsigned long size) const;
        
        char   top          ( void ) const;
        char   bottom       ( void ) const;
        
    
        int append          (const charlist & other);
        void append         (const char c);
        void prepend        (const char c);
        int append          (const char *str);
        int prepend         (const char *str);
        
        int append          (const char *str, int size);
        int append          (const char *str, const char *flags);
        int prepend         (const char *str, const char *flags);
        
        bool remove         ( void );
        void remove_top     ( void );
        void remove_bottom  ( void );
        
        void clear          ( void );
        void print          ( void );
        
        bool is_empty       ( void );
        
        bool fgetLine       (FILE * file);
        bool fgetWord       (FILE * file);
        bool getLine        (char * buffer, unsigned long size);
        bool getWord        (char * buffer, unsigned long size);
        
        bool insert         (const char *str);
        bool replace        (const char *str);
        bool insert         (const char c);
        bool replace        (const char c);
        
        
        char peek           ( void ) const;
        bool is_valid       ( void ) const;
        
        Slot * start        ( void );
        Slot * end          ( void );
        
        bool save           (const char * filename);
        bool load           (const char * filename);
        
        void seek_begining  ( void );
        void seek_end       ( void );
        
        unsigned long const length() const;
        
        void operator  =    (const char c);
        void operator  =    (const char * str);
        void operator +=    (char const c);
        void operator +=    (const char * str);
        void operator +=    (charlist &other);
        
        char operator  *    ( void ) const;
        bool operator ++    ( int i );
        bool operator --    ( int i );
        bool operator ++    ( void );
        bool operator --    ( void );
        
        friend charlist operator  +(charlist &other, charlist &other2);
        friend bool operator ==(charlist &other, charlist &other2);
        friend bool operator !=(charlist &other, charlist &other2);
        friend bool operator <=(charlist &other, charlist &other2);
        friend bool operator >=(charlist &other, charlist &other2);
        friend bool operator <(charlist &other, charlist &other2);
        friend bool operator >(charlist &other, charlist &other2);
        
        friend bool operator ==(charlist &other, const char * str);
        friend bool operator !=(charlist &other, const char * str);
        friend bool operator <=(charlist &other, const char * str);
        friend bool operator >=(charlist &other, const char * str);
        friend bool operator <(charlist &other, const char * str);
        friend bool operator >(charlist &other, const char * str);
        
        friend bool operator !=(const char * str, charlist &other);
        friend bool operator <=(const char * str, charlist &other);
        friend bool operator >=(const char * str, charlist &other);
        friend bool operator <(const char * str, charlist &other);
        friend bool operator >(const char * str, charlist &other);
    };
}}
#endif
