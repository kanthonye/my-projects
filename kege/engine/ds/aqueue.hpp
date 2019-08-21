//
//  aqueue.h
//  Node Base Renderer
//
//  Created by Kenneth Esdaile on 11/26/15.
//  Copyright © 2015 kanthonye. All rights reserved.
//
#ifndef aqueue_h
#define aqueue_h
namespace kege {namespace ds{

    template <class Element>  class aqueue
    {
        Element * elements;
        int head;
        int tail;
        int count;
        int asize;
    public:
        aqueue():elements(nullptr), head(0),tail(0),count(0),asize(0) {}
        virtual ~ aqueue(){ destory(); }
        
        void destory()
        {
            if (elements != nullptr)
            {
                delete [] elements;
                elements = nullptr;
                head = 0;
                tail = 0;
                asize = 0;
            }
        }
        
        void clear()
        {
            count = 0;
            head = 0;
            tail = 0;
        }
        
        void resize(int newsize)
        {
            Element * tmp = new Element[newsize];
            if (elements == nullptr)
            {
                elements = tmp;
                asize = newsize;
                return;
            }
            
            else if (head > 0)
            {
                int i = head;
                while (i < tail)
                {
                    elements[i-head] = elements[i];
                    i++;
                }
                head = 0;
                tail = count;
                return;
            }
            
            int i = 0;
            while (i<asize)
            {
                tmp[i] = elements[i];
                i++;
            }
            delete [] elements;
            elements = tmp;
            asize = newsize;
        }
        
        bool pop ()
        {
            if ( empty() )
                return false;
            head++;
            count--;
            if (count == 0)
            {
                tail = 0;
                head = 0;
            }
            return true;
        }
        
        bool empty ()
        {
            return ( elements == nullptr || count == 0 );
        }
        
        Element top ()
        {
            if (empty())
            {
                destory();
                throw 0;
            }
            return elements[head];
        }
        
        int size ()
        {
            return count;
        }
        
        int arrysize ()
        {
            return asize;
        }
        
        void push (Element elem)
        {
            if ( elements == nullptr || tail >= asize) resize(asize * 2 + 1);
            elements[tail++] = elem;
            count++;
        }
    };
}}
#endif /* aqueue_h */
