/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/30/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       array2.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef array2_hpp
#define array2_hpp
#include <stdio.h>
#include <cstring>
namespace kege {namespace ds{
    
    template <class data>  class array2
    {
        typedef const unsigned int cuint;
        typedef unsigned int uint;
        
        struct sarry
        {
            data * arry;
            long   size;
            uint    row;
            uint    col;
        };
        
        sarry * arry;
        long    elems;
        
    private:
        
        sarry * newarray(cuint row, cuint col);
        void validate(int x, int y)const;
        void delarray(sarry *& a);
        
    public:
        
        array2(void);
        array2(int row, int col);
        
        void resize(int row, int col);
        
        void swapelems(int x0, int y0, int x1, int y1);
        void swaprows(int a, int b);
        void swapcols(int a, int b);
        
        long count(void)const;
        bool empty(void)const;
        int  row(void)const;
        int  col(void)const;
        
        void clear(void);
        
        void set(int col,int row, data d);
        data & at(int col,int row) const;
        
        void operator =(array2< data > const& other);
        void operator()(int x, int y, data * d);
        data const& operator()(int x, int y)const;
        data & operator()(int x, int y);
        data const& operator[](int i)const;
        data& operator[](int i);
        
        virtual ~array2 (void);
        
        // these function need more testing
        void shift_upper_left();
        void shift_upper_right();
        void shift_lower_left();
        void shift_lower_right();
        void shift_left(int a);
        void shift_right(int a);
        void shift_up(int a);
        void shift_down(int a);
    };
    
    template<class data>  typename array2< data >::sarry * array2< data >::newarray(cuint row, cuint col)
    {
        sarry * a = new sarry;
        a->arry = new data[row*col];
        a->size = row*col;
        a->row = row;
        a->col = col;
        return a;
    }
    
    template<class data>  void array2< data >::delarray(sarry *& a)
    {
        if (a)
        {
            delete [] a->arry;
            a->arry = nullptr;
            a->col = 0;
            a->row = 0;
            delete a;
            a = nullptr;
        }
    }
    
    template<class data>  void array2< data >::validate(int x, int y)const
    {
        if (!arry) throw nullptr;
        if (x >= arry->col || arry->row <= y) throw "outbound";
    }
    
    template<class data>  array2< data >::array2(void)
    :   arry(nullptr)
    ,   elems(0)
    {
    }
    
    template<class data>  array2< data >::array2(int row, int col)
    :   arry(nullptr)
    ,   elems(0)
    {
        resize(row, col);
    }
    
    template<class tvar>  void array2<tvar>::resize(int row, int col)
    {
        if (arry)
        {
            sarry * newarry = newarray(row, col);
            
            uint rw = (arry->row <= row)? arry->row: row;
            uint cl = (arry->col <= col)? arry->col: col;
            uint i  = 0;
            
            for (uint r=0; r<rw; r++)
            {
                for (uint c=0; c<cl; c++)
                {
                    i = cl * r + c;
                    newarry->arry[i] = arry->arry[i];
                }
            }
            
            delarray(arry);
            arry = newarry;
        }
        else
        {
            arry = newarray(row, col);
        }
    }
    
    template<class data>  void array2< data >::swapelems(int x0, int y0, int x1, int y1)
    {
        uint m = arry->col * y0 + x0;
        uint n = arry->col * y1 + x1;
        
        if (m >= arry->size || arry->size <= n)
            return;
        
        data tmp = arry->arry[m];
        arry->arry[m] = arry->arry[n];
        arry->arry[n] = tmp;
    }
    
    template<class data>  void array2< data >::swaprows(int a, int b)
    {
        if (arry)
        {
            uint m,n;
            data tmp;
            for (uint c=0; c<arry->col; c++)
            {
                m = arry->col * a + c;
                n = arry->col * b + c;
                tmp = arry->arry[m];
                arry->arry[m] = arry->arry[n];
                arry->arry[n] = tmp;
            }
        }
    }
    
    template<class data>  void array2< data >::swapcols(int a, int b)
    {
        if (arry)
        {
            uint m,n;
            data tmp;
            for (uint r=0; r<arry->row; r++)
            {
                m = arry->col * r + a;
                n = arry->col * r + b;
                tmp = arry->arry[m];
                arry->arry[m] = arry->arry[n];
                arry->arry[n] = tmp;
            }
        }
    }
    
