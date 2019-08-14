/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/9/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       CoreTask.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "CoreTask.hpp"
namespace kege{
    
    CoreTask:: ~ CoreTask()
    {   // remove task from link
    }
    
    CoreTask::CoreTask()
    :   next(nullptr)
    ,   prev(nullptr)
    {
    }
}
