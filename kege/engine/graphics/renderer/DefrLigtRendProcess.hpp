/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       DefrLigtRendProcess.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef DefrLigtRendProcess_hpp
#define DefrLigtRendProcess_hpp
#include "Graphics.hpp"
#include "RenderEffect.hpp"
namespace kege{namespace gfx{
    
    class DefrLigtRendProcess : public RenderProcess
    {
    public:
        
        DefrLigtRendProcess( int x, int y, int width, int height );
        void Render( kege::SceneFrame& frame );
        void Draw( kege::SceneFrame& frame );
        void UnInit();
        bool Init();
        
        SharedFramebuffer fbo;
        const ds::string shader;
        int height, width, x, y;
    };
}}
#endif /* DefrLigtRendProcess_hpp */
