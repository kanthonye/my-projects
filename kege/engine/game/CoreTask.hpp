/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       CoreTask.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef CoreTask_hpp
#define CoreTask_hpp
#include "CoreSystem.hpp"
namespace kege{
    class CoreTaskManager;
    
    /**
     * CoreTask is a interface for implementing task that you want to executed in the back ground.
     */
    class CoreTask
    {
    public:
        
        virtual void Execute() = 0;
        virtual ~ CoreTask();
        CoreTask();
        
    private:
        
        friend CoreTaskManager;
        CoreTask* next;
        CoreTask* prev;
    };
}
#endif /* CoreTask_hpp */
