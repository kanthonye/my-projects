// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//  DST
//  fchar.cpp
//  Created by Kenneth Anthony Esdaile on 6/20/14.
//  Copyright (c) 2014 kae. All rights reserved.
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
#include "charlist.hpp"
#include "string.hpp"
#define nullptr 0
#define EOF (-1)

namespace kege{namespace kae_ds
{
    charlist::charlist ( void )
    {
        head     = 0;
        tail     = 0;
        position = 0;
        size     = 0;
    }
    
    charlist::charlist ( const char c )
    {
        head     = 0;
        tail     = 0;
        position = 0;
        size     = 0;;
        append(c);
    }
    charlist::charlist ( const char * str )
    {
        head     = 0;
        tail     = 0;
        position = 0;
        size     = 0;
        append(str);
    }
    
    charlist::charlist ( const charlist & other )
    {
        head     = 0;
        tail     = 0;
        position = 0;
        size     = 0;
        append(other);
    }
    
    charlist::charlist ( const charlist * other )
    {
        head     = 0;
        tail     = 0;
        position = 0;
        size     = 0;
        append(*other);
    }
    charlist::~charlist()
    {
        clear();
    }
    
    void charlist::operator  = (const char c)
    {
        clear();
        append(c);
    }
    void charlist::operator  = (const char * str)
    {
        clear();
        append(str);
    }
    
    void charlist::operator += (char const c)
    {
        append(c);
    }
    
    void charlist::operator += (const char * str)
    {
        append(str);
    }
    
    unsigned long const charlist::length() const
    {
        return size;
    }
    
    void charlist::prepend (const char c)
    {
        Slot *s = new Slot;
        s->data = c;
        s->next = nullptr;
        s->prev = nullptr;
        
        if (head == nullptr)
        {
            head = tail = s;
            size++;
        }
        else
        {
            s->next    = head;
            head->prev = s;
            head       = s;
            size++;
        }
    }
    
    int charlist::append (const charlist & other)
    {
        int n = 0;
        Slot *h = other.head;
        while (h != nullptr)
        {
            append(h->data);
            h = h->next;
            n++;
        }
        return n;
    }
    
    void charlist::append  (const char c)
    {
        Slot *s = new Slot;
        s->data = c;
        s->next = nullptr;
        s->prev = nullptr;
        
        if (head == NULL)
        {
            tail = head = s;
            size++;
        }
        else
        {
            s->prev    = tail;
            tail->next = s;
            tail       = s;
            size++;
        }
    }
    
    int charlist::prepend (const char *str)
    {
        if (str==nullptr)return 0;
        const char *s = str;
        while (*s) s++;
        if (*s == '\0') s--;
        
        int n = 0;
        while ((s-str)!=0)
        {
            prepend(*s--);
            n++;
        }
        return n;
    }
    int charlist::append  (const char *str)
    {
        int n = 0;
        if (str!=nullptr)
        {
            const char *s = str;
            while (*s)
            {
                append(*s++);
                n++;
            }
            return n;
        }
        else
            return n;
    }
    
    int charlist::append(const char *str, const char *flags)
    {
        if (str==nullptr)return false;
        int n = 0;
        const char *s = str;
        while (*s != 0)
        {
            if ( cequal(*s, flags) )
            {
                append(*s++);
                n++;
                return n;
            }
            append(*s++);
            n++;
        }
        return n;
    }
    
    int charlist::append(const char *str, int size)
    {
        if (str==nullptr)return false;
        int i=0;
        for (; i<size; i++) append(str[i]);
        return i;
    }
    int charlist::prepend(const char *str, const char *flags)
    {
        if (str==nullptr)return false;
        const char *s = str;
        while (*s) s++;
        if (*s == '\0') s--;
        int n=0;
        while ((s-str)!=0)
        {
            if ( cequal(*s, flags) )
            {
                prepend(*s--);
                n++;
                return n;
            }
            prepend(*s--);
            n++;
        }
        return n;
    }
    
    void charlist::remove_top ( void )
    {
        if (head!=nullptr)
        {
            Slot * n = head->next;
            delete head;
            if (n!=nullptr) n->prev = nullptr;
            head = n;
            
            if (head==nullptr)
            {
                lastpos = position = tail = head;
                size = 0;
            }
        }
    }
    void charlist::remove_bottom  ( void )
    {
        if (tail!=nullptr)
        {
            Slot * p = tail->prev;
            delete tail;
            if (p!=nullptr) p->next = nullptr;
            tail = p;
            
            if (tail==nullptr)
            {
                lastpos = position = head = tail;
                size = 0;
            }
        }
    }
    
