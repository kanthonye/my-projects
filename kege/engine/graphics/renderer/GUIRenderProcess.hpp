/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GUIRenderProcess.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GUIRenderProcess_hpp
#define GUIRenderProcess_hpp
#include "RenderProcess.hpp"
namespace kege{namespace gfx{

    class GUIRenderProcess : public RenderProcess
    {
    public:
        void Render( kege::SceneFrame& frame );
        void UnInit();
        bool Init();
    };
    
}}
#endif /* GUIRenderProcess_hpp */
