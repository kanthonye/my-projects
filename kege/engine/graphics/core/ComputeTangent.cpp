//
//  ComputeTangent.cpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/19/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//
#include "Mesh.hpp"
#include "ComputeTangent.hpp"
namespace kege{namespace gfx{

    void ComputeTangent(gfx::Mesh& rmesh)
    {
        // vertex position and vertex texcoord is necessary to compute vertex tangent
        const int poffset = rmesh.GetVertexBuffer().GetVertexLayout().GetElem(VERTEX_POSITION).offset;
        const int toffset = rmesh.GetVertexBuffer().GetVertexLayout().GetElem(VERTEX_TEXCOORD).offset;
        // id both vertex position and vertex texcoord is not available, tangents can not be computed
        if (poffset < 0 || toffset < 0) return;
        // resize our vertex buffer to include tangent->xyz
        const long count = rmesh.GetVertexBuffer().count();
        const int stride = rmesh.GetVertexBuffer().getstride();
        rmesh.GetVertexBuffer().resize(stride+3 * count);
        rmesh.GetVertexBuffer().setstride(stride+3);
        const int tang_offset = stride;
        
        rmesh.GetVertexBuffer().GetVertexLayout().AddElem(VERTEX_TANGENT, 3, tang_offset);
        const int newstride = rmesh.GetVertexBuffer().getstride();
        gfx::DataBuffer<cg::uint>& indices = rmesh.GetIndexBuffer();
        if (indices.count() == 0) return;
        
        float* bufr = rmesh.GetVertexBuffer().getdata();
        
        double r;
        int i,a,b,c;
        cg::vec2 vt[3];
        cg::vec3 vp[3];
        cg::vec3 tangent;
        cg::vec3 bitangent;
        cg::vec3 vp_edge[2];
        cg::vec2 vt_edge[2];
        
        int tang_x = 0;
        int tang_y = 0;
        int tang_z = 0;
        
        for (i = 0; i<indices.count(); i+=3)
        {
            a = indices.get( i ) * newstride;
            b = indices.get(i+1) * newstride;
            c = indices.get(i+2) * newstride;
            
            // vertex position 0
            vp[0].x = bufr[poffset + a];
            vp[0].y = bufr[poffset + a+1];
            vp[0].z = bufr[poffset + a+2];
            // vertex position 1
            vp[1].x = bufr[poffset + b];
            vp[1].y = bufr[poffset + b+1];
            vp[1].z = bufr[poffset + b+2];
            // vertex position 2
            vp[2].x = bufr[poffset + c];
            vp[2].y = bufr[poffset + c+1];
            vp[2].z = bufr[poffset + c+2];
            
            // texture coord 0
            vt[0].x = bufr[toffset + a];
            vt[0].y = bufr[toffset + a+1];
            // texture coord 1
            vt[1].x = bufr[toffset + b];
            vt[1].y = bufr[toffset + b+1];
            // texture coord 2
            vt[2].x = bufr[toffset + c];
            vt[2].y = bufr[toffset + c+1];
            
            // vertex edges 0 and 1
            vp_edge[0] = vp[0] - vp[1];
            vp_edge[1] = vp[2] - vp[1];
            
            // texture coord egdes 0 and 1
            vt_edge[0] = vt[0] - vt[1];
            vt_edge[1] = vt[2] - vt[1];
            
            r = (vt_edge[0].x * vt_edge[1].y - vt_edge[0].y * vt_edge[1].x);
            r = 1.0 / ((r == 0.0) ? 1.0 : r);
            // tangent at vertex index 0, 1 and 2
            tangent = (vp_edge[0] * vt_edge[1].y - vp_edge[1] * vt_edge[0].y) * r;
            //bitangent = (vertex_edge[1] * uvcord_edge[0].x - vertex_edge[0] * uvcord_edge[1].x)*r;
            
            tang_x = tang_offset;
            tang_y = tang_offset+1;
            tang_z = tang_offset+2;
            
            // store each tangents to later computer the average final tangent
            bufr[a+tang_x] += tangent.x;
            bufr[a+tang_y] += tangent.y;
            bufr[a+tang_z] += tangent.z;
            
            bufr[b+tang_x] += tangent.x;
            bufr[b+tang_y] += tangent.y;
            bufr[b+tang_z] += tangent.z;
            
            bufr[c+tang_x] += tangent.x;
            bufr[c+tang_y] += tangent.y;
            bufr[c+tang_z] += tangent.z;
        }
        // normalize the tangents
        for (i = 0; i <count; i++)
        {
            a = i * newstride + tang_offset;
            
            tang_x = a;
            tang_y = a + 1;
            tang_z = a + 2;
            
            r  = cg::sq(bufr[tang_x]);
            r += cg::sq(bufr[tang_y]);
            r += cg::sq(bufr[tang_z]);
            r  = cg::invrs(sqrt(r));
            
            bufr[tang_x] *= r;
            bufr[tang_y] *= r;
            bufr[tang_z] *= r;
        }
    }
    
