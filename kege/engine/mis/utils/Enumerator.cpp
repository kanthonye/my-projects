//
//  Enumerator.cpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 5/5/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "Enumerator.hpp"
namespace kege{
    
    unsigned int Enumerator::GetEnum(const ds::string& name)
    {
        EnumKey enumkey = name.hash();
        EnumList& list = _enummap[ enumkey ];
        
        for (EnumList::iterator i=list.begin(); i!=list.end(); i++)
        {
            if ((*i).second == name)
            {
                return (*i).first;
            }
        }
        
        unsigned int num = _enumerator++;
        list.push_back( EnumPair(num, name) );
        return num;
    }
    
    Enumerator::Enumerator()
    :   _enumerator(0)
    {}
}

