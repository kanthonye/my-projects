/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/10/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIEvent.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "GUIEvent.hpp"
namespace kege{namespace cg{
    
    const char* GUIEnumToStrong(int n)
    {
        switch (n)
        {
            case GUIEvent::RELEASE:  return "RELEASE";
            case GUIEvent::GRABBING: return "GRABBING";
            case GUIEvent::PRESSED:  return "PRESSED";
            case GUIEvent::PRESSING: return "PRESSING";
                
            default: break;
        }
        return "NOTHING";
    }
    void PrintGUIEvent(int n)
    {
        printf("%s\n", GUIEnumToStrong(n));
    }
}}

