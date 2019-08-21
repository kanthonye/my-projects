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
 *  @file       stack.h
 *  @project    data structure containers. */
#ifndef __DS__LINKED__STACK__
#define __DS__LINKED__STACK__
#include "ds_node.hpp"
namespace kege{namespace ds{
 
    template<class var> class stack
    {
    public:
        
        ds::snode<var> * remove(void)const;
        unsigned int count(void) const;
        
        bool has   (var& data);
        var& top   (void)const;
        bool empty (void)const;
        void push  (var data);
        bool pop   (void);
        void clear (void);
        
        ~stack();
        stack();
        
    private:
        
        ds::snode<var>* _top;
        int _items;
    };
    
    template<class var> bool ds::stack<var>::has(var& data)
    {
        snode<var>* s = _top;
        while (s != nullptr)
        {
            if (s->data == data)
            {
                return true;
            }
        }
        return false;
    }
    
    template<class var> ds::snode<var> * ds::stack<var>::remove(void)const
    {
        if (_top != nullptr)
        {
            snode<var> * s = _top;
            _top = _top->next;
            
            delete s;
            s = nullptr;
            
            _items--;
            return s;
        }
        return nullptr;
    }
    
    template<class var> unsigned int stack<var>::count()const
    {
        return _items;
    }
    
    template<class var> var& stack<var>::top() const
    {
        return _top->data;
    }
    
    template<class var> void stack<var>::push(var a)
    {
        snode<var> * s = new snode<var>(a);
        if (_top==nullptr)
            _top = s;
        else
        {
            s->next = _top;
            _top = s;
        }
        _items++;
    }
    
    template<class var> bool stack<var>::pop()
    {
        if (_top != nullptr)
        {
            snode<var> * s = _top;
            _top = _top->next;
            
            delete s;
            s = nullptr;
            
            _items--;
            return true;
        }
        return false;
    }
    
    template<class var> void stack<var>::clear()
    {
        if (_top != nullptr) while (pop());
    }
    
    template<class var> bool stack<var>::empty()const
    {
        return (_top == nullptr);
    }
    
    template<class var> stack<var>::~stack()
    {
        clear();
    }
    
    template<class var> stack<var>::stack()
    :   _top(nullptr)
    ,   _items(0)
    {
    }
}}
#endif
