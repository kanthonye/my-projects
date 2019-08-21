//       ___           ___           ___
//      /__/|         /  /\         /  /\
//     |  |:|        /  /::\       /  /:/_
//     |  |:|       /  /:/\:\     /  /:/ /\
//   __|  |:|      /  /:/~/::\   /  /:/ /:/_
//  /__/\_|:|____ /__/:/ /:/\:\ /__/:/ /:/ /\
//  \  \:\/:::::/ \  \:\/:/__\/ \  \:\/:/ /:/
//   \  \::/~~~~   \  \::/       \  \::/ /:/
//    \  \:\        \  \:\        \  \:\/:/
//     \  \:\        \  \:\        \  \::/
//      \__\/         \__\/         \__\/
/*! @author     Kenneth Anthony Esdaile
 *  @date       created on 6/18/14
 *  @copyright  Copyright (c) 2014 kae. All rights reserved.
 *  @file       dlist.hpp
 *  @project    data structure containers.
 */
#ifndef __DS__LINKED__LIST__
#define __DS__LINKED__LIST__
namespace kege{namespace ds{
    
    template<class var>  struct node2
    {
        ds::node2<var> * getprev() {return prev;}
        ds::node2<var> * getnext() {return next;}
        virtual var &getdata() = 0;
        
        node2() : next(nullptr), prev(nullptr) {}
        virtual ~ node2() {}
        node2<var> * next;
        node2<var> * prev;
    };
    
    
    template< class var >  struct dnode : public node2<var>
    {
        var &getdata() override {return data;}
        dnode(var v) : data(v) {}
        dnode(){}
        
        var data;
    };
    
    
    template <class var>  class dlist
    {
    public:
        
        class iterator
        {
        public:
            
            bool operator == (iterator const &a);
            bool operator != (iterator const &a);
            bool operator == (node2<var> * node);
            bool operator != (node2<var> * node);
            
            iterator getnext(void);
            iterator getprev(void);
            
            void operator ++ (int);
            void operator ++ ();
            void operator -- (int);
            void operator -- ();
            var& operator ->(void);
            var& operator * (void);
            var& element(void);
            bool valid ();
            
            node2<var> * node(void);
            
            iterator(node2<var> * node);
            iterator(void);
            
        private:
            
            node2<var> * prev;
            node2<var> * next;
            node2<var> * curr;
            friend dlist;
        };
        
    public:
        
        /* copy list */
        void operator =(const dlist& list);
        
        /* insert a list node before iterator position */
        bool insert_before(iterator & i, node2<var> * node);
        
        /* insert a list node after iterator position */
        bool insert_after(iterator & i, node2<var> * node);
        
        /* insert a list element before iterator position */
        bool insert_before(iterator & i, var elem);
        
        /* insert a list element after iterator position */
        bool insert_after(iterator & i, var elem);
        
        /* swap two list element */
        bool swap(iterator & i, iterator & j);
        
        /* erase list element */
        bool erase(iterator & i);
        
        /* erase list element */
        bool remove(var elem);
        
        /* detact a list from this list and return its node */
        node2<var> * remove(iterator & position);
        
        /* search for a list element */
        template <class varB> iterator find(varB* elem)const;
        
        /* return the iterator of first list element */
        iterator begin(void)const;
        
        /* return the iterator of last list element */
        iterator end(void)const;
        
        
        /* add new node to the front of list */
        node2<var> * push_frontn(node2<var> * node);
        
        /* add new node to the back of list */
        node2<var> * push_backn(node2<var> * node);
        
        /* add new element to the front of list */
        node2<var> * push_front(var elem);
        
        /* add new element to the back of list */
        node2<var> * push_back(var elem);
        
        /* add new node to the back of list and return ref to its element */
        var & push_front();
        
        /* add new node to the back of list and return ref to its element */
        var & push_back();
        
        /* return the front nodet */
        node2<var> * frontnode();
        
        /* return the back node */
        node2<var> * backnode();
        
        /* return the end of list */
        node2<var> * eol(void)const;
        
        /* return the list front element */
        var& front(void)const;
        
        /* return the list last element */
        var& back(void)const;
        
        void remove(node2<var> * node);
        
        /* remove the first node */
        bool pop_front(void);
        
        /* remove the last node */
        bool pop_back(void);
        
        /* return true if list is empty */
        bool empty(void)const;
        
        /* return total elements in list */
        long count(void)const;
        
        /* delete every list element */
        void clear(void);
        
        /* copy constructor */
        dlist(const dlist& list);
        
        /* destructor */
        virtual ~ dlist(void);
        
        /* constructor */
        dlist(void);
        
        
    protected:
        
        void swap_head(node2<var> * a);
        void swap_head2(node2<var> * a);
        void swap_tail(node2<var> * a);
        void swap_tail2(node2<var> * a);
        
        
    protected:
        
        friend ds::node2<var>;
        node2<var> * head;
        node2<var> * tail;
        unsigned int items;
    };
    
}}
#include "dlist.inl"
#endif

