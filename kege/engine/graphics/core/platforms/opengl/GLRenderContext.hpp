/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       GLRenderContext.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef GLRenderContext_hpp
#define GLRenderContext_hpp
#include "../../framework/RenderContext.hpp"
namespace kege{namespace core{
    
    class GLRenderContext : public RenderContext
    {
    public:
        
        void ClearScreen(float x, float y, float z, float w)const;
        void EnablePointFrame()const;
        void EnableWireFrame()const;
        void EnableFillFrame()const;
        void DisableCulling()const;
        void EnableCullingCCW()const;
        void EnableCullingCW()const;
        void DisableDepthTest()const;
        void EnableDepthTest()const;
        void DisableBlending()const;
        void EnableBlending()const;
        void AlphaBlending()const;
    };
}}
#endif /* GLRenderContext_hpp */
