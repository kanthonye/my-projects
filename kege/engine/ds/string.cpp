/*! @author     Kenneth Anthony Esdaile
 *  @date       created on 11/1/14
 *  @copyright  Copyright (c) 2014 kae. All rights reserved.
 *  @file       string.cpp
 *  @project    data structure containers. */
#include "string.hpp"
namespace kege {namespace ds{
    
    std::size_t ds::string::hash(const char* str)
    {
        if (str == NULL) return 0;
        
        enum
        {
            A = 54059, /* a prime */
            B = 76963, /* another prime */
            C = 86969, /* yet another prime */
            FIRSTH  =37 /* also prime */
        };
        
        const char * s = str;
        
        unsigned h = FIRSTH;
        while (*s)
        {
            h = (h * A) ^ (s[0] * B);
            s++;
        }
        return h;
    };
    
    std::size_t ds::string::hash()const
    {
        if (empty()) return 0;
        return hash(str.data);
    };
    
    bool ds::string::copy(long offset, const char* s, long slen, long start, long end)
    {
        if (s == NULL || slen <= 0) return false;
        
        if (str.data == NULL)
        {
            setsize(slen);
            memcpy(str.data, s, slen);
            str.data[slen] = 0;
            size = slen;
            return true;
        }
        
        int cpysize = int(end - start);
        int reqsize = int(offset + cpysize);
        if (str.size <= reqsize)
        {
            if (offset != 0)
            {
                resize(reqsize);
            }
            else
            {
                setsize(reqsize);
            }
        }
        if (cpysize > 0)
        {
            memcpy(&str.data[offset], s, cpysize);
            str.data[reqsize] = 0;
            size = reqsize;
            return true;
        }
        else return false;
    }
    
    void ds::string::copy(const char* s, long slen)
    {
        copy(0, s,slen, 0,slen);
    }
    
    void ds::string::overwrtie(long start, long strsize, const char* s)
    {
        if (str.data==NULL || s==NULL) return;
        size = strsize + (&str.data[start] - &str.data[0]);
        if (size+1 >= str.size)
        {
            resize(size + 1);
        }
        memcpy(&str.data[start], s, strsize);
        str.data[size] = 0;
    }
    
    void ds::string::setstring(long strsize, char* data)
    {
        str.data = data;
        str.size = strsize;
        size = strsize;
    }
    
    void ds::string::add(const char* s, long len)
    {
        if (len == 0) return;
        
        long strsize = size + len;
        
        if (str.size <= strsize)
            resize(strsize);
        
        memcpy(&str.data[size], s, len);
        str.data[strsize] = 0;
        size = strsize;
    }
    
    const bool ds::string::cmp(const char* s, long slen)
    {
        if (str.data==NULL || s==NULL) return 0;
        const char *r = str.data;
        int i=0;
        
        while (*r == s[i])
        {
            if (*r=='\0' || s[i]=='\0')break;
            r++;
            i++;
        }
        bool check_lenght = (r-str.data == slen);
        r--;
        i--;
        bool check_equal = (*r == s[i]);
        
        return (check_equal == true && true == check_lenght);
    }
    
    const long ds::string::length() const
    {
        return size;
    }
    
    char * ds::string::getdata()
    {
        return str.data;
    }
    
    const char * ds::string::c_str() const
    {
        return str.data;
    }
    
    const bool ds::string::empty (void) const
    {
        if (str.data == NULL) return true;
        return (str.data[0] == '\0');
    }
    
    void ds::string::resize (long new_size)
    {
        if (new_size <= 0)
        {
            clear();
            return;
        }
        
        str.size = new_size + 1;
        char * newstr = new char[str.size];
        
        long less = (new_size <= size) ? new_size : size;
        memcpy(newstr, str.data, less);
        newstr[less] = 0;
        size = less;
        
        delete [] str.data;
        str.data = newstr;
    }
    
