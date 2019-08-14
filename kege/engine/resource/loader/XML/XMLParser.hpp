/*! @author     Kenneth Anthony Esdaile
 *  @date       created on 3/24/19
 *  @copyright  Copyright (c) 2014 kae. All rights reserved.
 *  @file       XMLParser.hpp
 *  @project    KEGE
 */
#ifndef XMLParser_hpp
#define XMLParser_hpp
#include "XML.hpp"
#include <iostream>
#include "BufferReader.hpp"
namespace kege{
    
    class XMLParser
    {
        enum
        {   ERRO,
            PUSH,
            BODY,
            POP ,
            END ,
        };
    public:
        
        XML::attrib* GetAttributes(kege::BufferReader& reader);
        ds::string GetID(kege::BufferReader& reader);
        int  GetNextState(kege::BufferReader& reader);
        int  ProcessBody(kege::BufferReader& reader);
        int  PushElement(kege::BufferReader& reader);
        int  PopElement(kege::BufferReader& reader);
        void Pop(kege::BufferReader& reader);
        
        bool LoadText(kege::XML& xml, ds::string const& filename);
        
        void Clear();
        
        ~ XMLParser();
        
    private:
        
        ds::stack< std::pair<int,kege::XML*> > _stack;
        ds::string error;
        char temp[64];
    };
}
#endif /* XMLParser_hpp */
