/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/3/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ResourceFramework.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef ResourceFramework_hpp
#define ResourceFramework_hpp
#include "shared.hpp"
#include "string.hpp"
#include <typeinfo>
namespace kege{
    class ResourceManager;
    
    class CoreResource
    {
    public:
        
        virtual void Terminate() = 0;
        
        virtual ~ CoreResource() {}
        
        CoreResource( const ds::string& sid )
        :   _sid( sid )
        ,   _manager( nullptr )
        {}
        
    protected:
        
        friend ResourceManager;
        ResourceManager* _manager;
        ds::string _sid;
    };
    
    
    
    class CoreLoader  : public CoreResource
    {
    public:
        
        CoreLoader( const ds::string& ext, const ds::string& sid )
        :   CoreResource( sid )
        ,   _file_ext( ext )
        {}
        
    protected:
        
        friend ResourceManager;
        const ds::string _file_ext;
    };
    
    
    
    template<typename var> class ResourceLoader : public CoreLoader
    {
    public:
        
        virtual kege::shared< var > Load( const ds::string& filename ) = 0;
        
        virtual ~ ResourceLoader() {}
        
        ResourceLoader( const ds::string& ext )
        :   CoreLoader( ext, typeid( var ).name() )
        {}
    };
    
    
    
    template<typename var> class ResourceFramework : public CoreResource
    {
    public:
        
        virtual kege::shared< var > Add( const ds::string& name, var * a ) = 0;
        
        virtual kege::shared< var > Rem( const ds::string& name ) = 0;
        
        virtual kege::shared< var > Get( const ds::string& name )const = 0;
        virtual kege::shared< var > Get( const ds::string& name ) = 0;
        
        virtual kege::shared< var > Has( const ds::string& name )const = 0;
        
        virtual void Terminate() = 0;
        
        virtual ~ ResourceFramework() {}
        
        ResourceFramework()
        :   CoreResource( typeid( var ).name() )
        {}
    };
}
#endif /* ResourceFramework_hpp */
