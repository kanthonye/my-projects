/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/3/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       OBJParser.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#include "OBJParser.hpp"
#include "queue.hpp"
#include "slist.hpp"
namespace kege{
    
    typedef std::pair<ds::string, ds::string> OBJName;
    typedef std::pair<OBJName, gfx::Mesh*> OBJMesh;
    typedef ds::slist<OBJMesh> OBJMeshLibrary;
    
    struct OBJFaceGroup
    {
        core::DataBuffer< cg::uint > indices;
        ds::string usemtl;
    };
    
    struct OBJVertexData
    {
        core::DataBuffer< float > vp;
        core::DataBuffer< float > vn;
        core::DataBuffer< float > vt;
    };
    
    struct OBJMtl
    {
        cg::vec4 ka;
        cg::vec4 kd;
        cg::vec4 ks;
        float ns;
        float d;
        float illum;
        
        ds::string map_Ka;
        ds::string map_Kd;
        ds::string map_Ks;
        ds::string map_Ns;
        ds::string map_d;
    };
    
    float GetFloat( kege::BufferReader& reader, char* temp, int size )
    {
        reader.read( temp, size, " \n\t\r" );
        reader.skip( " \n\t\r" );
        return atof( temp );
    }
    void GetColor(float* a, kege::BufferReader& reader)
    {
        int n = 0;
        char temp[32];
        reader.seek( " " );
        reader.skip( " \n\t\r" );
        while ( !reader.chrcmp("\n") && n < 3 )
        {
            a[ n++ ] = GetFloat( reader, temp, 32 );
        }
    }
    ds::string GetFilename( kege::BufferReader& reader, char* temp, int size )
    {
        reader.seek( " " );
        reader.skip( " \n\t\r" );
        kege::BufferReader prev = reader;
        reader.seek(".\n");
        reader.seek(" \n");
        prev.read( temp, reader - prev );
        return temp;
    }
    
    bool MTLParseData( listpair<ds::string, OBJMtl*>& materials, const ds::string& filename )
    {
        kege::VFS::File file = kege::VFS::GetInstance().OpenFile( filename );
        if ( file.file == nullptr) return false;
        
        const ds::string path = file.filename.parse_fpath();
        kege::BufferReader reader = file;
        char temp[128];
        
        OBJMtl* mtl = nullptr;
        while ( !reader.eof() )
        {
            if ( reader.strcmp( "newmtl") )
            {
                reader.skip( "newmtl\b \n" );
                reader.read( temp, 128, " \n\t\r" );
                reader.skip( " \n\t\r" );
                
                mtl = new OBJMtl;
                materials.add( temp, mtl );
            }
            
            else if ( reader.strcmp( "Ka ") )
            {
                GetColor( mtl->ka.data, reader );
                reader.seek( " " );
                reader.skip( " \n\t\r" );
            }
            
            else if ( reader.strcmp( "Kd ") )
            {
                GetColor( mtl->kd.data, reader );
                reader.seek( " " );
                reader.skip( " \n\t\r" );
            }
            
            else if ( reader.strcmp( "Ks ") )
            {
                GetColor( mtl->ks.data, reader );
                reader.seek( " " );
                reader.skip( " \n\t\r" );
            }
            
            else if ( reader.strcmp( "ns ") )
            {
                mtl->ns = GetFloat( reader, temp, 32 );
            }
            else if ( reader.strcmp( "illum ") )
            {
                mtl->illum = GetFloat( reader, temp, 32 );
            }
            else if ( reader.strcmp( "d ") )
            {
                mtl->d = GetFloat( reader, temp, 32 );
            }
            
            else if ( reader.strcmp( "map_Ka ") )
            {
                mtl->map_Ka = path + GetFilename( reader, temp, 128 );
            }
            else if ( reader.strcmp( "map_Kd ") )
            {
                mtl->map_Kd = path + GetFilename( reader, temp, 128 );
            }
            
            else if ( reader.strcmp( "map_Ks ") )
            {
                mtl->map_Ks = path + GetFilename( reader, temp, 128 );
            }
            
            else if ( reader.strcmp( "map_Ns ") )
            {
                mtl->map_Ns = path + GetFilename( reader, temp, 128 );
            }
            
            else if ( reader.strcmp( "map_d ") )
            {
                mtl->map_d = path + GetFilename( reader, temp, 128 );
            }
        }
        return true;
    }
    
