/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       CoreTaskManager.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "CoreTask.hpp"
#include "Singleton.hpp"
#include "CoreTaskManager.hpp"
namespace kege{
    
    void CoreTaskManager::HandleMessage( const kege::Message& message )
    {
//        if ( !envelope.HasMessage() ) return;
//        if ( envelope.GetMessage()->GetDetail() == "TERMINATE" )
//        {
//            Stop();
//        }
    }
    
    void CoreTaskManager::AddTask(kege::CoreTask* task)
    {
        std::lock_guard<std::mutex> guard(_lock);
        // add task to link
        if (_head == nullptr)
        {
            _tail = _head = task;
        }
        else
        {
            _tail->next = task;
            task->prev = _tail;
            _tail = task;
        }
    }
    void CoreTaskManager::UnInit()
    {
        Stop();
        std::lock_guard<std::mutex> guard(_lock);
        CoreTask* task;
        while (_head != nullptr)
        {
            task = _head;
            _head = _head->next;
            // delete completed task
            if (task != nullptr)
            {
                delete task;
                task = nullptr;
            }
        }
        _tail = _head = nullptr;
        _init = false;
    }
    
    bool CoreTaskManager::Init()
    {
        _init = true;
        return _init;
    }
    
    void CoreTaskManager::ExecuteTasks()
    {
        std::lock_guard<std::mutex> guard(_lock);
        CoreTask* task;
        while (_head != nullptr)
        {
            task = _head;
            
            _head->Execute();
            _head = _head->next;
            
            // delete completed task
            if (task != nullptr)
            {
                delete task;
                task = nullptr;
            }
        }
        _tail = _head = nullptr;
    }
    
    void  CoreTaskManager::Stop()
    {
        _running = false;
    }
    
    void  CoreTaskManager::Run()
    {
        _running = true;
        while (_running)
        {
            ExecuteTasks();
        }
    }
    
    CoreTaskManager::~ CoreTaskManager()
    {
        kege::Singleton::Free<CoreTaskManager>();

        if ( _thread != nullptr )
        {
            if ( _thread->joinable() )
            {
                _thread->join();
            }
            delete _thread;
            _thread = nullptr;
        }
    }
    
    CoreTaskManager::CoreTaskManager( kege::GameEngine* engine )
    :   kege::CoreSystem( "CoreTaskManager", engine )
    ,   _thread(nullptr)
    ,   _head(nullptr)
    ,   _tail(nullptr)
    {
        _thread = new std::thread( &CoreTaskManager::Run, this );
         kege::Singleton::Set<CoreTaskManager>(this);
    }
}
