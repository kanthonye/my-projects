/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/10/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       DeferredRenderProcess.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef DefrGeomRendProcess_hpp
#define DefrGeomRendProcess_hpp
#include "Graphics.hpp"
#include "RenderEffect.hpp"
namespace kege{namespace gfx{
    
    class DefrGeomRendProcess : public RenderProcess
    {
    public:
        
        DefrGeomRendProcess( int x, int y, int width, int height );
        void Render( kege::SceneFrame& frame );
        void Draw( kege::SceneFrame& frame );
        void UnInit();
        bool Init();
        
        SharedFramebuffer fbo;
        const ds::string shader;
        int height, width, x, y;
    };
}}
#endif /* DeferredRenderProcess_hpp */