    char charlist::top ( void ) const
    {
        if (head!=nullptr)
            return head->data;
        else
            return EOF;
    }
    char charlist::bottom ( void ) const
    {
        if (tail!=nullptr)
            return tail->data;
        else
            return EOF;
    }
    
    ds::string charlist::toString (void) const
    {
        if (head == nullptr)
        {
            return ds::string();
        }
        
        
        int i = 0;
        Slot * h = head;
        char * data = new char[size+1];
        while (i<size && h!=nullptr)
        {
            data[i++] = h->data;
            h = h->next;
        }
        data[i] = '\0';
        return ds::string(data, size);
    }
    char* charlist::toCstr (char * buffer, unsigned long bsize) const
    {
        if (buffer==nullptr) throw (-1);
        
        if (head == nullptr)
        {
            buffer[0] = '\0';
            return buffer;
        }
        int i = 0;
        Slot * h = head;
        while (i<bsize && h!=nullptr)
        {
            buffer[i++] = h->data;
            h = h->next;
        }
        buffer[i-1] = '\0';
        return buffer;
    }
    
    
    bool charlist::is_empty ( void )
    {
        return !(head == nullptr);
    }
    
    void charlist::clear ( void )
    {
        if (head == nullptr) return;
            
        Slot * next;
        while (head != nullptr)
        {
            next = head->next;
            head->prev = nullptr;
            delete head;
            size--;
            head = next;
        }
        lastpos = position = nullptr;
        size = 0;
    }
    void charlist::print ( void )
    {
        if (head == nullptr) return;
        
        Slot * f = head;
        while (f != nullptr)
        {
            printf("%c",f->data);
            f = f->next;
        }
    }
    
    
    charlist::Slot * charlist::start ( void )
    {
        return head;
    }
    charlist::Slot * charlist::end ( void )
    {
        return tail;
    }
    
    bool charlist::fgetLine (FILE * file)
    {
        if (file!=nullptr)
        {
            char c = 1;
            while (c!=' ' && c!=EOF)
            {
                c=fgetc(file);
                append(c);
            }
            return true;
        } else {
            return false;
        }
    }
    bool charlist::fgetWord (FILE * file)
    {
        if (file!=nullptr)
        {
            char c = 1;
            while (c!=' '&&c!=EOF)
            {
                c=fgetc(file);
                append(c);
            }
            return true;
        } else {
            return false;
        }
    }
    bool charlist::save (const char * filename)
    {
        FILE * fp = nullptr;
        fp = fopen(filename, "w");
        
        if (fp==nullptr && head!=nullptr) return false;
        
        Slot * p = head;
        while (p->data != EOF)
        {
            putc(p->data, fp);
            p = p->next;
        }
        fclose(fp);
        
        return true;
    }
    bool charlist::load (const char * filename)
    {
        FILE * fp = 0;
        fp = fopen(filename, "r");
        
        if (fp==0) return false;
        int c;
        size = 0;
        while ((c=fgetc(fp)) != EOF)
        {
            append(c);
            size++;
        }
        fclose(fp);
        
        return true;
    }
    
    
    void charlist::seek_begining()
    {
        position = head;
    }
    void charlist::seek_end()
    {
        position = tail;
    }
    
    
    void charlist::operator += (charlist &other) {
        for (charlist::Slot * slot=other.head; slot!=nullptr; slot=slot->next)
            append(slot->data);
    }
    
    char charlist::operator  * ( void ) const
    {
        if (position!=nullptr)
            return position->data;
        else
            return '\0';
    }
    
    bool charlist::operator ++ ( int i )
    {
        if (position != nullptr)
        {
            position = position->next;
            return true;
        }
        return false;
    }
    bool charlist::operator -- ( int i )
    {
        if (position != nullptr)
        {
            position = position->prev;
            return true;
        }
        return false;
    }
    bool charlist::operator ++ ( void )
    {
        if (position != nullptr)
        {
            position = position->next;
            return true;
        }
        return false;
    }
    bool charlist::operator -- ( void )
    {
        if (position != nullptr)
        {
            position = position->prev;
            return true;
        }
        return false;
    }
    bool charlist::is_valid ( void ) const
    {
        return (position != nullptr)? true : false;
    }
    bool charlist::insert (const char *str)
    {
        if (position!=nullptr)
        {
            const char * s = str;
            while (insert(*s++));
            return true;
        } else {
            return false;
        }
    }
    bool charlist::replace (const char *str)
    {
        if (position!=nullptr)
        {
            const char * s = str;
            while (replace(*s++))
                charlist::operator++();
            return true;
        } else {
            return false;
        }
    }
    bool charlist::insert (const char c)
    {
        if (position!=nullptr && c!='\0')
        {
            Slot * n = position->next;
            
            Slot * s = new Slot;
            s->data = c;
            s->prev = position;
            s->next = n;
            
            position->next = s;
            n->prev        = s;
            position       = s;
            return true;
        }
        else
            return false;
    }
    bool charlist::replace (const char c)
    {
        if (position!=nullptr)
        {
            position->data = c;
            return true;
        } else {
            return false;
        }
    }
    
