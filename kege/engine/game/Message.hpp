//
//  Message.hpp
//  terrain_gs_lod
//
//  Created by Kenneth A Esdaile on 5/20/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef Message_hpp
#define Message_hpp
#include "vec4.hpp"
#include "shared.hpp"
#include "string.hpp"
#include "enumtypes.hpp"
namespace kege{
    
    struct MSG
    {
        enum Typ : short
        {
            UNKNOWN = 1,
            TERMINATE,
            WINDOW_CLOSED,
            
            ANONYMOUSE,
            GUI_EVENT,
            GUI_MSG,
            
            KEYBOARD_KEY,
            MOUSE_KEY,
            MOUSE_CURSOR_MOVE,
            MOUSE_WHEEL_MOVE,
            
            COMMAND,
            MOVE_FORWARD,
            MOVE_BACKWARD,
            MOVE_RIGHTWARD,
            MOVE_LEFTWARD,
            MOVE_UPWARD,
            MOVE_DOWNWARD,
            TURN_RIGHT,
            TURN_LEFT,
            JUMP,
            ZOOM_IN,
            ZOOM,
            UPLOAD_TILE,
            UNLOAD_TILE,
            SET_POSITION,
            SET_ROTATION,
            SET_SCALE,
            ROTATE_XYZ,
            ROTATE_XY,
            ROTATE_YZ,
            ROTATE_X,
            ROTATE_Y,
            ROTATE_Z,
            CAST_RAY,
            ROTATE,
            ZOOM_OUT,
            COLLISION,
            VELOCITY,
            
            WIRE_FRAME,
            POINT_FRAME,
        };
    };
}


namespace kege{
    
    class Message
    {
    public:
        
        cg::ushort GetType() const {return _type;}
        Message(cg::ushort type): _type( type ) {}
        virtual ~ Message(){}
        
    private:
        
        const cg::uint _type;
    };
    
    
    struct MoveBackward : public kege::Message
    {
        MoveBackward() : kege::Message( kege::MSG::MOVE_BACKWARD ) {}
    };
    
    struct MoveForward : public kege::Message
    {
        MoveForward() : kege::Message( kege::MSG::MOVE_FORWARD ) {}
    };
    
    struct MoveDownward : public kege::Message
    {
        MoveDownward() : kege::Message( kege::MSG::MOVE_DOWNWARD ) {}
    };
    
    struct MoveUpward : public kege::Message
    {
        MoveUpward() : kege::Message( kege::MSG::MOVE_UPWARD ) {}
    };
    
    struct MoveRightward : public kege::Message
    {
        MoveRightward() : kege::Message( kege::MSG::MOVE_RIGHTWARD ) {}
    };
    
    struct MoveLeftward : public kege::Message
    {
        MoveLeftward() : kege::Message( kege::MSG::MOVE_LEFTWARD ) {}
    };
    
    struct WindowClosed : public kege::Message
    {
        WindowClosed() : kege::Message( kege::MSG::WINDOW_CLOSED ) {}
    };
    
    struct MsgTerminate : public kege::Message
    {
        MsgTerminate() : kege::Message( kege::MSG::TERMINATE ) {}
    };
    
    struct MsgZoomOut : public kege::Message
    {
        MsgZoomOut(float v) : kege::Message( kege::MSG::ZOOM_OUT ), val(v) {}
        const float val;
    };
    
    struct MsgZoomin : public kege::Message
    {
        MsgZoomin(float v) : kege::Message( kege::MSG::ZOOM_IN ), val(v) {}
        const float val;
    };
    
    struct MsgRotateX : public kege::Message
    {
        MsgRotateX(float v) : kege::Message( kege::MSG::ROTATE_X ), val(v) {}
        const float val;
    };
    
    struct MsgRotateY : public kege::Message
    {
        MsgRotateY(float v) : kege::Message( kege::MSG::ROTATE_Y ), val(v) {}
        const float val;
    };
    
    struct MsgMsgRotateZ : public kege::Message
    {
        MsgMsgRotateZ(float v) : kege::Message( kege::MSG::ROTATE_Z ), val(v) {}
        const float val;
    };
    
    struct MsgRotateXY : public kege::Message
    {
        MsgRotateXY(double x, double y) : kege::Message( kege::MSG::ROTATE_XY ), x(x), y(y) {}
        const double x,y;
    };
    
    struct MsgCastRay : public kege::Message
    {
        MsgCastRay(double x, double y) : kege::Message( kege::MSG::CAST_RAY ), x(x), y(y) {}
        const double x,y;
    };
    
    struct MsgCommand : public kege::Message
    {
        MsgCommand( bool a, cg::uint c ) : kege::Message( kege::MSG::COMMAND ), action( a ), command( c ) {}
        const cg::uint command;
        const bool action;
    };
    

    
    
    
    
    
    
    
    
