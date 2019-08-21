/*! @author     Kenneth Anthony Esdaile
 *  @date       created on 3/24/19
 *  @copyright  Copyright (c) 2014 kae. All rights reserved.
 *  @file       XMLParser.cpp
 *  @project    KEGE
 */
#include "XMLParser.hpp"
namespace kege{
    
    int XMLParser::GetNextState(kege::BufferReader& reader)
    {
        kege::BufferReader r = reader;
        if (r == '<')
        {
            r.skip("<\b \t\n\r");
            if (r == '/')
            {
                reader = r;
                return XMLParser::POP;
            }
            else if (r.char_digit() || r.char_letter())
            {
                reader = r;
                return XMLParser::PUSH;
            }
            else if (r =='?')
            {
                r++;
                r.seek(">");
                r.skip(">\b \t\n\r");
                reader = r;
                return GetNextState(reader);
            }
            else
            {
                error = "id or '/' expected.";
                return XMLParser::ERRO;
            }
        }
        if (r == '>')
        {
            r.skip(">\b \t\n\r");
            if (r == '<')
            {
                reader = r;
                return XMLParser::PUSH;
            }
            else
            {
                reader = r;
                return XMLParser::BODY;
            }
        }
        if (r == '/')
        {
            return XMLParser::POP;
        }
        return XMLParser::END;
    }
    
    int XMLParser::ProcessBody(kege::BufferReader& reader)
    {
        if (!reader.chrcmp("<>"))
        {
            kege::BufferReader br = reader;
            br.seek("<");
            long size = (br-reader);
            char *target = new char[size+1];
            reader.read(target, size);
            _stack.top().second->GetText().setstring(size, target);
            reader.skip(" \n\t\r");
        }
        return GetNextState(reader);
    }
    
    XML::attrib* XMLParser::GetAttributes(kege::BufferReader& reader)
    {
        ds::string name, value;
        
        reader.read(temp, 64, " =");
        reader.skip(" \n\t\r");
        name = temp;
        
        if ( !reader.strcmp("=") )
        {
            throw "= expected";
        }
        reader.skip("=\b \n\t\r");
        if ( !reader.strcmp("\"") )
        {
            throw "\" expected";
        }
        
        reader.skip("\"\b \n\t\r");
        reader.read(temp, 64, "\"=");
        reader.skip("\"\b \n\t\r");
        value = temp;
        
        return new XML::attrib(name, value);
    }
    
    int XMLParser::PushElement(kege::BufferReader& reader)
    {
        reader.skip("<\b \n\t\r");
        kege::XML* xml = new kege::XML( GetID(reader) );
        reader.skip(" \n\t\r");
        while (!reader.chrcmp("/>"))
        {
            xml->AddAttr(GetAttributes(reader));
        }
        //reader.skip(" \n\t\r");
        _stack.push(std::pair<int,kege::XML*>(1, xml));
        return GetNextState(reader);
    }
    
    int XMLParser::PopElement(kege::BufferReader& reader)
    {
        if (reader.chrcmp("/?"))
        {
            if (reader == '?')
            {
                reader.skip("?\b \n\t\r");
                Pop(reader);
                return GetNextState(reader);
            }
            else
            {
                reader.skip("/\b \n\t\r");
            }
            
            if (reader.char_digit() || reader.char_letter())
            {
                reader.read(temp, 64, "> ");
                ds::string name = temp;
                if (name != _stack.top().second->GetName())
                {
                    error = "un-match <id> (" + name + " != " + _stack.top().second->GetName() + ")";
                    return XMLParser::ERRO;
                }
                Pop(reader);
                return GetNextState(reader);
            }
            else if (reader == '>')
            {
                Pop(reader);
                return GetNextState(reader);
            }
            else
            {
                error = "pop 'id' or '>' expected";
                return XMLParser::ERRO;
            }
        }
        else
        {
            error = "'/' expected";
            return XMLParser::ERRO;
        }
        return XMLParser::POP;
    }
    
    void XMLParser::Pop(kege::BufferReader& reader)
    {
        std::pair<int,kege::XML*> elem = _stack.top();
        elem.first = 0;
        if (_stack.count() >= 2)
        {
            _stack.pop();
            _stack.top().second->AddChild(elem.second);
        }
        reader.skip(">\b \n\t\r");
    }
    
    ds::string XMLParser::GetID(kege::BufferReader& reader)
    {
        reader.skip(" \n\t\r");
        reader.read(temp, 64, " /=\"<>?");
        reader.skip(" \n\t\r");
        return temp;
    }
    
    bool XMLParser::LoadText(kege::XML& xml, ds::string const& filename)
    {
        _stack.push(std::pair<int,kege::XML*>(0, &xml));
        kege::BufferReader reader;
        if (!reader.open(filename)) return false;
        
        try
        {
            int state = -1;
            while (!reader.eof() && state != END)
            {
                switch (state)
                {
                    default  : state = GetNextState(reader); break;
                    case PUSH: state = PushElement(reader);  break;
                    case BODY: state = ProcessBody(reader);  break;
                    case POP : state = PopElement(reader);   break;
                    case ERRO: throw error; break;
                }
            }
            
            while (!_stack.empty())
            {
                if (_stack.top().first == 1)
                {
                    printf("[ERROR : XMLParser] : %s has no corresponding end element\n", _stack.top().second->GetName().c_str());
                    xml.Print();
                    xml.Clear();
                    return false;
                }
                if (_stack.top().second != &xml)
                {
                    delete _stack.top().second;
                }
                _stack.pop();
            }
        }
        catch (ds::string& erro)
        {
            printf("[ERROR : XMLParser] : %s\n", erro.c_str());
            xml.Clear();
            return false;
        }
        catch (const char* erro)
        {
            printf("[ERROR : XMLParser] : %s\n", erro);
            xml.Clear();
            return false;
        }
        
        return true;
    }
    
    void XMLParser::Clear()
    {
        _stack.clear();
    }
    
    XMLParser::~ XMLParser()
    {
        Clear();
    }
}
