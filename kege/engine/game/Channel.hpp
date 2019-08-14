//
//  Channel.h
//  dev0
//
//  Created by Kenneth Esdaile on 12/31/17.
//  Copyright © 2017 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef Channel_hpp
#define Channel_hpp
#include <vector>
namespace kege{namespace com{

    template <typename ListenerT, typename ReturnT, typename MessageT> class MessengerR
    {
    public:
        
        typedef ReturnT* (ListenerT::*Funct)(MessageT msg);
        
        struct Handler
        {
            Handler(ListenerT * listener, Funct func)
            :   listener(listener), func(func)
            {}
            ListenerT * listener;
            Funct func;
        };
        
        void Add(ListenerT * listener, Funct func)
        {
            if (listener != nullptr)
            {
                listeners.push_back( Handler(listener,func) );
            }
        }
        
        bool Remove(ListenerT * listener)
        {
            for (typename std::vector<Handler>::iterator m= listeners.begin(); m!=listeners.end(); m++)
                if ((*m).listener == listener)
                {
                    listeners.erase(m);
                    return true;
                }
            return false;
        }
        
        ReturnT* Broadcast(MessageT message, bool everyone = false)
        {
            ReturnT * handled = nullptr;
            for (typename std::vector<Handler>::iterator m= listeners.begin(); m!=listeners.end(); m++)
            {
                handled = ((*m).listener->*(*m).func)(message);
                if (handled != nullptr)
                    return handled;
            }
            return handled;
        }
        
    protected:
        
        std::vector<Handler> listeners;
    };
}}
#endif /* Channel_h */
