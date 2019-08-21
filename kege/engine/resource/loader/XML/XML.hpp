//
//  XML.hpp
//  xmlparser
//
//  Created by Kenneth A Esdaile on 3/17/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef XML_hpp
#define XML_hpp
#include "string.hpp"
#include "dlist.hpp"
#include "stack.hpp"
#include "string.hpp"
namespace kege{

    class XML
    {
    public:
        
        class attrib
        {
        public:
            
            inline long ToLong() const {return value.to_long();}
            inline float ToFloat() const {return value.to_float();}
            inline int ToInt() const {return value.to_int();}
            
            attrib(ds::string const& n, ds::string const& v)
            :   name(n)
            ,   value(v)
            {}
            
            ds::string name;
            ds::string value;
        };
        
        typedef ds::dlist<XML*> list;
        typedef ds::dlist<XML*>::iterator iterator;
        typedef ds::dlist<XML::attrib*> attribs;
        
    public:
        
        const XML* GetChildByAttr(ds::string const& xml_name, ds::string const& an, ds::string const& av)const;
        XML* GetChildByAttr(ds::string const& xml_name, ds::string const& an, ds::string const& av);
        
        const XML* GetChildByAttr(ds::string const& an, ds::string const& av)const;
        XML* GetChildByAttr(ds::string const& an, ds::string const& av);
        
        const XML::attrib* GetAttr(ds::string const& name, ds::string const& value)const;
        XML::attrib* GetAttr(ds::string const& name, ds::string const& value);
        
        const XML::attrib* GetAttr(ds::string const& an)const;
        XML::attrib* GetAttr(ds::string const& an);
        
        XML::attrib* RemAttr(ds::string const& name);
        void AddAttr(XML::attrib* attr);
        
        void PopulateByTag(XML& nodes, ds::string const& name);
        XML* GetChildLike(ds::string const& name);
        
        const XML* GetChild(ds::string const& name)const;
        XML* GetChild(ds::string const& name);
        XML* RemChild(ds::string const& name);
        
        bool AddChild(ds::string const& url, XML* node);
        XML* AddChild(XML* node);
        
        const XML::attribs& GetAttributes()const;
        XML::attribs& GetAttributes();
        
        ds::dlist<XML*>::iterator Begin()const;
        ds::dlist<XML*>::iterator End()const;
        
        XML::list const& Elements()const;
        XML::list & Elements();
        
        void SetName(ds::string const& name);
        ds::string const& GetName()const;
        ds::string const& GetText()const;
        ds::string & GetText();
        
        XML* GetParent()const;
        XML* GetParent();
        XML* GetRoot();
        void Clear();
        
        void Print(bool all=false, int n=0);
        
        bool Load(const ds::string& filename);
        bool Save(const ds::string& name);
        bool Save(FILE* file, int space);
        
        XML(ds::string const& name);
        ~XML();
        XML();
        
    protected:
        
        XML::list nodes;
        
        attribs attributes;
        ds::string text;
        ds::string name;
        
        XML* parent;
        int refcnt;
    };
}
#endif /* xml_hpp */