    void ds::string::clear(void)
    {
        str.size = 0;
        size = 0;
        if (str.data == NULL) return;
        delete [] str.data;
        str.data = NULL;
    }
    
    void ds::string::setlength(const long len)
    {
        size = len;
    }
    
    void ds::string::setsize(const long len)
    {
        clear();
        str.size = len+1;
        str.data = new char[str.size];
        size = 0;
    }
    
    string ds::string::tolowercase(void)const
    {
        if (str.data == NULL) return string();
        
        char * s = new char[size+1];
        memcpy(s, str.data, size+1);
        s[size] = 0;
        
        for (unsigned c=0; c<size; c++) s[c] = tolower(s[c]);
        return string(s,size);
    }
    
    string ds::string::touppercase(void)const
    {
        if (str.data == NULL) return string();
        
        char * s = new char[size+1];
        memcpy(s, str.data, size+1);
        s[size] = 0;
        
        for (unsigned c=0; c<size; c++) s[c] = toupper(s[c]);
        return string(s,size);
    }
    
    void ds::string::operator = (const char * cptr)
    {
        if (cptr == NULL)
        {
            if (str.data != NULL)
            {
                str.data[0] = 0;
                size = 0;
            }
            return;
        }
        copy(cptr, strlen(cptr));
    }
    
    void ds::string::operator = (const string & other)
    {
        if (other.str.data == NULL) return;
        copy(other.str.data, other.size);
    }
    
    void ds::string::operator += (const string & a)
    {
        add(a.str.data, a.size);
    }
    
    void ds::string::operator += (const char * str)
    {
        if (str == NULL) return;
        if (*str == 0) return;
        add(str, strlen(str));
    }
    
    void ds::string::operator += (const char c)
    {
        add(&c, 1);
    }
    
    string ds::string::operator + (const string & a)
    {
        return ds::add(str.data,size, a.str.data,a.size);
    }
    string ds::string::operator + (const char * s)
    {
        return ds::add(str.data, size, s, strlen(s));
    }
    string ds::string::operator + (const char chr)
    {
        return ds::add(str.data, size, &chr, 1);
    }
    
    string operator + (const char * s, const string & other)
    {
        return ds::add(s,strlen(s), other.str.data, other.size);
    }
    
    string operator + (const string & a, const char c)
    {
        return ds::add(a.str.data, a.size, &c, 1);
    }
    
    string operator + (const char c, const string & a)
    {
        return ds::add(&c, 1, a.str.data, a.size);
    }
    
    string operator + (const string & left, const string & right)
    {
        return ds::add(left.str.data, left.size, right.str.data, right.size);
    }
    
    bool operator < (const char * s, const string & other)
    {
        if (other.str.data == NULL || s == NULL) return false;
        if (str_len(s) < other.size) return true;
        else return false;
    }
    
    bool operator < (const string & other, const char * s)
    {
        if (other.str.data == NULL || !s) return false;
        if (other.size < str_len(s)) return true;
        else return false;
    }
    
    bool operator > (const char * s, const string & other)
    {
        if (other.str.data == NULL || s == NULL) return false;
        if (str_len(s) > other.size) return true;
        else return false;
    }
    
    bool operator > (const string & other, const char * s)
    {
        if (other.str.data == NULL || s == NULL) return false;
        if (other.size > str_len(s)) return true;
        else return false;
    }
    
    bool operator <= (const char * s, const string & other)
    {
        if (other.str.data == NULL || s == NULL) return false;
        if (str_len(s) <= other.size) return true;
        else return false;
    }
    
    bool operator <= (const string & other, const char * str)
    {
        if (other.str.data == NULL || str == NULL) return false;
        if (other.size <= str_len(str)) return true;
        else return false;
    }
    
    bool operator >= (const char * str, const string & other)
    {
        if (other.str.data == NULL || str == NULL) return false;
        if (str_len(str) >= other.size) return true;
        else return false;
    }
    
