/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/5/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       RenderProcess.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef RenderProcess_hpp
#define RenderProcess_hpp
namespace kege{namespace gfx{
    class RenderingSystem;
    
    class RenderProcess
    {
    public:
        
        virtual void Render( gfx::RenderingSystem* renderer ) = 0;
        virtual void UnInit( gfx::RenderingSystem* renderer ) = 0;
        virtual bool Init( gfx::RenderingSystem* renderer ) = 0;
        
        virtual ~ RenderProcess(){}
    };

}}
#endif /* RenderProcess_hpp */
