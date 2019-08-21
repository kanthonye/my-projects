/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ForwardRenderProcess.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef ForwardRenderProcess_hpp
#define ForwardRenderProcess_hpp
#include "RenderProcess.hpp"
namespace kege{namespace gfx{

    class ForwardRenderProcess : public RenderProcess
    {
    public:
        void Render( gfx::RenderingSystem* renderer );
        void UnInit( gfx::RenderingSystem* renderer );
        bool Init( gfx::RenderingSystem* renderer );
    };
    
}}
#endif /* ForwardRenderProcess_hpp */
