//
//  shared.hpp
//  dev0
//
//  Created by Kenneth A Esdaile on 9/7/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef memptr_hpp
#define memptr_hpp
#include <stdlib.h>
namespace kege{
    template <typename var> class shared;

    template <typename var> class pointer
    {
    public:
        
        ~ pointer()
        {
            if (ptr != nullptr)
            {
                delete ptr;
                ptr = nullptr;
            }
        }
        
        pointer(var* p)
        :   ptr(p)
        ,   count(0)
        {}
        
        pointer()
        :   ptr(nullptr)
        ,   count(0)
        {}
        
    private:
        
        friend shared<var>;
        var* ptr;
        int count;
    };
    
    
    template <typename var> class shared
    {
    public:
        
        inline const var* operator ->()const{return ref->ptr;}
        inline const var* operator  *()const{return ref->ptr;}
        inline const var* rawptr()    const {return ref->ptr;}
        inline       var* operator ->()     {return ref->ptr;}
        inline       var* operator  *()     {return ref->ptr;}
        inline       var* rawptr()          {return ref->ptr;}
        
        void operator =(kege::pointer< var >* p)
        {
            setref( p );
        }
        
        void operator =(const shared<var>& p)
        {
            setref( p.ref );
        }
        
        //void operator =(var* p)
        //{
        //    SetRef( new kege::pointer< var >( p ) );
        //}
        
        bool operator ==(const var* p)const
        {
            if (ref == nullptr)
            {
                return (p == nullptr) ? true : false;
            }
            return ref->ptr == p;
        }
        
        bool operator !=(const var* p)const
        {
            if (ref == nullptr)
            {
                return (p != nullptr) ? true : false;
            }
            return ref->ptr != p;
        }
        
        bool operator ==(const shared& s)const
        {
            return ref == s.ref;
        }
        
        bool operator !=(const shared& s)const
        {
            return ref != s.ref;
        }
        
        void deref(bool release = false)
        {
            if (ref != nullptr)
            {
                ref->count--;
                if (ref->count <= 0 || release)
                {
                    delete ref;
                }
                ref = nullptr;
            }
        }
        
        shared(const shared& p)
        :    ref(nullptr)
        {
            setref(p.ref);
        }
        
        shared(var* p)
        :    ref(nullptr)
        {
            setref( new kege::pointer< var >(p) );
        }
        
        ~ shared()
        {
            deref();
        }
        
        shared()
        :    ref(nullptr)
        {}
        
    private:
        
        void setref(kege::pointer< var >* p)
        {
            deref();
            ref = p;
            if (ref != nullptr)
            {
                ref->count++;
            }
        }
        
    private:
        
        kege::pointer< var >* ref;
    };
}
#endif /* memptr_hpp */
