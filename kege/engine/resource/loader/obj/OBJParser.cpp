/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/3/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       OBJParser.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */

#include "OBJParser.hpp"
namespace kege{
    
    typedef std::pair<ds::string, ds::string> OBJName;
    typedef std::pair<OBJName, gfx::Mesh*> OBJMesh;
    typedef ds::slist<OBJMesh> OBJMeshLibrary;
    
    struct OBJ
    {
        ds::slist< cg::int3 > indices;
        ds::string usemtl;
        ds::string name;
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
    
    void ReadIndexData(ds::slist< cg::int3 >& face_indices, kege::BufferReader& reader, char * buffer)
    {
        unsigned int count = 0;
        int n[16] = {-1,-1,-1};
        while (reader.strcmp("f ") && !reader.eof())
        {
            reader.skip("f ");
            while ( !reader.strcmp("\n") )
            {
                count = 0;
                while ( !reader.chrcmp(" \n") )
                {
                    reader.read(buffer, 64, " /f\n");
                    n[count] = atoi(buffer);
                    reader.skip("/");
                    count++;
                }
                reader.skip(" ");
                
                face_indices.push_back( {n[0]-1, n[1]-1, n[2]-1} );
            }
            reader.skip(" \n\t\r");
        }
    }
    
    bool OBJParseData
    (   ds::slist<OBJ>& model
     ,  ds::slist<cg::point3>& vp
     ,  ds::slist<cg::point3>& vn
     ,  ds::slist<cg::point3>& vt
     ,  ds::string& mtllib
     ,  kege::BufferReader& reader  )
    {
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
                ReadIndexData(obj->indices, reader, temp);
            }
            else
            {
                reader.seek("\n");
                reader.skip("\n");
            }
        }
        return true;
    }
    
    bool OBJParseData
    (   ds::slist<OBJ>& objects
     ,  gfx::DataBuffer<float>& vp
     ,  gfx::DataBuffer<float>& vn
     ,  gfx::DataBuffer<float>& vt
     ,  ds::string& mtllib
     ,  const ds::string& filename  )
    {
        kege::BufferReader reader = kege::VFS::GetInstance().OpenFile(filename);
        if (reader.eof())
        {
            return false;
        }
        
        ds::slist<cg::point3> vertices;
        ds::slist<cg::point3> normals;
        ds::slist<cg::point3> texcoord;
        
        if ( OBJParseData(objects, vertices, normals, texcoord, mtllib, reader) )
        {
            // copy vertex position to vertex array
            if (vertices.count())
            {
                vp.setbuffer(3 * vertices.count(), 3, 0);
                for (ds::slist<cg::point3>::iterator i=vertices.begin(); i!=nullptr; i++)
                {
                    vp.add3(i.element());
                }
            }
            
            // copy vertex normal to vertex array
            if (normals.count())
            {
                vn.setbuffer(3 * normals.count(), 3, 0);
                for (ds::slist<cg::point3>::iterator i=normals.begin(); i!=nullptr; i++)
                {
                    vn.add3(i.element());
                }
            }
            
            // copy vertex texcoord to vertex array
            if (texcoord.count())
            {
                vt.setbuffer(2 * texcoord.count(), 2, 0);
                for (ds::slist<cg::point3>::iterator i=texcoord.begin(); i!=nullptr; i++)
                {
                    vt.add2(i.element().xy);
                }
            }
            texcoord.clear();
            vertices.clear();
            normals.clear();
            return true;
        }
        return false;
    }
    
    void BuildMeshIndexBuffer(gfx::Mesh& mesh, const ds::slist< cg::int3 >& indices)
    {
        gfx::IndexBuffer& index_buffer = mesh.GetIndexBuffer();
        index_buffer.setbuffer(indices.count(), 1, 0);
        for (ds::slist< cg::int3 >::iterator u=indices.begin(); u!=nullptr; u++)
        {
            index_buffer.add( u.element().x );
        }
    }
    
    cg::int3* GetMeshIndex(short index, const ds::slist< cg::int3 >& indices)
    {
        cg::uint count = 0;
        for (ds::slist< cg::int3 >::iterator u=indices.begin(); u!=nullptr; u++,count++)
        {
            if (u.element().x == index)
            {
                return &u.element();
            }
        }
        return 0;
    }
    
    int SetVertexAttributes
    (   gfx::VertexBuffer& vertex_buffer
     ,  const gfx::DataBuffer<float>& vp
     ,  const gfx::DataBuffer<float>& vn
     ,  const gfx::DataBuffer<float>& vt )
    {
        int stride = 0;
        if (vp.size())
        {
            vertex_buffer.GetVertexLayout().AddElem(gfx::VERTEX_POSITION, 3, stride);
            stride += 3;
        }
        if (vn.size())
        {
            vertex_buffer.GetVertexLayout().AddElem(gfx::VERTEX_NORMAL,   3, stride);
            stride += 3;
        }
        if (vt.size())
        {
            vertex_buffer.GetVertexLayout().AddElem(gfx::VERTEX_TEXCOORD, 2, stride);
            stride += 2;
        }
        cg::uint vertice = (cg::uint) vp.count() / 3;
        vertex_buffer.setbuffer(stride * vertice, stride, 0);
        return stride;
    }
}



