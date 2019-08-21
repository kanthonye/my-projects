//
//  tga.c
//  model_object
//
//  Created by Kenneth Esdaile on 5/9/15.
//  Copyright (c) 2015 kae. All rights reserved.
//
#include "tga.hpp"
namespace kege{namespace tga{
    
    void swap_bytes(unsigned char pixel[5],unsigned char *p,int bytes)
    {
        if (bytes == 4)
        {
            pixel[0] = p[2];
            pixel[1] = p[1];
            pixel[2] = p[0];
            pixel[4] = p[3];
        }
        else if (bytes == 3)
        {
            pixel[0] = p[2];
            pixel[1] = p[1];
            pixel[2] = p[0];
        }
        else if (bytes == 2)
        {
            pixel[0] = (p[1] & 0x7c) << 1;
            pixel[1] = ((p[1] & 0x03) << 6) | ((p[0] & 0xe0) >> 2);
            pixel[2] = (p[0] & 0x1f) << 3;
            pixel[3] = (p[1] & 0x80);
        }
    }
    
    unsigned char * read(tga::HEADER& header, const ds::string& filename)
    {
        FILE *fptr = nullptr;
        if ((fptr = fopen(filename.c_str(),"r")) == NULL)
        {
            fprintf(stderr,"File open (%s) failed\n",filename.c_str());
            return nullptr;
        }
        return read(header, fptr);
    }
    
    unsigned char * read(tga::HEADER& header, FILE* fptr)
    {
        if (fptr == NULL)
        {
            fprintf(stderr,"[ERROR]: loading tga file: null file pointer not accepted\n");
            return nullptr;
        }
        
        int n=0,i,j;
        int channels,skipover = 0;
        unsigned char byte, p[5];
        
        /* Display the header fields */
        header.idlength = fgetc(fptr);
        header.colourmaptype = fgetc(fptr);
        header.datatypecode = fgetc(fptr);
        fread(&header.colourmaporigin,2,1,fptr);
        fread(&header.colourmaplength,2,1,fptr);
        header.colourmapdepth = fgetc(fptr);
        fread(&header.x_origin,2,1,fptr);
        fread(&header.y_origin,2,1,fptr);
        fread(&header.width,2,1,fptr);
        fread(&header.height,2,1,fptr);
        header.bitsperpixel = fgetc(fptr);
        header.imagedescriptor = fgetc(fptr);
        
        /* What can we handle */
        if (header.datatypecode != 2 && header.datatypecode != 10)
        {
            printf("Can only handle image type 2 and 10\n");
            exit(-1);
        }
        if (header.bitsperpixel != 16 && header.bitsperpixel != 24 && header.bitsperpixel != 32)
        {
            printf("Can only handle pixel depths of 16, 24, and 32\n");
            exit(-1);
        }
        if (header.colourmaptype != 0 && header.colourmaptype != 1)
        {
            printf("Can only handle colour map types of 0 and 1\n");
            return nullptr;
        }
        
        /* Skip over unnecessary stuff */
        skipover += header.idlength;
        skipover += header.colourmaptype * header.colourmaplength;
        //printf("Skip over %d bytes\n",skipover);
        fseek(fptr,skipover,SEEK_CUR);
        
        /* Read the image */
        channels = header.bitsperpixel / 8;
        unsigned int imgsize = header.width * header.height * channels;
        /* Allocate space for the image */
        unsigned char* imgdata = new unsigned char[imgsize];
        
        if (header.datatypecode == 2) /* Uncompressed */
        {
            if (fread(imgdata,1,imgsize,fptr) != imgsize)
            {
                fprintf(stderr,"Unexpected end of file at pixel\n");
                delete []imgdata;
                imgdata = nullptr;
                imgsize = 0;
            }
            for (n=0; n<imgsize; n+=channels)
            {
                byte = imgdata[n];
                imgdata[ n ] = imgdata[n+2];
                imgdata[n+2] = byte;
            }
        }
        else if (header.datatypecode == 10) /* Compressed */
        {
            unsigned counts = channels+1;
            for (n=0; n<imgsize; n+=channels)
            {
                if (fread(p, 1, counts, fptr) != counts)
                {
                    fprintf(stderr,"Unexpected end of file at pixel %d\n",n);
                    delete [] imgdata;
                    imgdata = nullptr;
                    return imgdata;
                }
                
                j = p[0] & 0x7f;
                swap_bytes(&(imgdata[n]), &(p[1]), channels);
                n++;
                
                if (p[0] & 0x80) /* RLE chunk */
                {
                    for (i=0;i<j;i++)
                    {
                        swap_bytes(&(imgdata[n]),&(p[1]), channels);
                        n++;
                    }
                }
                else /* Normal chunk */
                {
                    for (i=0;i<j;i++)
                    {
                        if (fread(p, 1, channels, fptr) != channels)
                        {
                            fprintf(stderr,"Unexpected end of file at pixel %d\n",i);
                            delete [] imgdata;
                            imgdata = nullptr;
                            return imgdata;
                        }
                        swap_bytes(&(imgdata[n]), p, channels);
                        n++;
                    }
                }
            }
        }
        fclose(fptr);
        return imgdata;
    }
    
    bool write(const HEADER& header, const unsigned char* imgdata, const ds::string& filename)
    {
        FILE *file = nullptr;
        if ((file = fopen(filename.c_str(),"w")) == NULL)
        {
            fprintf(stderr,"Failed to open outputfile\n");
            return false;
        }
        unsigned int i,byte;
        putc(header.idlength, file);
        putc(header.colourmaptype, file);
        putc(header.datatypecode, file);
        fwrite(&header.colourmaporigin,2,1,file);
        fwrite(&header.colourmaplength,2,1,file);
        putc(header.colourmapdepth, file);
        fwrite(&header.x_origin,2,1,file);
        fwrite(&header.y_origin,2,1,file);
        fwrite(&header.width,2,1,file);
        fwrite(&header.height,2,1,file);
        putc(header.bitsperpixel,file);
        putc(header.imagedescriptor, file);
        
        short channels = header.bitsperpixel / 8;
        unsigned int imgsize = header.width * header.height * channels;
        /* Allocate space for the image */
        unsigned char* data = new unsigned char[imgsize];
        memcpy(data, imgdata, imgsize);
        /* make rgb to bgr */
        for (i=0; i<imgsize; i+=channels)
        {
            byte = data[ i ];
            data[ i ] = data[i+2];
            data[i+2] = byte;
        }
        fwrite(data, 1, imgsize*channels, file);
        delete [] data;
        data = nullptr;
        fclose(file);
        return true;
    }
    
    
    bool write(short width, short height, short channels, const unsigned char * data, const kege::ds::string& filename)
    {
        tga::HEADER header;
        header.idlength = 0;
        header.colourmaptype = 0;
        header.datatypecode = 2;
        header.colourmaporigin = 0;
        header.colourmaplength = 0;
        header.colourmapdepth = 0;
        header.x_origin = 0;
        header.y_origin = 0;
        header.width = width;
        header.height = height;
        header.bitsperpixel = channels*8;
        header.imagedescriptor = 0;
        return tga::write(header, data, filename);
    }
    
}}




