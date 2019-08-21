//
//  XML.cpp
//  xmlparser
//
//  Created by Kenneth A Esdaile on 3/17/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "XML.hpp"
#include "XMLParser.hpp"
namespace kege{
    
    const XML* XML::GetChildByAttr(ds::string const& n, ds::string const& an, ds::string const& av)const
    {
        const XML::attrib* a = GetAttr(an, av);
        if (a != nullptr) return this;
        
        for (XML::list::iterator i=nodes.begin(); i!=nullptr; i++)
        {
            XML* e = i.element()->GetChildByAttr(n, an, av);
            if (e != nullptr)
                return e;
        }
        return nullptr;
    }
    
    XML* XML::GetChildByAttr(ds::string const& n, ds::string const& an, ds::string const& av)
    {
        const XML::attrib* a = GetAttr(an, av);
        if (a != nullptr) return this;
        
        for (XML::list::iterator i=nodes.begin(); i!=nullptr; i++)
        {
            if (i.element()->GetName() == n)
            {
                XML* e = i.element()->GetChildByAttr(n, an, av);
                if (e != nullptr)
                    return e;
            }
        }
        return nullptr;
    }
    
    const XML* XML::GetChildByAttr(ds::string const& an, ds::string const& av)const
    {
        for (XML::list::iterator i=nodes.begin(); i!=nullptr; i++)
        {
            const XML::attrib* a = i.element()->GetAttr(an, av);
            if (a != nullptr) return this;
        }
        return nullptr;
    }
    XML* XML::GetChildByAttr(ds::string const& an, ds::string const& av)
    {
        for (XML::list::iterator i=nodes.begin(); i!=nullptr; i++)
        {
            const XML::attrib* a = i.element()->GetAttr(an, av);
            if (a != nullptr) return i.element();
        }
        return nullptr;
    }
    
    const XML::attrib* XML::GetAttr(ds::string const& name, ds::string const& value)const
    {
        for (XML::attribs::iterator a=attributes.begin(); a!=nullptr; a++)
        {
            if (a->name == name)
                if (a->value == value)
                    return a.element();
        }
        return nullptr;
    }
    
    XML::attrib * XML::GetAttr(ds::string const& name, ds::string const& value)
    {
        for (XML::attribs::iterator a=attributes.begin(); a!=nullptr; a++)
        {
            if (a->name == name)
                if (a->value == value)
                    return a.element();
        }
        return nullptr;
    }
    
    const XML::attrib* XML::GetAttr(ds::string const& name)const
    {
        for (XML::attribs::iterator a=attributes.begin(); a!=nullptr; a++)
            if (a->name == name)
                return a.element();
        return nullptr;
    }
    
    XML::attrib * XML::GetAttr(ds::string const& name)
    {
        for (XML::attribs::iterator a=attributes.begin(); a!=nullptr; a++)
            if (a->name == name)
                return a.element();
        return nullptr;
    }
    
    XML::attrib* XML::RemAttr(ds::string const& name)
    {
        for (XML::attribs::iterator a=attributes.begin(); a!=nullptr; a++)
            if (a->value == name)
            {
                XML::attrib* w = a.element();
                attributes.erase(a);
                return w;
            }
        return nullptr;
    }
    
    void XML::AddAttr(XML::attrib* attr)
    {
        if (attr == nullptr) return;
        attributes.push_back(attr);
    }
    
    void XML::PopulateByTag(XML& node, ds::string const& ename)
    {
        for (XML::list::iterator i=nodes.begin(); i!=nullptr; i++)
            if (i.element()->name == ename) node.AddChild(i.element());
    }
    
    XML* XML::GetChildLike(ds::string const& name)
    {
        const char* n;
        const char* m;
        for (XML::list::iterator i=nodes.begin(); i!=nullptr; i++)
        {
            n = i.element()->name.c_str();
            m = name.c_str();
            while (*m == *n && *m!=0 && *n!=0)
            {
                m++;
                n++;
            }
            if (*m == 0)
            {
                return i.element();
            }
        }
        return nullptr;
    }
    const XML* XML::GetChild(ds::string const& url)const
    {
        if (url.empty()) return nullptr;
        
        if (url[0] == '/')
        {
            ds::string ename;
            ds::string urlname = url;
            const char* str = strtok(urlname.getdata(), "/\\\n\t\r");
            const XML* root = this;
            while (str != nullptr && root != nullptr)
            {
                ename = str;
                root = root->GetChild(ename);
                str = strtok(nullptr, "/\\\n\t\r");
            }
            if (root != nullptr)
            {
                if (root->name == ename)
                    return root;
            }
            return nullptr;
        }
        else
        {
            for (XML::list::iterator i=nodes.begin(); i!=nullptr; i++)
                if (i.element()->name == url)
                    return i.element();
            return nullptr;
        }
    }
    
    XML* XML::GetChild(ds::string const& url)
    {
        if (url.empty()) return nullptr;
        
        if (url[0] == '/')
        {
            ds::string ename;
            ds::string urlname = url;
            const char* str = strtok(urlname.getdata(), "/\\\n\t\r");
            XML* root = this;
            while (str != nullptr && root != nullptr)
            {
                ename = str;
                root = root->GetChild(ename);
                str = strtok(nullptr, "/\\\n\t\r");
            }
            if (root != nullptr)
            {
                if (root->name == ename)
                    return root;
            }
            return nullptr;
        }
        else
        {
            for (XML::list::iterator i=nodes.begin(); i!=nullptr; i++)
                if (i.element()->name == url)
                    return i.element();
            return nullptr;
        }
    }
    
