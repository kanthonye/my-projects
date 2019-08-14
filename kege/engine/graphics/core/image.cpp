//
//  image.cpp
//  Node Base Renderer
//
//  Created by Kenneth Esdaile on 11/21/15.
//  Copyright © 2015 kanthonye. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include "tga.hpp"
#include "bmp.hpp"
#include "lodepng.h"
#include "image.hpp"
#include "VFS.hpp"
namespace kege{
    
    kege::image<cg::uchar> open_image_tga(const ds::string & filename)
    {
        if (filename.empty())
        {
            return kege::image<cg::uchar>();
        }
        kege::tga::HEADER info;
        cg::ubyte* data = kege::tga::read(info, filename.c_str());
        if ( data == nullptr )
        {
            printf("[ERROR : open_image_tga()] file->%s\n", filename.c_str());
            return kege::image<cg::uchar>();
        }
        return kege::image<cg::uchar>(info.bitsperpixel/8, info.bitsperpixel, info.width, info.height, gfx::GFX::UNSIGNED_BYTE, data);
    }
    
    kege::image<cg::uchar> open_image_png(const ds::string & filename)
    {
        ds::string fname = kege::VFS::GetInstance().GetFilename(filename);
        if (fname.empty())
        {
            return kege::image<cg::uchar>();
        }
        unsigned width, height;
        std::vector<unsigned char> img;
        unsigned error = lodepng::decode(img, width, height, fname.c_str());
        if(error != 0)
        {
            printf("%u %s file->%s\n",error, lodepng_error_text(error), fname.c_str());
            return kege::image<cg::uchar>();
        }
        
        cg::ubyte* data = new cg::ubyte[img.size()+1];
        memcpy(data, &img[0], img.size()*sizeof(unsigned char));
        data[img.size()] = 0;
        img.clear();
        
        return kege::image<cg::uchar>(4, 32, height, width, gfx::GFX::UNSIGNED_BYTE, data);
    }
    
    kege::image<cg::uchar> open_image_bmp(const ds::string & filename)
    {
        if (filename.empty())
        {
            return kege::image<cg::uchar>();
        }
        kege::bmp::BMP_FILEINFO info;
        cg::ubyte* data = kege::bmp::read(info, filename.c_str());
        if ( data == nullptr )
        {
            printf("[ERROR : open_image_bmp()] file->%s\n", filename.c_str());
            return kege::image<cg::uchar>();
        }
        return kege::image<cg::uchar>(info.bpp/8, info.bpp, info.width, info.height, gfx::GFX::UNSIGNED_BYTE, data);
    }
    
    kege::image<cg::uchar> open_image_jpg(const ds::string & filename)
    {
        return kege::image<cg::uchar>();
    }

    kege::image<cg::uchar> open_image(const ds::string & filename)
    {
        if (filename.empty()) return kege::image<cg::uchar>();
        
        ds::string ext = filename.parse_fext();
        const char* s = ext.c_str();
        
        if (s[0] == '.') s++;
        
        if((s[0]=='t' || s[0]=='T') && (s[1]=='g' || s[1]=='G') && (s[2]=='a' || s[2]=='A'))
        {
            return open_image_tga(kege::VFS::GetInstance().GetFilename(filename));
        }
        else if((s[0]=='p' || s[0]=='P') && (s[1]=='n' || s[1]=='N') && (s[2]=='g' || s[2]=='G'))
        {
            return open_image_png(kege::VFS::GetInstance().GetFilename(filename));
        }
        else if((s[0]=='b' || s[0]=='B') && (s[1]=='m' || s[1]=='M') && (s[2]=='p' || s[2]=='P'))
        {
            return open_image_bmp(kege::VFS::GetInstance().GetFilename(filename));
        }
        return kege::image<cg::uchar>();
    }
    
    
//    bool Image::SaveAsPNG(const ds::string & filename)
//    {
//        std::vector<std::uint8_t> PngBuffer;
//        long size = width * height * 4;
//        PngBuffer.resize(size);
//
//        std::int32_t x,y;
//        if (bpp == 4)
//        {
//            for(std::int32_t I = 0; I < height; ++I)
//            {
//                for(std::int32_t J = 0; J < width; ++J)
//                {
//                    std::size_t OldPos = (height - I - 1) * (width * 4) + 4 * J;
//                    std::size_t NewPos = (width * 4 * I) + 4 * J;
//                    PngBuffer[NewPos + 0] = data[OldPos + 2]; //B is offset 2
//                    PngBuffer[NewPos + 1] = data[OldPos + 1]; //G is offset 1
//                    PngBuffer[NewPos + 2] = data[OldPos + 0]; //R is offset 0
//                    PngBuffer[NewPos + 3] = data[OldPos + 3]; //A is offset 3
//                }
//            }
//        }
//        else
//        {
//            for(y = 0; y < height; y++)
//            {
//                for(x = 0; x < width; x++)
//                {
//                    std::size_t m = (height - y - 1) * (width * 3) + 3 * x;
//                    std::size_t n = (width * 4 * y) + (4 * x);
////                    std::size_t m = (width * 3 * y) + (3 * x);
////                    std::size_t n = (width * 4 * y) + (4 * x);
//
//                    PngBuffer[n + 2] = data[m + 2]; //B is offset 2
//                    PngBuffer[n + 1] = data[m + 1]; //G is offset 1
//                    PngBuffer[n + 0] = data[m + 0]; //R is offset 0
//                    PngBuffer[n + 3] = 255; //A is offset 3
//                }
//            }
//        }
//
//        std::vector<std::uint8_t> ImageBuffer;
//        lodepng::encode(ImageBuffer, PngBuffer, width, height);
//        lodepng::save_file(ImageBuffer, filename.c_str());
//        return true;
//    }
}


