//======================================================================
//  Author  : Kenneth A Esdaile
//  Date    : Created on 4/14/19.
//  Title   : ColladaLibrary.cpp
//  Project : KEGE
//======================================================================
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//======================================================================
#include "Scene.hpp"
#include "ColladaLibrary.hpp"
namespace kege{namespace dae{
    
    void ColladaLibrary::ToPolygonBuffers(gfx::DataBuffer<cg::uint>& vcount, gfx::DataBuffer<cg::uint>& v, kege::XML* polylist)
    {
        kege::XML::attrib* x_size = polylist->GetAttr("count");
        if (x_size == nullptr) throw "[error] : null attrib 'count'.";
        
        kege::XML* x_vcount = polylist->GetChild("vcount");
        kege::XML* x_vindex = polylist->GetChild("p");
        if (x_vindex == nullptr)
        {
            x_vindex = polylist->GetChild("v");
            if (x_vindex == nullptr) throw "[error] : null <p> or <v> element.";
        }
        kege::XML inputs;
        polylist->PopulateByTag(inputs, "input");
        long total_input = inputs.Elements().count();
        
        char* data;
        int val;
        long num;
        long size = x_size->ToInt();
        
        if (x_vcount != nullptr)
        {
            vcount.setcount(0);
            vcount.setsize(size);
            vcount.setstride(1);
            num = 0;
            data = strtok(x_vcount->GetText().getdata(), " \n\t\r");
            while (data != nullptr && size >= vcount.count())
            {
                val  = atoi(data);
                num += val;
                vcount.add(val);
                data = strtok(nullptr, " \n\t\r");
            }
            size = num * total_input;
        }
        else
        {
            if (polylist->GetName() == "triangles")
            {
                vcount.setstride(3);
                size *= 3;
            }
            else if (polylist->GetName() == "lines")
            {
                vcount.setstride(2);
                size *= 2;
            }
        }
        
        v.setcount(size/total_input);
        v.setsize(size);
        v.setstride(total_input);
        num = 0;
        data = strtok(x_vindex->GetText().getdata(), " \n\t\r");
        while (data != nullptr && num < size)
        {
            *v[num++] = atoi(data);
            data = strtok(nullptr, " \n\t\r");
        }
    }
    
    kege::XML* ColladaLibrary::GetInputSource(kege::XML* sources, kege::XML* input)
    {
        if (input == nullptr) return nullptr;
        kege::XML::attrib* source = input->GetAttr("source");
        return sources->GetChildByAttr("id", RemoveHashtag(source->value));
    }
    
    gfx::DataBuffer<float> ColladaLibrary::ToVertexBuffer(kege::XML* source)
    {
        if (source == nullptr) return gfx::DataBuffer<float>();
        
        kege::XML* accessor = source->GetChild("/technique_common/accessor");
        if (accessor == nullptr) throw "[error] : null element <acessor>.";
        
        kege::XML::attrib* xstride = accessor->GetAttr("stride");
        if (xstride == nullptr) throw "[error] : null attrib 'stride'.";
        int stride = xstride->ToInt();
        
        //kege::XML::attrib* xcount = accessor->GetAttr("count");
        //if (xcount == nullptr) throw "[error] : null attrib 'count'.";
        //long count = xcount->ToInt();
        
        kege::XML* float_array = source->GetChild("float_array");
        if (float_array == nullptr) throw "[error] : null element <float_array>.";
        
        kege::XML::attrib* xsize = float_array->GetAttr("count");
        if (xsize == nullptr) throw "[error] : null arrtib 'count'.";
        int size = xsize->ToInt();
        
        char* str_data = strtok(float_array->GetText().getdata(), " \n\t\r");
        float* floats = new float[size];
        cg::uint num = 0;
        while (str_data != nullptr && num < size)
        {
            floats[num++] = atof(str_data);
            str_data = strtok(nullptr, " \n\t\r");
        }
        return gfx::DataBuffer<float>(stride, size, floats);
    }
    
    char const* ColladaLibrary::RemoveHashtag(kege::ds::string const& a)
    {
        const char * s = a.c_str();
        if (*s == '#') s++;
        return s;
    }
    
    int ColladaLibrary::GetTotalInputs(kege::XML* polylist)
    {
        kege::XML nodes;
        polylist->PopulateByTag(nodes, "input");
        return (int)nodes.Elements().count();
    }
    
    int ColladaLibrary::GetInputOffset(kege::XML* input)
    {
        if (input == nullptr) return -1;
        kege::XML::attrib* offset = input->GetAttr("offset");
        return atoi(offset->value.c_str());
    }
    
    void ColladaLibrary::StringToFloats(float* arry, const int size, kege::ds::string& text)
    {
        int count = 0;
        char* data = strtok(text.getdata(), " \n\t\r");
        while (data != nullptr && count < size)
        {
            arry[count++] = atof(data);
            data = strtok(nullptr, " \n\t\r");
        }
    }
    cg::mat44 ColladaLibrary::ToMatrix(kege::ds::string& text)
    {
        cg::mat44 m;
        StringToFloats(m.data, 16, text);
        return cg::transpose(m);
    }
    
    cg::quat ColladaLibrary::ToQuat(kege::ds::string& text)
    {
        cg::vec4 v;
        StringToFloats(v.data, 4, text);
        return cg::quat(v.w, v.xyz);
    }
    
    cg::vec4 ColladaLibrary::ToVec4(kege::ds::string& text)
    {
        cg::vec4 v;
        StringToFloats(v.data, 4, text);
        return v;
    }
    
    cg::vec3 ColladaLibrary::ToVec3(kege::ds::string& text)
    {
        cg::vec3 v;
        StringToFloats(v.data, 3, text);
        return v;
    }
    
    cg::mat33 ColladaLibrary::GetUpAxisMatrix()
    {
        cg::mat33 matrix(1.0);
//        kege::XML* up_axis = collada->GetChild("/COLLADA/asset/up_axis");
//        if (up_axis != nullptr)
//        {
//            if (up_axis->GetText() == "Z_UP")
//            {
//                matrix = cg::mat33
//                ( 1.0, 0.0, 0.0
//                 ,0.0, 0.0, 1.0
//                 ,0.0, 1.0, 0.0 );
//            }
//            else if (up_axis->GetText() == "X_UP")
//            {
//                matrix = cg::mat33
//                ( 0.0, 1.0, 0.0
//                 ,1.0, 0.0, 0.0
//                 ,0.0, 0.0, 1.0 );
//            }
//        }
        return matrix;
    }
    
}}