    XML* XML::RemChild(ds::string const& url)
    {
        if (url[0] == '/')
        {
            ds::string ename;
            ds::string urlname = url;
            const char* str = strtok(urlname.getdata(), "/\\\n\t\r");
            XML* root = this;
            while (str != nullptr && root != nullptr)
            {
                ename = str;
                root = root->GetChild(ename);
                str = strtok(nullptr, "/\\\n\t\r");
            }
            if (root != nullptr)
            {
                if (root->name == ename)
                {
                    return root;
                }
            }
            return nullptr;
        }
        else
        {
            for (XML::list::iterator i=nodes.begin(); i!=nullptr; i++)
                if (i.element()->name == url)
                {
                    XML* n = i.element();
                    nodes.erase(i);
                    n->refcnt--;
                    return n;
                }
        }
        return nullptr;
    }
    
    bool XML::AddChild(ds::string const& url, XML* n)
    {
        XML* child = GetChild(url);
        if (child != nullptr)
        {
            child->AddChild(n);
            return true;
        }
        return false;
    }
    
    XML* XML::AddChild(XML* child)
    {
        if (child == nullptr) return nullptr;
        
        child->parent = this;
        child->refcnt++;
        
        nodes.push_back(child);
        return child;
    }
    
    XML::attribs const& XML::GetAttributes()const
    {
        return attributes;
    }
    XML::attribs& XML::GetAttributes()
    {
        return attributes;
    }
    
    XML::list const& XML::Elements()const
    {
        return nodes;
    }
    
    XML::list & XML::Elements()
    {
        return nodes;
    }
    
    ds::dlist<XML*>::iterator XML::Begin()const
    {
        return nodes.begin();
    }
    
    ds::dlist<XML*>::iterator XML::End()const
    {
        return nodes.end();
    }
 
    void XML::SetName(ds::string const& n)
    {
        name = n;
    }
    ds::string const& XML::GetName()const
    {
        return name;
    }
    ds::string const& XML::GetText()const
    {
        return text;
    }
    ds::string & XML::GetText()
    {
        return text;
    }
    
    XML* XML::GetParent()const
    {
        return parent;
    }
    XML* XML::GetParent()
    {
        return parent;
    }
    
    XML* XML::GetRoot()
    {
        if (parent == nullptr) return this;
        return parent->GetRoot();
    }
    
    void XML::Clear()
    {
        for (ds::dlist<XML*>::iterator i=nodes.begin(); i!=nullptr; i++)
        {
            i->refcnt--;
            if (i->refcnt <= 0)
            {
                delete i.element();
            }
        }
        nodes.clear();
        
        for (XML::attribs::iterator a=attributes.begin(); a!=nullptr; a++)
            delete a.element();
        attributes.clear();
    }
    
    bool XML::Load(ds::string const& filename)
    {
        kege::XMLParser p;
        if ( p.LoadText(*this, filename) )
        {
            return true;
        }
        return false;
    }
    
    bool XML::Save(ds::string const& filename)
    {
        FILE* file = fopen(filename.c_str(), "w");
        bool loaded = Save(file, 0);
        if (file!=nullptr)
        {
            fclose(file);
        }
        return loaded;
    }
    
    bool XML::Save(FILE* file, int space)
    {
        if (file == nullptr) return false;
        for (int i=0; i<space; i++) fprintf(file, "  ");
        
        fprintf(file, "<%s", GetName().c_str());
        for (XML::attribs::iterator a=attributes.begin(); a!=nullptr; a++)
        {
            fprintf(file, " %s=\"%s\"",a->name.c_str(), a->value.c_str());
        }
        
        if (nodes.count() == 0 && GetText().empty())
        {
            fprintf(file, "/>\n");
            return true;
        }
        else
        {
            fprintf(file, ">");
        }
        
        if (!GetText().empty())
        {
            fwrite(GetText().c_str(), sizeof(char), GetText().length(), file);
        }
        else
        {
            fwrite("\n", sizeof(char), 1, file);
            for (ds::dlist<XML*>::iterator i=nodes.begin(); i!=nullptr; i++)
            {
                i->Save(file, space+1);
            }
            for (int i=0; i<space; i++) fprintf(file, "  ");
        }
        
        fprintf(file, "</%s>\n", GetName().c_str());
        return true;
    }
    
    XML::XML(ds::string const& name)
    :   parent(nullptr)
    ,   name(name)
    ,   refcnt(0)
    {
    }
    
    XML::XML()
    :   parent(nullptr)
    ,   refcnt(0)
    {
    }
    
    XML::~ XML()
    {
        Clear();
    }
    
    void XML::Print(bool all,int n)
    {
        for (int s=0; s<n; s++) printf("-");
        printf("%s :",name.c_str());
        
        if (all)
        {
            if (!attributes.empty())
            {
                for (attribs::iterator s=attributes.begin(); s!=nullptr; s++)
                    printf(" [%s = %s] ",s->name.c_str(), s->value.c_str());
            }
            
            if (!text.empty())
            {
                printf("{ %s }\n",text.c_str());
            }else printf("\n");
        }
        else printf("\n");
        
        if (!nodes.empty())
        {
            ds::dlist<XML*>::iterator i;
            for (i=nodes.begin(); i!=nullptr; i++)
                i->Print(all,n+2);
        }
    }
}
