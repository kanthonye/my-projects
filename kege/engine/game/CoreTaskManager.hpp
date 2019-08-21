/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       CoreTaskManager.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef CoreTaskManager_hpp
#define CoreTaskManager_hpp
#include <mutex>
#include <thread>
#include <unistd.h>
#include "CoreSystem.hpp"
namespace kege{
    class CoreTask;
    
    /**
     * CoreTaskManager is a system that runs on a separate thread from the
     * thread the GameEngine runs on. Its main uses is for processing task
     * in the background. for example loading data from files, etc
     */
    class CoreTaskManager : public kege::CoreSystem
    {
    public:
        
        void HandleMessage( const kege::Message& message );
        void AddTask(kege::CoreTask* task);
        void UnInit();
        bool Init();
        
        ~ CoreTaskManager();
        CoreTaskManager( kege::GameEngine* engine );
        
    private:
        
        void  ExecuteTasks();
        void  Stop();
        void  Run();
        
    private:
        
        friend CoreTask;
        kege::CoreTask* _head;
        kege::CoreTask* _tail;
        std::thread* _thread;
        std::mutex _lock;
        
        bool _running;
    };
}
#endif /* CoreTaskManager_hpp */