    bool operator >= (const string & other, const char * s)
    {
        if (other.str.data || s == NULL) return false;
        if (other.size >= str_len(s)) return true;
        else return false;
    }
    
    bool operator == (const char * s, const string & other)
    {
        if (other.str.data == NULL || s == NULL) return false;
        return strcmp(s, other.str.data) == 0;
    }
    
    bool operator == (const string & other, const char * str)
    {
        if (other.str.data == NULL || str == NULL) return false;
        return strcmp(str, other.str.data) == 0;
    }
    
    bool operator != (const char * str, const string & other)
    {
        if (other.str.data == NULL || str == NULL) return true;
        return !(strcmp(str, other.str.data) == 0);
    }
    
    bool operator != (const string & other, const char * str)
    {
        if (other.str.data == NULL || str == NULL) return true;
        return !(strcmp(str, other.str.data) == 0);
    }
    
    bool operator < (const string& a, const string& b)
    {
        if (a.str.data == NULL || b.str.data == NULL) return false;
        if (a.size < b.size) return true;
        else return false;
    }
    
    bool operator > (const string& a, const string& b)
    {
        if (a.str.data == NULL || b.str.data == NULL) return false;
        if (a.size > b.size) return true;
        else return false;
    }
    
    bool operator <= (const string& a, const string& b)
    {
        if (a.str.data == NULL || b.str.data == NULL) return false;
        if (a.size <= b.size) return true;
        else return false;
    }
    bool operator >= (const string& a, const string& b)
    {
        if (a.str.data == NULL || b.str.data == NULL) return false;
        if (a.size >= b.size) return true;
        else return false;
    }
    
    bool operator == (const string & a, const string & b)
    {
        if (NULL == a.str.data || b.str.data == NULL)
            return false;
        return str_cmp(a.str.data, b.str.data);
    }
    bool operator != (const string & a, const string & b)
    {
        if (a.str.data == NULL || b.str.data == NULL) return false;
        return !str_cmp(a.str.data, b.str.data);
    }
    
    string ds::string::parse_fname()const
    {
        const char * s = str.data;
        while (*s!='\0' && *s!='.') s++;
        
        const char * e = s;
        while (*e!='\0') e++;
        
        while (*s!='\0' && *s!='/') s--;
        if (*s=='/') s++;
        else s++;
        
        return string(s, e-s);
    }
    
    string ds::string::parse_fext()const
    {
        if (!str.data) return string();
        
        const char * p = str.data;
        while (*p!='\0' && *p!='.') p++;
        p++;
        
        const char * s = p;
        while (*s!='\0' && *s!=' ' && *s!='\n') s++;
        
        //int i = int(p-data);
        int u = int(s-p);
        return string(p,u);
    }
    
    string ds::string::parse_fpath()const
    {
        const char * s = str.data;
        while (*s!='\0' && *s!='.') s++;
        
        while (*s!='\0' && *s!='/') s--;
        if (*s=='/') s++;
        else s++;
        
        int n = int(s - str.data);
        
        return string(str.data,n);
    }
    
    string ds::string::parse_name()const
    {
        const char * name = str.data;
        while (*name!='\0' && *name!='.') name++;
        
        long j = (name - str.data);
        
        while (*name!='\0' && *name!='/') name--;
        if (*name=='/') name++;
        else name++;
        
        return string(name, j - (name - str.data));
    }
    
    ds::string add(const char * p, long psize, const char * q, long qsize)
    {
        if (!p || !q) return string();
        long arrlen = psize + qsize + 1;
        char * s = new char[arrlen];
        memcpy(s, p, psize);
        memcpy(&s[psize], q, qsize);
        s[arrlen-1] = 0;
        return ds::string(s, arrlen, arrlen-1);
    }
    
