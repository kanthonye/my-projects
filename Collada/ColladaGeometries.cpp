//======================================================================
//  Author  : Kenneth A Esdaile
//  Date    : Created on 4/14/19.
//  Title   : ColladaGeometries.hpp
//  Project : KEGE
//======================================================================
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//======================================================================
#include "Collada.hpp"
#include "ColladaGeometries.hpp"
namespace kege{namespace dae{
    
    void BuildMeshIndexBuffer(gfx::IndexBuffer& output, const gfx::IndexBuffer& input, short offset, short total_input)
    {
        long size = input.size() / total_input;
        output.setsize(size);
        output.setcount(0);
        output.setstride(1);
        for (int i=0; i<input.size(); i+=total_input)
        {
            output.add( *input[i + offset] );
        }
    }
    
    long GetMeshIndex(short index, short offset, short total_input, const gfx::IndexBuffer& indices)
    {
        for (long i=0; i<indices.size(); i+=total_input)
        {
            if (*indices[i + offset] == index)
            {
                return i;
            }
        }
        return 0;
    }

    void ContructGeometry
    (   gfx::RawMesh& mesh
     ,  const gfx::IndexBuffer&  vcount
     ,  const gfx::IndexBuffer&  vi, short total_input
     ,  const gfx::VertexBuffer& vp, short posi_offset
     ,  const gfx::VertexBuffer& vn, short norm_offset
     ,  const gfx::VertexBuffer& vt, short texr_offset
     ,  const gfx::VertexBuffer& vc, short colr_offset
     ,  const gfx::VertexBuffer& vw
     ,  const gfx::VertexBuffer& vj )
    {
        gfx::VertexBuffer& vbo = mesh.GetVertexBuffer();
        cg::vec3 min(60000.0);
        cg::vec3 max(-60000.0);
        cg::vec3 cen(0.0);
        
        cg::uint stride = 0;
        cg::uint vn_offset = 0;
        cg::uint vt_offset = 0;
        cg::uint vw_offset = 0;
        cg::uint vj_offset = 0;
        cg::uint vc_offset = 0;
        
        if (!vp.empty())
        {
            vbo.AddVertexInfo(gfx::VERTEX_POSITION, vp.getstride(), stride);
            stride += vp.getstride();
        }
        if (!vn.empty())
        {
            vbo.AddVertexInfo(gfx::VERTEX_NORMAL, vn.getstride(), stride);
            vn_offset = stride;
            stride += vp.getstride();
        }
        if (!vt.empty())
        {
            vbo.AddVertexInfo(gfx::VERTEX_TEXCOORD, vt.getstride(), stride);
            vt_offset = stride;
            stride += vt.getstride();
        }
        if (!vw.empty())
        {
            vbo.AddVertexInfo(gfx::VERTEX_WEIGHT, vw.getstride(), stride);
            vw_offset = stride;
            stride += vw.getstride();
        }
        if (!vj.empty())
        {
            vbo.AddVertexInfo(gfx::VERTEX_JOINT, vp.getstride(), stride);
            vj_offset = stride;
            stride += vj.getstride();
        }
        if (!vc.empty())
        {
            vbo.AddVertexInfo(gfx::VERTEX_COLOR, vp.getstride(), stride);
            vc_offset = stride;
            stride += vc.getstride();
        }
        
        BuildMeshIndexBuffer(mesh.GetIndexBuffer(), vi, posi_offset, total_input);
        
        vbo.setsize(stride * vp.count());
        vbo.setcount(vp.count());
        vbo.setstride(stride);
        
        long element, index, m, n;//, vertex = 0;
        cg::uint k = 0;
        for (int vertex=0; vertex<vp.count(); vertex++)
        {
            element = vertex * stride;
            m = element + posi_offset;
            n = vertex * vp.getstride();
            
            *vbo[ m ] = *vp[ n ];
            *vbo[m+1] = *vp[n+1];
            *vbo[m+2] = *vp[n+2];
            
            if (min.x < *vbo[ n ]) min.x = *vbo[ n ];
            if (min.y < *vbo[n+1]) min.y = *vbo[n+1];
            if (min.z < *vbo[n+2]) min.z = *vbo[n+2];
            if (max.x < *vbo[ n ]) max.x = *vbo[ n ];
            if (max.y < *vbo[n+1]) max.y = *vbo[n+1];
            if (max.z < *vbo[n+2]) max.z = *vbo[n+2];
            cen.x += *vbo[ n ];
            cen.y += *vbo[n+1];
            cen.z += *vbo[n+2];
            
            index = GetMeshIndex(vertex, posi_offset, total_input, vi);
            
            if (!vn.empty())
            {
                m = element + vn_offset;
                n = *vi[index + norm_offset] * vn.getstride();
                for (k=0; k<vn.getstride(); k++) *vbo[m+k] = *vn[n+k];
            }
            if (!vt.empty())
            {
                m = element + vt_offset;
                n = *vi[index + texr_offset] * vt.getstride();
                for (k=0; k<vt.getstride(); k++) *vbo[m+k] = *vt[n+k];
            }
            if (!vc.empty())
            {
                m = element + vc_offset;
                n = *vi[index + colr_offset] * vc.getstride();
                for (k=0; k<vc.getstride(); k++) *vbo[m+k] = *vc[n+k];
            }
            
            if (!vw.empty())
            {
                m = element + vw_offset;
                n = vertex * vw.getstride();
                for (k=0; k<vw.getstride(); k++) *vbo[m+k] = *vw[n+k];
            }
            if (!vj.empty())
            {
                m = element + vj_offset;
                n = vertex * vj.getstride();
                for (k=0; k<vj.getstride(); k++) *vbo[m+k] = *vj[n+k];
            }
        }
        
        cen.x /= vp.count();
        cen.y /= vp.count();
        cen.z /= vp.count();
        
        mesh.SetCenterPoint(cen);
        mesh.SetMaxPoint(max);
        mesh.SetMinPoint(min);
    }
    
