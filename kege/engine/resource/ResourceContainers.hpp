/*! @author      Kenneth Esdaile
 *  @date        created on 7/4/17
 *  @copyright   Copyright © 2017 Kenneth Anthony Esdaile. All rights reserved.
 *  @file        ResrMngr.hpp
 *  @project     entity */

#ifndef Asset_hpp
#define Asset_hpp
#include <map>
#include "shared.hpp"
#include "dlist.hpp"
#include "slist.hpp"
#include "string.hpp"
namespace kege{
    
    template<typename key, typename var> class ListPair
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
    
    
    
    
    template<typename key, typename var> class Resmap
    {
    public:
        
        typedef std::map<key, var> ItemMap;
        typedef typename ItemMap::iterator iterator;
        typedef typename ItemMap::const_iterator const_iterator;
        
        /*
         * add object to resource. only once of each object can exist
         */
        var& operator [](const key& k)
        {
            return items[k];
        }
        
        /*
         * add object to resource. only once of each object can exist
         */
        var& add(const key& k, var& a)
        {
            items[k] = a;
            return a;
        }
        
        /*
         * instantly remove var by name from resource
         */
        var* rem(const key& k)
        {
            typename ItemMap::iterator m = items.find(k);
            if (m == items.end()) return nullptr;
            var* a = &m->second;
            items.erase(m);
            return a;
        }
        
        /*
         * instantly remove var by name from resource
         */
        const var* get(const key& k)const
        {
            typename ItemMap::const_iterator m = items.find(k);
            if (m == items.end()) return nullptr;
            return &m->second;
        }
        
        /*
         * instantly remove var by name from resource
         */
        var* get(const key& k)
        {
            typename ItemMap::iterator m = items.find(k);
            if (m == items.end()) return nullptr;
            return &m->second;
        }
        
        /*
         * instantly remove var by name from resource
         */
        inline const_iterator begin()const
        {
            return items.begin();
        }
        
        /*
         * instantly remove var by name from resource
         */
        inline iterator begin()
        {
            return items.begin();
        }
        
        /*
         * instantly remove var by name from resource
         */
        inline iterator size()const
        {
            return items.size();
        }
        
        /*
         * instantly remove var by name from resource
         */
        inline const_iterator end()const
        {
            return items.end();
        }
        
        /*
         * instantly remove var by name from resource
         */
        inline iterator end()
        {
            return items.end();
        }
        
        void clear()
        {
            items.clear();
        }
        
        ~ Resmap()
        {
            clear();
        }
        
        Resmap()
        {}
        
    protected:
        
        ItemMap items;
    };
}
#endif /* Asset_hpp */