    template<class data>  void array2< data >::shift_left(int a)
    {
        int m,n;
        for (n=arry->col-1; n>=0; n-=a)
        {
            for (m=0; m<a; m++)
            {
                swapcols(m, n+m);
            }
        }
    }
    template<class data>  void array2< data >::shift_right(int a)
    {
        uint m,n;
        for (n=a; n<arry->col; n+=a)
        {
            for (m=0; m<a; m++)
            {
                swapcols(m, n+m);
            }
        }
    }
    template<class data>  void array2< data >::shift_up(int a)
    {
        int m,n;
        for (n=arry->row-a; n>=a; n-=a)
        {
            for (m=0; m<a; m++)
            {
                swaprows(m, n+m);
            }
        }
    }
    template<class data>  void array2< data >::shift_down(int a)
    {
        uint m,n;
        for (n=a; n<arry->row; n+=a)
        {
            for (m=0; m<a; m++)
            {
                swaprows(m, n+m);
            }
        }
    }
    
    template<class data>  void array2< data >::shift_upper_left()
    {
        uint x,y,m,n;
        for (y=0; y<arry->row-1; y++)
        {
            for (x=0; x<arry->col-1; x++)
            {
                m = arry->col * y + x;
                n = arry->col * (y+1) + (x+1);
                
                data tmp = arry->arry[m];
                arry->arry[m] = arry->arry[n];
                arry->arry[n] = tmp;
            }
        }
    }
    template<class data>  void array2< data >::shift_upper_right()
    {
        uint x,y,m,n;
        for (y=0; y<arry->row-1; y++)
        {
            for (x=arry->col-1; x>=1; x--)
            {
                m = arry->col * (y+1) + (x-1);
                n = arry->col * y + x;
                
                data tmp = arry->arry[m];
                arry->arry[m] = arry->arry[n];
                arry->arry[n] = tmp;
            }
        }
    }
    template<class data>  void array2< data >::shift_lower_left()
    {
        uint x,y,m,n;
        for (y=arry->row-1; y>0; y--)
        {
            for (x=0; x<arry->col-1; x++)
            {
                m = arry->col * (y-1) + (x+1);
                n = arry->col * y + x;
                
                data tmp = arry->arry[m];
                arry->arry[m] = arry->arry[n];
                arry->arry[n] = tmp;
            }
        }
    }
    template<class data>  void array2< data >::shift_lower_right()
    {
        uint x,y,m,n;
        for (y=arry->row-1; y>0; y--)
        {
            for (x=arry->col-1; x>=1; x--)
            {
                m = arry->col * (y-1) + (x-1);
                n = arry->col * y + x;
                
                data tmp = arry->arry[m];
                arry->arry[m] = arry->arry[n];
                arry->arry[n] = tmp;
            }
        }
    }
    template<class data>  long array2< data >::count(void)const
    {
        return elems;
    }
    
    template<class data>  bool array2< data >::empty(void)const
    {
        return (!arry || !elems);
    }
    
    template<class data>  int array2< data >::row(void)const
    {
        if(arry) return arry->row;
        return 0;
    }
    
    template<class data>  int array2< data >::col(void)const
    {
        if(arry) return arry->col;
        return 0;
    }
    
    template<class tvar>  void array2<tvar>::clear(void)
    {
        if (arry)
        {
            delarray(arry);
            elems = 0;
        }
    }
    
    template<class data>  void array2< data >::set(int x, int y, data d)
    {
        validate(x,y);
        arry->arry[ (arry->col * y + x) ] = d;
    }
    
    template<class data>  data & array2< data >::at(int x, int y) const
    {
        validate(x,y);
        return arry->arry[ (arry->col * y + x) ];
    }
    
    template<class data>  void array2< data >::operator =(array2< data > const& other)
    {
        clear();
        elems = other.elems;
        arry = newarray(other.arry.row, other.arry.col);
        memcpy(arry, other.arry.arry, other.arry.size * sizeof(data));
    }
    
    template<class data>  void array2< data >::operator()(int x, int y, data * d)
    {
        validate(x,y);
        arry->arry[ (arry->col * y + x) ] = d;
    }
    
    template<class data>  data const& array2< data >::operator[](int i)const
    {
        if (!arry) throw nullptr;
        if (i >= arry->size) throw "out-of-bound";
        return arry->arry[i];
    }
    
    template<class data>  data& array2< data >::operator[](int i)
    {
        return arry->arry[i];
    }
    
    template<class data>  data const& array2< data >::operator()(int x, int y)const
    {
        validate(x,y);
        return arry->arry[ (arry->col * y + x) ];
    }
    
    template<class data>  data & array2< data >::operator()(int x, int y)
    {
        validate(x,y);
        return arry->arry[ (arry->col * y + x) ];
    }
    
    template<class tvar>  array2<tvar>::~array2()
    {
        delarray(arry);
    }
}}
#endif /* array2_hpp */
