//
//  image.hpp
//  dev0
//
//  Created by Kenneth A Esdaile on 2/15/18.
//  Copyright © 2018 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef image_inl
#define image_inl
namespace kege{
    
    template<typename var> image<var> image<var>::operator *(const image<var>& img)
    {
        const short chans = cg::max(_chan, img.chan);
        const short height = cg::min(_height, img._height);
        const short width = cg::min(_width, img._width);
        const short line = chans * width;
        const double inverse = 0.0039215686; // = (1 / 255)
        const unsigned int size = chans * height * width;
        
        if (size == 0)
        {
            return image<var>();
        }
        
        var * pixels = new var[size];
        short w,h,i,r;
        
        for (h=0; h<height; h++)
        {
            r = h * line;
            for (w=0; w<width; w++)
            {
                i = chans * w + r;
                pixels[i] = (_data[i] * img._data[i]) * inverse;
            }
        }
        return image<var>(chans, height, width, pixels);
    }
    
    template<typename var> image<var> image<var>::operator +(const image<var>& img)
    {
        const short height = cg::min(_height, img._height);
        const short width = cg::min(_width, img._width);
        const short chans = cg::max(_chan, img.chan);
        const long size = chans * height * width;
        
        if (size == 0)
        {
            return image<var>(0, 0, 0, nullptr);
        }
        
        var * pixels = new var[size];
        short line = chans * width;
        short w,h,i,r;
        for (h=0; h<height; h++)
        {
            r = h * line;
            for (w=0; w<width; w++)
            {
                i = chans * w + r;
                pixels[i] = (_data[i] + img._data[i]) * 0.5f;
            }
        }
        return image<var>(chans, height, width, pixels);
    }
    
    template<typename var> image<var> image<var>::operator -(const image<var>& img)
    {
        const short height = cg::min(_height, img._height);
        const short width = cg::min(_width, img._width);
        const short chans = cg::max(_chan, img.chan);
        const long size = chans * height * width;
        
        if (size == 0)
        {
            return image<var>();
        }
        
        var* pixels = new var[size];
        short line = chans * width;
        short w,h,i,r;
        
        for (h=0; h<height; h++)
        {
            r = h * line;
            for (w=0; w<width; w++)
            {
                i = chans * w + r;
                pixels[i] = (_data[i] - img._data[i]);
                if (pixels[i] < 0x0) pixels[i] = 0x0;
            }
        }
        return image<var>(chans, height, width, pixels);
    }
    
    template<typename var> image<var> image<var>::operator /(const image<var>& img)
    {
        const short height = cg::min(_height, img._height);
        const short width = cg::min(_width, img._width);
        const short chans = cg::max(_chan, img.chan);
        const long size = chans * height * width;
        
        if (size == 0)
        {
            return image<var>();
        }
        
        var * pixels = new var[size];
        short line = chans * width;
        short w,h,i,r;
        
        for (h=0; h<height; h++)
        {
            r = h * line;
            for (w=0; w<width; w++)
            {
                i = chans * w + r;
                pixels[i] = _data[i] / cg::max(img._data[i], 1.0);
            }
        }
        return image<var>(chans, height, width, pixels);
    }
    
    template<typename var> void image<var>::operator *=(const image& img)
    {
        const short height = cg::min(_height, img._height);
        const short width = cg::min(_width, img._width);
        const short chans = cg::max(_chan, img.chan);
        const long size = chans * height * width;
        
        long i;
        for (i=0; i<size; i++)
        {
            _data[i] *= img._data[i];
            _data[i] *= sqrt(_data[i]);
        }
    }
    template<typename var> void image<var>::operator /=(const image& img)
    {
        const short height = cg::min(_height, img._height);
        const short width = cg::min(_width, img._width);
        const short chans = cg::max(_chan, img.chan);
        const long size = chans * height * width;
        
        long i;
        for (i=0; i<size; i++)
        {
            _data[i] /= cg::max(1.0, img._data[i]);
        }
    }
    template<typename var> void image<var>::operator +=(const image& img)
    {
        if (img._height != _height ||
            img._width != _width ||
            img._chan != _chan )
        {
            return;
        }
        ;
        const long size = _chan * _height * _width;
        long i;
        for (i=0; i<size; i++)
        {
            _data[i] = (_data[i] + img._data[i]) * 0.5;
        }
    }
    template<typename var> void image<var>::operator -=(const image& img)
    {
        if (img._height != _height ||
            img._width != _width ||
            img._chan != _chan )
        {
            return;
        }
        ;
        const long size = _chan * _height * _width;
        long i;
        for (i=0; i<size; i++)
        {
            _data[i] = cg::max(_data[i] - img._data[i], 0x0);
        }
    }
    template<typename var> void image<var>::operator =(const image& img)
    {
        const long size = img._chan * img._height * img._width;
        if (size == 0)
        {
            return;
        }
        
        var* new_data = new var[size];
        memcpy(new_data, img._data, size*sizeof(var));
        clear();
        
        _height = img._height;
        _width = img._width;
        _chan = img._chan;
        _type = img._type;
        _bpp = img._bpp;
        _data = new_data;
    }
    
