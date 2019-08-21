/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Object.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef kege_Object_hpp
#define kege_Object_hpp
#include "Message.hpp"
namespace kege{
    
    class Object
    {
    public:
        
        enum Type
        {
            GUI_COMPONENT,
            ENTITY_COMPONENT,
        };
        
        virtual void HandleMessage( const kege::Message& message ) = 0;
        //inline int GetType() const {return _type;}
        virtual ~ Object(){}
        
    protected:
        
        //Object(int type) : _type( type ) {}
        
    protected:
        
        //int _type;
    };
}
#endif /* kege_Object_hpp */
