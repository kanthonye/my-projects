/*!
 *  @author     Kenneth Anthony Esdaile
 *  @date       created on 4/23/19
 *  @copyright  Copyright (c) 2014 kae. All rights reserved.
 *  @file       System.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef System_hpp
#define System_hpp
#include "string.hpp"
#include "enumtypes.hpp"
#include "Message.hpp"
#include "Object.hpp"
#include "Logger.hpp"
namespace kege{
    class CoreSystems;
    
    class System : public kege::Object
    {
    public:
        
        virtual void HandleMessage( const kege::Message& message ) {}
        virtual void SendMessage( const kege::Message& message ) {}
        const ds::string& GetStrType(){return _sys_stype;}
        bool IsInit() const { return _init; }
        
        virtual void UnInit() {}
        virtual bool Init() = 0;
        virtual ~ System(){}
        
    protected:
        
        System(const ds::string& systyp)
        :   _sys_stype(systyp)
        ,   _init(false)
        {}
        
    protected:
        
        ds::string _sys_stype;
        bool _init;
        
        friend kege::CoreSystems;
    };
}
#endif /* System_hpp */
