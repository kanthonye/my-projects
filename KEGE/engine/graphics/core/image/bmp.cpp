//
//  bmp_loader.cpp
//  model_object
//
//  Created by Kenneth Esdaile on 5/21/15.
//  Copyright (c) 2015 kae. All rights reserved.
//

#include "bmp.hpp"
namespace kege{namespace bmp{
    
    typedef struct {
        unsigned short type;    //The characters "BM"
        unsigned int size;      //The size of the file in bytes
        unsigned short reserved1;//Unused - must be zero
        unsigned short reserved2;//Unused - must be zero
        unsigned int offsetBits; //Offset to start of Pixel Data
    }HEADER_BMP;
    
    unsigned char * read(BMP_FILEINFO& fileinfo, const char * filename)
    {
        FILE * file = fopen(filename,"rb");
        if (!file)
        {
            printf("Image %s could not be opened\n", filename);
            return 0;
        }
        unsigned BM = *((unsigned short*)((void*)("BM")));
        
        HEADER_BMP header;
        fread(&header, 1, sizeof(HEADER_BMP), file);
        
        if ( header.type != BM )
        {
            printf("bmp_loader() ERROR: %s is not a correct BMP file.\n",filename);
            return 0;
        }
        // read the bitmap file info header
        fread(&fileinfo, 1, sizeof(BMP_FILEINFO), file);
        
        // move file ptr to begining of image data
        fseek(file, header.offsetBits, SEEK_SET);
        
        if ( fileinfo.bpp != 24 )
        {
            printf("bmp_loader() ERROR: %s is not 24bit.\n",filename);
            return 0;
        }
        
        // Create a buffer
        unsigned char * data = new unsigned char [fileinfo.img_size + 1];
        
        // Read the actual data from the file into the buffer
        fread(data,1,fileinfo.img_size,file);
        
        // Everything is in memory now, the file wan be closed
        fclose (file);
        
        if ( data == nullptr )
        {
            return nullptr;
        }
        
        unsigned char t;
        // transform BGR to RGB by swapping R and B values
        for (unsigned int i = 0; i < fileinfo.img_size; i += 3 )
        {
            t = data[i];
            data[i] = data[i+2];
            data[i+2] = t;
        }
        data[fileinfo.img_size]='\0';
        return data;
    }
    
    
    bool write(int width, int height, unsigned char * data, const char * filename)
    {
        FILE * file = fopen(filename,"rb");
        if (!file)
        {
            printf("Image %s could not be created\n", filename);
            return 0;
        }
        HEADER_BMP header;
        header.size = sizeof(HEADER_BMP);
        header.type = 0x4D42;
        header.reserved1 = 0;
        header.reserved2 = 0;
        header.reserved2 = sizeof(HEADER_BMP) + sizeof(BMP_FILEINFO);
        
        BMP_FILEINFO fileinfo;
        fileinfo.header_size = sizeof(BMP_FILEINFO);
        fileinfo.width = width;
        fileinfo.height = height;
        fileinfo.plane = 1;
        fileinfo.bpp = 24;
        fileinfo.compression = 0;
        fileinfo.img_size = width * height * 3;
        fileinfo.xppm = 0;
        fileinfo.yppm = 0;
        fileinfo.colr_used = 0;
        fileinfo.colr_important = 0;
        
        unsigned char t;
        // transform RGB to BGR by swapping R and B values
        for (unsigned int i = 0; i < fileinfo.img_size; i += 3 )
        {
            t = data[i];
            data[i] = data[i+2];
            data[i+2] = t;
        }
        
        fwrite(&header, 1, sizeof(HEADER_BMP), file);
        fwrite(&fileinfo, 1, sizeof(BMP_FILEINFO), file);
        fwrite(&data, 1, fileinfo.img_size, file);
        fclose(file);
        return 1;
    }

}}











