/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/10/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ShadowRenderProcess.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef ShadowRenderProcess_hpp
#define ShadowRenderProcess_hpp
#include "RenderEffect.hpp"
namespace kege{namespace gfx{
    
    class ShadowRenderProcess : public RenderEffect
    {
    public:
        
        ShadowRenderProcess( int x, int y, int width, int height, const ds::string& fbo_read, const ds::string& fbo_write, const ds::string& shader );
        void Render( kege::SceneFrame& frame );
        void Draw( kege::SceneFrame& frame );
        void UnInit();
        bool Init();
    };
}}
#endif /* ShadowRenderProcess_hpp */
