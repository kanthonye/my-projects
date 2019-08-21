//======================================================================
//  Author  : Kenneth A Esdaile
//  Date    : Created on 10/7/17.
//  Title   : ColladaAnimations.hpp
//  Project : KEGE
//======================================================================
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//======================================================================
#include "queue.hpp"
#include "Collada.hpp"
#include "ObjectMaterial.hpp"
#include "ColladaGeometries.hpp"
#include "ColladaControllers.hpp"
namespace kege{namespace dae{
    
    void ColladaControllers::AttachSkeletalBonesToJoints(gfx::Joint* hierarchy, gfx::Skeleton* skeleton, kege::XML* skin)
    {
        // get the collada controller bones to link them with there paired joints
        core::DataBuffer<ds::string> joints = GetJoints(skin);
        
        // get the collada controller inverse bones matrix list.
        core::DataBuffer<float> inv_binds = GetInverseBindMatrices(skin);
        cg::mat44* inv = (cg::mat44*) inv_binds.getdata();
        
        // bones are the joints that is attached to the mesh.
        // note: not all joints from the hierarchy will affect the mesh
        // only these bones will.
        gfx::Bones& bones = skeleton->GetBones();
        bones.resize(joints.size());
        
        for (int i=0; i<bones.size(); i++)
        {
            bones[i].joint  = skeleton->GetJoint(*joints[i]);
            bones[i].inv_bind = cg::transpose(inv[i]);
        }
    }
    
    void ColladaControllers::SetupSkeletalJointmap(gfx::Joint* hierarchy, gfx::Skeleton* skeleton)
    {
        // get the skeleton joint map
        gfx::JointMap& joint_map  = skeleton->GetJointMap();
        // setup joint map.
        ds::queue<gfx::Joint*> que(hierarchy);
        while (!que.empty())
        {
            gfx::Joint* s = que.top();
            long k = s->name.hash();
            que.pop();
            
            joint_map[k] = s;
            
            for(ds::slist<gfx::Joint*>::iterator u=s->children.begin(); u!=nullptr; u++)
                que.push(u.element());
        }
    }
    
    shared::Skeleton ColladaControllers::BuildSkeleton(kege::XML* instance, dae::ColladaVisualScenes& scenes)
    {
        ds::string url = RemoveHashtag(instance->GetAttr("url")->value);
        ds::string sid = instance->GetChild("skeleton")->GetText();
        
        kege::XML* controller = GetController(url);
        kege::XML* skin = GetSkin(controller);
        
        // get the skeleton hierarchy of joints
        gfx::Joint* hierarchy = scenes.GetHierarchy(scenes.GetJointNode(sid));
        gfx::Skeleton* skeleton = new gfx::Skeleton;
        skeleton->joints = hierarchy;
        //skeleton->AddChild(hierarchy);
        
        SetupSkeletalJointmap(hierarchy, skeleton);
        AttachSkeletalBonesToJoints(hierarchy, skeleton, skin);
        return shared::Skeleton(skeleton);
    }
    
    shared::Mesh ColladaControllers::InstanceController(const ds::string& id, dae::ColladaGeometries geometries)
    {
        kege::XML* controller = GetController(id);
        kege::XML* skin = GetSkin(controller);
        
        core::DataBuffer< float > vw,vj;
        GetVertexWeights(vw, vj, skin);
        
        shared::Geometry geometry = geometries.ContructGeometry( skin->GetAttr("source")->value, vw, vj );
        cg::uint draw_count = (cg::uint) geometry->GetIndexBuffer()->size();
        
        shared::DrawElement dmatl = new gfx::DrawElement( core::DRAW_TRIANGLES, 0, draw_count, new gfx::ObjectMaterial() );
        return shared::Mesh( new gfx::Mesh( geometry, dmatl ) );
    }
    
    void InsertionSortMinMax(float* a, int size)
    {
        float b;
        int j,i=1;
        while (i<size)
        {
            j = i;
            if (a[j] < a[j-1])
            {
                b = a[j];
                while (b < a[j-1] && j > 0)
                {
                    a[j] = a[j-1];
                    j--;
                }
                a[j] = b;
            }
            i++;
        }
    }
    
    void InsertionSortMaxMin(float* w, float* j, int size)
    {
        float a,b;
        int l,i=1;
        while (i<size)
        {
            l = i;
            if (w[l] > w[l-1])
            {
                a = w[l];
                b = j[l];
                while (a > w[l-1] && l > 0)
                {
                    w[l] = w[l-1];
                    j[l] = j[l-1];
                    l--;
                }
                w[l] = a;
                j[l] = b;
            }
            i++;
        }
    }
    
