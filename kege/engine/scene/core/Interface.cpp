/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/16/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Interface.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "../../scene/core/Interface.hpp"
namespace kege{

    bool Interface::Bind( short key, cg::uint command, bool force_bind )
    {
        if ( key < 512 )
        {
            if ( commands[ key ] < kege::MSG::UNKNOWN || force_bind == true )
            {
                commands[ key ] = command;
                return true;
            }
        }
        return false;
    }
    
    void Interface::UnBind( short key, cg::uint command  )
    {
        if ( key < 512 )
        {
            commands[ key ] = kege::MSG::UNKNOWN;
        }
    }
    
    void Interface::OnMouseCursor(const kege::Cursor& cursor)
    {
        HandleMessage( kege::MsgRotateXY( cursor.dx, cursor.dy ) );
    }
    
    void Interface::OnMouseWheel(const kege::Cursor& cursor)
    {
        //HandleMessage( kege::MsgCommand( key.action, commands[ key.GetKey() ] ) );
    }
    
    void Interface::OnKey(const kege::Key& key)
    {
        std::map<long, ds::dlist<kege::Object*>>::iterator handlers = _message_handlers.find( commands[ key.GetKey() ] );
        if ( handlers != _message_handlers.end() )
        {
            for (ds::dlist<kege::Object*>::iterator i=handlers->second.begin(); i!=nullptr; i++)
            {
                i->HandleMessage( kege::MsgCommand( key.action, commands[ key.GetKey() ] ) );
            }
        }
    }
    
    void Interface::RemvMsgHandler( cg::uint msgtyp, kege::Object* object )
    {
        std::map<long, ds::dlist<kege::Object*>>::iterator list = _message_handlers.find( msgtyp );
        if ( list != _message_handlers.end() )
        {
            for (ds::dlist<kege::Object*>::iterator i=list->second.begin(); i!=nullptr; i++)
            {
                if (i.element() == object)
                {
                    list->second.erase( i );
                    break;
                }
            }
        }
    }
    
    void Interface::AddMsgHandler(cg::uint msgtyp, kege::Object* object)
    {
        std::map<long, ds::dlist<kege::Object*>>::iterator list = _message_handlers.find( msgtyp );
        if ( list != _message_handlers.end() )
        {
            for (ds::dlist<kege::Object*>::iterator i=list->second.begin(); i!=nullptr; i++)
            {
                if (i.element() == object)
                {
                    return;
                }
            }
        }
        _message_handlers[ msgtyp ].push_back( object );
    }
    
    void Interface::HandleMessage( const kege::Message& message )
    {
        std::map<long, ds::dlist<kege::Object*>>::iterator handlers = _message_handlers.find( message.GetType() );
        if ( handlers != _message_handlers.end() )
        {
            for (ds::dlist<kege::Object*>::iterator i=handlers->second.begin(); i!=nullptr; i++)
            {
                i->HandleMessage( message );
            }
        }
    }
    
    Interface::Interface()
    {
        for (int i=0; i<512; i++) commands[ i ] = kege::MSG::UNKNOWN;
    }
    
}
