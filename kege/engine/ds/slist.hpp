/*! @author     Kenneth Anthony Esdaile
 *  @date       created on 10/7/14
 *  @copyright  Copyright (c) 2014 kae. All rights reserved.
 *  @file       slist.hpp
 *  @project    data structure containers. */
#ifndef DST_SList_h
#define DST_SList_h
#include "ds_node.hpp"
namespace kege{namespace ds{

    template<class var>  class slist
    {
    public:
        
        class iterator
        {
        public:
            void operator = (iterator const &i);
            bool operator ==(iterator const &i);
            bool operator !=(iterator const &i);
            bool operator !=(void * vptr);
            bool operator ==(void * vptr);
            var& operator ->(void);
            var& operator * (void);
            var& element(void);
            
            void operator ++(int i);
            
            iterator(const iterator& itr);
            iterator(snode<var> * s);
            iterator();
        private:
            snode<var> * prev;
            snode<var> * curr;
            friend slist<var>;
        };
        
    public:
        
        void operator = (const slist<var>& list);
        
        snode<var> * push_frontn(snode<var> * node);
        snode<var> * push_backn(snode<var> * node);
        snode<var> * push_front(var data);
        snode<var> * push_back(var data);
        snode<var> * head(void) const;
        snode<var> * tail(void)const;
        
        snode<var> * remove(iterator & itr);
        void erase(iterator & itr);
        
        iterator begin(void)const;
        iterator eol(void)const;
        iterator find(var data);
        
        bool pop_front(void);
        var& push_front();
        var& push_back();
        var& first(void)const;
        var& last(void)const;
        
        void copy(slist<var> & list);
        void clone(slist<var> & list);
        void clear(void);
        long count(void)const;
        bool empty(void)const;
        
        virtual ~ slist();
        slist();
        
    protected:
        
        snode<var> * _head;
        snode<var> * _tail;
        long _items;
    };
}}
#include "slist.inl"
#endif
