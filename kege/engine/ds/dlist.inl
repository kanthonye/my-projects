 //
//  dlist.c
//
//  Created by Kenneth Esdaile on 7/17/17.
//  Copyright © 2017 Kenneth Anthony Esdaile. All rights reserved.
//

#include <stdio.h>
#include "dlist.hpp"
namespace kege{namespace ds{
    
    template <class var>  bool dlist<var>::iterator::operator == (iterator const &a)
    {
        return (curr == a.curr);
    }
    
    template <class var>  bool dlist<var>::iterator::operator != (iterator const &a)
    {
        return (curr != a.curr);
    }
    
    template <class var>  bool dlist<var>::iterator::operator == (node2<var> * node)
    {
        return (curr == node);
    }
    
    template <class var>  bool dlist<var>::iterator::operator != (node2<var> * node)
    {
        return (curr != node);
    }
    template <class var>  typename dlist<var>::iterator dlist<var>::iterator::getnext(void)
    {
        if (curr == nullptr)
            return curr;
        return iterator(curr->next);
    }
    template <class var>  typename dlist<var>::iterator dlist<var>::iterator::getprev(void)
    {
        if (curr == nullptr)
            return curr;
        return iterator(curr->prev);
    }
    
    template <class var>  void dlist<var>::iterator::operator ++ (int)
    {
        prev = curr;
        curr = next;
        next = (curr != nullptr) ? curr->next : nullptr;
    }
    
    template <class var>  void dlist<var>::iterator::operator ++ ()
    {
        prev = curr;
        curr = next;
        next = (curr != nullptr) ? curr->next : nullptr;
    }
    
    template <class var>  void dlist<var>::iterator::operator -- (int)
    {
        prev = curr;
        curr = next;
        next = (curr != nullptr) ? curr->prev : nullptr;
    }
    
    template <class var>  void dlist<var>::iterator::operator -- ()
    {
        prev = curr;
        curr = next;
        next = (curr != nullptr) ? curr->prev : nullptr;
    }
    
    template <class var>  var& dlist<var>::iterator::operator ->(void)
    {
        return curr->getdata();
    }
    
    template <class var>  var& dlist<var>::iterator::operator  * (void)
    {
        return curr->getdata();
    }
    
    template <class var>  var& dlist<var>::iterator::element(void)
    {
        return curr->getdata();
    }
    
    template <class var>  bool dlist<var>::iterator::valid()
    {
        return (curr != nullptr);
    }
    
    template <class var>  node2<var> * dlist<var>::iterator::node(void)
    {
        if (curr == nullptr)
            return nullptr;
        return curr;
    }
    
    template <class var> dlist<var>::iterator::iterator(node2<var> * node)
    :   curr(node)
    ,   prev(nullptr)
    ,   next(nullptr)
    {
        // note that node can be the first node to be remove, if this is the case mem var prev should be set
        if (node)
        {
            if (node->prev && !node->next)
            {
                next = node->prev;
            }
            else if (!node->prev && node->next)
            {
                next = node->next;
            }
            else
            {
                prev = node->prev;
                next = node->next;
            }
        }
    }
    
    template<class var> dlist<var>::iterator::iterator(void)
    :   curr(nullptr)
    ,   prev(nullptr)
    ,   next(nullptr)
    {}
}}



namespace kege{namespace ds{
    
    template <class var> node2<var> * dlist<var>::push_frontn(node2<var> * node)
    {
        if (node == 0) return nullptr;
        
        if (head == 0)
            head = tail = node;
        else
        {
            head->prev = node;
            node->next = head;
            head = node;
        }
        items++;
        return node;
    }
    