    ds::string::chrstr ds::string::va_list_print(char const* format, va_list& argptr)
    {
        static char buffer[1024];
        int n = vsprintf(buffer, format, argptr);
        if (n >= 1024) n--;
        buffer[n] = 0;
        return ds::string::chrstr(buffer,n);
    }
    
    string ds::string::strprint(ccptr format, ...)
    {
        va_list argptr;
        va_start(argptr, format);
        ds::string::chrstr str = va_list_print(format, argptr);
        va_end(argptr);
        const char*s = str.data;
        return ds::string(s,str.size);
    }
    
    string & ds::string::sprint(ccptr format, ...)
    {
        va_list argptr;
        va_start(argptr, format);
        ds::string::chrstr s = va_list_print(format, argptr);
        va_end(argptr);
        
        if (s.size > str.size || str.data == NULL)
        {
            setsize(s.size+1);
            memcpy(str.data, s.data, s.size);
        }
        else
        {
            memcpy(str.data, s.data, s.size);
        }
        size = s.size;
        str.data[s.size] = 0;
        return *this;
    }
    
    double ds::string::to_float()const
    {
        if ( empty() ) return 0.0f;
        ds::string n = *this;
        return atof(strtok(n.str.data, " \t\n\r"));
    }
    long ds::string::to_long()const
    {
        if ( empty() ) return 0;
        ds::string n = *this;
        return atol(strtok(n.str.data, " \t\n\r"));
    }
    int ds::string::to_int()const
    {
        if ( empty() ) return 0;
        ds::string n = *this;
        return atoi(strtok(n.str.data, " \t\n\r"));
    }
    
    ds::string::string(char * s, long slen, long len)
    :   size(0)
    {
        str.data = s;
        str.size = slen;
        size = len;
    }
    
    ds::string::string(char const* cstr, long len)
    :   size(0)
    {
        copy(cstr, len);
    }
    
    ds::string::string(char* pstr, long len)
    :   size(len)
    ,   str(pstr,len)
    {}
    
    ds::string::string (const string & other)
    :   size(0)
    {
        copy(other.str.data, other.size);
    }
    
    ds::string::string (string & other)
    :   size(0)
    {
        copy(other.str.data, other.size);
    }
    
    ds::string::string (const char * cptr)
    :   size(0)
    {
        copy(cptr, strlen(cptr));
    }
    
    ds::string::string (char * cptr)
    :   size(0)
    {
        copy(cptr, strlen(cptr));
    }
    
    ds::string::string ()
    :   size(0)
    {
    }
    ds::string::~string (void)
    {
        clear();
    }
    
}
    
    
    
    char * str_tok(char *& bufr, char * buffer, const char * flags)
    {
        const char * sptr = NULL;
        unsigned count = 0;
        
        if (buffer != NULL)
            bufr = buffer;
        
        char * word = bufr;
        while (*bufr!='\0')
        {
            sptr = flags;
            while (*sptr!='\0')
            {
                if (*bufr == *sptr)
                {
                    if (count != 0)
                    {
                        bufr++;
                        word[count] = '\0';
                        return word;
                    }
                    else
                    {
                        bufr++;
                        word++;
                    }
                }
                sptr++;
            }
            count++;
            bufr++;
        }
        word[count] = '\0';
        return word;
    }
    
    
    long str_cwspace(const char *& p)
    {
        const char * o = p;
        while (*p == ' ' || *p == '\n' || *p == '\t' || *p == '\r') p++;
        return p-o;
    }
    
    int str_ispath(const char * path)
    {
        long l = strlen(path);
        while (path[--l]!='.' && l>=0);
        
        if (path[l]!='.')
            return 1;
        else
            return 0;
    }
    
    int str_isfile(const char * path)
    {
        long l = strlen(path);
        while (path[--l]!='.' && l>=0);
        
        if (path[l]=='.' && path[0]!='.')
            return 1;
        else
            return 0;
    }
    
