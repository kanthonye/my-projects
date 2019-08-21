//
//  print.cpp
//  column-major
//
//  Created by Kenneth A Esdaile on 7/12/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//
#include "../../../graphics/core/cgmath/print.hpp"
#include <stdio.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <stdlib.h>
#include "string.hpp"


namespace kege{namespace cg{
    void print(char const* format, ...)
    {
        unsigned count=0;
        char b [64];
        kege::ds::string str;
        str.setsize(64);
        str.setlength(0);
        const char *p = format;
        
        va_list list;
        va_start(list, format);
        while(*p!='\0')
        {
            switch(*p)
            {
                case '%':{
                    count++;
                    switch(*++p)
                    {
                        case 'c':{
                            printf("%c", va_arg(list, int));
                        }break;
                            
                        case 'i':{
                            printf("%i", va_arg(list, int));
                        }break;
                            
                        case 'l':{
                            printf("%li", va_arg(list, long));
                        }break;
                            
                        case 's':{
                            printf("%s", va_arg(list, char*));
                        }break;
                            
                        case 'f':{
                            printf("%f", va_arg(list, double));
                        }break;
                            
                        case 'v':
                        case 'p':{
                            if (p[1] == '2')
                            {
                                kege::cg::vec2 *v = (kege::cg::vec2*) va_arg(list, float*);
                                printf("( %6.3f, %6.3f )", v->x, v->y);
                            }
                            else if (p[1] == '3')
                            {
                                kege::cg::vec3 *v = (kege::cg::vec3*) va_arg(list, void*);
                                printf("( %6.3f, %6.3f, %6.3f )", v->x, v->y, v->z);
                            }
                            else if (p[1] == '4')
                            {
                                kege::cg::vec4 *v = (kege::cg::vec4*) va_arg(list, float*);
                                printf("( %6.3f, %6.3f, %6.3f, %6.3f )", v->x, v->y, v->z, v->w);
                            }
                            str += b;
                            p++;
                        }break;
                            
                        default: str += *p; break;
                    }break;
                }break;
                    
                default: str += *p; break;
            }
            count++;
            p++;
        }
        va_end(list);
    }
}}


void print(const kege::cg::mat44& m)
{
    printf("{( %6.3f, %6.3f , %6.3f , %6.3f ) \n", m.m00, m.m10, m.m20, m.m30);
    printf(" ( %6.3f, %6.3f , %6.3f , %6.3f ) \n", m.m01, m.m11, m.m21, m.m31);
    printf(" ( %6.3f, %6.3f , %6.3f , %6.3f )}\n", m.m02, m.m12, m.m22, m.m32);
    printf(" ( %6.3f, %6.3f , %6.3f , %6.3f )}\n", m.m03, m.m13, m.m23, m.m33);
}
void print(const kege::cg::mat33& m)
{
    printf("{( %6.3f, %6.3f , %6.3f ) \n", m.m00, m.m10, m.m20);
    printf(" ( %6.3f, %6.3f , %6.3f ) \n", m.m01, m.m11, m.m21);
    printf(" ( %6.3f, %6.3f , %6.3f )}\n", m.m02, m.m12, m.m22);
}
void print(const kege::cg::vec4& m)
{
    printf("< %6.3f, %6.3f, %6.3f, %6.3f >", m.x, m.y, m.z, m.w);
}
void print(const kege::cg::vec3& m)
{
    printf("< %6.3f, %6.3f, %6.3f >", m.x, m.y, m.z);
}
void print(const kege::cg::vec2& m)
{
    printf("( %6.3f, %6.3f )\n", m.x, m.y);
}
void print(const kege::cg::mat22& m)
{
    printf("{ ( %6.3f, %6.3f )  \n", m.m00, m.m10);
    printf("  ( %6.3f, %6.3f ) }\n", m.m01, m.m11);
}