    struct MsgKeyboardKey : public kege::Message
    {
        MsgKeyboardKey( short a, short key, short mod, const kege::MSG::Typ comm )
        :   kege::Message( kege::MSG::KEYBOARD_KEY )
        ,   command( comm )
        ,   action( a )
        ,   mods( mod )
        ,   key( key )
        {}
        
        MsgKeyboardKey( short a, short key, short mod )
        :   kege::Message( kege::MSG::KEYBOARD_KEY )
        ,   command( kege::MSG::UNKNOWN )
        ,   action( a )
        ,   mods( mod )
        ,   key( key )
        {}
        
        kege::MSG::Typ command;
        short action;
        short mods;
        short key;
    };
    
    struct MsgMouseKey : public kege::Message
    {
        MsgMouseKey( short a, short key, short mod, const kege::MSG::Typ comm )
        :   kege::Message( kege::MSG::MOUSE_KEY )
        ,   command( comm )
        ,   action( a )
        ,   mods( mod )
        ,   key( key )
        {}
        
        MsgMouseKey( short a, short key, short mod )
        :   kege::Message( kege::MSG::KEYBOARD_KEY )
        ,   command( kege::MSG::UNKNOWN )
        ,   action( a )
        ,   mods( mod )
        ,   key( key )
        {}
        
        kege::MSG::Typ command;
        short action;
        short mods;
        short key;
    };
    
    struct MsgMouseCursorMove : public kege::Message
    {
        MsgMouseCursorMove( double x, double y, const kege::MSG::Typ comm )
        :   kege::Message( kege::MSG::MOUSE_CURSOR_MOVE )
        ,   command( comm )
        ,   x( x )
        ,   y( y )
        {}
        MsgMouseCursorMove( double x, double y )
        :   kege::Message( kege::MSG::MOUSE_CURSOR_MOVE )
        ,   command( kege::MSG::UNKNOWN )
        ,   x( x )
        ,   y( y )
        {}
        
        kege::MSG::Typ command;
        double x, y;
    };
    
    struct MsgMouseWheelMove : public kege::Message
    {
        MsgMouseWheelMove( double x, double y, const kege::MSG::Typ comm )
        :   kege::Message( kege::MSG::MOUSE_WHEEL_MOVE )
        ,   command( comm )
        ,   x( x )
        ,   y( y )
        {}
        MsgMouseWheelMove( double x, double y )
        :   kege::Message( kege::MSG::MOUSE_CURSOR_MOVE )
        ,   command( kege::MSG::UNKNOWN )
        ,   x( x )
        ,   y( y )
        {}
        
        kege::MSG::Typ command;
        double x, y;
    };
    
    
    
    
    
    
    
    class Content
    {
    public:
        
        const ds::string& GetDataType()const {return type;}
        ds::string& GetDataType() {return type;}
        
        virtual const void* GetData()const = 0;
        virtual void* GetData() = 0;
        
        Content(const ds::string& t)
        :   type(t) {}
        
        virtual ~ Content(){}
        
    private:
        
        ds::string type;
    };
    
    
    
    template<typename var> class ContentT : public kege::Content
    {
    public:
        
        const void* GetData()const {return &data;}
        void* GetData() {return &data;}
        
        ContentT(var& data, const ds::string& type)
        :   Content(type)
        ,   data(data)
        {}
        
    private:
        
        var data;
    };
    
    template<typename var> class MsgT : public Message
    {
    public:
        
        MsgT(const ds::string& sndr, const ds::string& detail, const ds::string& type, var& mdata)
        :   Message(0)
        ,   msgt_data(mdata, type)
        {}
        
    private:
        
        ContentT<var> msgt_data;
    };
}
    
    

namespace kege{
    
    class Envelope
    {
    public:
        
        void operator =(const Envelope& envelope);
        void operator =(Message* msg);
        
        const Message* GetMessage() const {return message;}
        Message* GetMessage() {return message;}
        bool HasMessage()const{return (message != nullptr);}
        
        Envelope(const Envelope& envelope);
        Envelope(Message* msg);
        Envelope(Message& msg);
        ~ Envelope();
        
    private:
        
        void CLear();
        
        Message* message;
        bool delmsg;
    };
}
    


namespace kege{
    
    template<typename var> class MsgTi : public MsgT<var>
    {
    public:
        
        MsgTi(int datatype, short state, var& mdata, const ds::string& detail)
        :   MsgT<var>(datatype, mdata, detail)
        ,   state(state)
        {}
        
        short GetState()const
        {
            return state;
        }
        
    private:
        short state;
    };
    
    
    template<typename VarT> class MsgRefT : public Message
    {
    public:
        
        MsgRefT(int datatype, VarT* mdata, const ds::string& detail)
        :   Message(datatype, mdata, detail)
        ,   msgt_data(mdata)
        {}
        
    private:
        
        VarT* msgt_data;
    };
}
#endif /* Message_hpp */
