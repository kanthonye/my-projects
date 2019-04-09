//
//  main.cpp
//  Diamond-Sqaure-Algorithm
//
//  Created by Kenneth A Esdaile on 10/28/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#include <time.h>
#include <vector>
#include <iostream>


class DSA
{
private:
    
    bool write_image(int w, int h, short bpp, const unsigned char* imgdata, const char* filename);
    bool write_dsa(int w, int h, const unsigned char* data, const char* filename);
    
public:
    
    void save_tga(const char* filename);
    void save(const char* filename);
    
    static int   randi(const int from, const int to);
    static float randf(const float from, const float to);
    static float clamp(float val, float min, float max);
    
    // whitenoise variant functions is use to produce white-noise texture
    static float whitenoise(float scale, float intensity);
    
    // cloudiness variant functions is use to produce cloud like texture
    static float cloudiness(float scale, float intensity);
    
    // whitenoise variant functions is use to produce white-noise texture
    static float cloudiness2(float scale, float intensity);
    
    // roughness variant functions is use to produce rock like texture
    static float roughness(float scale, float intensity);
    
public:
    
    void set(int x, int y, float value);
    void set(int i, float value);
    int comp_index(int x, int y);
    
    float getDiamondAvg(int x, int y, int offset);
    float getSquareAvg(int cx, int cy, int offset);
    void do_diamond_step(int x, int y, int offset, float variant);
    void do_square_step(int tl_x, int tl_y, int offset, float variant);
    
    void run_algorithm(float (*variant_function)(float, float), float intensity, int seed);
    
    DSA(int length, float a0, float a1, float a2, float a3);
    DSA(int length, int seed);
    
private:
    
    std::vector<float> data;
    int length;
    int size;
    int a[4];
};




bool DSA::write_image(int w, int h, short bpp, const unsigned char* imgdata, const char* filename)
{
    FILE *file = nullptr;
    if ((file = fopen(filename,"w")) == NULL)
    {
        fprintf(stderr,"Failed to open outputfile\n");
        return false;
    }
    unsigned int i,byte;
    
    char  idlength = 0;
    char  colourmaptype = 0;
    char  datatypecode = 2;
    short int colourmaporigin = 0;
    short int colourmaplength = 0;
    char  colourmapdepth = 0;
    short int x_origin = 0;
    short int y_origin = 0;
    short width = w;
    short height = h;
    char  bitsperpixel = bpp;
    char  imagedescriptor = 0;
    short channels = bpp / 8;
    
    putc(idlength, file);
    putc(colourmaptype, file);
    putc(datatypecode, file);
    fwrite(&colourmaporigin,2,1,file);
    fwrite(&colourmaplength,2,1,file);
    putc(colourmapdepth, file);
    fwrite(&x_origin,2,1,file);
    fwrite(&y_origin,2,1,file);
    fwrite(&width,2,1,file);
    fwrite(&height,2,1,file);
    putc(bitsperpixel,file);
    putc(imagedescriptor, file);
    
    unsigned int imgsize = width * height * channels;
    /* Allocate space for the image */
    unsigned char* data = new unsigned char[imgsize];
    memcpy(data, imgdata, imgsize);
    
    if (channels == 3)
    {
        /* make rgb to bgr */
        for (i=0; i<imgsize; i+=channels)
        {
            byte = data[ i ];
            data[ i ] = data[i+2];
            data[i+2] = byte;
        }
    }
    fwrite(data, 1, imgsize*channels, file);
    delete [] data;
    data = nullptr;
    fclose(file);
    return true;
}


bool DSA::write_dsa(int w, int h, const unsigned char* data, const char* filename)
{
    FILE *file = nullptr;
    if ((file = fopen(filename,"w")) == NULL)
    {
        fprintf(stderr,"Failed to open outputfile\n");
        return false;
    }
    
    fwrite("dsa", sizeof(char), 3, file);
    fwrite(&w,2,1,file);
    fwrite(&h,2,1,file);
    putc(0, file);
    
    fwrite(data, sizeof(char), w*h, file);
    fclose(file);
    return true;
}

