/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       RenderSetting.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef RenderSetting_hpp
#define RenderSetting_hpp
#include "../../../graphics/core/cgmath/cgm.hpp"
namespace kege{namespace core{
    
    class RenderContext
    {
    public:
        
        virtual void ClearScreen(float x, float y, float z, float w)const = 0;
        virtual void EnablePointFrame()const = 0;
        virtual void EnableWireFrame()const = 0;
        virtual void EnableFillFrame()const = 0;
        virtual void DisableCulling()const = 0;
        virtual void EnableCullingCCW()const = 0;
        virtual void EnableCullingCW()const = 0;
        virtual void DisableDepthTest()const = 0;
        virtual void EnableDepthTest()const = 0;
        virtual void DisableBlending()const = 0;
        virtual void EnableBlending()const = 0;
        
        virtual ~ RenderContext(){}
    };
}}
namespace kege{namespace shared{
    typedef mem::shared< core::RenderContext > RenderContext;
}}
#endif /* Renderer_hpp */