    template <class var> node2<var> * dlist<var>::push_backn(node2<var> * node)
    {
        if (node == 0) return nullptr;
        
        if (head == 0)
            tail = head = node;
        else
        {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        items++;
        return node;
    }
    
    template <class var> node2<var> * dlist<var>::push_front(var elem)
    {
        return push_frontn( new dnode<var>(elem) );
    }
    
    template <class var> node2<var> * dlist<var>::push_back(var elem)
    {
        return push_backn( new dnode<var>(elem) );
    }
    
    template <class var> var & dlist<var>::push_front()
    {
        return push_frontn(new dnode<var>())->getdata();
    }
    
    template <class var> var & dlist<var>::push_back()
    {
        return push_backn(new dnode<var>())->getdata();
    }
    
    template <class var>  node2<var> * dlist<var>::frontnode()
    {
        return head;
    }
    
    template <class var>  node2<var> * dlist<var>::backnode()
    {
        return tail;
    }
    
    template <class var>  node2<var> * dlist<var>::eol(void)const
    {
        return nullptr;
    }

    template <class var>  var& dlist<var>::front(void)const
    {
        return head->getdata();
    }
    
    template <class var>  var& dlist<var>::back(void)const
    {
        return tail->getdata();
    }
    
    template <class var> void dlist<var>::remove(node2<var> * node)
    {
        if (node == nullptr) return;
        
        /* if only one node in the list */
        if (node == head && tail == node)
        {
            head = tail = nullptr;
            items--;
        }
        /* iterator is the head of list */
        if (node == head)
        {
            head = head->next;
            if (head != nullptr)
            {
                head->prev = nullptr;
            }
            else
            {
                tail = nullptr;
            }
            items--;
        }
        /* iterator is the tail of list */
        else if (node == tail)
        {
            tail = tail->prev;
            if (tail != nullptr)
            {
                tail->next = nullptr;
            }
            else
            {
                head = nullptr;
            }
            items--;
        }
        /* iterator is in between two other nodes */
        else if(node->next != nullptr && nullptr != node->prev)
        {
            node->next->prev = node->prev;
            node->prev->next = node->next;
            items--;
        }
        node->next = nullptr;
        node->prev = nullptr;
    }
    
    template <class var> bool dlist<var>::pop_front(void)
    {
        if (head == nullptr) return false;
        
        node2<var> * curr = head;
        head = head->next;
        
        if (head != nullptr)
            head->prev = nullptr;
        if (tail == head)
            tail = head = nullptr;
        
        delete curr;
        curr = nullptr;
        items--;
        return true;
    }
    
    template <class var> bool dlist<var>::pop_back(void)
    {
        if (tail == nullptr) return false;
        
        node2<var> * curr = tail;
        tail = tail->prev;
        
        if (tail != nullptr)
            tail->next = nullptr;
        else
        {
            head = nullptr;
        }
        
        delete curr;
        curr = nullptr;
        items--;
        return true;
    }

    template <class var> bool dlist<var>::empty()const
    {
        return (head == nullptr);
    }
    
    template <class var>  long dlist<var>::count(void)const
    {
        return items;
    }
    
    template <class var> void dlist<var>::clear(void)
    {
        while (pop_back());
        head = tail = nullptr;
        items = 0;
    }
    
    template <class var>  void dlist<var>::swap_head(node2<var> * a)
    {
        a->next->prev = head;
        head->next = a->next;
        
        head->prev = a;
        a->next = head;
        
        head = a;
        head->prev = nullptr;
    }
    
    template <class var>  void dlist<var>::swap_head2(node2<var> * a)
    {
        node2<var> * n = a->next;
        node2<var> * p = a->prev;
        node2<var> * h = head;
        head = head->next;
        
        p->next = h;
        h->prev = p;
        
        n->prev = h;
        h->next = n;
        
        head->prev = a;
        a->next = head;
        head = a;
        
        head->prev = nullptr;
    }
    
    template <class var>  void dlist<var>::swap_tail(node2<var> * a)
    {
        a->prev->next = tail;
        tail->prev = a->prev;
        
        tail->next = a;
        a->prev = tail;
        
        tail = a;
        tail->next = nullptr;
    }
    
    template <class var>  void dlist<var>::swap_tail2(node2<var> * a)
    {
        node2<var> * n = a->next;
        node2<var> * p = a->prev;
        node2<var> * t = tail;
        tail = tail->prev;
        
        p->next = t;
        t->prev = p;
        
        n->prev = t;
        t->next = n;
        
        tail->next = a;
        a->prev = tail;
        tail = a;
        tail->next = nullptr;
    }
    
    
    
    
    
    
    template <class var>  bool dlist<var>::insert_before(iterator & itr, node2<var> * node)
    {
        if (itr.curr == nullptr) return false;
        
        node->prev = itr.curr->prev;
        if (itr.curr->prev!=nullptr)
        {
            itr.curr->prev->next = node;
            itr.prev->next = node;
        }
        
        node->next = itr.curr;
        itr.curr->prev = node;
        
        return true;
    }
    
    template <class var>  bool dlist<var>::insert_after(iterator & itr, node2<var> * node)
    {
        if (itr.curr == nullptr) return false;
        
        node->next = itr.curr->next;
        if (itr.curr->next!=nullptr) itr.curr->next->prev = node;
        
        itr.curr->next = node;
        node->prev = itr.curr;
        
        return true;
    }
    
    template <class var>  bool dlist<var>::insert_after(iterator & position, var elem)
    {
        insert_after(position, create_node(elem));
    }
    
    template <class var>  bool dlist<var>::insert_before(iterator & position, var elem)
    {
        insert_before(position, create_node(elem));
    }
    
    template <class var>  bool dlist<var>::swap(iterator & a, iterator & b)
    {
        if (a.curr == nullptr || nullptr == b.curr || a.curr == b.curr)
            return false;
        
        if ((a.curr == head || tail == a.curr) && (b.curr == head || tail == b.curr))
        {
            node2<var> * p = tail->prev;
            node2<var> * n = head->next;
            tail->prev = nullptr;
            head->next = nullptr;
            
            if (p && p!=head)
            {
                p->next = head;
                head->prev = p;
            }
            else
            {
                head->prev = tail;
            }
            
            if (n && n!=tail)
            {
                n->prev = tail;
                tail->next = n;
            }
            else
            {
                tail->next = head;
            }
            
            n    = tail;
            tail = head;
            head = n;
        }
        /* iterator is the head of list */
        else if (a.curr == tail || tail == b.curr)
        {
            if (a.curr == tail)
            {
                if (tail->prev == b.curr)
                {
                    swap_tail(b.curr);
                }
                else
                {
                    swap_tail2(b.curr);
                }
            }
            else if (b.curr == tail)
            {
                if (tail->prev == a.curr)
                {
                    swap_tail(a.curr);
                }
                else
                {
                    swap_tail2(a.curr);
                }
            }
        }
        /* iterator is the tail of list */
        else if (a.curr == head || head == b.curr)
        {
            if (a.curr == head)
            {
                if (head->next == b.curr)
                {
                    swap_head(b.curr);
                }
                else
                {
                    swap_head2(b.curr);
                }
            }
            else if (b.curr == head)
            {
                if (head->next == a.curr)
                {
                    swap_head(a.curr);
                }
                else
                {
                    swap_head2(a.curr);
                }
            }
        }
        /* iterator is in between two other nodes */
        else
        {
            node2<var> * an = a.curr->next;
            node2<var> * ap = a.curr->prev;
            
            node2<var> * bn = b.curr->next;
            node2<var> * bp = b.curr->prev;
            
            bp->next = a.curr;
            a.curr->next = bp;
            bn->prev = a.curr;
            a.curr->next = bn;
            
            ap->next = b.curr;
            b.curr->next = ap;
            an->prev = b.curr;
            b.curr->next = an;
        }
        return true;
    }
    
    template <class var>  node2<var> * dlist<var>::remove(iterator & itr)
    {
        if (itr.curr == nullptr) return nullptr;
        /* if only one node in the list */
        if (itr.curr == head && tail == itr.curr)
        {
            head = tail = nullptr;
            items--;
        }
        /* iterator is the head of list */
        else if (itr.curr == head)
        {
            head = head->next;
            if (head != nullptr)
            {
                head->prev = nullptr;
            }
            else
            {
                tail = nullptr;
            }
            items--;
        }
        /* iterator is the tail of list */
        else if (itr.curr == tail)
        {
            tail = tail->prev;
            if (tail != nullptr)
            {
                tail->next = nullptr;
            }
            else
            {
                head = nullptr;
            }
            items--;
        }
        /* iterator is in between two other nodes */
        else if(itr.curr->next != nullptr && nullptr != itr.curr->prev)
        {
            itr.curr->next->prev = itr.curr->prev;
            itr.curr->prev->next = itr.curr->next;
            items--;
        }
        
        if (itr.curr == itr.prev) itr.prev = nullptr;
        
        if (itr.curr != nullptr)
        {
            itr.curr->next = nullptr;
            itr.curr->prev = nullptr;
        }
        return itr.curr;
    }
    
    template <class var>  bool dlist<var>::erase(iterator & itr)
    {
        itr.curr = remove(itr);
        if (itr.curr == nullptr) return false;
        delete itr.curr;
        itr.curr = nullptr;
        return true;
    }
    
    template <class var>  bool dlist<var>::remove(var elem)
    {
        node2<var> * h = head;
        while (h != nullptr)
        {
            if (h->getdata() == elem)
                break;
            h = h->next;
        }
        
        // case 1: only one element in list
        if (h == head && tail == h)
        {
            head = tail = nullptr;
            items--;
        }
        // case 2: h is the head of list
        else if (h == head)
        {
            head = head->next;
            if (head != nullptr)
            {
                head->prev = nullptr;
            }
            else
            {
                tail = nullptr;
            }
            items--;
        }
        // case 3: h is the tail of list
        else if (h == tail)
        {
            tail = tail->prev;
            if (tail != nullptr)
            {
                tail->next = nullptr;
            }
            else
            {
                head = nullptr;
            }
            items--;
        }
        // case 4: h is in the middle of list
        else if(h->next != nullptr && nullptr != h->prev)
        {
            h->next->prev = h->prev;
            h->prev->next = h->next;
            items--;
        }
        
        delete h;
        h = nullptr;
        return true;
    }
    
    template<class var> void dlist<var>::operator =(const dlist& list)
    {
        node2<var> * h = list.head;
        while (h != nullptr)
        {
            push_back(h->getdata());
            h = h->next;
        }
    }
    
    template<class var> dlist<var>::dlist(const dlist& list)
    :   head(nullptr)
    ,   tail(nullptr)
    ,   items(0)
    {
        dlist<var>::operator=(list);
    }
    
    template<class var> dlist<var>::~ dlist(void)
    {
        clear();
    }
    
    template<class var> dlist<var>::dlist(void)
    :   head(nullptr)
    ,   tail(nullptr)
    ,   items(0)
    {}
    
    template <typename var>  template <class varB>
    typename dlist<var>::iterator dlist<var>::find(varB* a)const
    {
        node2<var> * n = nullptr;
        for (n=head; n!=nullptr; n=n->next)
            if (n->getdata() == a) break;
        return iterator(n);
    }
    
    template <typename var>  typename dlist<var>::iterator dlist<var>::begin(void)const
    {
        return iterator(head);
    }
    
    template <typename var>  typename dlist<var>::iterator dlist<var>::end(void)const
    {
        return iterator(tail);
    }
    
}}



