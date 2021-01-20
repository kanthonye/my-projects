//
//  System.hpp
//  Particles
//
//  Created by Kenneth A Esdaile on 5/11/20.
//  Copyright © 2020 Kenneth A Esdaile. All rights reserved.
//

#ifndef System_hpp
#define System_hpp
#include <map>
#include "bitopp.hpp"
#include "Object.hpp"
#include "string.hpp"
#include "Logger.hpp"
#include "Messenger.hpp"
namespace kege
{    
    class Config;
    
    class BaseSystem : public ObjectType< BaseSystem >
    {
    public:
        
        virtual void Disconnect( Messenger& messenger ){}
        virtual void Connect( Messenger& messenger ){}
        virtual void Handle( const Message& msg ){}
        virtual void Configure( Config& config ){}
        virtual void Update( double dt ){}
        virtual uint GetType()const;
        virtual void Shutdown();
        virtual bool Init();
        
        void Insert( int entity );
        void Remove( int entity );
        
        static int GET_SYSTEM_TOTAL_TYPES();
        const string& GetName()const;
        bool IsInit()const;
        
        virtual ~BaseSystem();

    protected:
        
        /* for SystemType uses only */
        static int GEN_NEW_SYST_TYPE()
        {
            return _system_total_types++;
        }
        
        /* constructor. */
        BaseSystem( int type_id, const string& name )
        :   _name( name )
        ,   _init( false )
        ,   _syst_type( type_id )
        {}
        
    protected:
        
        const string _name;
        bool _init;
        
    private:
        
        static int _system_total_types;
        int _syst_type;
    };
}

namespace kege
{    
    template< typename M > class System : public BaseSystem
    {
    public:
        
        System( int type, const string& name )
        : BaseSystem( type, name )
        , _mgr(nullptr) 
        {}
        
        void SetMgr(M* mgr){_mgr = mgr;}
        M* GetMgr(){return _mgr;}
        virtual ~ System(){}
        
    private:
        
        M* _mgr;
    };
}
    
namespace kege
{    
    template< typename M, typename T > class SystemType : public System< M >
    {
    public:
        
        static unsigned int GET_SYST_TYPE() { return _sys_type_id; }
        
        SystemType( const string& name ) 
        : System< M >( _sys_type_id, name ) 
        {}
        
        virtual ~ SystemType(){}
        
    private:
        
        static const unsigned int _sys_type_id;
    };
    
    template< typename M, typename T > 
    const unsigned int SystemType< M,T >::_sys_type_id = SystemType< M,T >::GEN_NEW_SYST_TYPE();
}

    
namespace kege
{    
    /**
     CSM (Core System Manager)
     */
    template< typename M > class CSM : public ObjectType< CSM< M > >
    {
    public:
        typedef ref< System< M > > Syst;
        typedef std::vector< Syst > Systems;
        typedef typename Systems::reverse_iterator ReverseIterator;
        typedef typename Systems::iterator Iterator;
        
        /**
         create add a systems to this manager 
         */
        template< typename S > S* Add( Syst system )
        {
            if ( system != nullptr )
            {
                _systems.push_back( system );
                system->SetMgr( _mgr );
            }
            return (S*) system.rawptr();
        }
        
        /**
         create add a systems to this manager 
         */
        template< typename S > S* Add()
        {
            return this->Add< S >( new S );
        }
        
        /**
         remove a systems from this manager 
         */
        template< typename S > void Del()
        {
            uint syst_type = SystemType< M,S >::GET_SYST_TYPE();
            for(Iterator s=_systems.begin(); s!=_systems.end(); s++)
            {
                if((*s)->GetType() == syst_type)
                {
                    (*s).deref();
                    _systems.erase(s);
                    break;
                }
            }
        }
        
        /**
         retreive a systems from this manager 
         */
        template< typename S > S* Get()
        {
            uint syst_type = SystemType< M,S >::GET_SYST_TYPE();
            for(Iterator s=_systems.begin(); s!=_systems.end(); s++)
            {
                if((*s)->GetType() == syst_type)
                {
                    return (S*) (*s).rawptr();
                }
            }
            return nullptr;
        }
        
        /**
         Disconnect systems from the provided messenger 
         */
        void Disconnect( Messenger& messenger )
        {
            for(Iterator s=_systems.begin(); s!=_systems.end(); s++)
            {
                (*s)->Disconnect( messenger );
            }
        }
        
        /**
         Connect systems to the provided messenger 
         */
        void Connect( Messenger& messenger )
        {
            for(Iterator s=_systems.begin(); s!=_systems.end(); s++)
            {
                (*s)->Connect( messenger );
            }
        }
        
        /**
         Allow systems to handle the provided message 
         */
        void Handle( const Message& msg )
        {
            for(Iterator s=_systems.begin(); s!=_systems.end(); s++)
            {
                (*s)->Handle( msg );
            }
        }
        
        /**
         Allow systems to get configurations
         */
        void Configure( Config& config )
        {
            for(Iterator s=_systems.begin(); s!=_systems.end(); s++)
            {
                (*s)->Configure( config );
            }
        }
        
        /**
         update all systems in the order which they were added
         */
        void Update( double delta )
        {
            for(Iterator s=_systems.begin(); s!=_systems.end(); s++)
            {
                (*s)->Update( delta );
            }
        }
        
        /**
         Shutdown all systems in reverse order in which they were added
         */
        void Shutdown()
        {
            for(ReverseIterator s=_systems.rbegin(); s!=_systems.rend(); s++)
            {
                (*s)->Shutdown();
            }
        }
        
        bool Init()
        {
            for(Iterator s=_systems.begin(); s!=_systems.end(); s++)
            {
                if( !(*s)->Init() )
                    return false;
            }
            return true;
        }
        
        void Clear()
        {
            _systems.clear();
        }
        
        virtual ~CSM()
        {
            Clear();
        }
        
        CSM( M* mgr )
        : _mgr( mgr ) 
        {}
        
    public:
        
        Systems _systems;
        M* _mgr;
    };
}




namespace kege{
    
    template< typename T > struct MsgShutdownSystem : public MsgType< MsgShutdownSystem< T > >
    {
        MsgShutdownSystem() : MsgType< MsgShutdownSystem >( nullptr ) {}
    };
    
    template< typename T > struct MsgDisableSystem : public MsgType< MsgDisableSystem< T > >
    {
        MsgDisableSystem() : MsgType< MsgDisableSystem >( nullptr ) {}
    };
    
    template< typename E, typename T > struct MsgTempDisableSystem : public MsgType< MsgTempDisableSystem< E,T > >
    {
        MsgTempDisableSystem() 
        : MsgType< MsgTempDisableSystem< E,T > >( nullptr )
        , sys_type_id( SystemType< E,T >::GET_SYST_TYPE() ) 
        {}
        int sys_type_id;
    };
    
    /* enable a particular system */
    template< typename T > struct MsgEnableSystem : public MsgType< MsgEnableSystem< T > >
    {
        MsgEnableSystem() : MsgType< MsgEnableSystem >( nullptr ) {}
    };
    
    struct MsgShutdown : public MsgType< MsgShutdown >
    {
        MsgShutdown() : MsgType< MsgShutdown >( nullptr ) {}
    };
    
    struct MsgExecuteRender : public MsgType< MsgExecuteRender >
    {
        MsgExecuteRender( const string& s )
        :   MsgType< MsgExecuteRender >( nullptr )
        ,   name( s ) {}
        string name;
    };
}
#endif /* System_hpp */
