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
 *  @file       queue.h
 *  @project    data structure containers. */
#ifndef __DST__LINKED__QUEUE__
#define __DST__LINKED__QUEUE__
namespace kege{namespace ds{
    
    template<class var>  class queue
    {
    public:
        
        struct node
        {
            var data;
            node * next;
            node(var d) : data(d),next(nullptr){}
        };
        
    public:
        
        void clear (void);
        void push (node * element);
        void push (var data);
        var& push ();
        var pop (void);
        var& top (void) const;
        bool empty (void) const;
        const int size (void) const;
        
        node * get_quetop(void) const;
        node * get_queback(void) const;
        
        queue(var data);
        ~queue();
        queue();
        
    private:
        
        unsigned int items;
        node * head;
        node * tail;
    };
}}








namespace kege{namespace ds{
    
    template<class var>  queue<var>::queue(var data)
    :   head(nullptr)
    ,   tail(nullptr)
    ,   items(0)
    {
        push(data);
    }
    
    template<class var>  queue<var>::queue()
    :   head(nullptr)
    ,   tail(nullptr)
    ,   items(0)
    {
    }
    
    template<class var>  queue<var>::~queue()
    {
        if (head != nullptr) clear();
    }
    
    template<class var>  typename queue<var>::node * queue<var>::get_quetop() const
    {
        if (head!=nullptr)
            return head;
        else
            return nullptr;
    }
    
    template<class var>  typename queue<var>::node * queue<var>::get_queback() const
    {
        if (tail!=nullptr)
            return tail;
        else
            return nullptr;
    }
    
    template<class var>  void queue<var>::push(var data)
    {
        node * s = new node(data);
        
        if (head == nullptr)
        {
            tail = head = s;
        }
        else
        {
            tail->next = s;
            tail = s;
        }
        items++;
    }
    
    template<class var>  void queue<var>::push(node * e)
    {
        if (head==nullptr)
        {
            tail = head = e;
            items++;
        }
        else
        {
            tail->next = e;
            tail = e;
            items++;
        }
    }
    
    template<class var>  var& queue<var>::push()
    {
        node* e = new node;
        push(e);
        return &e;
    }
    
    template<class var>  var queue<var>::pop()
    {
        if (head == nullptr)
            throw nullptr;
        
        var data = head->data;
        node * n = head;
        head = head->next;
        delete n;
        n = nullptr;
        items--;
        
        if (head==nullptr)
            tail=nullptr;
        return data;
    }
    
    template<class var>  var& queue<var>::top() const
    {
        if (head!=nullptr)
            return head->data;
        else throw nullptr;
    }
    
    template<class var>  void queue<var>::clear()
    {
        if (head != nullptr)
        {
            while ( head != nullptr )
            {
                node * h = head;
                head = head->next;
                delete h;
                h = nullptr;
            }
            head = nullptr;
            tail = nullptr;
            items = 0;
        }
    }
    
    template<class var>  bool queue<var>::empty() const
    {
        return (head==nullptr && tail==nullptr);
    }
    
    template<class var>  const int queue<var>::size() const
    {
        return items;
    }
    
} }
#endif /* defined(__DST__stack__) */
