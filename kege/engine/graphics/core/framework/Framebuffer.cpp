//
//  Framebuffer.cpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 5/25/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "../../../graphics/core/framework/Framebuffer.hpp"
namespace kege {namespace core{
    
    void FBOLayout::AddRenderTexture2D( int index , int comp_type, int format, int channels, void* data, bool draw_buffer )
    {
        operator[]( index ).index = index;
        operator[]( index ).comp_type = comp_type;
        operator[]( index ).format = format;
        operator[]( index ).channels = channels;
        operator[]( index ).draw_buffer = draw_buffer;
        operator[]( index ).data = data;
    }
}}