    void ComputeTangentNonIndex(gfx::Mesh& rmesh)
    {
        const int poffset = rmesh.GetVertexBuffer().GetVertexLayout().GetElem(VERTEX_POSITION).offset;
        const int toffset = rmesh.GetVertexBuffer().GetVertexLayout().GetElem(VERTEX_TEXCOORD).offset;
        if (poffset < 0 || toffset < 0) return;
        
        const long count    = rmesh.GetVertexBuffer().count();
        const int minstride = rmesh.GetVertexBuffer().getstride();
        const int maxstride = minstride+3;
        rmesh.GetVertexBuffer().GetVertexLayout().AddElem(VERTEX_TANGENT, 3, minstride);
        rmesh.GetVertexBuffer().resize(maxstride * count);
        rmesh.GetVertexBuffer().setstride(maxstride);
        float* bufr = rmesh.GetVertexBuffer().getdata();
        
        double r;
        int i,a,b,c;
        cg::vec2 vt[3];
        cg::vec3 vp[3];
        cg::vec3 tangent;
        cg::vec3 bitangent;
        cg::vec3 vp_edge[2];
        cg::vec2 vt_edge[2];
        
        for (i = 0; i<count; i+=3)
        {
            a = i*maxstride;
            b = a+maxstride;
            c = b+maxstride;
            // vertex position 0
            vp[0].x = bufr[poffset + a];
            vp[0].y = bufr[poffset + a+1];
            vp[0].z = bufr[poffset + a+2];
            // vertex position 1
            vp[1].x = bufr[poffset + b];
            vp[1].y = bufr[poffset + b+1];
            vp[1].z = bufr[poffset + b+2];
            // vertex position 2
            vp[2].x = bufr[poffset + c];
            vp[2].y = bufr[poffset + c+1];
            vp[2].z = bufr[poffset + c+2];
            // vertex edges 0 and 1
            vp_edge[0] = vp[0] - vp[1];
            vp_edge[1] = vp[2] - vp[1];
            // texture coord 0
            vt[0].x = bufr[toffset + a];
            vt[0].y = bufr[toffset + a+1];
            // texture coord 1
            vt[1].x = bufr[toffset + b];
            vt[1].y = bufr[toffset + b+1];
            // texture coord 2
            vt[2].x = bufr[toffset + c];
            vt[2].y = bufr[toffset + c+1];
            // texture coord egdes 0 and 1
            vt_edge[0] = vt[0] - vt[1];
            vt_edge[1] = vt[2] - vt[1];
            
            r = (vt_edge[0].x * vt_edge[1].y - vt_edge[0].y * vt_edge[1].x);
            r = 1.0 / ((r == 0.0) ? 1.0 : r);
            // tangent at vertex index 0, 1 and 2
            tangent = (vp_edge[0] * vt_edge[1].y - vp_edge[1] * vt_edge[0].y) * r;
            //bitangent = (vertex_edge[1] * uvcord_edge[0].x - vertex_edge[0] * uvcord_edge[1].x)*r;
            
            // store each tangents to later computer the average final tangent
            bufr[a + minstride] += tangent.x;
            bufr[a+minstride+1] += tangent.y;
            bufr[a+minstride+2] += tangent.z;
            
            bufr[b + minstride] += tangent.x;
            bufr[b+minstride+1] += tangent.y;
            bufr[b+minstride+2] += tangent.z;
            
            bufr[c + minstride] += tangent.x;
            bufr[c+minstride+1] += tangent.y;
            bufr[c+minstride+2] += tangent.z;
        }
        // normalize the tangents
        for (i = 0; i <count; i++)
        {
            a = i * maxstride + minstride;
            r = cg::sq(bufr[a]) + cg::sq(bufr[a+1]) + cg::sq(bufr[a+2]);
            r = sqrt(r);
            r = 1.0 / ((r == 0.0) ? 1.0 : r);
            bufr[ a ] *= r;
            bufr[a+1] *= r;
            bufr[a+2] *= r;
            
            //printf("%f %f %f\n",bufr[a],bufr[a+1],bufr[a+2]);
        }
    }
}}