void DSA::save_tga(const char* filename)
{
    unsigned char* img = new unsigned char[length*length*3];
    if (img != nullptr)
    {
        int n;
        for (int i=0; i<data.size(); i++)
        {
            n = i*3;
            img[ n ] = data[i] * 255;
            img[n+1] = data[i] * 255;
            img[n+2] = data[i] * 255;
        }
        write_image(length, length, 24, img, filename);
        delete [] img;
        img = nullptr;
    }
}

void DSA::save(const char* filename)
{
    unsigned char* img = new unsigned char[length*length];
    if (img != nullptr)
    {
        for (int i=0; i<data.size(); i++) img[i] = data[i] * 255;
        write_dsa(length, length, img, filename);
        delete [] img;
        img = nullptr;
    }
}

int DSA::randi(const int from, const int to)
{
    return from + (rand() % (to-from+1)); // range from (from) to (to)
}

float DSA::clamp(float val, float min, float max)
{
    return (val < min) ? min : (val > max) ? max : val;
}

float DSA::randf(const float from, const float to)
{
    if (from==0 && to==0) return 0;
    double num = (double) rand() / RAND_MAX;
    return from + ((to - from) * num);
}

// whitenoise variant functions is use to produce white-noise texture
float DSA::whitenoise(float scale, float intensity)
{
    return DSA::randf(-1.0, 1.0);
}

// cloudiness variant functions is use to produce cloud like texture
float DSA::cloudiness(float scale, float intensity)
{
    return DSA::randf(-1.0, 1.0) * scale * intensity;
}

// whitenoise variant functions is use to produce white-noise texture
float DSA::cloudiness2(float scale, float intensity)
{
    return DSA::randf(-scale, scale) * intensity;
}

// roughness variant functions is use to produce rock like texture
float DSA::roughness(float scale, float intensity)
{
    return DSA::randf(-1.0, 1.0) * DSA::randf(0.0, intensity);
}



void DSA::set(int x, int y, float value)
{
    set(length * y + x, value);
}

void DSA::set(int i, float value)
{
    if (i >= size) return;
    data[i] = clamp(value, 0.0f, 1.0f);
}

int DSA::comp_index(int x, int y)
{
    //printf("%i %i\n",x,y);
    return length * y + x;
}

float DSA::getDiamondAvg(int x, int y, int offset)
{
    //  [2]---------[4]
    //   |     |     |
    //   |---(x,y)---| (x,y) <-- avg = (2+4+5+6) / 4
    //   |     |     |
    //  [6]---------[5]
    float avg = 0, count = 0;
    int mx = x - offset;
    int my = y - offset;
    int nx = x + offset;
    int ny = y + offset;
    
    if (mx >= 0 && mx >= 0)
    {
        a[0] = comp_index(mx, my);
        avg += data[a[0]];
        count++;
    }
    if (nx <= length-1 && my >= 0)
    {
        a[0] = comp_index(nx, my);
        avg += data[a[0]];
        count++;
    }
    if (ny <= length-1 && mx >= 0)
    {
        a[0] = comp_index(mx, ny);
        avg += data[a[0]];
        count++;
    }
    if (nx <= length-1 && ny <= length-1)
    {
        a[0] = comp_index(nx, ny);
        avg += data[a[0]];
        count++;
    }
    
    return avg / count;
}

float DSA::getSquareAvg(int cx, int cy, int offset)
{
    //   o-----[2]-----o
    //   |      |      |
    //  [5]---(x,y)---[3] (x,y) <-- [avg = (2+3+4+5) / 4]
    //   |      |      |
    //   o-----[4]-----o
    float avg = 0, count = 0;
    int w  = offset * 0.5;
    int mx = cx - w;
    int my = cy - w;
    int nx = cx + w;
    int ny = cy + w;
    if (mx >= 0)
    {
        a[0] = comp_index(mx,cy);
        avg += data[a[0]];
        count++;
    }
    if (nx < length)
    {
        a[0] = comp_index(nx,cy);
        avg += data[a[0]];
        count++;
    }
    if (my >= 0)
    {
        a[0] = comp_index(cx,my);
        avg += data[a[0]];
        count++;
    }
    if (ny < length)
    {
        a[0] = comp_index(cx,ny);
        avg += data[a[0]];
        count++;
    }
    return avg / count;
}