    char * str_parse_name(char * filename)
    {
        char * b = filename;
        while (*b!='\0' && *b!='.') b++;
        *b = '\0';
        b--;
        while (*b!='\0' && *b!='/' && *b!='\\') b--;
        b++;
        return b;
    }
    
    char * str_parse_fext(char * path)
    {
        char * p = path;
        while (*p++ != '\0');
        p-=2;
        while (*p!='\0' && *p!='.') p--;
        
        char * s = p;
        while (*s!='\0' && *s!=' ' && *s!='\n') s++;
        *s = '\0';
        return p;
    }
    
    char * str_parse_fname(char * filename)
    {
        char * p = filename;
        while (*p!='\0' && *p!='.') p++;
        /*no filename was found*/
        if (*p == '\0') return NULL;
        char * s = p;
        while (*s!='\0' && *s!=' ' && *s!='\n') s++;
        *s = '\0';
        while (*p!='\0' && *p!='/' && *p!='\\')p--;
        p++;
        return p;
    }
    
    char * str_parse_fpath(char * path)
    {
        char * b = path;
        char * e = path;
        
        while (*b!='\0' && *b!='/' && *b!='\\') b++;
        /*no path was found*/
        if (*b == '\0') return NULL;
        
        while (*e++!='\0');
        e-=2;
        while (*e!='\0' && *e!='/' && *e!='\\') e--;
        *++e = '\0';
        
        return b;
    }
    
    char * str_parse_fpath(char * buffer, unsigned int bsize, const char * filename)
    {
        const char * b = filename;
        
        while (*b!='\0' && *b!='/' && *b!='\\') b++;
        
        if (*b == '\0') return NULL;
        /*no path was found*/
        unsigned int count = 0;
        while (*b !='\0' && count < bsize) buffer[count++] = *b++;
        
        count--;
        while (buffer[count]!='\0' && buffer[count]!='/' && buffer[count]!='\\') count--;
        buffer[count+1] = '\0';
        
        return buffer;
    }
    