    void ReadVertexData(ds::slist<cg::point3>& vp, kege::BufferReader& reader, const char* flags)
    {
        char data[3][64];
        int m,n;
        while ( reader.strcmp( flags ) )
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
    void GetVertexBufferData( ds::slist<cg::point3>& vp, ds::slist<cg::point3>& vn, ds::slist<cg::point3>& vt, kege::BufferReader& reader )
    {
        while ( reader.strcmp("v ") || reader.strcmp("vt") || reader.strcmp("vn") )
        {
            if ( reader.strcmp("v ") )
            {
                ReadVertexData(vp, reader, "v ");
            }
            if ( reader.strcmp("vt") )
            {
                ReadVertexData(vt, reader, "vt");
            }
            if ( reader.strcmp("vn") )
            {
                ReadVertexData(vn, reader, "vn");
            }
        }
    }
    
    ds::string GetMtlName( kege::BufferReader& reader, char* temp  )
    {
        reader.skip("usemtl\b ");
        reader.read(temp, 512, "\n");
        reader.skip(" \n\t\r");
        return  temp;
    }
    
    void GetIndexBufferData( ds::slist< OBJFaceGroup >& face_groups, kege::BufferReader& reader  )
    {
        ds::string usemtl;
        char temp[ 128 ];
        
        while ( !reader.eof() )
        {
            if ( reader.strcmp("usemtl") )
            {
                usemtl = GetMtlName( reader, temp );
            }
            else if ( reader.strcmp("f ") )
            {
                unsigned int count = 0;
                ds::slist< cg::uint > indices;
                while (reader.strcmp("f ") && !reader.eof())
                {
                    reader.skip("f ");
                    while ( !reader.strcmp("\n") )
                    {
                        count = 0;
                        while ( !reader.chrcmp(" \n") )
                        {
                            reader.read( temp, 64, " /f\n" );
                            indices.push_back( atoi( temp ) - 1 );
                            reader.skip("/");
                            count++;
                        }
                        reader.skip(" ");
                    }
                    reader.skip(" \n\t\r");
                }
                // copy vertex indices
                if ( indices.count() )
                {
                    OBJFaceGroup& face_group = face_groups.push_back();
                    face_group.usemtl = usemtl;
                    usemtl.clear();
                    
                    face_group.indices.setbuffer( indices.count(), 1, 0 );
                    for (ds::slist< cg::uint >::iterator i=indices.begin(); i!=nullptr; i++)
                    {
                        face_group.indices.add( i.element() );
                    }
                }
            }
            else if ( reader.strcmp("g ") || reader.strcmp("s ") || reader.strcmp("l ") )
            {
                reader.seek("\n");
                reader.skip("\n");
            }
            else
            {
                break;
            }
        }
    }
    
    const char * PaserName(const char*& curr_line, char* temp)
    {
        curr_line = kege::str_next(curr_line, " ");
        curr_line = kege::str_skip(curr_line, " ");
        kege::str_cpyf(temp, curr_line, "\n ");
        curr_line = kege::str_next(curr_line, "\n");
        curr_line = kege::str_skip(curr_line, " \n");
        return temp;
    }
    
    void OBJParseData( ds::queue< ds::string >& obj_names, ds::slist< OBJFaceGroup >& face_groups, OBJVertexData& vertex_data, ds::string& mtllib, kege::BufferReader& reader )
    {
        char temp[ 256 ];
        ds::slist< cg::point3 > vp;
        ds::slist< cg::point3 > vn;
        ds::slist< cg::point3 > vt;
        
        while (!reader.eof())
        {
            if (reader.strcmp("# "))
            {
                reader.seek("\n");
                reader.skip("\n");
            }
            else if (reader.strcmp("o "))
            {
                reader.skip("o \n\t\r");
                reader.read(temp, 512, "\n");
                reader.skip(" \n\t\r");
                obj_names.push( temp );
            }
            else if (reader.strcmp("mtllib"))
            {
                /* parse material library name */
                reader.skip("mtllib\b ");
                reader.read(temp, 512, "\n");
                reader.skip(" \n\t\r");
                mtllib = temp;
            }
            else if ( reader.strcmp("v ") || reader.strcmp("vt") || reader.strcmp("vn") )
            {
                GetVertexBufferData( vp, vn, vt, reader );
            }
            else if ( reader.strcmp("usemtl") || reader.strcmp("f ") )
            {
                GetIndexBufferData( face_groups, reader  );
            }
            else
            {
                reader.seek("\n");
                reader.skip("\n");
            }
        }
        
        // copy vertex position to vertex array
        if ( vp.count() )
        {
            vertex_data.vp.setbuffer( 3 * vp.count(), 3, 0 );
            for (ds::slist< cg::point3 >::iterator i=vp.begin(); i!=nullptr; i++)
            {
                vertex_data.vp.add3( i.element() );
            }
        }
        // copy vertex normal to vertex array
        if ( vn.count() )
        {
            vertex_data.vn.setbuffer( 3 * vn.count(), 3, 0 );
            for (ds::slist< cg::point3 >::iterator i=vn.begin(); i!=nullptr; i++)
            {
                vertex_data.vn.add3( i.element() );
            }
        }
        // copy vertex texcoord to vertex array
        if ( vt.count() )
        {
            vertex_data.vt.setbuffer(2 * vt.count(), 2, 0);
            for (ds::slist< cg::point3 >::iterator i=vt.begin(); i!=nullptr; i++)
            {
                vertex_data.vt.add2( i.element().xy );
            }
        }
    }
    
    bool OBJParseData( ds::queue< ds::string >& obj_names, ds::slist< OBJFaceGroup >& face_groups, OBJVertexData& vertex_data, ds::string& mtllib, const ds::string& filename )
    {
        kege::VFS::File file = kege::VFS::GetInstance().OpenFile( filename );
        if ( file.file != nullptr)
        {
            kege::BufferReader reader = file;
            OBJParseData( obj_names, face_groups, vertex_data, mtllib, reader );
            //ds::string path = file.filename.parse_fpath();
            //mtllib = path + mtllib;
            return true;
        }
        return false;
    }
}



namespace kege{
    
