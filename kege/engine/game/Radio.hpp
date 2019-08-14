/*! @author     Kenneth Esdaile
 *  @date       created on 11/25/16
 *  @copyright  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
 *  @file       Radio.hpp
 *  @project    GameEngine */

#ifndef Radio_hpp
#define Radio_hpp
#include <map>
#include <vector>
#include <stdio.h>
#include "string.hpp"
namespace kege{namespace com{
    
    class Radio
    {
    private:
        
        template <typename MessageT>  class CommLine
        {
            typedef std::function< bool(MessageT) > function;
        public:
            
            template <typename HandlerT> void Add(HandlerT * h)
            {
                typename std::vector< void* >::iterator it = std::find(addresses.begin(), addresses.end(), h);
                if (it != addresses.end())
                    return;
                addresses.push_back(h);
                handlers.push_back( [h](MessageT msg)->bool{ return h->ReceiveMessage(msg); } );
            }
            
            template <typename HandlerT> bool Remove(HandlerT* h)
            {
                typename std::vector< void* >::iterator it = std::find(addresses.begin(), addresses.end(), h);
                if (it == addresses.end())
                    return false;
                long n = it - addresses.begin();
                handlers.erase(handlers.begin() + n);
                addresses.erase(it);
                return true;
            }
            
            bool Broadcast(MessageT msg)
            {
                bool receive = false;
                for (typename std::vector< function >::iterator func= handlers.begin(); func!=handlers.end(); func++)
                    if ( (*func)( msg ) ) receive = true;
                return receive;
            }
            
            ~ CommLine(){}
            CommLine(){}
            
        private:
            
            std::vector< function > handlers;
            std::vector< void* > addresses;
        };
        
        template <typename MessageT>  static CommLine< MessageT > & GetInstance()
        {
            static CommLine<MessageT> comm;
            return comm;
        }
        
    public:
        
        /**
         add a listeners for channel MessageT.
         each listeners mush have overloadfunction operator()(message)
         */
        template <typename MessageT, typename HandlerT>  static void Add(HandlerT* handler)
        {
            GetInstance< MessageT >().Add(handler);
        }
        
        /**
         remove a handler from a channel type MessageT.
         */
        template <typename MessageT, typename HandlerT>  static bool Remove(HandlerT* handler)
        {
            return GetInstance< MessageT >().Remove(handler);
        }
        
        /**
         notify all its listeners of message typename MessageT
         */
        template <typename MessageT>  static bool Broadcast(MessageT message)
        {
            return GetInstance< MessageT >().Broadcast(message);
        }
    };
}}
#endif /* Radio_hpp */