    void ColladaControllers::GetVertexWeights(core::DataBuffer<float>& vw, core::DataBuffer<float>& vj, kege::XML* skin)
    {
        kege::XML* vertex_weights = skin->GetChild("vertex_weights");
        if (vertex_weights == nullptr) throw "[error] : null element <vertex_weights>.";
        
    
        kege::XML inputs;
        vertex_weights->PopulateByTag(inputs, "input");
        
        kege::XML* joint_input = inputs.GetChildByAttr("semantic", "JOINT");
        kege::XML* weights_input = inputs.GetChildByAttr("semantic", "WEIGHT");
        
        core::DataBuffer<cg::uint> vcount, v;
        ToPolygonBuffers(vcount, v, vertex_weights);
        
        short join_offset = GetInputOffset(joint_input);
        short weig_offset = GetInputOffset(weights_input);
        kege::XML* weights_source = GetInputSource(skin, weights_input);
        core::DataBuffer<float> weights = ToVertexBuffer(weights_source);

        const int influence = 4;
        vw.setsize(vcount.size() * influence);
        vj.setsize(vcount.size() * influence);
        vw.setstride(influence);
        vj.setstride(influence);
        
        long start = 0;
        long end = 0;
        int count = 0;
        int stride;
        long index = 0;
        long m,n;
        
        const int length = 10;
        float vert[2][length];
        float sum;
        const int total_input = 2;
        for (long vertex=0; vertex<vcount.size(); vertex++)
        {
            stride = *vcount[vertex];
            start  = end;
            end   += total_input * stride;
            
            count = 0;
            for (index=start; index<end; index+=total_input)
            {
                m = *v[index + weig_offset];
                n = *v[index + join_offset];
                vert[0][count] = n;
                vert[1][count] = *weights[ m ];
                count++;
            }
            
            // in some cases the vertex influence can be lessthan than the influence
            // you want. in this case zero the rest of the influence
            while (count < influence)
            {
                vert[0][count] = 0;
                vert[1][count] = 0;
                count++;
            }
            
            // in some cases the vertex influence can be greater than the influence
            // you want. in this case take the largest influences and normalize them
            if (stride > influence)
            {
                InsertionSortMaxMin(vert[1], vert[0], stride);
            }
            
            // the sum of each influence must be equal to one if the sume
            // is not equal to one then the influence must be normalize
            sum = 0;
            for (m=0; m<influence; m++) sum += vert[1][m];
            if (sum != 1.0)
            {
                sum = (sum == 0) ? 1.0 : 1.0 / sum;
                for (m=0; m<influence; m++) vert[1][m] *= sum;
            }
            
            for (m=0; m<influence; m++)
            {
                vj.add(vert[0][m]);
                vw.add(vert[1][m]);
            }
        }
    }
    
    core::DataBuffer<ds::string> ColladaControllers::GetJoints(kege::XML* skin)
    {
        kege::XML* source = GetInputSource(skin, GetJointInput(skin));
        
        kege::XML* name_array = source->GetChild("Name_array");
        if (name_array == nullptr) throw "[error] : null element <name_array>.";
        
        kege::XML::attrib* x_size = name_array->GetAttr("count");
        if (x_size == nullptr) throw "[error] : null arrtib 'count'.";
        
        kege::XML* accessor = source->GetChild("/technique_common/accessor");
        if (accessor == nullptr) throw "[error] : null element <acessor>.";
        
        kege::XML::attrib* x_stride = accessor->GetAttr("stride");
        if (x_stride == nullptr) throw "[error] : null attrib 'stride'.";
        
        kege::XML::attrib* x_count = accessor->GetAttr("count");
        if (x_count == nullptr) throw "[error] : null attrib 'count'.";
        
        long stride = x_stride->ToInt();
        //long count = x_count->ToInt();
        long size = x_size->ToInt();
        
        ds::string* na = new ds::string[size];
        
        
        char* data = strtok(name_array->GetText().getdata(), " \n\t\r");
        cg::uint num = 0;
        while (data != nullptr && size >= num)
        {
            na[num++] = data;
            data = strtok(nullptr, " \n\t\r");
        }
        return core::DataBuffer<ds::string>((int)stride, (int)size, na);
    }
    
    core::DataBuffer<float> ColladaControllers::GetInverseBindMatrices(kege::XML* skin)
    {
        kege::XML* source = GetInputSource(skin, GetInverseBindMatrixInput(skin));
        return ToVertexBuffer(source);
    }
    
    cg::mat44 ColladaControllers::GetBindShapeMatrix(kege::XML* skin)
    {
        cg::mat44 m;
        kege::XML* matrix = skin->GetChild("bind_shape_matrix");
        if (matrix == nullptr) throw "[error] : null element <bind_shape_matrix>.";
        StringToFloats(m.data, 16, matrix->GetText());
        return m;
    }
    
    kege::XML* ColladaControllers::GetInputSource(kege::XML* skin, kege::XML* input)
    {
        if (input == nullptr || skin == nullptr) return nullptr;
        kege::XML::attrib* source = input->GetAttr("source");
        return skin->GetChildByAttr("id", RemoveHashtag(source->value));
    }
    
    kege::XML* ColladaControllers::GetInverseBindMatrixInput(kege::XML* skin)
    {
        kege::XML* joints = skin->GetChild("joints");
        if (joints == nullptr) return nullptr;
        
        joints = joints->GetChildByAttr("semantic", "INV_BIND_MATRIX");
        if (joints == nullptr) return nullptr;
        
        return joints;
    }
    
    kege::XML* ColladaControllers::GetController(const ds::string& id)
    {
        return controllers->GetChildByAttr("id", RemoveHashtag(id));
    }
    
    kege::XML* ColladaControllers::GetJointInput(kege::XML* skin)
    {
        kege::XML* joints = skin->GetChild("joints");
        if (joints == nullptr) return nullptr;
        
        joints = joints->GetChildByAttr("semantic", "JOINT");
        if (joints == nullptr) return nullptr;
        
        return joints;
    }
    
    kege::XML* ColladaControllers::GetSkin(kege::XML* controller)
    {
        return controller->GetChild("skin");
    }
}}
