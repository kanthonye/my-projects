/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/10/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       RenderEffect.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef RenderEffect_hpp
#define RenderEffect_hpp
#include "RenderProcess.hpp"
namespace kege{namespace gfx{
    
    class RenderEffect : public RenderProcess
    {
    public:
        
        RenderEffect( int x, int y, int width, int height, const ds::string& fbo_read, const ds::string& fbo_write, const ds::string& shader );
        virtual void Render( gfx::RenderingSystem* renderer );
        virtual void Draw( gfx::RenderingSystem* renderer );
        virtual void UnInit( gfx::RenderingSystem* renderer );
        virtual bool Init( gfx::RenderingSystem* renderer );
        
        virtual ~ RenderEffect(){}
        
    protected:
        
        const ds::string fbo_write;
        const ds::string fbo_read;
        const ds::string shader_name;
        const int height;
        const int width;
        const int x,y;
    };
}}
#endif /* RenderEffect_hpp */
