//
//  GFXEnum.hpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 7/17/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef kege_GFXEnum_hpp
#define kege_GFXEnum_hpp
namespace kege{namespace gfx{
    
    enum GFX
    {
        VERTEX_POSITION = 0,
        VERTEX_TEXCOORD = 1,
        VERTEX_NORMAL   = 2,
        VERTEX_TANGENT  = 3,
        VERTEX_COLOR    = 4,
        VERTEX_WEIGHT   = 5,
        VERTEX_JOINT    = 6,
        VERTEX_IMGCOORD = 7,
        VERTEX_TXTRINFO = 8,
        VERTEX_MATRIX   = 9,
        
        SHADER_VERTEX,
        SHADER_FRAGMENT,
        SHADER_GEOMETRY,
        SHADER_TESS_EVAL,
        SHADER_TESS_CTROL,
        
        DRAW_POINTS,
        DRAW_LINES,
        DRAW_LINES_STRIP,
        DRAW_TRIANGLES,
        DRAW_TRIANGLE_STRIP,
        DRAW_PATCH,
        
        STATIC_DRAW,
        DYNAMIC_DRAW,
        STREAM_DRAW,
        
        DEPTH_BUFFER_BIT,
        COLOR_BUFFER_BIT,
        STENCIL_BUFFER_BIT,
        
        COLOR_COMPONENT,
        DEPTH_COMPONENT,
        
        REPEAT,
        MIRRORED_REPEAT,
        CLAMP_TO_EDGE,
        LINEAR_FILTER,
        NEAREST_FILTER,
        
        RED,
        RGB,
        RGBA,
        
        RGB16,
        RGB32,
        
        UNSIGNED_BYTE,
        UNSIGNED_SHORT,
        UNSIGNED_INT,
        BYTE,
        SHORT,
        FLOAT,
        FLOAT16,
        FLOAT32,
        INT,
        INT8,
        INT16,
        INT24,
        INT32,
        VEC4,
        VEC3,
        VEC2,
        MAT4,
        MAT3,
        MAT2,
    };
}}
#endif /* kege_GFXEnum_hpp */
