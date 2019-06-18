//
//  LibraryMeshs.cpp
//  AppDev
//
//  Created by Kenneth Esdaile on 6/8/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//
#include "Logger.hpp"
#include "LoaderTXT.hpp"
#include "LoaderOBJ.hpp"
namespace kege{namespace res{

    struct OBJ
    {
        ds::slist<int> v;
        ds::slist<int> f;
        ds::string usemtl;
        ds::string name;
    };
    
    struct Polygon
    {
        gfx::IndexBuffer v;
        gfx::IndexBuffer f;
        ds::string usemtl;
        ds::string name;
        unsigned int drawcount;
    };
    
    const char * PaserName(const char*& curr_line, char* temp)
    {
        curr_line = kege::str_next(curr_line, " ");
        curr_line = kege::str_skip(curr_line, " ");
        kege::str_cpyf(temp, curr_line, "\n ");
        curr_line = kege::str_next(curr_line, "\n");
        curr_line = kege::str_skip(curr_line, " \n");
        return temp;
    }
    
    void ReadVertexData(ds::slist<cg::point3>& vp, kege::BufferReader& reader, char * buffer, const char* flags)
    {
        char data[3][64];
        int m,n;
        while (reader.strcmp(flags))
        {
            n = 0;
            reader.skip(flags);
            reader.skip(" \t\r");
            while (!reader.chrcmp("\n"))
            {
                reader.read(data[n++], 64, " \n");
                reader.skip(" ");
            }
            m = 0;
            cg::vec3& v = vp.push_back();
            while (m < n && m < 3)
            {
                v.data[m] = atof(data[m]);
                m++;
            }
            reader.skip("\n");
        }
    }
    
    void ReadIndexData(res::LoaderOBJ::OBJ& obj, kege::BufferReader& reader, char * buffer)
    {
        unsigned int count = 0;
        
        while (reader.strcmp("f ") && !reader.eof())
        {
            count = 0;
            reader.skip("f ");
            while (!reader.strcmp("\n"))
            {
                reader.read(buffer, 64, " /f\n");
                obj.f.push_back(atoi(buffer));
                reader.skip(" /");
                count++;
            }
            obj.v.push_back(count);
            reader.skip(" \n\t\r");
        }
    }
    
    bool LoaderOBJ::OBJParseDataFrmTextBuffer
    (   ds::slist<OBJ>& model
     ,  ds::slist<cg::point3>& vp
     ,  ds::slist<cg::point3>& vn
     ,  ds::slist<cg::point3>& vt
     ,  ds::string& mtllib
     ,  kege::BufferReader& reader  )
    {
//        const char * curr_line = text_data;
        char temp[512];
        
        ds::string usemtl;
        OBJ* obj = nullptr;
        
        while (!reader.eof())
        {
            if (reader.strcmp("mtllib"))
            {
                /* parse material library name */
                reader.skip("mtllib\b ");
                reader.read(temp, 512, "\n");
                reader.skip(" \n\t\r");
                mtllib = temp;
            }
            
            if (reader.chrcmp("og"))
            {
                // new mesh object
                reader.skip("og ");
                reader.read(temp, 512, "\n");
                reader.skip(" \n\t\r");
                obj = &model.push_back();
                obj->name = temp;
            }
            
            if (reader.strcmp("v "))
            {
                ReadVertexData(vp, reader, temp, "v ");
            }
            
            if (reader.strcmp("vt"))
            {
                ReadVertexData(vt, reader, temp, "vt");
            }
            
            if (reader.strcmp("vn"))
            {
                ReadVertexData(vn, reader, temp, "vn");
            }
            
            if (reader.strcmp("usemtl"))
            {
                reader.skip("usemtl\b ");
                reader.read(temp, 512, "\n");
                reader.skip(" \n\t\r");
                obj = &model.push_back();
                if (obj != nullptr)
                {
                    obj->usemtl = temp;
                }
                else
                {
                    usemtl = temp;
                }
            }
            
            if (reader.strcmp("f "))
            {
                if (obj == nullptr)
                {
                    obj = &model.push_back();
                    obj->usemtl = usemtl;
                }
                ReadIndexData(*obj, reader, temp);
            }
            else
            {
                reader.seek("\n");
                reader.skip("\n");
            }
        }
        return true;
    }
    
