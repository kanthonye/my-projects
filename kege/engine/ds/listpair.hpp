/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/21/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       listpair.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef listpair_hpp
#define listpair_hpp
#include <map>
#include "shared.hpp"
#include "dlist.hpp"
#include "slist.hpp"
#include "string.hpp"
namespace kege{
    
    template<typename key, typename var> class listpair
    {
    public:
        
        class Pair
        {
        public:
            Pair(key& k, var& v) : k(k), v(v) {}
            Pair() {}
            key k;
            var v;
        };
        
        typedef ds::slist< Pair > List;
        typedef typename List::iterator Iterator;
        
        Pair& operator [](const key& k)
        {
            Pair& m = list.push_back();
            m.k = k;
            return m;
        }
        
        var& add(const key& k, var& v)
        {
            if ( has(v) ) return v;
            Pair& m = list.push_back();
            m.v = v;
            m.k = k;
            return m.v;
        }
        
        Pair& add(const key& k)
        {
            // first check if object already exist
            Iterator m;
            for (m = list.begin(); m != nullptr; m++)
            {
                if (m.element().k == k)
                {
                    return &m.element().v;
                }
            }
            return list.push_back();
        }
        
        var* get(const key& k)const
        {
            Iterator m;
            for (m = list.begin(); m != nullptr; m++)
            {
                if (m.element().k == k)
                {
                    return &m.element().v;
                }
            }
            return nullptr;
        }
        
        var* get(const key& k)
        {
            Iterator m;
            for (m = list.begin(); m != nullptr; m++)
            {
                if (m.element().k == k)
                {
                    return &m.element().v;
                }
            }
            return nullptr;
        }
        
        bool has(key& k)const
        {
            Iterator m;
            for (m = list.begin(); m != nullptr; m++)
            {
                if (m.element().k == k)
                {
                    return true;
                }
            }
            return false;
        }
        
        bool has(var& v)const
        {
            Iterator m;
            for (m = list.begin(); m != nullptr; m++)
            {
                if (m.element().v == v)
                {
                    return true;
                }
            }
            return false;
        }
        
        var* rem(const key& k)
        {
            Iterator m;
            for (m = list.begin(); m != nullptr; m++)
            {
                if (m.element().k == k)
                {
                    var* v = &m.element().v;
                    list.erase(m);
                    return v;
                }
            }
            return nullptr;
        }
        
        /*
         * instantly remove var by name from resource
         */
        inline Iterator begin()const
        {
            return list.begin();
        }
        
        /*
         * instantly remove var by name from resource
         */
        inline Iterator begin()
        {
            return list.begin();
        }
        
        /*
         * instantly remove var by name from resource
         */
        inline Iterator size()const
        {
            return list.size();
        }
        
        /*
         * instantly remove var by name from resource
         */
        inline void clear()
        {
            list.clear();
        }
        
        List list;
    };
}
#endif /* listpair_hpp */