namespace kege{
    
    void OBJBuildMesh
    (   gfx::Mesh& mesh
     ,  const OBJ& obj
     ,  const gfx::DataBuffer<float>& vp
     ,  const gfx::DataBuffer<float>& vn
     ,  const gfx::DataBuffer<float>& vt  )
    {
        cg::uint vertice = (cg::uint) vp.count() / 3;
        SetVertexAttributes( mesh.GetVertexBuffer(), vp, vn, vt );
        gfx::DataBuffer<float>& vertex_buffer = mesh.GetVertexBuffer();
        
        cg::int3* index;
        const float* v = nullptr;
        unsigned int i, vindex, n=0;
        
        unsigned int n_offset = 1;
        unsigned int t_offset = 1;
        
        if (vp.size()) n++;
        if (vt.size()) t_offset = n++;
        if (vn.size()) n_offset = n++;
        
        double mass_total = cg::invrs( obj.indices.count() );
        
        cg::point3 center_of_mass = 0.0;
        cg::point3 max =-60000.0;
        cg::point3 min = 60000.0;
        
        BuildMeshIndexBuffer(mesh, obj.indices);
        
        for (vindex=0; vindex<vertice; vindex++)
        {
            index = GetMeshIndex(vindex, obj.indices);
            
            i = vindex * 3;
            v = vp[i];
            vertex_buffer.add3(v[0], v[1], v[2]);
            
            max.x = cg::max(max.x, v[0]);
            max.y = cg::max(max.y, v[1]);
            max.z = cg::max(max.z, v[2]);
            
            min.x = cg::min(min.x, v[0]);
            min.y = cg::min(min.y, v[1]);
            min.z = cg::min(min.z, v[2]);
            
            center_of_mass.x += v[0];
            center_of_mass.y += v[1];
            center_of_mass.z += v[2];
            
            if( vt.count() )
            {
                i = index->y * 2;
                v = vt[i];
                vertex_buffer.add2(v[0], v[1]);
            }
            
            if( vn.count() )
            {
                i = index->y * 3;
                v  = vn[i];
                vertex_buffer.add3(v[0], v[1], v[2]);
            }
        }
        
        center_of_mass *= mass_total;
        mesh.SetCenterPoint(center_of_mass);
        mesh.SetMinPoint(min);
        mesh.SetMaxPoint(max);
    }
    
    bool OBJLoadLibrary(ds::array< gfx::Mesh* >& lib, const ds::string& filename)
    {
        ds::slist<OBJ> objects;
        gfx::DataBuffer<float> vp;
        gfx::DataBuffer<float> vn;
        gfx::DataBuffer<float> vt;
        ds::string mtllib;
        if (!OBJParseData(objects, vp, vn, vt, mtllib, filename))
        {
            return false;
        }
        int n = 0;
        lib.resize( objects.count() );
        for (ds::slist< OBJ >::iterator obj=objects.begin(); obj!=nullptr; obj++)
        {
            gfx::Mesh* mesh = new gfx::Mesh;
            OBJBuildMesh(*mesh, obj.element(), vp, vn, vt);
            lib[ n++ ] = mesh;
        }
        return true;
    }
}
 
    


    
    

