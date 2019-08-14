/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/5/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       RenderProcess.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef RenderProcess_hpp
#define RenderProcess_hpp
#include "SceneFrame.hpp"
namespace kege{namespace gfx{
    class RenderingSystem;
    
    class RenderProcess
    {
    public:
        
        virtual void Render( kege::SceneFrame& frame ) = 0;
        virtual void UnInit() = 0;
        virtual bool Init() = 0;
        
        virtual ~ RenderProcess(){}
        RenderProcess();
        
    protected:
        
        friend RenderingSystem;
        RenderingSystem* renderer;
    };

}}
#endif /* RenderProcess_hpp */
