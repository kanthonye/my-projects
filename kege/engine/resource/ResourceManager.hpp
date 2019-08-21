/*! @author     Kenneth Esdaile
 *  @date       created on 4/30/17
 *  @copyright    Copyright © 2017 Kenneth Anthony Esdaile. All rights reserved.
 *  @file       ResourceManager.hpp
 *  @project    entity */

#ifndef ResMgr_hpp
#define ResMgr_hpp
#include "Resource.hpp"
namespace kege{

    class ResourceManager
    {
        typedef kege::listpair<ds::string, CoreResource*> CoreResources;
        typedef kege::listpair<ds::string, CoreLoader*> CoreLoaders;
        
    public:// kege::ResourceManager ResourceManager
        
        template<typename var> ResourceLoader< var >* AddLoader( ResourceLoader< var >* loader );
        template<typename var> ResourceLoader< var >* RemoveLoader( const ds::string& ext );
        template<typename var> ResourceLoader< var >* GetLoader( const ds::string& ext );
        
        template<typename var> ResourceFramework< var >* GetResource();
        
        
        
        template<typename var> mem::shared< var > Load( const ds::string& filename );
        
        /*
         * add object to resource. only once of each object can exist
         */
        template<typename var> mem::shared< var > Add( const ds::string& name, var* a );
        
        /*
         * add object to resource. only once of each object can exist
         */
        template<typename var> mem::shared< var > Add(const ds::string& name);
        
        /*
         * add object to resource. only once of each object can exist
         */
        template<typename var> mem::shared< var > Get(const ds::string& name);
        
        /*
         * instantly remove var by name from resource
         */
        template<typename var> mem::shared< var > Rem(const ds::string& name);
        
        /*
         * instantly remove var by name from resource
         */
        template<typename var> bool Del(const ds::string& name);
        
        
        void Terminate();
        
        virtual ~ ResourceManager();
        ResourceManager(){}
        
    private:
        
        void operator=(const ResourceManager& mgr);
        ResourceManager(const ResourceManager& mgr);
        
        kege::itemmap< long, CoreResources> _resources;
        kege::itemmap< long, CoreLoaders> _loaders;
    };
    
    
    template<typename var> ResourceLoader< var >* ResourceManager::AddLoader( ResourceLoader< var >* loader )
    {
        CoreLoaders* loaders = _loaders.get( loader->_file_ext.hash() );
        if (loaders != nullptr)
        {
            loaders->add(loader->_sid, loader);
            return loader;
        }
        _loaders[ loader->_file_ext.hash() ].add( loader->_sid, loader );
        return loader;
    }
    
    template<typename var> ResourceLoader< var >* ResourceManager::GetLoader( const ds::string& ext )
    {
        CoreLoaders* loaders = _loaders.get( ext.hash() );
        const ds::string nameID = typeid( var ).name();
        if (loaders != nullptr)
        {
            return (ResourceLoader< var >*) loaders->get( nameID );
        }
        return nullptr;
    }
    
    template<typename var> ResourceLoader< var >* ResourceManager::RemoveLoader( const ds::string& ext )
    {
        CoreLoaders* loaders = _loaders.get( ext.hash() );
        if (loaders != nullptr)
        {
            const ds::string sid = typeid( var ).name();
            return (ResourceLoader< var >*) loaders->rem( sid );
        }
        return nullptr;
    }
    
    template<typename var> ResourceFramework< var >* ResourceManager::GetResource()
    {
        const ds::string sid = typeid( var ).name();
        CoreResources* resources = _resources.get( sid.hash() );
        if ( resources != nullptr )
        {
            CoreResource** resource = resources->get( sid );
            if ( resource != nullptr )
            {
                return (ResourceFramework< var >*) *resource;
            }
        }
        return nullptr;
    }
    
    template<typename var> mem::shared< var > ResourceManager::Load( const ds::string& filename )
    {
        const ds::string& ext = filename.parse_fext();
        return GetLoader< var >( ext )->Load( filename );
    }
    
    template<typename var> mem::shared< var > ResourceManager::Add( const ds::string& name, var* a )
    {
        return GetResource< var >()->Add( name, a );
    }
    
    template<typename var> mem::shared< var > ResourceManager::Add(const ds::string& name)
    {
        return GetResource< var >()->Add( name, new var );
    }
    
    template<typename var> mem::shared< var > ResourceManager::Get(const ds::string& name)
    {
        return GetResource<var>()->Get(name);
    }
    
    template<typename var> mem::shared< var > ResourceManager::Rem(const ds::string& name)
    {
        return GetResource<var>()->Rem(name);
    }
    
    template<typename var> bool ResourceManager::Del(const ds::string& name)
    {
        return GetResource<var>()->Del(name);
    }
}
#endif /* Resource_hpp */