    const char * readinput (void)
    {
        static char str[256];
        int i=0;
        while ((str[i]=getchar())!='\n' && i<255) i++;
        str[i] = '\0';
        return str;
    }
    /**
     @brief copy from one string to another.
     @param str = string length to compute
     @return length of string
     */
    unsigned int str_len(const char * str)
    {
        if (str != 0) {
            const char *s = str;
            while (*s) s++;
            return (int)(s-str);
        } else {
            return 0;
        }
    }
    /**
     @brief copy from one string to another.
     @param left = the string being copied to
     @param right = the string being copied from
     @param flags = string of char to check equality, if equal then stop copying
     @return the number of characters copied
     */
    int str_cpyf(char * left, const char *right, const char * flags)
    {
        int i = 0;
        int count = 0;
        
        while (*right!='\0')
        {
            i = 0;
            while(flags[i] != '\0')
                if (*right == flags[i++]) {
                    left[count] = '\0';
                    return count;
                }
            left[count++] = *right++;
        }
        left[count] = '\0';
        return count;
    }
    /**
     @brief copy from one string to another.
     @param to = the buffer to store the copied string to
     @param size = the size of the string being copied.
     @param from = the string being copied
     @return the number of characters copied
     */
    long str_cpy(char * to, const long size, const char * from)
    {
        if (!to || !from) return 0;
        long s = 0;
        while (*from && s<size) to[s++] = *from++;
        to[s] = '\0';
        return s;
    }
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
    long str_cpy(char * bufr,long const bsize,long const bfrom,long const bto, ccptr cstr,long const csize,long const cfrom)
    {
        if (bfrom < bto && bto <= bsize && cfrom < csize)
        {
            if (bufr==NULL || cstr==NULL)
                return 0;
            long afrm = bfrom;
            long bfrm = cfrom;
            while (afrm < bto && bfrm < csize)
            {
                if (cstr[bfrm]==endchar)
                    break;
                bufr[afrm++] = cstr[bfrm++];
            }
            bufr[afrm] = endchar;
            return afrm - bfrom;
        }
        return 0;
    }
    long str_cpy(char * p,long psize, long pstart, ccptr q, long qsize, long qstart, long readsize)
    {
        if (psize - pstart < readsize) return 0;
        if (qsize - qstart < readsize) return 0;
        long size = pstart+readsize;
        long i,j;
        for (i=pstart, j=qstart; i<size; i++,j++) p[i] = q[j];
        p[i] = 0;
        return i;
    }
    /**
     @brief compare two strings
     */
    int str_cmp(const char * left,const char * right)
    {
        if (left==NULL || right==NULL) return 0;
        const char *r = right;
        const char *l = left;
        bool equality = false;
        while (*r == *l)
        {
            if (*r=='\0' || *l=='\0')
            {
                if (*r=='\0' && *l=='\0')
                    equality = true;
                break;
            }
            r++;
            l++;
        }
        //if (r-right == 0) return false;
        //bool check_lenght = (r-right == l-left);
        //r--;
        //l--;
        //bool check_equal = (*r == *l);
        
        //while (*r!='\0') r++;
        //while (*l!='\0') l++;
        return equality;
    }
    /**
     @brief resize a string
     @param cptr hold the pointer to the resized string
     @param size the size to resize the string to
     @warning the string must be deleted after finish using
     */
    unsigned str_resize (char * cptr, const unsigned size)
    {
        unsigned count = 0;
        char * new_data = new char[size];
        if (cptr)
        {
            unsigned length = size - 1;
            for (count = 0; (count < length)&&(cptr[count]!='\0'); count++)
            {
                if (count >= size) break;
                new_data[count] = cptr[count];
            }
            new_data[count] = '\0';
            delete [] cptr;
            cptr = NULL;
        }
        cptr = new_data;
        return count;
    }
    /**
     @brief check if a char is equal to a string of characters, return true if any one of the string of characters are equal to c
     @param c the char to compare
     @param flags the string of char to check equality from
     */
    bool str_equal (char c, const char * flags)
    {
        while (*flags != '\0') if (c == *flags++) return true;
        return false;
    }
    
    /**
     @brief check if a char is equal to a string of characters, return true if any one of the string of characters are equal to c
     @param c the char to compare
     @param flags the string of char to check equality from
     */
    bool chr_equal (char c, const char * flags)
    {
        while (*flags != '\0') if (c == *flags++) return true;
        return false;
    }
    
    /**
     @brief keep counting characters until a flag is cought
     @param line the string of char to compare to the string of flags
     @param flags the string of char to check equality from
     */
    int str_count(const char * line, const char * flags)
    {
        const char * f = NULL;
        const char * s = line;
        bool end = false;
        while (*s != '\0')
        {
            f = flags;
            while(*f != '\0') if (*s == *f++) end = true;
            if (end) break;
            s++;
        }
        return (int) (s-line);
    }
    
    const char * str_nextelem(const char * elem, const char * line, const char * flags)
    {
        const char * e;
        const char * l;
        const char * f;
        while (*line != '\0')
        {
            e = elem;
            l = line;
            f = flags;
            while(*l != *e && *l!=0)
            {
                f = flags;
                while (*f != '\0')
                {
                    if (*l == *f)
                    {
                        line = l;
                        return line;
                    }
                    else f++;
                }
                l++;
            }
            while(*l == *e && *l!=0 && *e!=0)
            {
                f = flags;
                while (*f != '\0')
                {
                    if (*l == *f)
                    {
                        line = l;
                        return line;
                    }
                    else f++;
                }
                l++;
                e++;
            }
            if (*e==0)
            {
                line  = l;
                line -= (e-elem);
                break;
            }
            else
            {
                line = l;
            }
        }
        return line;
    }
    