    bool LoaderOBJ::OBJLoadDataFrmFile
    (   ds::slist<Polygon>& objs
     ,  gfx::DataBuffer<float>& vp
     ,  gfx::DataBuffer<float>& vn
     ,  gfx::DataBuffer<float>& vt
     ,  ds::string& mtllib
     ,  const ds::string& filename  )
    {
        kege::BufferReader reader = kege::VFS::GetInstance().OpenFile(filename);
        //ds::string buffer = kege::LoadTxtFile(filename);
        if (reader.eof())
        {
            return false;
        }
        
        ds::slist<cg::point3> vp_list;
        ds::slist<cg::point3> vn_list;
        ds::slist<cg::point3> vt_list;
        ds::slist<OBJ> obj_list;
        
        if (OBJParseDataFrmTextBuffer(obj_list, vp_list, vn_list, vt_list, mtllib, reader))
        {
            // copy vertex position to vertex array
            if (vp_list.count())
            {
                vp.setbuffer(3 * vp_list.count(), 3, 0);
                for (ds::slist<cg::point3>::iterator i=vp_list.begin(); i!=nullptr; i++)
                {
                    vp.add3(i.element());
                }
                vp_list.clear();
            }
            // copy vertex normal to vertex array
            if (vn_list.count())
            {
                vn.setbuffer(3 * vn_list.count(), 3, 0);
                for (ds::slist<cg::point3>::iterator i=vn_list.begin(); i!=nullptr; i++)
                {
                    vn.add3(i.element());
                }
                vn_list.clear();
            }
            // copy vertex texcoord to vertex array
            if (vt_list.count())
            {
                vt.setbuffer(2 * vt_list.count(), 2, 0);
                for (ds::slist<cg::point3>::iterator i=vt_list.begin(); i!=nullptr; i++)
                {
                    vt.add2(i.element().xy);
                }
                vt_list.clear();
            }
            // copy objects to obj objects
            if (obj_list.count())
            {
                unsigned int drawcount;
                for (ds::slist<OBJ>::iterator i=obj_list.begin(); i!=nullptr; i++)
                {
                    // create new polygon to copy object data to
                    Polygon *p = &objs.push_back();
                    p->name = (i.element().name);
                    
                    // copy indices
                    p->f.setbuffer((unsigned int) i.element().f.count(), 1, 0);
                    for (ds::slist<int>::iterator u=i.element().f.begin(); u!=nullptr; u++)
                    {
                        p->f.add(u.element()-1);
                    }
                    i.element().f.clear();
                    
                    // copy faces
                    drawcount = 0;
                    p->v.setbuffer((unsigned int) i.element().v.count(), 1, 0);
                    for (ds::slist<int>::iterator u=i.element().v.begin(); u!=nullptr; u++)
                    {
                        p->v.add(u.element());
                        drawcount += u.element();
                    }
                    i.element().v.clear();
                    
                    p->usemtl = i.element().usemtl;
                    p->name = i.element().name;
                    p->drawcount = drawcount;
                }
                obj_list.clear();
            }
            return true;
        }
        return false;
    }
    
