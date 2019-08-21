//
//  GenID.hpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/29/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef GenID_hpp
#define GenID_hpp
#include "cgm.hpp"
#include "queue.hpp"
namespace kege{
    
    /** the @b GenTypID class generates unique integer type id for different object types */
    class GenTypID
    {
    private:
        
        static cg::uint GenID()
        {
            counter++;
            return counter;
        }
        
        template<typename var> class TypID
        {
        public:
            static unsigned int GetID(){return type_id;}
            TypID(){}
        private:
            static unsigned int type_id;
        };
        
    public:
        
        template<typename var> static cg::uint GenID()
        {
            return GenTypID::TypID<var>().GetID();
        }
        
        template<typename var> static cg::uint GetID()
        {
            return GenTypID::TypID<var>::GetID();
        }
        
    private:
        static cg::uint counter;
    };
    
    template<typename var> unsigned int GenTypID::TypID<var>::type_id = kege::GenTypID::GenID();
}


namespace kege{
    
    /**
     the @b IDMngr class is an ID Manager that generate unique integer id.
     Its perpose is to be use for generating unique integer id for each
     object. IDs can also be return to the manager and reused.
     */
    class GenID
    {
    public:
        
        static void DelID(cg::uint id)
        {
            GetInstance().Del_ID(id);
        }
        static cg::uint NewID()
        {
            return GetInstance().New_ID();
        }
        ~ GenID()
        {
            ids.clear();
        }
        GenID(){}
        
    private:
        
        static GenID& GetInstance()
        {
            static GenID instance;
            return instance;
        }
        
        void Del_ID(cg::uint id)
        {
            ids.push(id);
        }
        
        cg::uint New_ID()
        {
            if (ids.empty())
            {
                counter++;
                return counter;
            }
            cg::uint id = ids.pop();
            return id;
        }
        
    private:
        
        static ds::queue<cg::uint> ids;
        static cg::uint counter;
    };
}
#endif /* GenID_hpp */
