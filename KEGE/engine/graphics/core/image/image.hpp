//
//  image.hpp
//  Node Base Renderer
//
//  Created by Kenneth Esdaile on 11/21/15.
//  Copyright © 2015 kanthonye. All rights reserved.
//

#ifndef KEGE_IMAGE_HPP
#define KEGE_IMAGE_HPP
#include "cgm.hpp"
#include "string.hpp"
#include "VFS.hpp"
#include "GFXEnum.hpp"
namespace kege{
    
    class abstr_image;
    
    class abstr_image
    {
    public:
        
        virtual const void* data()const = 0;
        virtual void* data() = 0;
        
        virtual bool empty()const = 0;
        virtual void clear() = 0;
        
        inline short height() const {return _height;}
        inline short width() const {return _width;}
        inline short chan() const {return _chan;}
        inline short type() const {return _type;}
        inline short bpp() const {return _bpp;}
        
        abstr_image(char chan, char bpp, short height, short width, short typ)
        :   _height(height)
        ,   _width(width)
        ,   _type(typ)
        ,   _chan(chan)
        ,   _bpp(bpp)
        {}
        
        virtual ~ abstr_image(){}
        
    protected:
        
        short _height; // image height
        short _width;  // image width
        short _type;   // data type
        char  _chan;   // channels
        char  _bpp;    // bits per pixel
    };
}

namespace kege{ namespace shared{
    
    typedef mem::shared< abstr_image > image;
}}

namespace kege{
    
    template<typename var> class image : public abstr_image
    {
    public:
        
        void operator *=(const image& img);
        void operator /=(const image& img);
        void operator +=(const image& img);
        void operator -=(const image& img);
        
        void operator  =(const image& img);
        
        image operator *(const image& img);
        image operator /(const image& img);
        image operator -(const image& img);
        image operator +(const image& img);
        
        image operator *(float value);
        image operator /(float value);
        image operator +(float value);
        image operator -(float value);
        
        image grayscale(double max)const;
        void  normalize(double max);
        
        const void* data()const;
        void* data();
        
        bool empty()const;
        void clear();
        
        const var* operator()(unsigned short x, unsigned short y)const;
        const var* operator[](unsigned int i)const;
        
        void operator()(unsigned short x, unsigned short y, var val);
        var* operator()(unsigned short x, unsigned short y);
        var* operator[](unsigned int i);
        
        void setdata(var* val);
        
        image(char chan, char bpp, short height, short width, short typ, var * pixels);
        image(const ds::string & filename);
        virtual ~ image();
        image();
        
    protected:
        
        var* _data; // image data
    };
    
    typedef kege::image<cg::ubyte> image8i;
    typedef kege::image< float > image16f;
    
    typedef mem::shared< image16f > shared_image16f;
    typedef mem::shared< image8i > shared_image8i;
    
    kege::image<cg::uchar> open_image_tga(const ds::string & filename);
    kege::image<cg::uchar> open_image_png(const ds::string & filename);
    kege::image<cg::uchar> open_image_bmp(const ds::string & filename);
    kege::image<cg::uchar> open_image_jpg(const ds::string & filename);
    kege::image<cg::uchar> open_image(const ds::string & filename);
}
#include "image.inl"
#endif /* image_hpp */