    const char * str_nextelem(const char * elem, const char * line)
    {
        const char * e;
        const char * l;
        while (*line != '\0')
        {
            e = elem;
            l = line;
            while(*l != *e && *l!=0) l++;
            while(*l == *e && *l!=0 && *e!=0) {l++; e++;}
            if (*e==0)
            {
                line  = l;
                line -= (e-elem);
                break;
            }
            else
            {
                line = l;
            }
        }
        return line;
    }
    
    
    long str_copy(char * bufr, int bsize, const char *str, const char * flags)
    {
        char * b = bufr;
        const char * s = str;
        const char * f;
        while (*s != '\0')
        {
            f = flags;
            while(*s != *f && *f != '\0') f++;
            if(*f == '\0') *b++ = *s++;
            else break;
        }
        *b = 0;
        return s - str;
    }
    
    /**
     skip all current character contain in flags
     @param str the string input.
     @param flags the characters to stop at.
     @return the string position.
     */
    const char * str_skip(const char * str, const char * flags)
    {
        const char * f;
        while (*str != 0)
        {
            f = flags;
            while(*str != *f && *f != 0) f++;
            if(*f != 0) str++;
            else break;
        }
        return str;
    }
    char * str_skip(char * str, const char * flags)
    {
        const char * f;
        while (*str != 0)
        {
            f = flags;
            while(*str != *f && *f != 0) f++;
            if(*f != 0) str++;
            else break;
        }
        return str;
    }
    
    /**
     skip all character other than the ones contained in flags
     @param str the string input.
     @param flags the characters to stop at.
     @return the string position.
     */
    const char * str_next(const char * line, const char * flags)
    {
        const char * f;
        while (*line != '\0')
        {
            f = flags;
            while(*line != *f && *f != '\0') f++;
            if(*f == '\0') line++;
            else break;
        }
        return line;
    }
    
    
    const char * str_newln(const char * str)
    {
        str = kege::str_next(str, "\n");
        str = kege::str_skip(str, " \n\t\n");
        return str;
    }
    char * str_newln(char * str)
    {
        str = kege::str_next(str, "\n");
        str = kege::str_skip(str, " \n\t\n");
        return str;
    }
    
    /**
     skip all character other than the ones contained in flags
     @param str the string input.
     @param flags the characters to stop at.
     @return the string position.
     */
    char * str_next(char * str, const char * flags)
    {
        const char * f;
        while (*str != '\0')
        {
            f = flags;
            while(*str != *f && *f != '\0') f++;
            if(*f == '\0') str++;
            else break;
        }
        return str;
    }
    
    /**
     check if a string contains a particlar character.
     @param str the string to search.
     @param flags the characters to look for.
     @return true if characters are found, false otherwise
     */
    bool str_has(const char* str, const char* flag)
    {
        const char* f = nullptr;
        while (*str != 0)
        {
            f = flag;
            while (*f != 0)
            {
                if (*str == *f) return true;
                else f++;
            }
            str++;
        }
        return false;
    }
    
    /**
     skip a string element separated by space.
     @param str the string input.
     @return the string position.
     */
    const char* str_skipword(const char* str)
    {
        str = kege::str_next(str, " \n");
        str = kege::str_skip(str, " \n\t\r");
        return str;
    }
    
