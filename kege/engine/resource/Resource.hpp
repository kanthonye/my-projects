//
//  Resource.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/31/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef Resource_hpp
#define Resource_hpp
#include "VFS.hpp"
#include "Logger.hpp"
#include "listpair.hpp"
#include "itemmap.hpp"
#include "ResourceFramework.hpp"
namespace kege{
    
    template<typename var> class Resource : public ResourceFramework< var >
    {
        typedef kege::listpair<ds::string, mem::pointer< var >> Assets;
    public:
        
        mem::shared< var > Add( const ds::string& name, var * a ) override
        {
            Assets& assets = _resources[ name.hash() ];
            assets.add( name, mem::pointer< var >( a ) );
            return a;
        }
        
        mem::shared< var > Rem( const ds::string& name ) override
        {
            unsigned long key = name.hash();
            Assets* assets = _resources.get( key );
            if ( assets == nullptr )
            {
                return nullptr;
            }
            return assets->rem( key );
        }
        
        mem::shared< var > Get( const ds::string& name )const override
        {
            Assets* assets = _resources.get( name.hash() );
            if ( assets == nullptr )
            {
                return nullptr;
            }
            return assets->get( name );
        }
        
        mem::shared< var > Get( const ds::string& name ) override
        {
            Assets* assets = _resources.get( name.hash() );
            if ( assets == nullptr )
            {
                return nullptr;
            }
            return assets->get( name );
        }
        
        bool Has( const ds::string& name )const override
        {
            Assets* assets = _resources.get( name.hash() );
            if ( assets == nullptr )
            {
                return nullptr;
            }
            return assets->has( name );
        }
        
        void Terminate()override
        {
            _resources.clear();
            
            //typename Assets::iterator a;
            //typename kege::Resmap< long, Assets>::iterator r;
            //for (r=_resources; r!=_resources.end(); r++)
            //{
            //    for (a=r->second.begin(); a!=nullptr; a++)
            //    {
            //        a.element();
            //    }
            //}
        }
        
        ~ Resource()
        {
            Terminate();
        }
        
        Resource() {}
        
        
        kege::itemmap< long, Assets> _resources;
    };
}
#endif /* Resource_hpp */
