//
//  tga.h
//  model_object
//
//  Created by Kenneth Esdaile on 5/9/15.
//  Copyright (c) 2015 kae. All rights reserved.
//

#ifndef __tga__
#define __tga__
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "string.hpp"
namespace kege{namespace tga{

    typedef struct {
        char  idlength;
        char  colourmaptype;
        char  datatypecode;
        short int colourmaporigin;
        short int colourmaplength;
        char  colourmapdepth;
        short int x_origin;
        short int y_origin;
        short width;
        short height;
        char  bitsperpixel;
        char  imagedescriptor;
    } HEADER;
    
    unsigned char * read(tga::HEADER& header, FILE* file);
    unsigned char * read(tga::HEADER& header, const ds::string& filename);
    bool write(const HEADER& header, const unsigned char * imgdata, const ds::string& filename);
    bool write(short width, short height, short channels, const unsigned char * data, const kege::ds::string & filename);
}}
#endif /* defined(__model_object__tga__) */
