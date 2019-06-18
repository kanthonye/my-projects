//======================================================================
//  Author  : Kenneth A Esdaile
//  Date    : Created on 4/14/19.
//  Title   : ColladaVisualScenes.cpp
//  Project : KEGE
//======================================================================
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//======================================================================
#include "ColladaVisualScenes.hpp"
namespace kege{namespace dae{
    
    kege::XML* ColladaVisualScenes::GetJointNode(const ds::string& id)
    {
        kege::XML* visual_scene = library->GetChild("visual_scene");
        if (visual_scene == nullptr)
        {
            return nullptr;
        }
        
        ds::queue<kege::XML*> queue(visual_scene);
        kege::XML* joint = nullptr;
        while (!queue.empty())
        {
            joint = queue.pop();
            kege::XML::attrib* b = joint->GetAttr("type");
            
            if (b != nullptr)
            {
                if (b->value == "JOINT")
                {
                    break;
                }
            }
            
            for (kege::XML::iterator n=joint->Begin(); n!=nullptr; n++)
            {
                if (n->GetName() == "node")
                {
                    queue.push(n.element());
                }
            }
        }
        return joint;
    }
    
    gfx::Skeleton* ColladaVisualScenes::GetSkeleton(const ds::string& id)
    {
        gfx::Joint* hierarchy = GetHierarchy(GetJointNode(id));
        if (hierarchy != nullptr)
        {
            gfx::Skeleton* skeleton = new gfx::Skeleton;
            //skeleton->AddChild(hierarchy);
            skeleton->joints = hierarchy;
            return skeleton;
        }
        return nullptr;
    }
    
    gfx::Joint* ColladaVisualScenes::GetHierarchy(kege::XML* node)
    {
        if (node->GetName() != "node") return nullptr;
        
        kege::XML::attrib* type = node->GetAttr("type");
        kege::XML::attrib* id = node->GetAttr("id");
        
        if (type->value == "JOINT")
        {
            gfx::Joint* joint = new gfx::Joint(id->value);
            kege::XML* matrix = node->GetChild("matrix");
            if (matrix != nullptr)
            {
                joint->local = ToMatrix(matrix->GetText());
            }
            
            kege::XML nodes;
            node->PopulateByTag(nodes, "node");
            for (kege::XML::list::iterator n=nodes.Begin(); n!=nullptr; n++)
            {
                gfx::Joint* child = GetHierarchy(n.element());
                if (child != nullptr)
                {
                    joint->AddChild(child);
                }
            }
            return joint;
        }
        return nullptr;
    }
    
    gfx::Transform ColladaVisualScenes::GetTransform(kege::XML* node)
    {
        kege::XML* matrix = node->GetChild("matrix");
        if (matrix != nullptr)
        {
            return ToMatrix(matrix->GetText());
        }
        return gfx::Transform(GetRotation(node), GetTranslation(node), GetScale(node));
    }
    
    cg::vec3 ColladaVisualScenes::GetTranslation(kege::XML* node)
    {
        kege::XML* e = node->GetChild("translate");
        if (e == nullptr) return 0.0;
        return ToVec3(e->GetText());
    }
    
    cg::quat ColladaVisualScenes::GetRotation(kege::XML* node)
    {
        kege::XML rotate;
        node->PopulateByTag(rotate, "rotate");
        cg::quat rotation;
        for (kege::XML::list::iterator q=rotate.Begin(); q!=nullptr; q++)
        {
            rotation *= ToQuat(q->GetText());
        }
        return rotation;
    }
    
    cg::vec3 ColladaVisualScenes::GetScale(kege::XML* node)
    {
        kege::XML* e = node->GetChild("scale");
        if (e == nullptr) return 0.0;
        return ToVec3(e->GetText());
    }
    
    kege::XML* ColladaVisualScenes::GetInstance(kege::XML* node)
    {
        return node->GetChildLike("instance");
    }
}}