    kege::XML* ColladaGeometries::GetPolylistInput(kege::XML* polylist, const ds::string& semantic)
    {
        return polylist->GetChildByAttr("semantic", semantic);
    }
    
    kege::XML* ColladaGeometries::GetMeshSource(kege::XML* mesh, const ds::string& id)
    {
        return mesh->GetChildByAttr("id", RemoveHashtag(id));
    }
    
    kege::XML* ColladaGeometries::GetMeshVertices(kege::XML* mesh)
    {
        kege::XML* input = mesh->GetChild("/vertices/input");
        return GetInputSource(mesh, input);
    }
    
    void ColladaGeometries::GetMeshPolylist(kege::XML::list& polylist, kege::XML* mesh)
    {
        for (kege::XML::iterator i=mesh->Begin(); i!=nullptr; i++)
        {
            if (i->GetName() == "polylist")
            {
                polylist.push_back(i.element());
            }
            else if (i->GetName() == "triangles")
            {
                polylist.push_back(i.element());
            }
            else if (i->GetName() == "lines")
            {
                polylist.push_back(i.element());
            }
            else if (i->GetName() == "points")
            {
                polylist.push_back(i.element());
            }
            else if (i->GetName() == "polygon")
            {
                polylist.push_back(i.element());
            }
        }
    }
    
    kege::XML* ColladaGeometries::GetMesh(const ds::string& id)
    {
        kege::XML* geometry = geometries->GetChildByAttr("id", RemoveHashtag(id));
        return geometry->GetChild("mesh");
    }
    
    
    kege::XML* ColladaGeometries::GetInputSource(kege::XML* mesh, kege::XML* input)
    {
        if (input == nullptr) return nullptr;
        kege::XML::attrib* source = input->GetAttr("source");
        return GetMeshSource(mesh, source->value);
    }
    
    gfx::Mesh ColladaGeometries::InstanceGeometry(const ds::string& id)
    {
        gfx::RawMesh* mesh = NewRawMesh(id);// new gfx::RawMesh;
        ContructGeometry(*mesh, id);
        return mesh;
    }
    
    void ColladaGeometries::ContructGeometry(gfx::RawMesh& mesh, const ds::string& id, gfx::VertexBuffer& vw, gfx::VertexBuffer& vj)
    {
        kege::XML* dae_mesh = GetMesh(id);
        if (dae_mesh == nullptr) throw "[error: nullptr] dae <mesh>";
        
        kege::XML::list polygons;
        GetMeshPolylist(polygons, dae_mesh);
        
        kege::XML* polylist = polygons.front();
        kege::XML* v_input = GetPolylistInput(polylist, "VERTEX");
        kege::XML* n_input = GetPolylistInput(polylist, "NORMAL");
        kege::XML* t_input = GetPolylistInput(polylist, "TEXCOORD");
        kege::XML* c_input = GetPolylistInput(polylist, "COLOR");
        
        int v_offset = GetInputOffset(v_input);
        int t_offset = GetInputOffset(t_input);
        int n_offset = GetInputOffset(n_input);
        int c_offset = GetInputOffset(c_input);
        int total_input = GetTotalInputs(polylist);
        
        kege::XML* vertices = GetMeshVertices(dae_mesh);
        kege::XML* normals = GetInputSource(dae_mesh, n_input);
        kege::XML* tcoords = GetInputSource(dae_mesh, t_input);
        kege::XML* colors = GetInputSource(dae_mesh, c_input);
        
        gfx::IndexBuffer v, vcount;
        ToPolygonBuffers(vcount, v, polylist);
        
        gfx::VertexBuffer vp = ToVertexBuffer(vertices);
        gfx::VertexBuffer vn = ToVertexBuffer(normals);
        gfx::VertexBuffer vt = ToVertexBuffer(tcoords);
        gfx::VertexBuffer vc = ToVertexBuffer(colors);
        dae::ContructGeometry(mesh, vcount, v, total_input, vp, v_offset, vn, n_offset, vt, t_offset, vc, c_offset, vw, vj);
    }
    
    void ColladaGeometries::ContructGeometry(gfx::RawMesh& mesh, const ds::string& id)
    {
        gfx::VertexBuffer vj, vw;
        ContructGeometry(mesh, id, vw, vj);
    }
}}