    template<typename var> image<var> image<var>::operator *(float value)
    {
        unsigned int line = _chan * _width;
        unsigned int size = _height * line;
        
        if (size == 0)
        {
            return image(0, 0, 0, nullptr);
        }
        
        var* new_pixels = new var[size];
        long i;
        
        for (i=0; i<size; i++)
        {
            new_pixels[i] = _data[i] * value;
        }
        return image(_chan, _bpp, _height, _width, new_pixels);
    }
    
    template<typename var> image<var> image<var>::operator /(float value)
    {
        unsigned int line = _chan * _width;
        unsigned int size = _height * line;
        
        if (size == 0)
        {
            return image(0, 0, 0, nullptr);
        }
        
        var* new_pixels = new var[size];
        long i;
        
        for (i=0; i<size; i++)
        {
            new_pixels[i] = _data[i] / value;
        }
        return image(_chan, _bpp, _height, _width, new_pixels);
    }
    
    template<typename var> image<var> image<var>::operator +(float value)
    {
        unsigned int line = _chan * _width;
        unsigned int size = _height * line;
        
        if (size == 0)
        {
            return image(0, 0, 0, nullptr);
        }
        
        var* new_pixels = new var[size];
        long i;
        
        for (i=0; i<size; i++)
        {
            new_pixels[i] = _data[i] + value;
        }
        return image(_chan, _bpp, _height, _width, new_pixels);
    }
    
    template<typename var> image<var> image<var>::operator -(float value)
    {
        unsigned int line = _chan * _width;
        unsigned int size = _height * line;
        
        if (size == 0)
        {
            return image(0, 0, 0, nullptr);
        }
        
        var* new_data = new var[size];
        long i;
        
        for (i=0; i<size; i++)
        {
            new_data[i] = cg::max(_data[i] - value, 0x0);
        }
        return image(_chan, _bpp, _height, _width, new_data);
    }
    
    template<typename var> inline var const* image<var>::operator()(unsigned short x, unsigned short y)const
    {
        return operator[]( (x * _chan) + (y * _chan * _width) );
    }
    
    template<typename var> inline var const* image<var>::operator[](unsigned int i)const
    {
        return &_data[i];
    }
    
    template<typename var> inline void image<var>::operator()(unsigned short x, unsigned short y, var val)
    {
        operator[]( (x * _chan) + (y * _chan * _width) ) = val;
    }
    
    template<typename var> inline var * image<var>::operator()(unsigned short x, unsigned short y)
    {
        return operator[]( (x * _chan) + (y * _chan * _width) );
    }
    
    template<typename var> inline var * image<var>::operator[](unsigned int i)
    {
        return &_data[i];
    }
    
    template<typename var> inline void image<var>::setdata(var* val)
    {
        _data = val;
    }
    
    template<typename var> inline const void* image<var>::data()const
    {
        return _data;
    }
    template<typename var> inline void* image<var>::data()
    {
        return _data;
    }
    
    template<typename var> inline bool image<var>::empty()const
    {
        return _data == nullptr;
    }
    
    template<typename var> image<var> image<var>::grayscale(double max)const
    {
        long size = _height * _width;
        
        if (size == 0)
        {
            return image();
        }
        
        const double inverse = 1.0 / cg::max(_chan * max, 1.0);
        const short line = _chan * _width;
        short x,y,z, i, row;
        
        var* new_data = new var[size];
        
        for (y=0; y<_height; y++)
        {
            row = y * line;
            for (x=0; x<_width; x++)
            {
                i = x + row;
                for (z=0; z<_chan; z++)
                {
                    new_data[i] += _data[ i+z ];
                }
                new_data[i] *= inverse;
            }
        }
        return image(1, _bpp, _height, _width, new_data);
    }
    
    template<typename var> void image<var>::normalize(double max)
    {
        const double inverse = 1.0 / cg::max(_chan * max, 1.0);
        const short line = _chan * _width;
        short x,y,z, i, row;
        
        for (y=0; y<_height; y++)
        {
            row = y * line;
            for (x=0; x<_width; x++)
            {
                i = x + row;
                for (z=0; z<_chan; z++)
                {
                    _data[i] = _data[i] * inverse;
                }
            }
        }
    }
    
    template<typename var> void image<var>::clear()
    {
        if (_data != nullptr)
        {
            delete [] _data;
            _data = nullptr;
        }
        _height = 0;
        _width = 0;
        _chan = 0;
        _bpp = 0;
    }
    
    template<typename var>
    image<var>::image(char chan, char bpp, short height, short width, short typ, var* data)
    :   kege::abstr_image(chan, bpp, height, width, typ)
    ,   _data(data)
    {
    }
    
    template<typename var> image<var>::image(const ds::string & filename)
    :   kege::abstr_image(3, 24, 0, 0, core::UNSIGNED_BYTE)
    ,   _data(nullptr)
    {
    }
    
    template<typename var> image<var>::~ image()
    {
        clear();
    }
    
    template<typename var> image<var>::image()
    :   kege::abstr_image(3, 24, 0, 0, core::UNSIGNED_BYTE)
    ,   _data(nullptr)
    {
    }
}
#endif /* image_hpp */