    /**
     @brief break a string up into token
     @param buffer the string to break up
     @param flags how to break up the string
     @return return a string token.
     */
    char * str_tok (char * buffer, const char * flags)
    {
        static char * bufr;
        const char * sptr = NULL;
        unsigned count = 0;
        
        if (buffer != NULL)
            bufr = buffer;
        
        char * word = bufr;
        while (*bufr!='\0')
        {
            sptr = flags;
            while (*sptr!='\0')
            {
                if (*bufr == *sptr)
                {
                    if (count != 0)
                    {
                        bufr++;
                        word[count] = '\0';
                        return word;
                    }
                    else
                    {
                        bufr++;
                        word++;
                    }
                }
                sptr++;
            }
            count++;
            bufr++;
        }
        word[count] = '\0';
        return word;
    }
    /**
     @brief same as str_tok() except that the two parameter are constant.
     @param buffer the string to break up
     @param flags how to break up the string
     @return return a string token.
     */
    char * str_word (const char * buffer, const char * flags) {
        static const char * bufr;
        static char word[256];
        const char * sptr = NULL;
        unsigned count = 0;
        
        if (buffer != NULL)
            bufr = buffer;
        
        while (*bufr!='\0')
        {
            sptr = flags;
            while (*sptr!='\0')
            {
                if (*bufr == *sptr) {
                    if (count != 0) {
                        word[count] = '\0';
                        return word;
                    } else {
                        bufr++;
                    }
                }
                sptr++;
            }
            word[count++] = *bufr;
            bufr++;
        }
        word[count] = '\0';
        return word;
    }
    
    bool cequal(char c, const char * flags)
    {
        if (c == '\0') return false;
        while (*flags != 0) if (c == *flags++) return true;
        return false;
    }
    
    long strsize(const char * str, const char * flags)
    {
        const char * s = str;
        const char * f;
        while (*str != 0)
        {
            f = flags;
            while (*str != *f && *str != 0 && *f != 0) f++;
            if (*str == *f) return str-s;
            str++;
        }
        return str-s;
    }
    
    long strskip(const char * str, const char * flags)
    {
        const char * s = str;
        while (str != 0)
        {
            if (cequal(*s, flags)) s++;
            else break;
        }
        return s-str;
    }
    
    bool string_match(const char * q, const char * p, const char * flags)
    {
        const char * a = q;
        const char * b = p;
        while(*a == *b && *a!=0 && *b!=0)
        {
            if (kege::str_equal(*a++, flags)) break;
            if (kege::str_equal(*b++, flags)) break;
        }
        long as = q-a;
        long bs = p-b;
        if (as==0 || bs==0)
        {
            return false;
        }
        return as == bs;
    }
    
    bool string_contain(const char * elem, const char * line, const char * flags)
    {
        const char * e;
        const char * l;
        while (*line != '\0')
        {
            e = elem;
            l = line;
            while(*l != *e && *l!=0)
            {
                if (kege::str_equal(*l, flags)) return false;
                l++;
            }
            while(*l == *e && *l!=0 && *e!=0)
            {
                if (kege::str_equal(*l, flags)) return false;
                l++;
                e++;
            }
            if (*e==0)
            {
                return true;
            }
            else
            {
                line = l;
            }
        }
        return false;
    }
    
    bool string_equal(char const* word, char const* curr)
    {
        if (word == NULL && curr == NULL) return false;
        
        char const* s = curr;
        char const* e = curr;
        char const* w = word;
        int i=0;
        while (*e == *w)
        {
            w++;
            e++;
            i++;
            if (*e == 0 || *w == 0)
            {
                w--;
                e--;
                i--;
                break;
            }
        }
        if (*w == *e && (e-s)==i)
        {
            return true;
        }
        return false;
    }
    
    kege::ds::string srinkpath(const kege::ds::string& fname, const kege::ds::string& path)
    {   using namespace kege;
        if (path.empty())
        {
            return fname;
        }
        ds::string str = path;
        char *f = &str[str.length()-1];
        char *e, *s = str.getdata();
        while (*f!=0) f++;
        f--;
        e=f;
        for (const char* a=fname.c_str(); *a!=0; a++)
        {
            if (a[0] != '.' && a[1] != '.')
            {
                if (f[1] == '/')
                    f+=2;
                *f = 0;
                str.setlength(str.length() - (e-f+1));
                str.overwrtie(str.length(), strlen(a), a);
                return str;
            }
            a+=2;
            
            if (*f == '/') f--;
            while (*f != '/') f--;
            if (f - s != 0) f--;
            else
            {
                return a;
            }
        }
        return path;
    }
}
