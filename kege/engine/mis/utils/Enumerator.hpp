//
//  Enumerator.hpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 5/5/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef Enumerator_hpp
#define Enumerator_hpp
#include <map>
#include <vector>
#include "string.hpp"
namespace kege{
    
    class Enumerator
    {
    public:
        
        typedef unsigned long EnumKey;
        typedef unsigned int EnumValue;
        typedef std::pair<EnumValue, kege::ds::string> EnumPair;
        typedef std::vector< EnumPair > EnumList;
        typedef std::map< EnumKey, EnumList > Enummap;
        
        unsigned int GetEnum(const ds::string& name);
        Enumerator();
        
    private:
        
        unsigned int _enumerator;
        Enummap _enummap;
    };
    
    class GlobalEnum
    {
        static kege::Enumerator& Instance()
        {
            static kege::Enumerator instance;
            return instance;
        }
        
    public:
        
        static unsigned int Get(const kege::ds::string& name)
        {
            return Instance().GetEnum( name );
        }
    };
}
#endif /* Enumerator_hpp */
