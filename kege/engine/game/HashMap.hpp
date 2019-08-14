//
//  HashMap.hpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 4/23/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef HashMap_hpp
#define HashMap_hpp
#include "string.hpp"
#include <unordered_map>
namespace kege{
    
    template<typename Var> class HashMap
    {
    public:
        
        typedef typename std::unordered_map<unsigned long, Var>::const_iterator ConstIterator;
        typedef typename std::unordered_map<unsigned long, Var>::iterator Iterator;
        typedef std::unordered_map<unsigned long, Var> VarMap;
        
        Var* operator [](const ds::string& key)
        {
            Var* v = Get(key);
            if (v == nullptr)
            {
                unsigned long k = key.hash();
                return &_varmap[k];
            }
            return v;
        }
        
        bool Add(const ds::string& key, Var var)
        {
            unsigned long k = key.hash();
            if (_varmap.find(k) == _varmap.end())
            {
                _varmap[k] = var;
                return true;
            };
            return false;
        }
        const Var* Get(const ds::string& key)const
        {
            unsigned long k = key.hash();
            ConstIterator m = _varmap.find(k);
            if (m != _varmap.end())
            {
                return &m->second;
            };
            return nullptr;
        }
        Var* Get(const ds::string& key)
        {
            unsigned long k = key.hash();
            Iterator m = _varmap.find(k);
            if (m != _varmap.end())
            {
                return &m->second;
            };
            return nullptr;
        }
        Var* Rem(const ds::string& key)
        {
            unsigned long k = key.hash();
            Iterator m = _varmap.find(k);
            if (m != _varmap.end())
            {
                Var* v = &m->second;
                _varmap.erase(m);
                return v;
            };
            return nullptr;
        }
        
        inline HashMap::ConstIterator Begin()const
        {
            return _varmap.begin();
        }
        
        inline HashMap::ConstIterator End()const
        {
            return _varmap.end();
        }
        
        inline HashMap::Iterator Begin()
        {
            return _varmap.begin();
        }
        
        inline HashMap::Iterator End()
        {
            return _varmap.end();
        }
        
        inline void Clear()
        {
            _varmap.clear();
        }
        
    private:
        
        VarMap _varmap;
    };
}
#endif /* HashMap_hpp */