    void GetVertexIndices( core::IndexBuffer& index_buffer, const core::DataBuffer< cg::uint >& indices )
    {
        index_buffer.setbuffer(indices.count(), 1, 0);
        for ( int u=0; u<indices.size(); u++ )
        {
            index_buffer.add( *indices[ u ] );
        }
    }
    
    const cg::uint* GetMeshIndex( short index,  const core::DataBuffer< cg::uint >& indices )
    {
        for ( int u=0; u<indices.size(); u++ )
        {
            if ( *indices[ u ] == index)
            {
                return indices[ u ];
            }
        }
        return 0;
    }
    
    int SetVertexAttributes( core::VertexLayout* layout, const core::DataBuffer<float>& vp, const core::DataBuffer<float>& vn, const core::DataBuffer<float>& vt )
    {
        int stride = 0;
        if (vp.size())
        {
            layout->AddElem(core::VERTEX_POSITION, 3, stride);
            stride += 3;
        }
        if (vn.size())
        {
            layout->AddElem(core::VERTEX_NORMAL,   3, stride);
            stride += 3;
        }
        if (vt.size())
        {
            layout->AddElem(core::VERTEX_TEXCOORD, 2, stride);
            stride += 2;
        }
        return stride;
    }

    shared::Geometry OBJBuildMesh( const OBJFaceGroup& face_group, const OBJVertexData& vertex_data )
    {
        core::VertexBuffer* vp = new core::VertexBuffer;
        core::IndexBuffer*  ib = new core::IndexBuffer;
        core::VertexLayout* vl = &vp->GetVertexLayout();

        cg::uint vertice = (cg::uint) vertex_data.vp.count() / 3;
        cg::uint stride  = SetVertexAttributes( vl, vertex_data.vp, vertex_data.vn, vertex_data.vt );
        vp->setbuffer(stride * vertice, stride, 0);
        
        const cg::uint* index;
        const float* v = nullptr;
        unsigned int i;
        unsigned int vindex;
        unsigned int n=0;
        
        unsigned int n_offset = 1;
        unsigned int t_offset = 1;
        
        if ( vertex_data.vp.size() ) n++;
        if ( vertex_data.vt.size() ) t_offset = n++;
        if ( vertex_data.vn.size() ) n_offset = n++;
        
        cg::point3 center_of_mass = 0.0;
        cg::point3 max =-60000.0;
        cg::point3 min = 60000.0;
        
        GetVertexIndices( *ib, face_group.indices );
        
        for (vindex=0; vindex<vertice; vindex++)
        {
            index = GetMeshIndex( vindex, face_group.indices );
            
            i = vindex * 3;
            v = vertex_data.vp[ i ];
            vp->add3( v[ 0 ], v[ 1 ], v[ 2 ] );
            
            max.x = cg::max(max.x, v[ 0 ]);
            max.y = cg::max(max.y, v[ 1 ]);
            max.z = cg::max(max.z, v[ 2 ]);
            
            min.x = cg::min(min.x, v[ 0 ]);
            min.y = cg::min(min.y, v[ 1 ]);
            min.z = cg::min(min.z, v[ 2 ]);
            
            center_of_mass.x += v[ 0 ];
            center_of_mass.y += v[ 1 ];
            center_of_mass.z += v[ 2 ];
            
            n = 1;
            
            if( vertex_data.vt.count() )
            {
                i = index[ n++ ] * 2;
                v = vertex_data.vt[ i ];
                vp->add2(v[ 0 ], v[ 1 ]);
            }
            
            if( vertex_data.vn.count() )
            {
                i = index[ n++ ] * 3;
                v = vertex_data.vn[ i ];
                vp->add3(v[ 0 ], v[ 1 ], v[ 2 ]);
            }
        }
        
        //double mass_total = cg::invrs( face_group.indices.count() );
        //center_of_mass *= mass_total;
        //mesh.SetCenterPoint(center_of_mass);
        //mesh.SetMinPoint(min);
        //mesh.SetMaxPoint(max);
        return new gfx::Geometry( vp, ib );
    }
    
    bool OBJLoadGeometies( ds::array< shared::Geometry >& geometries, const ds::string& filename )
    {
        ds::slist< OBJFaceGroup > face_groups;
        ds::queue< ds::string > obj_names;
        OBJVertexData vertex_data;
        ds::string mtllib;
        
        if ( OBJParseData( obj_names, face_groups, vertex_data, mtllib, filename ) )
        {
            if ( face_groups.count() > 1 )
            {
                int n = 0;
                geometries.resize( face_groups.count() );
                for (ds::slist< OBJFaceGroup >::iterator obj=face_groups.begin(); obj!=nullptr; obj++)
                {
                    geometries[ n++ ] = OBJBuildMesh( obj.element(), vertex_data );
                }
            }
            else
            {
                geometries.resize( 1 );
                geometries[ 0 ] = OBJBuildMesh( face_groups.first(), vertex_data );
            }
            return true;
        }
        return false;
    }
}
