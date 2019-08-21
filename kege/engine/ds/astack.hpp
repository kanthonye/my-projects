/*! @author     Kenneth Anthony Esdaile
 *  @date       created on 12/12/15
 *  @copyright  Copyright (c) 2014 kae. All rights reserved.
 *  @file       astack.h
 *  @project    data structure containers. */
#ifndef astack_h
#define astack_h

#ifndef kae_ds
#   define kae_ds ds
#endif

#ifndef nullptr
#   define nullptr nullptr
#endif

namespace kege {namespace kae_ds{
    
    template <class Element>  class astack
    {
        Element * elements;
        int count;
        int asize;
        
    public:
        
        astack():elements(nullptr), count(0), asize(0) {}
        virtual ~ astack(){ destory(); }
        
        void destory()
        {
            if (elements != nullptr)
            {
                delete [] elements;
                elements = nullptr;
                count = 0;
                asize = 0;
            }
        }
        
        void clear() {
            count = 0;
        }
        
        void setsize(int newsize)
        {
            Element * tmp = new Element[newsize];
            if (elements != nullptr)
            {
                for (int i=0; i<count; i++)
                    tmp[i] = elements[i];
                delete [] elements;
                elements = tmp;
                asize = newsize;
            } else {
                elements = tmp;
                asize = newsize;
            }
        }
        
        bool pop () {
            if ( empty() )
                return false;
            count--;
            return true;
        }
        
        bool empty ()
        {
            return ( elements == nullptr || count <= 0 );
        }
        
        Element & top ()
        {
            return elements[count-1];
        }
        
        int size ()
        {
            return count;
        }
        
        int arrysize () {
            return asize;
        }
        
        int push (Element &elem)
        {
            if ( elements == nullptr || count >= asize ) setsize(asize * 2 + 1);
            elements[count++] = elem;
            return count-1;
        }
    };
} }
#endif /* astack_h */
