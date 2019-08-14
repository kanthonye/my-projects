//
//  Message.cpp
//  terrain_gs_lod
//
//  Created by Kenneth A Esdaile on 5/20/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#include "Message.hpp"
namespace kege{
    
//    Message::Message(void* sref, const ds::string& sndr, const ds::string& detail, Content* content)
//    :   sender(sndr)
//    ,   detail(detail)
//    ,   content(content)
//    ,   sender_ref(sref)
//    ,   refcnt(0)
//    {}
//
//    Message::Message(const ds::string& sndr, const ds::string& detail, Content* content)
//    :   sender(sndr)
//    ,   detail(detail)
//    ,   content(content)
//    ,   sender_ref(nullptr)
//    ,   refcnt(0)
//    {}
//
//    Message:: ~ Message()
//    {
//        sender_ref = nullptr;
//        content = nullptr;
//        detail.clear();
//        sender.clear();
//    }
    
    
    
    
    void Envelope::operator =(const kege::Envelope& envelope)
    {
        delmsg = envelope.delmsg;
        operator=(envelope.message);
    }
    
    void Envelope::operator =(kege::Message* msg)
    {
        CLear();
        message = msg;
//        if (message != nullptr) message->refcnt++;
    }
    
    void Envelope::CLear()
    {
        if (message != nullptr)
        {
//            message->refcnt--;
//            if (message->refcnt == 0 && delmsg == true)
//            {
//                delete message;
//            }
            message = nullptr;
        }
    }
    Envelope::Envelope(const kege::Envelope& envelope)
    :   message(nullptr)
    ,   delmsg(true)
    {
        operator=(envelope);
    }
    Envelope::Envelope(kege::Message* msg)
    :   message(nullptr)
    ,   delmsg(true)
    {
        operator=(msg);
    }
    Envelope::Envelope(kege::Message& msg)
    :   message(&msg)
    ,   delmsg(false)
    {
        operator=(&msg);
    }
    Envelope::~ Envelope()
    {
        CLear();
    }
}