    cg::mat33 LoaderOBJ::OBJBuildRawMesh(gfx::RawMesh& mesh, Polygon& poly, gfx::DataBuffer<float>& vp, gfx::DataBuffer<float>& vn, gfx::DataBuffer<float>& vt)
    {
        gfx::VertexBuffer& vertex_buffer = mesh.GetVertexBuffer();
        int stride = 0;
        if (vp.size())
        {
            vertex_buffer.AddVertexInfo(gfx::VERTEX_POSITION, 3, stride);
            stride += 3;
        }
        if (vn.size())
        {
            vertex_buffer.AddVertexInfo(gfx::VERTEX_NORMAL,   3, stride);
            stride += 3;
        }
        if (vt.size())
        {
            vertex_buffer.AddVertexInfo(gfx::VERTEX_TEXCOORD, 2, stride);
            stride += 2;
        }
        vertex_buffer.setbuffer(stride * poly.drawcount, stride, 0);
        
        float* v = nullptr;
        unsigned int draw_count = 0;
        unsigned int vcount = 0;
        unsigned int start = 0;
        unsigned int end = 0;
        unsigned int a,i,c, n=0;
        
        unsigned int n_offset = 1;
        unsigned int t_offset = 1;
        
        if (vp.size()) n++;
        if (vt.size()) t_offset = n++;
        if (vn.size()) n_offset = n++;
        const unsigned int inputs = n;
        
        double mass_total = (cg::uint) cg::invrs(poly.v.count());
        
        cg::point3 center_of_mass = 0.0;
        cg::point3 max =-60000.0;
        cg::point3 min = 60000.0;
        
        for (c=0; c<poly.v.count(); c++)
        {
            start  = end;
            vcount = *poly.v[c];
            draw_count += vcount;
            end = draw_count;
            
            for (i=start; i<end; i+=inputs)
            {
                a  = *poly.f[i];
                a *= 3;
                v  = vp[a];
                vertex_buffer.add3(v[0], v[1], v[2]);
                
                if( vt.count() )
                {
                    a  = *poly.f[i + t_offset];
                    a *= 2;
                    v  = vt[a];
                    vertex_buffer.add2(v[0], v[1]);
                }
                
                if( vn.count() )
                {
                    a  = *poly.f[i + n_offset];
                    a *= 3;
                    v  = vn[a];
                    vertex_buffer.add3(v[0], v[1], v[2]);
                }
                
                // bound box AABB and com for rigidbody
                max.x = cg::min(max.x, v[0]);
                max.y = cg::min(max.y, v[1]);
                max.z = cg::min(max.z, v[2]);
                
                min.x = cg::min(min.x, v[0]);
                min.y = cg::min(min.y, v[1]);
                min.z = cg::min(min.z, v[2]);
                
                center_of_mass.x += v[0];
                center_of_mass.y += v[1];
                center_of_mass.z += v[2];
            }
        }
        center_of_mass *= mass_total;
        return cg::mat33(min, center_of_mass, max);
    }
    
    bool LoaderOBJ::OBJBuildRawMesh(gfx::RawMesh& mesh, const ds::string& filename)
    {
        ds::slist<Polygon> objs;
        gfx::VertexBuffer vp;
        gfx::VertexBuffer vn;
        gfx::VertexBuffer vt;
        ds::string mtllib;
         if (!OBJLoadDataFrmFile(objs, vp, vn, vt, mtllib, filename))
        {
            return false;
        }
        OBJBuildRawMesh(mesh, objs.first(), vp, vn, vt);
        return true;
    }
    
