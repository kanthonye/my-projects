//
//  slist.inl
//  dev-kege
//
//  Created by Kenneth A Esdaile on 4/19/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef slist_inl
#define slist_inl
namespace kege{namespace ds{
    
    template<class var>  void ds::slist<var>::operator =(const slist<var>& list)
    {
        for (ds::slist<var> * i=list._head; i!=nullptr; i++) push_back(i->data);
    }
    
    template <class var>  snode<var> * slist<var>::push_front (var data)
    {
        return push_frontn(new snode<var>(data));
    }
    
    template <class var>  snode<var> * slist<var>::push_back(var data)
    {
        return push_backn(new snode<var>(data));
    }
    
    template <class var> snode<var>* slist<var>::push_frontn(snode<var> * node)
    {
        if (node == nullptr) throw nullptr;
        
        if (_head == nullptr)
            _head = _tail = node;
        else
        {
            node->next = _head;
            _head = node;
        }
        _items++;
        return node;
    }
    
    template <class var> snode<var>* slist<var>::push_backn(snode<var> * node)
    {
        if (node == nullptr) throw nullptr;
        
        if (_head == nullptr)
            _tail = _head = node;
        else
        {
            _tail->next = node;
            _tail = node;
        }
        _items++;
        return node;
    }
    
    template <class var> var& slist<var>::push_front()
    {
        return push_frontn(new snode<var>())->data;
    }
    template <class var> var& slist<var>::push_back()
    {
        return push_backn(new snode<var>())->data;
    }
    
    template <class var>  bool slist<var>::pop_front(void)
    {
        if (_head != nullptr)
        {
            if (_head == _tail) _tail = nullptr;
            
            snode<var> * n = _head;
            _head = _head->next;
            _items--;
            
            delete n;
            n = nullptr;
            return true;
        }
        else
        {
            return false;
        }
    }
    
    template <class var> void slist<var>::clear(void)
    {
        while (pop_front());
        _head = nullptr;
        _tail = nullptr;
        _items = 0;
    }
    
    template <class var> long slist<var>::count(void)const
    {
        return _items;
    }
    
    template <class var> inline var& slist<var>::first(void)const
    {
        return _head->data;
    }
    
    template <class var> inline var& slist<var>::last(void)const
    {
        return _tail->data;
    }
    
    template <class var> inline bool slist<var>::empty(void)const
    {
        return (_head==nullptr);
    }
    
    template <class var> snode<var> * slist<var>::head(void) const
    {
        return _head;
    }
    template <class var> snode<var> * slist<var>::tail(void)const
    {
        return _tail;
    }
    
    template <class var> typename slist<var>::iterator slist<var>::find(var data)
    {
        snode<var> * prev = nullptr;
        snode<var> * curr = _head;
        snode<var> * next = curr->next;
        while (curr != nullptr)
        {
            if (curr->data == data) break;
            prev = curr;
            curr = next;
            next = curr->next;
        }
        return iterator(prev,next,curr);
    }
    
    template<class var> ds::snode<var> * slist<var>::remove(iterator & itr)
    {
        ds::snode<var>* sn = itr.curr;
        if (_head == itr.curr)
        {
            itr.curr = _head = _head->next;
            if (_head == nullptr)
            {
                _tail = nullptr;
            }
            _items--;
        }
        else if (_tail == itr.curr)
        {
            _tail = itr.prev;
            if (_tail == nullptr)
            {
                _head = nullptr;
            }
            else _tail->next = nullptr;
            _items--;
        }
        else
        {
            itr.prev->next = itr.curr->next;
            itr.curr = itr.prev;
            _items--;
        }
        return sn;
    }
    
    template<class var> void slist<var>::erase(iterator & itr)
    {
        ds::snode<var> * s = remove(itr);
        if (s == nullptr) return;
        delete s;
        s = nullptr;
    }
    
    template<class var> typename ds::slist<var>::iterator ds::slist<var>::begin(void)const
    {
        return iterator(_head);
    }
    
    template<class var> typename ds::slist<var>::iterator ds::slist<var>::eol(void)const
    {
        return iterator();
    }
    
    template<class var>  slist<var>::slist()
    :   _head(nullptr)
    ,   _tail(nullptr)
    ,   _items(0)
    {
    }
    
    template<class var> slist<var>::~slist()
    {
        clear();
    }
}}

namespace kege{namespace ds{
    
    template <class var> void slist<var>::iterator::operator = (const iterator& itr)
    {
        prev = itr.prev;
        curr = itr.curr;
    }
    
    template <class var> bool slist<var>::iterator::operator ==(const iterator& itr)
    {
        return curr = itr.curr;
    }
    
    template<class var> bool slist<var>::iterator::operator !=(const iterator& itr)
    {
        return (curr != itr.curr);
    }
    
    template<class var> inline bool slist<var>::iterator::operator !=(void * vptr)
    {
        return (curr != vptr);
    }
    
    template<class var> inline bool slist<var>::iterator::operator ==(void * vptr)
    {
        return (curr == vptr);
    }
    
    template <class var> var& slist<var>::iterator::operator ->(void)
    {
        return curr->data;
    }
    
    template <class var> var& slist<var>::iterator::operator *(void)
    {
        return curr->data;
    }
    
    template <class var> var& slist<var>::iterator::element(void)
    {
        return curr->data;
    }
    
    template <class var> void slist<var>::iterator::operator ++(int i)
    {
        prev = curr;
        curr = curr->next;
    }
    
    template<class var>  slist<var>::iterator::iterator(const iterator& itr)
    :   curr(itr.curr)
    ,   prev(itr.prev)
    {
    }
    
    template<class var>  slist<var>::iterator::iterator(snode<var> * s)
    :   curr(s)
    ,   prev(nullptr)
    {
    }
    
    template<class var>  slist<var>::iterator::iterator()
    :   curr(nullptr)
    ,   prev(nullptr)
    {}
}}
#endif /* slist_inl */