    bool charlist::remove ( void )
    {
        if (position!=nullptr)
        {
            Slot * p = position->prev;
            Slot * n = position->next;
            
            delete position;
            size--;
            
            if (p!=nullptr)
                p->next = n;
            else
                head    = n;
            
            if (n!=nullptr)
                n->prev = p;
            else
                tail    = p;
            
            position = (p!=nullptr)?p:n;
            return true;
        } else {
            return false;
        }
    }
    
    char charlist::peek ( void ) const
    {
        if (position!=nullptr)
            return position->data;
        else
            return '\0';
    }
    
    bool charlist::getLine(char * buffer, unsigned long bsize)
    {
        lastpos = position;
        if (buffer!=nullptr && position!=nullptr)
        {
            int i = 0;
            while (i<bsize && position!=nullptr)
            {
                buffer[i] = position->data;
                i++;
                if (position->data!='\n') position = position->next;
                else break;
            }
            buffer[i-1] = '\0';
            if (position->data=='\n') position = position->next;
            return true;
        } else {
            return false;
        }
    }
    bool charlist::getWord (char * buffer, unsigned long bsize)
    {
        Slot * p = lastpos;
        if (buffer!=nullptr && lastpos!=nullptr)
        {
            int i = 0;
            while (i<bsize && p!=nullptr)
            {
                buffer[i] = p->data;
                
                if (p->data!='\n') p = p->next;
                else break;
            }
            buffer[i-1] = '\0';
            return true;
        } else {
            return false;
        }
    }
    
    charlist operator +(charlist &other, charlist &other2) {
        charlist s;
        for (charlist::Slot * slot=other.head; slot!=nullptr; slot=slot->next)
            s.append(slot->data);
        for (charlist::Slot * slot=other2.head; slot!=nullptr; slot=slot->next)
            s.append(slot->data);
        return s;
    }
    
    bool operator ==(charlist &other, charlist &other2)
    {
        if (other.size==other2.size)
        {
            other.start();
            other2.start();
            int  i = 0;
            while (*other==*other2)
            {
                other++;
                other2++;
                i++;
            }
            if (i==other.size && i==other2.size)
                return true;
            else
                return false;
        } else 
            return false;
    }
    bool operator !=(charlist &other, charlist &other2)
    {
        return !(other==other2);
    }
    bool operator <=(charlist &other, charlist &other2)
    {
        if (other.size<=other2.size) return true;
        else return false;
    }
    bool operator >=(charlist &other, charlist &other2)
    {
        if (other.size>=other2.size) return true;
        else return false;
    }
    bool operator <(charlist &other, charlist &other2)
    {
        if (other.size<other2.size) return true;
        else return false;
    }
    bool operator >(charlist &other, charlist &other2)
    {
        if (other.size>other2.size) return true;
        else return false;
    }
    
    bool operator ==(charlist &other, const char * str)
    {
        int slen = str_len(str);
        if (other.size==slen)
        {
            const char *s = str;
            other.start();
            int  i = 0;
            while (*other==*s)
            {
                other++;
                s++;
                i++;
            }
            if (i==other.size && i==slen)
                return true;
            else
                return false;
        } else
            return false;
    }
    bool operator !=(charlist &other, const char * str)
    {
        return !(other==str);
    }
    bool operator <=(charlist &other, const char * str)
    {
        if (other.size<=str_len(str)) return true;
        else return false;
    }
    bool operator >=(charlist &other, const char * str)
    {
        if (other.size>=str_len(str)) return true;
        else return false;
    }
    bool operator <(charlist &other, const char * str)
    {
        if (other.size<str_len(str)) return true;
        else return false;
    }
    bool operator >(charlist &other, const char * str)
    {
        if (other.size>str_len(str)) return true;
        else return false;
    }
    
    bool operator !=(const char * str, charlist &other)
    {
        return !(other==str);
    }
    bool operator <=(const char * str, charlist &other)
    {
        if (str_len(str) <= other.size) return true;
        else return false;
    }
    bool operator >=(const char * str, charlist &other)
    {
        if (str_len(str) >= other.size) return true;
        else return false;
    }
    bool operator <(const char * str, charlist &other)
    {
        if (str_len(str) < other.size) return true;
        else return false;
    }
    bool operator >(const char * str, charlist &other)
    {
        if (str_len(str) > other.size) return true;
        else return false;
    }
}}

