/*! @author      Kenneth Esdaile
 *  @date        created on 7/4/17
 *  @copyright   Copyright © 2017 Kenneth Anthony Esdaile. All rights reserved.
 *  @file        itemmap.hpp
 *  @project     entity */

#ifndef itemmap_hpp
#define itemmap_hpp
#include <map>
#include "shared.hpp"
#include "dlist.hpp"
#include "slist.hpp"
#include "string.hpp"
namespace kege{

    template<typename key, typename var> class itemmap
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
        
        ~ itemmap()
        {
            clear();
        }
        
        itemmap()
        {}
        
    protected:
        
        ItemMap items;
    };
}
#endif /* itemmap_hpp */


