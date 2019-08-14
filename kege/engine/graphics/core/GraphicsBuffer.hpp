//
//  GraphicsBuffer.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/18/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef GraphicsBuffer_hpp
#define GraphicsBuffer_hpp
#include "Framebuffer.hpp"
namespace kege{ namespace gfx{
    
    class GraphicsBuffer
    {
    public:
        
        void BeginGeometricPass()const;
        void EndGeometricPass()const;
        void BeginLightingPass()const;
        void EndLightingPass()const;
        void ClearBuffer()const;
        
        void Create(short width, short height);
    private:
        
        int clear_buffer_bits;
        gfx::Framebuffer* fbo;
    };
}}
#endif /* DeferredGraphicsBuffer_hpp */
