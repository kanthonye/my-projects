//
//  Messenger.hpp
//  dev0
//
//  Created by Kenneth A Esdaile on 9/10/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef Messenger_hpp
#define Messenger_hpp
#include <vector>
#include "Message.hpp"
namespace kege{
    
    
    template <typename ListenerT, typename MessageT> class Messenger
    {
    public:
        
        typedef bool (ListenerT::*Funct)(MessageT msg);
        
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
        
        bool Broadcast(MessageT message, bool everyone = false)
        {
            bool reveived = false, handled;
            for (typename std::vector<Handler>::iterator m= listeners.begin(); m!=listeners.end(); m++)
            {
                handled = ((*m).listener->*(*m).func)(message);
                if (handled && !everyone)
                    return true;
                else if (!reveived && handled)
                    reveived = true;
            }
            return reveived;
        }
        
    protected:
        
        std::vector<Handler> listeners;
    };
}
#endif /* Messenger_hpp */
