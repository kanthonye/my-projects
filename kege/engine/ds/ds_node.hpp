//
//  ds_node.hpp
//  dev0
//
//  Created by Kenneth Esdaile on 12/4/17.
//  Copyright © 2017 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef ds_node_h
#define ds_node_h
namespace kege{namespace ds{
    template <class var>  class dlist;
    
    template< class var >  struct inode
    {
        virtual inode< var > * getnext() = 0;
        virtual inode< var > * getprev() = 0;
        inline  var getdata() {return data;}
        inode(var v) : data(v) {}
        inode(){}
        var data;
    };
    
    template<class var>  struct snode : public ds::inode<var>
    {
        ds::inode<var> * getprev() {return nullptr;}
        ds::inode<var> * getnext() {return next;}
        snode(var a) : ds::inode<var>(a), next(nullptr) {}
        snode() : next(nullptr) {}
        snode<var> * next;
    };
}}
#endif /* ds_node_h */
