/*!
 *  @author     Kenneth Anthony Esdaile
 *  @date       created on 9/29/18
 *  @copyright  Copyright (c) 2014 kae. All rights reserved.
 *  @file       Singleton.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef Singleton_hpp
#define Singleton_hpp
#include <stdlib.h>
namespace kege{
    class Singleton
    {
    private:
        
        template <typename InstanceT> class Instance
        {
        public:
            
            static void Set(InstanceT* val0, bool val1)
            {
                instance = val0;
                alloc = val1;
            }
            
            static InstanceT* Get()
            {
                return instance;
            }
            
            static bool SM()
            {
                return alloc;
            }
            
            static InstanceT* instance;
            static bool alloc;
        };
        
    public:
        
        
        template <typename SingletonT> static void Set(SingletonT* singleton, bool is_static = false)
        {
            Instance<SingletonT>::Set(singleton, is_static);
        }
        
        template <typename SingletonT> static SingletonT* Get()
        {
            return Instance<SingletonT>::Get();
        }
        
        template <typename SingletonT> static void Free()
        {
            if (Instance<SingletonT>::Get() != nullptr)
            {
                if ( !Instance<SingletonT>::alloc )
                {
                    Instance<SingletonT>::Set(nullptr, false);
                }
                else
                {
                    delete Instance<SingletonT>::Get();
                    Instance<SingletonT>::Set(nullptr, false);
                }
            }
        }
    };
    
    template <typename InstanceT> InstanceT* Singleton::Instance<InstanceT>::instance = nullptr;
    template <typename InstanceT> bool Singleton::Instance<InstanceT>::alloc = false;
}
#endif /* Singleton_h */