namespace kege{
    
    void OBJUnifyIndexBuffer( gfx::Mesh& mesh, const ds::slist< OBJ >& objects )
    {
        long count = 0;
        for (ds::slist<OBJ>::iterator obj=objects.begin(); obj!=nullptr; obj++)
        {
            count += obj.element().indices.count();
        }
        gfx::IndexBuffer& index_buffer = mesh.GetIndexBuffer();
        index_buffer.setbuffer(count, 1, 0);
        for (ds::slist<OBJ>::iterator obj=objects.begin(); obj!=nullptr; obj++)
        {
            for (ds::slist< cg::int3 >::iterator u=obj.element().indices.begin(); u!=nullptr; u++)
            {
                index_buffer.add( u.element().x );
            }
        }
    }
    
    bool OBJUnifyVertexBuffer
    (   gfx::Mesh& mesh
     ,  const ds::slist< OBJ >& objects
     ,  const gfx::DataBuffer<float>& vp
     ,  const gfx::DataBuffer<float>& vn
     ,  const gfx::DataBuffer<float>& vt )
    {
        cg::uint vertice = (cg::uint) vp.count() / 3;
        SetVertexAttributes( mesh.GetVertexBuffer(), vp, vn, vt );
        
        cg::int3* index;
        const float* v = nullptr;
        unsigned int i, vindex, n=0;
        
        unsigned int n_offset = 1;
        unsigned int t_offset = 1;
        
        if (vp.size()) n++;
        if (vt.size()) t_offset = n++;
        if (vn.size()) n_offset = n++;
        
        cg::point3 center_of_mass = 0.0;
        cg::point3 max =-60000.0;
        cg::point3 min = 60000.0;
        
        gfx::DataBuffer< float >& vertex_buffer = mesh.GetVertexBuffer();
        double mass_total = cg::invrs( mesh.GetIndexBuffer().count() );
        for (ds::slist<OBJ>::iterator obj=objects.begin(); obj!=nullptr; obj++)
        {
            for (vindex=0; vindex<vertice; vindex++)
            {
                index = GetMeshIndex(vindex, obj.element().indices);
                
                i = vindex * 3;
                v = vp[i];
                vertex_buffer.add3(v[0], v[1], v[2]);
                
                max.x = cg::max(max.x, v[0]);
                max.y = cg::max(max.y, v[1]);
                max.z = cg::max(max.z, v[2]);
                
                min.x = cg::min(min.x, v[0]);
                min.y = cg::min(min.y, v[1]);
                min.z = cg::min(min.z, v[2]);
                
                center_of_mass.x += v[0];
                center_of_mass.y += v[1];
                center_of_mass.z += v[2];
                
                if( vt.count() )
                {
                    i = index->y * 2;
                    v = vt[i];
                    vertex_buffer.add2(v[0], v[1]);
                }
                
                if( vn.count() )
                {
                    i = index->y * 3;
                    v  = vn[i];
                    vertex_buffer.add3(v[0], v[1], v[2]);
                }
            }
        }
        
        center_of_mass *= mass_total;
        mesh.SetCenterPoint(center_of_mass);
        mesh.SetMinPoint(min);
        mesh.SetMaxPoint(max);
        return true;
    }
    
    bool OBJLoadUnifyMesh(gfx::Mesh& mesh, const ds::string& filename)
    {
        ds::string mtllib;
        ds::slist<OBJ> objects;
        gfx::DataBuffer<float> vp;
        gfx::DataBuffer<float> vn;
        gfx::DataBuffer<float> vt;
        if ( !OBJParseData( objects, vp, vn, vt, mtllib, filename ) )
        {
            return false;
        }
        OBJUnifyIndexBuffer( mesh, objects );
        OBJUnifyVertexBuffer( mesh, objects, vp, vn, vt );
        return true;
    }
}