void DSA::do_diamond_step(int x, int y, int offset, float variant)
{
    int w  = (offset * 0.5);
    int cx = x + w;
    int cy = y + w;
    int ii = comp_index(cx, cy);
    set(ii, (variant+getDiamondAvg(cx, cy, w)));
}

void DSA::do_square_step(int tl_x, int tl_y, int offset, float variant)
{
    int sx, sy, i, w = (offset * 0.5);
    // (xy)---(top)----o
    //   |      |      |
    // (left)---o---(right)
    //   |      |      |
    //   o----below----o
    
    // (top)
    sx = tl_x + w;
    if (sx <= length-1)
    {
        i  = comp_index(sx, tl_y);
        set(i, (variant+getSquareAvg(sx, tl_y, offset)));
        //printf("\n");
    }
    
    // (right)
    sx = tl_x + offset;
    sy = tl_y + w;
    if (sx < length && sy < length)
    {
        i  = comp_index(sx, sy);
        set(i, (variant+getSquareAvg(sx, sy, offset)));
        //printf("\n");
    }
    
    // (below)
    sx = tl_x + w;
    sy = tl_y + offset;
    if (sx < length && sy < length)
    {
        i  = comp_index(sx, sy);
        set(i, (variant+getSquareAvg(sx, sy, offset)));
        //printf("\n");
    }
    
    // (left)
    sy = tl_y + w;
    if (sx < length && sy < length)
    {
        i  = comp_index(tl_x, sy);
        set(i, (variant+getSquareAvg(tl_x, sy, offset)));
        //printf("\n");
    }
}

void DSA::run_algorithm(float (*variant_function)(float, float), float intensity, int seed)
{
    int x,y,offset=length-1;
    const int SIZE = length-1;
    float variant,scale = 1.0;
    
    srand(seed);
    
    while (offset > 1)
    {
        scale = offset / (float)length;
        for (y=0; y<SIZE; y+=offset)
        {
            for (x=0; x<SIZE; x+=offset)
            {
                variant = variant_function(scale, intensity);
                do_diamond_step(x,y, offset, variant);
                
                variant = variant_function(scale, intensity);
                do_square_step(x,y, offset, variant);
            }
        }
        offset = offset * 0.5;
    }
}

DSA::DSA(int length, float a0, float a1, float a2, float a3)
:   length(length+1)
{
    size = this->length * this->length;
    data.resize(size);
    
    a[0] = 0;
    a[1] = (this->length - 1) + a[0];
    a[2] =  this->length * (this->length - 1);
    a[3] = (this->length - 1) + a[2];
    
    data[a[0]] = a2;
    data[a[1]] = a3;
    data[a[2]] = a0;
    data[a[3]] = a1;
}

DSA::DSA(int length, int seed)
:   length(length+1)
{
    size = this->length * this->length;
    data.resize(size);
    
    a[0] = 0;
    a[1] = (this->length - 1) + a[0];
    a[2] =  this->length * (this->length - 1);
    a[3] = (this->length - 1) + a[2];
    
    srand(seed);
    
    data[a[0]] = randf(0.0, 1.0);
    data[a[1]] = randf(0.0, 1.0);
    data[a[2]] = randf(0.0, 1.0);
    data[a[3]] = randf(0.0, 1.0);
    
    printf("%f\n",data[a[0]]);
    printf("%f\n",data[a[1]]);
    printf("%f\n",data[a[2]]);
    printf("%f\n",data[a[3]]);
}

int main(int argc, const char * argv[])
{
    DSA dsa(1024, 0);
    dsa.run_algorithm(DSA::cloudiness2, 1.0, (int)time(0));
    dsa.save_tga("/Users/kanthonye/Projects/Diamond-Sqaure-Algorithm/DSA/dsa.tga");
    return 0;
}
