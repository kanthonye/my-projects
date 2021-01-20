//
//  KEGE (Kenneth Esdaile Game Engine)
//  TypeID.hpp
//
//  Created by Kenneth A Esdaile on 8/6/20.
//  Copyright © 2020 Kenneth A Esdaile. All rights reserved.
//

#ifndef KEGE_TYPE_ID_HPP
#define KEGE_TYPE_ID_HPP
namespace kege
{
    class TypeID
    {
        template< typename T > struct Type
        {
            static int type;
        };
        
        template< typename T > struct Counter
        {
            static int count;
        };
        
    public:
        
        template< typename K, typename T > static int Get()
        {
            if ( Type< T >::type < 0 )
            {
                Type< T >::type = Counter< K >::count++;
            }
            return Type< T >::type;
        }
        
        template< typename K > static int GetCount()
        {
            return Counter< K >::count;
        }
    };
    
    template< typename T > int TypeID::Type< T >::type = -1;
    template< typename K > int TypeID::Counter< K >::Counter::count = 0;
}
#endif /* KEGE_TYPE_ID_HPP */