    bool LoaderOBJ::OBJLoadMeshLibrary(OBJMeshLibrary& meshlibrary, ds::string& mtllib, const ds::string& filename)
    {
        ds::slist<Polygon> objs;
        gfx::VertexBuffer vp;
        gfx::VertexBuffer vn;
        gfx::VertexBuffer vt;
        
        if (!OBJLoadDataFrmFile(objs, vp, vn, vt, mtllib, filename))
        {
            return false;
        }
        
        for (ds::slist<Polygon>::iterator o=objs.begin(); o!=nullptr; o++)
        {
            gfx::RawMesh* mesh = new gfx::RawMesh;
            
            meshlibrary.push_back( OBJMesh(OBJName(o.element().name, o.element().usemtl), mesh) );
            
            cg::mat33 box = OBJBuildRawMesh(*mesh, o.element(), vp, vn, vt);
            //gfx::ComputeTangentNonIndex(*mesh);
            mesh->SetDrawCount(o.element().drawcount);
            mesh->SetMinPoint(box.row[0]);
            //mesh->SetCentrOfMass(box.row[1]);
            mesh->SetMaxPoint(box.row[2]);
            mesh->DrawTriangles();
            //mesh->Initialize();
        }
        return true;
    }
    

    
    gfx::Scenenode* LoaderOBJ::Load(kege::ResourceManager* manager, const ds::string& filename)
    {
        const ds::string fname = filename.parse_name();
        if (resource != nullptr)
        {
            gfx::Scenenode* n = resource->Get(fname);
            if (n != nullptr)
            {
                return n;
            }
        }
        
        ds::string mtllib;
        OBJMeshLibrary meshlibrary;
        if ( !OBJLoadMeshLibrary(meshlibrary, mtllib, filename) )
        {
            return nullptr;
        }
        
        kege::Resource<gfx::RawMesh>* resr_mesh = manager->GetResource<gfx::RawMesh>();
        kege::Resource<gfx::RawMaterial>* resr_matl = manager->GetResource<gfx::RawMaterial>();
        if (resr_matl->GetLoader("mtl") == nullptr) resr_matl->AddLoader(new kege::LoaderMTL);
        resr_matl->Load(manager, filename.parse_fpath() + mtllib);
        
        ds::string name;
        gfx::RawMesh* mesh = nullptr;
        gfx::RawMaterial* mtl = nullptr;
        gfx::Gameobject* gameobject = nullptr;
        for (OBJMeshLibrary::iterator m=meshlibrary.begin(); m!=nullptr; m++)
        {
            if (gameobject == nullptr)
            {
                gameobject = new gfx::Gameobject;
            }
            mtl  = resr_matl->Get(m.element().first.first);
            name = m.element().first.second;
            mesh = m.element().second;
            
            resr_mesh->Add(name, mesh);
            gameobject->AddChild(new gfx::Entity(name, gfx::Mesh(mesh, mtl)));
        }
        resource->Add(fname, gameobject);
        return gameobject;
    }
    
    LoaderOBJ::LoaderOBJ()
    :   kege::Loader<gfx::Scenenode>("Scenenode","obj")
    {
    }
    
    
    
    
    gfx::Gameobject* LoaderOBJ::OBJLoadGameobject(kege::ResourceManager* manager, const ds::string& filename)
    {
        ds::string mtllib;
        OBJMeshLibrary meshlibrary;
        if ( !OBJLoadMeshLibrary(meshlibrary, mtllib, filename) )
            return nullptr;
       
        kege::Resource<gfx::RawMaterial>* mtlres = nullptr;
        kege::Resource<gfx::RawMesh>* mshres = nullptr;
        if (manager != nullptr)
        {
            mtlres = manager->GetResource<gfx::RawMaterial>();
            mshres = manager->GetResource<gfx::RawMesh>();
            if (mtlres->GetLoader("mtl") == nullptr)
            {
                mtlres->AddLoader(new kege::LoaderMTL);
            }
            mtlres->Load(manager, filename.parse_fpath() + mtllib);
        }
        
//        ds::string name;
//        gfx::RawMaterial* mtl = nullptr;
//        gfx::RawMesh* rawmesh = nullptr;
        gfx::Gameobject* gameobject = nullptr;
//        for (OBJMeshLibrary::iterator mesh=meshlibrary.begin(); mesh!=nullptr; mesh++)
//        {
//            if (gameobject == nullptr)
//            {
//                gameobject = new gfx::Gameobject( filename.parse_name() );
//            }
//            name = mesh.element().first;
//            rawmesh = mesh.element().second;
//            gameobject->AddChild(new gfx::Entity(name, gfx::Mesh(rawmesh), mtl));
//        }
        return gameobject;
    }
}}


