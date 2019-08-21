//
//  bmp_loader.h
//  model_object
//
//  Created by Kenneth Esdaile on 5/21/15.
//  Copyright (c) 2015 kae. All rights reserved.
//

#ifndef __LOAD_BMP__
#define __LOAD_BMP__
#include <stdio.h>
namespace kege{namespace bmp{
    
    typedef struct {
        unsigned int header_size;
        unsigned int width;
        unsigned int height;
        unsigned short plane;
        unsigned short bpp;
        unsigned int compression;
        unsigned int img_size;
        unsigned int xppm;
        unsigned int yppm;
        unsigned int colr_used;
        unsigned int colr_important;
    }BMP_FILEINFO;
    
    unsigned char * read(BMP_FILEINFO& fileinfo, const char * filename);
    bool write(int width, int height, unsigned char * data, const char * filename);
    
}}
#endif /* defined(__model_object__bmp_loader__) */
